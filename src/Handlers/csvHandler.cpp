//
// Created by rokas on 7/20/23.
//

#include "csvHandler.hpp"

#include "MemQB/MemQB.hpp"
#include "MemQB/QueryBuilder.hpp"
#include "Parsers/csv/csv.hpp"

using namespace MemQB::QueryBuilder;
using json = nlohmann::json;

void MemQB::Handlers::CSV::handleFile(GraphDB* db, const std::string& filePath,
                                      const json& conversionTemplate) {

    std::filesystem::path path{filePath};

    IO::CSVReader csvReader(IO::APIType::STREAM);
    csvReader.openFile(path);

    auto csvHeaders = csvReader.getCSVHeader();
    csvReader.loadFileIntoMemory();

    const size_t nRows = csvReader.getNumRows();

    std::vector<QueryBuilder::FormattedQuery> formattedQueries;
    std::vector<std::string> vCurrentRow;

    std::unordered_map<std::string, size_t> lookupTable;

    // Prepopulate a lookup table
    // Get the values needed for nodes
    for (auto& [label, properties] : conversionTemplate["Nodes"].items()) {
        for (auto& [key, value] : properties.items()) {
            auto iter = std::find(csvHeaders->begin(), csvHeaders->end(),
                                  value.template get<std::string>());

            if (iter != csvHeaders->end()) {
                lookupTable[key] = std::distance(csvHeaders->begin(), iter);
            } else {
                throw std::runtime_error("Cannot find reference to " + key +
                                         " in csv header.");
            }
        }
    }

    // Get the values needed for relationships
    for (size_t currentRow = 0; currentRow < nRows; currentRow++) {
        vCurrentRow.clear();

        vCurrentRow = csvReader.getRow(currentRow);

        FormattedQuery formattedQuery;

        // Create Nodes
        for (auto& [label, properties] : conversionTemplate["Nodes"].items()) {
            Node tempNode;
            tempNode.label = label;

            for (auto& [key, value] : properties.items()) {
                tempNode.properties.emplace_back(key,
                                                 vCurrentRow[lookupTable[key]]);
            }

            formattedQuery.nodes.emplace_back(tempNode);
        }

        // Create Relationships
        for (auto& relationship : conversionTemplate["Relationships"].items()) {
            Relationship tempRel;

            tempRel.label =
                relationship.value()["name"].template get<std::string>();
            tempRel.n1 = relationship.value()["l1"].template get<std::string>();
            tempRel.n2 = relationship.value()["l2"].template get<std::string>();

            for (auto& [key, value] : relationship.value()["props"].items()) {
                tempRel.properties.emplace_back(key,
                                                vCurrentRow[lookupTable[key]]);
            }

            formattedQuery.relationships.emplace_back(tempRel);
        }

        formattedQueries.emplace_back(formattedQuery);

        if (formattedQueries.size() == AMT_HANDLE_AT_ONCE ||
            (currentRow + 1 == nRows && !formattedQueries.empty())) {

            // Construct a query with all the formatted values
            std::string query = QueryBuilder::constructQuery(formattedQueries);

            // Execute the query
            db->Execute(query);

            // Clear the vector
            formattedQueries.clear();
        }
    }
}
