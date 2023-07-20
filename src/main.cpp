#include "parsers/csv/csv.hpp"

#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Hi" << std::endl;

    CSVReader x{};

    std::filesystem::path fpath(argv[1]);
    x.openFile(fpath);

    std::vector<std::string> vec = {};
    x.readLine(vec);

    std::cout << vec[0] << std::endl;
}