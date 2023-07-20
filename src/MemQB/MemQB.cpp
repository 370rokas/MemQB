//
// Created by rokas on 7/20/23.
//

#include "MemQB.hpp"

void MemQB::QB::addTask(const MemQB::Task& newTask) {
    taskQueue.push(newTask);

    if (!processing) {
        processTasks();
    }
}

unsigned long MemQB::QB::queueSize() { return taskQueue.size(); }

bool MemQB::QB::queueEmpty() { return taskQueue.empty(); }

void MemQB::QB::processNextTask() {
    Task& currentTask = taskQueue.front();

    switch (currentTask.taskType) {
    case (MemQB::FileFormat::CSV):

        break;
    }
}

void MemQB::QB::processTasks() {
    if (processing)
        return;
    processing = true;

    while (!taskQueue.empty()) {
        processNextTask();
        taskQueue.pop();
    }

    processing = false;
}
