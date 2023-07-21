#include "Parsers/csv/csv.hpp"

#include <iostream>

using namespace MemQB;

int main(int argc, char** argv) {
    std::cout << "Hi" << std::endl;

    IO::CSVReader x{IO::APIType::STREAM};

    std::filesystem::path fpath(argv[1]);
    x.openFile(fpath);

    std::vector<std::string> vec = {};

    x.loadFileIntoMemory();

    // std::vector<std::string> row{};
    // for (size_t i = 0; i < x.getNumRows(); i++) {
    //     row = x.getRow(i);
    //
    //    for (auto item : row) {
    //        std::cout << item << '\t';
    //    }
    //    std::cout << std::endl;
    //}
}