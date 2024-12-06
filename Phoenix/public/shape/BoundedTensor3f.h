#ifndef PHOENIX_BoundedTensor3f_H
#define PHOENIX_BoundedTensor3f_H

#include "shape/Bounds2f.hpp"
#include <unsupported/Eigen/CXX11/Tensor>

namespace Phoenix {
/**
 * @brief Row-major 3D tensor matrix
 */
using RowTensor3f = Eigen::Tensor<float, 3, Eigen::RowMajor>;

class BoundedTensor3f : public RowTensor3f {
public:
    // 默认构造函数
    BoundedTensor3f();

    // 从张量和边界构造
    BoundedTensor3f(const RowTensor3f& tensor, const Bounds2f& bounds);

    // 获取边界
    const Bounds2f& getBounds() const {
        return bounds;
    }

    // 设置边界
    void setBounds(const Bounds2f& newBounds) {
        bounds = newBounds;
    }

private:
    Bounds2f bounds; // 2D边界信息
};
} // namespace Phoenix
#endif // PHOENIX_BoundedTensor3f_H