//
// Created by rokas on 7/20/23.
//

#include "csvHandler.hpp"


#include "Parsers/csv/csv.hpp"

using json = nlohmann::json;

void MemQB::Handlers::CSV::handleFile(
                    GraphDB *db,
                    const std::string& filePath,
                    const json& conversionTemplate) {

    std::filesystem::path path{filePath};

    CSVReader reader;
    reader.openFile(path);

    auto csvHeader = reader.getCSVHeader();

    // TODO: finish

    // Read couple lines (perhaps 10)

    // Create a new vector, move lines from csv vector to new vector
    // with designated template formatting

    // Construct a query with all the formatted values

    // Execute the query
}
