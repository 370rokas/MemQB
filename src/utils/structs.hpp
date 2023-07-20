//
// Created by rokas on 7/20/23.
//

#ifndef MEMQB_STRUCTS_HPP
#define MEMQB_STRUCTS_HPP

#include <string>

enum class FileFormat {
    CSV,
};

struct Task {
    std::string fileLocation;
    FileFormat taskType;
};

#endif //MEMQB_STRUCTS_HPP
