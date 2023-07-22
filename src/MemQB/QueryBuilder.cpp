//
// Created by rokas on 7/21/23.
//

#include "QueryBuilder.hpp"

#include <stdexcept>
#include <iostream>

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

std::string MemQB::QueryBuilder::constructNode(const std::string& ref, const Node& nodeData) {
    std::string query = "(";

    query.append(ref);
    query.push_back(':');
    query.append(nodeData.label);

    if (!nodeData.properties.empty()) {
        query.push_back('{');

        size_t nProps = nodeData.properties.size();
        size_t curProp = 1;
        for (auto &v : nodeData.properties) {
            query.append(v.first);
            query.push_back(':');

            std::cout << v.first << "-" << std::any_cast<std::string>(v.second) << std::endl;

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
    }

    query.push_back(')');
    return query;
}

std::string constructRelationship(std::string ref,  Relationship relationshipData) {

};

std::pair<std::string, std::string> constructNodeAndRelationship(Node nodeData) {

}

std::string MemQB::QueryBuilder::constructQuery(MemQB::QueryBuilder::FormattedQuery queryData) {
    return std::string();
}

std::string MemQB::QueryBuilder::constructQuery(std::vector<FormattedQuery> queryData) {
    return std::string();
}
