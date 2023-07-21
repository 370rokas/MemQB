//
// Created by rokas on 7/20/23.
//

#ifndef MEMQB_HPP
#define MEMQB_HPP

#include <queue>
#include <string>

#include <nlohmann/json.hpp>

#include "DBWrapper/GraphDB.hpp"

constexpr int AMT_HANDLE_AT_ONCE = 10;

namespace MemQB {

enum class FileFormat {
    CSV,
};

struct Task {
    FileFormat taskType;
    std::string fileLocation;
    nlohmann::json valueMappings;
};

class QB {
protected:
    std::queue<Task> taskQueue;
    bool processing = false;

    GraphDB* database = nullptr;

    // Private Functions
    void processTasks();
    void processNextTask();

public:
    /*
     * @brief: Constructors
     */
    QB(const std::string& host, uint16_t port, bool ssl);

    // Queue Management tasks
    void addTask(const Task& newTask);

    // Utils
    unsigned long queueSize();
    bool queueEmpty();
};
} // namespace MemQB

#endif // MEMQB_HPP
