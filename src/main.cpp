#include "Parsers/csv/csv.hpp"

#include <iostream>

using namespace MemQB;

int main(int argc, char** argv) {
    std::cout << "Hi" << std::endl;

    IO::CSVReader x{IO::APIType::STREAM};

    std::filesystem::path fpath(argv[1]);
    x.openFile(fpath);

    std::vector<std::string> vec = {};

    x.readLine();
    x.readLine();

    for (auto kv : x.csvFile) {
        std::cout << kv.first << ": ";
        for (auto it = kv.second->begin(); it != kv.second->end(); ++it) {
            std::cout << *it << "\t";
        }
        std::cout << std::endl;
    }
}