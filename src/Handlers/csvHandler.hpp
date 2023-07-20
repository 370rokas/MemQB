//
// Created by rokas on 7/20/23.
//

#ifndef MEMQB_CSVHANDLER_HPP
#define MEMQB_CSVHANDLER_HPP

#include "DBWrapper/GraphDB.hpp"

#include <nlohmann/json.hpp>

namespace MemQB::Handlers::CSV {
    void handleFile(
            GraphDB* db,
            const std::string& filePath,
            const nlohmann::json& conversionTemplate);
}

#endif //MEMQB_CSVHANDLER_HPP
