//
// Created by rokas on 7/21/23.
//

#ifndef MEMQB_QUERYBUILDER_HPP
#define MEMQB_QUERYBUILDER_HPP

#include <vector>
#include <string>
#include <any>

namespace MemQB::QueryBuilder {
    /*
     * @brief: Structure representing a memgraph node.
     */
    struct Node {
        std::string label;
        std::vector<std::pair<std::string, std::any>> properties;
    };

    /*
     * @brief: Structure representing a memgraph relationship.
     */
    struct Relationship {
        std::string label;

        std::string n1;
        std::string n2;

        std::vector<std::pair<std::string, std::any>> properties;
    };

    /*
     * @brief: Structure representing a single query which can contain multiple nodes and relationships.
     */
    struct FormattedQuery {
        std::vector<Node> nodes;
        std::vector<Relationship> relationships;
    };
}

#endif //MEMQB_QUERYBUILDER_HPP
