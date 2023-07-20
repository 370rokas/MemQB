//
// Created by rokas on 7/20/23.
//

#ifndef MEMQB_HPP
#define MEMQB_HPP

#include <string>
#include <queue>

#include <nlohmann/json.hpp>

#include "DBWrapper/GraphDB.hpp"

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
        // Constructors
        QB(const std::string& host, uint16_t port, bool ssl);

        // Queue Management tasks
        void addTask(const Task& newTask);

        // Utils
        unsigned long queueSize();
        bool queueEmpty();
    };

}

#endif //MEMQB_HPP
