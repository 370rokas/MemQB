//
// Created by rokas on 7/20/23.
//

#include "include/MemQB.hpp"

void MemQB::QB::addTask(MemQB::Task newTask) {
    taskQueue.push(newTask);
}

unsigned long MemQB::QB::queueSize() {
    return taskQueue.size();
}

bool MemQB::QB::queueEmpty() {
    return taskQueue.empty();
}
