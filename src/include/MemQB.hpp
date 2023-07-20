//
// Created by rokas on 7/20/23.
//

#ifndef MEMQB_HPP
#define MEMQB_HPP

#include <string>
#include <queue>

#include <nlohmann/json.hpp>

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

    public:
        // Queue Management tasks
        void addTask(Task newTask);

        // Utils
        unsigned long queueSize();
        bool queueEmpty();
    };

}

#endif //MEMQB_HPP
