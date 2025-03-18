#ifndef PHOENIX_PpmLoader_H
#define PHOENIX_PpmLoader_H

#include "Phoenix/loader/IMatrixLoader.hpp"
#include "Phoenix/utility/ColorRGB.h"

namespace Phoenix {

// 2. 实现具体的策略类
class PpmLoader : public IMatrixLoader {
public:
    PpmLoader()
        : IMatrixLoader(FORMAT_PPM)
        , color_format(ColorRGB::HEAT_MAP) {}

    PpmLoader(ColorRGB::ColorFormat color_format)
        : IMatrixLoader(FORMAT_PPM)
        , color_format(color_format) {}

    virtual ~PpmLoader() = default;

public: // override
    /**
     * @brief Load from file
     * @param matrix Matrix to load
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int load(IRowMatrixXf* matrix, const std::string& path, int format) override;

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
    int save_ppm(const IRowMatrixXf* matrix, const std::string& path) const;

public:
    ColorRGB::ColorFormat color_format;
    bool                  flip_rows{false}; // if flip rows
};

} // namespace Phoenix
#endif