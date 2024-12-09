#ifndef PHOENIX_PpmLoader_H
#define PHOENIX_PpmLoader_H

#include "loader/IMatrixLoader.hpp"

namespace Phoenix {

// 2. 实现具体的策略类
class PpmLoader : public IMatrixLoader {
public:
    PpmLoader() = default;
    PpmLoader(int sub_type)
        : sub_type(sub_type) {}

    virtual ~PpmLoader() = default;

public:
    Code load(IRowMatrixXf& matrix, const std::string& path) override;

    Code save(IRowMatrixXf& matrix, const std::string& path) override;

    enum SubType {
        NORMAL  = 0, // black to white
        HEATMAP = 1, // heatmap
    };

public:
    int sub_type{NORMAL};
};

} // namespace Phoenix
#endif