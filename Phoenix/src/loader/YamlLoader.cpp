#include "loader/YamlLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
// #include <unordered_map>
#include <utility>

//---------------------------------
int Phoenix::YamlLoader::load_properties(const std::string& path) {
    // 新建一个
    properties_ = std::make_shared<PropertiesData>();
    data_       = properties_;

    // 读取文件
    std::ifstream file(path);
    std::string   line;

    if (!file.is_open()) {
        std::cout << "Error opening file: " << path << std::endl;
        return ErrorCode::Code_FILE_NOT_OPEN;
    }

    while (std::getline(file, line)) {
        // Trim whitespace from the line
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Skip empty lines or lines that don't contain a colon
        if (line.empty() || line.find(':') == std::string::npos) {
            continue;
        }

        // Split the line into key and value
        std::istringstream lineStream(line);
        std::string        key, value;
        if (std::getline(lineStream, key, ':') && std::getline(lineStream, value)) {
            // Trim whitespace from key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            properties_->add_property(key, value);
            // std::cout << "To addkey: " << key << " value: " << value << std::endl;
        }
    }

    file.close();
    return 0;
}
//---------------------------------
int Phoenix::YamlLoader::save_properties(const std::string& path) const {
    if (data_ == nullptr) return ErrorCode::Code_E_POINTER;

    //
    auto properties_ = std::dynamic_pointer_cast<PropertiesData>(data_);
    if (properties_ == nullptr) {
        return ErrorCode::Code_INVALID_FORMAT;
    }

    // 保存文件
    std::ofstream file(path);
    for (const auto& property : properties_->properties) {
        file << property.first << ": " << property.second << std::endl;
    }
    file.close();
    return 0;
}