#ifndef PHOENIX_BoundedTensor_H
#define PHOENIX_BoundedTensor_H
#include "shape/Bounds2f.hpp"
#include <Eigen/Dense>
#include <vector>

namespace Phoenix {
using RowMatrixXf = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

class BoundedTensor : public Bounds2f {
public:
    BoundedTensor(const Bounds2f& bounds, size_t rows, size_t cols, size_t layers);

    // 获取指定层的矩阵
    Eigen::MatrixXf&       getLayer(size_t layer);
    const Eigen::MatrixXf& getLayer(size_t layer) const;

    // 获取层数
    size_t getLayerCount() const {
        return matrices_.size();
    }

    // 获取矩阵尺寸
    size_t rows() const {
        return rows_;
    }
    size_t cols() const {
        return cols_;
    }

private:
    std::vector<Eigen::MatrixXf> matrices_; // 存储多层矩阵
    size_t                       rows_;
    size_t                       cols_;
};
} // namespace Phoenix
#endif // PHOENIX_BoundedTensor_H