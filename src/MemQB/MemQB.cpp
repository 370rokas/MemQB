//
// Created by rokas on 7/20/23.
//

#include "MemQB.hpp"

#include "Handlers/csvHandler.hpp"

void MemQB::QB::addTask(const MemQB::Task& newTask) {
    this->taskQueue.push(newTask);

    if (!this->processing) {
        processTasks();
    }
}

unsigned long MemQB::QB::queueSize() { return this->taskQueue.size(); }

bool MemQB::QB::queueEmpty() { return this->taskQueue.empty(); }

void MemQB::QB::processNextTask() {
    Task& currentTask = this->taskQueue.front();

    switch (currentTask.taskType) {
    case (MemQB::FileFormat::CSV):
        MemQB::Handlers::CSV::handleFile(
                database,
                currentTask.fileLocation);
        break;
    }
}

void MemQB::QB::processTasks() {
    if (this->processing)
        return;
    this->processing = true;

    while (!this->taskQueue.empty()) {
        this->processNextTask();
        this->taskQueue.pop();
    }

    this->processing = false;
}

MemQB::QB::QB(const std::string &host, uint16_t port, bool ssl) {
    database = new GraphDB(host, port, ssl);


}
