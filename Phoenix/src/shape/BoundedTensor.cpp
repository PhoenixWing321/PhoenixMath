#include "shape/BoundedTensor.h"

namespace Phoenix {
BoundedTensor::BoundedTensor(const Bounds2f& bounds, size_t rows, size_t cols, size_t layers)
    : Bounds2f(bounds)
    , rows_(rows)
    , cols_(cols) {
    // 初始化所有层的矩阵
    matrices_.resize(layers);
    for (auto& matrix : matrices_) {
        matrix = Eigen::MatrixXf::Zero(rows, cols);
    }
}

Eigen::MatrixXf& BoundedTensor::getLayer(size_t layer) {
    return matrices_.at(layer);
}

const Eigen::MatrixXf& BoundedTensor::getLayer(size_t layer) const {
    return matrices_.at(layer);
}
}