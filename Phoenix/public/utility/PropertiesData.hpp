#ifndef PHOENIX_PropertiesData_H
#define PHOENIX_PropertiesData_H

#include "utility/IData.hpp"
#include <iomanip> // For std::setw and std::setprecision
#include <iostream>

namespace Phoenix {

class PropertiesData : public IData {
public:
    PropertiesData()
        : IData()
        , properties() {}

    virtual ~PropertiesData() = default;

public:
    void add_property(const std::string& key, const std::string& value) {
        properties.push_back(std::make_pair(key, value));
    }

    std::string get_property(const std::string& key) const {
        for (const auto& property : properties) {
            if (property.first == key) {
                return property.second;
            }
        }
        return "";
    }

public:
    std::vector<std::pair<std::string, std::string>> properties;
};

} // namespace Phoenix
#endif // PHOENIX_PropertiesData_H