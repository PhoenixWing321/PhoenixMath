#ifndef PHOENIX_YamlData_H
#define PHOENIX_YamlData_H

#include "utility/IData.hpp"
#include <iomanip> // For std::setw and std::setprecision
#include <iostream>

namespace Phoenix {

struct YamlData : public IData {
    YamlData()
        : IData()
        , properties() {}

    virtual ~YamlData() = default;

    void add_args(const std::string& value) {
        args.push_back(value);
    }

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

    void set_property(const std::string& key, const std::string& value) {
        for (auto& property : properties) {
            if (property.first == key) {
                property.second = value;
                return;
            }
        }
        properties.push_back(std::make_pair(key, value));
    }

    void dump() const {
        for (auto item : properties) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
        if (!args.empty()) {
            std::cout << "args: " << std::endl;
            for (auto arg : args) {
                std::cout << "  - " << arg << std::endl;
            }
        }
    }

public:
    std::vector<std::pair<std::string, std::string>> properties;
    std::vector<std::string>                         args;
};

} // namespace Phoenix
#endif // PHOENIX_YamlData_H