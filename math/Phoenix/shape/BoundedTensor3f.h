#ifndef PHOENIX_BoundedTensor3f_H
#define PHOENIX_BoundedTensor3f_H

#include "Phoenix/shape/Bounds2f.hpp"
#include <unsupported/Eigen/CXX11/Tensor>

namespace Phoenix {
/**
 * @brief Row-major 3D tensor matrix
 */
using RowTensor3f = Eigen::Tensor<float, 3, Eigen::RowMajor>;

class BoundedTensor3f : public RowTensor3f {
public:
    BoundedTensor3f();

    BoundedTensor3f(const RowTensor3f& tensor, const Bounds2f& bounds);

public:
    Bounds2f bounds; // 2D bounds
};
} // namespace Phoenix
#endif // PHOENIX_BoundedTensor3f_H