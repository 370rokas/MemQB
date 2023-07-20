//
// Created by rokas on 7/20/23.
//

#ifndef TESTPARSER_GRAPHDB_HPP
#define TESTPARSER_GRAPHDB_HPP

#include <string>
#include <vector>

#include <mgclient.hpp>

class GraphDB {
protected:
    std::unique_ptr<mg::Client> client;
    bool ready = false; // true if connection succeeded

public:
    GraphDB(const std::string& host, uint16_t port, bool ssl);
    ~GraphDB();

    // Helper Functions
    bool IsReady() {
        return ready;
    }

    std::unique_ptr<mg::Client>* GetClient();

    // Query Functions
    void Execute(const std::string& query);

    // Pre-Made Queries
    void ClearDatabaseData();
};


#endif //TESTPARSER_GRAPHDB_HPP
