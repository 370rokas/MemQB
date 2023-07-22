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
 * @brief: Constructs a vector of queries
 * @param: queryData A vector of formatted queries
 * @return: A constructed cypher query.
 */
std::string constructQuery(const std::vector<FormattedQuery>& queryData);

/*
 * @brief: Constructs a node
 * @param: ref How the node will be referenced to
 * @param: nodeData Formatted node data
 * @return: A constructed cypher query.
 */
std::string constructNode(const std::string& ref, const Node& nodeData);

/*
 * @brief: Constructs a relationship
 * @param: ref How the relationship will be referenced to
 * @param: r1 The first relationship object
 * @param: r2 The second relationship object
 * @param: relationshipData Formatted relationship data
 * @return: A constructed cypher query.
 */
std::string constructRelationship(const std::string &ref, const std::string &r1, const std::string &r2,
                                  const Relationship &relationshipData);

} // namespace MemQB::QueryBuilder

#endif // MEMQB_QUERYBUILDER_HPP
