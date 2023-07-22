//
// Created by rokas on 7/21/23.
//

#include "QueryBuilder.hpp"

#include <stdexcept>
#include <algorithm>

using namespace MemQB::QueryBuilder;

bool isNumeric(const std::any& value) {
    // Use type information to check if the value is numeric
    return value.type() == typeid(int) ||
           value.type() == typeid(unsigned int) ||
           value.type() == typeid(long) ||
           value.type() == typeid(unsigned long) ||
           value.type() == typeid(long long) ||
           value.type() == typeid(unsigned long long) ||
           value.type() == typeid(float) ||
           value.type() == typeid(double) ||
           value.type() == typeid(long double);
}

std::string constructProperties(const std::vector<std::pair<std::string, std::any>>& props) {
    std::string query = "{";

    size_t nProps = props.size();
    size_t curProp = 1;
    for (auto &v : props) {
        query.append(v.first);
        query.push_back(':');

        if (v.second.type() == typeid(std::string)) {
            query.push_back('"');
            query.append(std::any_cast<std::string>(v.second));
            query.push_back('"');
        } else if (isNumeric(v.second)) {
            // Numeric

            if (v.second.type() == typeid(int)) {
                query.append(std::to_string(
                        std::any_cast<int>(v.second)
                ));
            } else if (v.second.type() == typeid(double)) {
                query.append(std::to_string(
                        std::any_cast<double>(v.second)
                ));
            } else if (v.second.type() == typeid(float)) {
                query.append(std::to_string(
                        std::any_cast<float>(v.second)
                ));
            } else {
                throw std::runtime_error("Unimplemented numeric type: " +
                                         std::string(v.second.type().name()));
            }
        } else {
            throw std::runtime_error("Unsupported type: " +
                                     std::string(v.second.type().name()));
        }

        if (curProp < nProps) {
            query.push_back(',');
        }
        curProp++;
    }

    query.push_back('}');
    return query;
}

std::string MemQB::QueryBuilder::constructNode(const std::string& ref, const Node& nodeData) {
    std::string query = "(";

    query.append(ref);
    query.push_back(':');
    query.append(nodeData.label);

    if (!nodeData.properties.empty()) {
        query.push_back(' ');
        query.append(constructProperties(nodeData.properties));
    }

    query.push_back(')');
    return query;
}

std::string MemQB::QueryBuilder::constructRelationship(const std::string& ref,
                                  const std::string& r1,
                                  const std::string& r2,
                                  const Relationship& relationshipData) {
    std::string query = "(";
    query.append(r1);
    query.push_back(')');

    query.push_back('-');

    query.push_back('[');
    query.append(ref);
    query.push_back(':');
    query.append(relationshipData.label);

    if (!relationshipData.properties.empty()) {
        query.push_back(' ');
        query.append(constructProperties(relationshipData.properties));
    }

    query.push_back(']');

    query.push_back('-');
    query.push_back('>');

    query.push_back('(');
    query.append(r2);
    query.push_back(')');
    return query;
};

std::string MemQB::QueryBuilder::constructQuery(const std::vector<FormattedQuery>& queryData) {
    std::string finalQuery = "CREATE ";

    size_t nFormattedQuery = 0; // Current FormattedQuery
    size_t nCypherQuery = 0;    // Current generated cypher query

    for (auto& query : queryData) {
        // Foreach node
        for (auto& node: query.nodes) {
            std::string ref = node.label + std::to_string(nFormattedQuery);
            std::transform(ref.begin(), ref.end(), ref.begin(), ::tolower);

            if (nCypherQuery > 0) {
                finalQuery.push_back(',');
            }
            finalQuery.append(constructNode(ref, node));

            nCypherQuery++;
        }

        // Foreach relationship
        for (auto & rel : query.relationships) {
            std::string ref = rel.label + std::to_string(nFormattedQuery);
            std::transform(ref.begin(), ref.end(), ref.begin(), ::tolower);

            std::string r1 = rel.n1 + std::to_string(nFormattedQuery);
            std::transform(r1.begin(), r1.end(), r1.begin(), ::tolower);

            std::string r2 = rel.n2 + std::to_string(nFormattedQuery);
            std::transform(r2.begin(), r2.end(), r2.begin(), ::tolower);

            finalQuery.push_back(',');
            finalQuery.append(constructRelationship(ref, r1, r2, rel));

            nCypherQuery++;
        }

        nFormattedQuery++;
    }

    finalQuery.push_back(';');
    return finalQuery;
}
