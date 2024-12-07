#ifndef PHOENIX_NonUniformMatrixXf_H
#define PHOENIX_NonUniformMatrixXf_H

#include "shape/EigenDefine.hpp"
#include <Eigen/Dense>

namespace Phoenix {

class NonUniformMatrixXf : public RowMatrixXf {
public:
    NonUniformMatrixXf()
        : RowMatrixXf(0, 0)
        , bounds{} {}

    ~NonUniformMatrixXf() = default;

public:
    std::vector<float> v_coords; // row coordinates of center, V- direction
    std::vector<float> u_coords; // column coordinates of center, U- direction
};
} // namespace Phoenix
#endif