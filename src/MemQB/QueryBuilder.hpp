//
// Created by rokas on 7/21/23.
//

#ifndef MEMQB_QUERYBUILDER_HPP
#define MEMQB_QUERYBUILDER_HPP

#include <any>
#include <string>
#include <vector>

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
 * @brief: Structure representing a single query which can contain multiple
 * nodes and relationships.
 */
struct FormattedQuery {
    std::vector<Node> nodes;
    std::vector<Relationship> relationships;
};

/*
 * @brief: Construct a single query
 * @param: queryData A single formatted query
 * @return: A constructed cypher query.
 */
std::string constructQuery(FormattedQuery queryData);

/*
 * @brief: Constructs a vector of queries
 * @param: queryData A vector of formatted queries
 * @return: A constructed cypher query.
 */
std::string constructQuery(std::vector<FormattedQuery> queryData);

/*
 * @brief: Constructs node
 * @param: ref How the node will be referenced to
 * @param: nodeData Formatted node data
 * @return: A constructed cypher query.
 */
std::string constructNode(const std::string& ref, const Node& nodeData);
} // namespace MemQB::QueryBuilder

#endif // MEMQB_QUERYBUILDER_HPP
