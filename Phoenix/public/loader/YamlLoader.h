#ifndef PHOENIX_YamlLoader_H
#define PHOENIX_YamlLoader_H

#include "loader/ILoader.hpp"
#include "utility/ErrorCode.hpp"
#include "utility/PropertiesData.hpp"

namespace Phoenix {

// 2. 实现具体的策略类
class YamlLoader : public ILoader {
public:
    YamlLoader()
        : ILoader(FileFormat_YAML) {}

    virtual ~YamlLoader() = default;

public: // override
    /**
     * @brief Load from file
     * @param data Data to load
     * @param path File path
     * @param format Format of the data or file
     * @return int Error code
     */
    virtual int load(const std::string& path, int format) override {
        return load_properties(path);
    };

    /**
     * @brief Save to file
     * @param data Data to save
     * @param path File path
     * @param format Format of the data or file
     * @return int Error code
     */
    virtual int save(const std::string& path, int format) const override {

        return save_properties(path);
    };

public:
    std::shared_ptr<PropertiesData> get_properties() {
        return properties_;
    };

    /**
     * @brief Load properties from a YAML file
     * @param path Path to the YAML file
     * @return int Error code
     * @note create new data_ each time call this function
     */
    int load_properties(const std::string& path);
    int save_properties(const std::string& path) const;

private:
    std::shared_ptr<PropertiesData> properties_;
};

} // namespace Phoenix
#endif