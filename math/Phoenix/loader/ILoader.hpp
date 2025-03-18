#ifndef PHOENIX_ILoader_H
#define PHOENIX_ILoader_H

#include "Phoenix/utility/IData.hpp"
#include <iostream>
#include <memory>

namespace Phoenix {

struct ILoader {

    int                    format_; ///< format of the data or target file
    std::shared_ptr<IData> data_;   ///< data to load or save

    ILoader(int format = FileFormat_UNDEFINED)
        : format_(format) {}

    virtual ~ILoader() = default;

    /**
     * @brief Load from file
     * @param data Matrix to load
     * @param path File path
     * @param format Format of the data or file，0 means undefined format
     * @return int Error code
     */
    virtual int load(const std::string& path, int format) = 0;

    /**
     * @brief Save to file
     * @param data Matrix to save
     * @param path File path
     * @param format Format of the data or file，0 means undefined format
     * @return int Error code
     */
    virtual int save(const std::string& path, int format) const = 0;

    inline void set_format(int format) {
        format_ = format;
    }

    inline int get_format() const {
        return format_;
    }

    inline std::shared_ptr<IData> get_data() const {
        return data_;
    }

    inline void set_data(std::shared_ptr<IData> data) {
        data_ = data;
    }
};

} // namespace Phoenix
#endif // PHOENIX_ILoader_H