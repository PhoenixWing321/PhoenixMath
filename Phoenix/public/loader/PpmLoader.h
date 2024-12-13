#ifndef PHOENIX_PpmLoader_H
#define PHOENIX_PpmLoader_H

#include "loader/IMatrixLoader.hpp"
#include "utility/ColorRGB.h"

namespace Phoenix {

// 2. 实现具体的策略类
class PpmLoader : public IMatrixLoader {
public:
    PpmLoader()
        : sub_type(ColorRGB::HEAT_MAP) {}
    PpmLoader(ColorRGB::ColorFormat sub_type)
        : sub_type(sub_type) {}

    virtual ~PpmLoader() = default;

public: // override
    /**
     * @brief Load from file
     * @param matrix Matrix to load
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int load(IRowMatrixXf* matrix, const std::string& path, int format) const override;

    /**
     * @brief Save to file
     * @param matrix Matrix to save
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int save(const IRowMatrixXf* matrix, const std::string& path,
                     int format) const override;

public:
    int save_polar(const IRowMatrixXf* matrix, const std::string& path) const;

public:
    ColorRGB::ColorFormat sub_type;
};

} // namespace Phoenix
#endif