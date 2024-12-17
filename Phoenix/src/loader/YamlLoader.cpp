#include "loader/YamlLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
// #include <unordered_map>
#include <utility>

// 去除字符串两端的空白字符
void trim(std::string& s, const char* chars = " \t") {
    s.erase(0, s.find_first_not_of(chars));
    s.erase(s.find_last_not_of(chars) + 1);
    // auto start = s.begin();
    // while (start != s.end() && std::isspace(*start)) {
    //     start++;
    // }

    // auto end = s.end();
    // do {
    //     end--;
    // } while (std::distance(start, end) > 0 && std::isspace(*end));

    // return std::string(start, end + 1);
}
//---------------------------------
int Phoenix::YamlLoader::load_yaml(const std::string& path) {
    // 新建一个
    properties_ = std::make_shared<YamlData>();
    data_       = properties_;

    // 读取文件
    std::ifstream file(path);
    std::string   line;

    if (!file.is_open()) {
        std::cout << "Error opening file: " << path << std::endl;
        return ErrorCode::Code_FILE_NOT_OPEN;
    }

    while (std::getline(file, line)) {
        // std::cout << "line: " << line << std::endl;
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
        if (std::getline(lineStream, key, ':')) {
            // Trim whitespace from key and value
            trim(key);

            // 判断key是否为args
            if (key == "args") {
                std::string arg;
                // 进入多行解析模式
                while (std::getline(file, line)) {
                    // 找到第一个 '-' 且前面是空白字符
                    size_t dashPos = line.find_first_of('-');
                    // 如果 '-' 不在字符串开头，或者 '-' 前面不是空白字符，则停止
                    if (dashPos == std::string::npos || line.find_first_not_of(" \t") != dashPos) {
                        break;
                    }
                    arg = line.substr(dashPos + 1);
                    trim(arg, " \t");
                    trim(arg, "\"");
                    if (arg.empty()) {
                        continue; // 遇到下一个键值对时跳过
                    }
                    properties_->add_args(arg);
                    // std::cout << "To add args: " << arg << std::endl;
                }
                continue;
            }

            // get value
            std::getline(lineStream, value);

            trim(value);
            properties_->add_property(key, value);
            // std::cout << "key: " << key << " value: " << value << std::endl;
        }
    }

    file.close();
    return 0;
}
//---------------------------------
int Phoenix::YamlLoader::save_properties(const std::string& path) const {
    if (data_ == nullptr) return ErrorCode::Code_E_POINTER;

    //
    auto properties_ = std::dynamic_pointer_cast<YamlData>(data_);
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