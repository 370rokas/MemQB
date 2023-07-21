//
// Created by rokas on 7/20/23.
//

#include "csvHandler.hpp"

#include "Parsers/csv/csv.hpp"

using json = nlohmann::json;

void MemQB::Handlers::CSV::handleFile(GraphDB* db, const std::string& filePath,
                                      const json& conversionTemplate) {

    std::filesystem::path path{filePath};

    IO::CSVReader csvReader(IO::APIType::STREAM);
    csvReader.openFile(path);

    auto csvHeaders = csvReader.getCSVHeader();
    std::vector<std::vector<std::string>> formattedData;


    // TODO: finish

    // loop while there are values here!

    // Read couple lines (perhaps 10)

    // Create a new vector, move lines from csv vector to new vector
    // with designated template formatting

    // Construct a query with all the formatted values

    // Execute the query

    // cleanup csv handler and whatnot
}
