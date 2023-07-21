//
// Created by rokas on 7/20/23.
//

#include "csvHandler.hpp"

#include "MemQB/MemQB.hpp"
#include "Parsers/csv/csv.hpp"

using json = nlohmann::json;

void MemQB::Handlers::CSV::handleFile(GraphDB* db, const std::string& filePath,
                                      const json& conversionTemplate) {

    std::filesystem::path path{filePath};

    IO::CSVReader csvReader(IO::APIType::STREAM);
    csvReader.openFile(path);

    auto csvHeaders = csvReader.getCSVHeader();
    csvReader.loadFileIntoMemory();

    const size_t nRows = csvReader.getNumRows();

    std::vector<std::vector<std::string>> formattedRows;
    std::vector<std::string> vCurrentRow;

    for (size_t currentRow = 0; currentRow < nRows; currentRow++) {
        vCurrentRow.clear();

        auto row = csvReader.getRow(currentRow);

        // TODO: format the row, then put it into formattedRows
        formattedRows.push_back(row);

        if (formattedRows.size() == AMT_HANDLE_AT_ONCE
            || (currentRow + 1 == nRows && !formattedRows.empty())) {
            // TODO: Construct a query with all the formatted values
            std::cout << "UPLOAD TO THE DATABASE " << formattedRows.size() << "\n";
            // TODO: Execute the query

            // Clear the vector
            formattedRows.clear();
        }
    }
}
