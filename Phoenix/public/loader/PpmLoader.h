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

public:
    Code load(IRowMatrixXf& matrix, const std::string& path) override;

    Code save(IRowMatrixXf& matrix, const std::string& path) override;

public:
    ColorRGB::ColorFormat sub_type;
};

} // namespace Phoenix
#endif