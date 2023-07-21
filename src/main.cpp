#include <iostream>

#include <MemQB/MemQB.hpp>

using namespace MemQB;

int main(int argc, char** argv) {
    std::cout << "Hi" << std::endl;

    auto memQB = QB("100.86.156.96", 7687, false);

    Task testTask;
    testTask.taskType = FileFormat::CSV;
    testTask.fileLocation = argv[1];
    testTask.valueMappings = nlohmann::json::parse(R"(
        {
            "Nodes": {
                "Person": {
                    "Email": "email",
                    "Name": "name"
                },

                "Password": {
                    "Password": "password"
                }
            },

            "Relationships": [
                {
                    "name": "RELATED_PASSWORD",
                    "l1": "Person",
                    "l2": "Password",
                    "props": {}
                },

                {
                    "name": "RELATED_PERSON",
                    "l1": "Password",
                    "l2": "Person",
                    "props": {}
                }
            ]
        }
    )");

    memQB.addTask(testTask);

    return 0;
}