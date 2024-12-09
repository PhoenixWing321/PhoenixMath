#include "loader/CoordsMatrixXfLoader.h"
#include "loader/MatrixLoader.h"

namespace Phoenix {
Code CoordsMatrixXfLoader::load(IRowMatrixXf& matrix, const std::string& path) {
    CoordsMatrixXf* coordsMatrix = nullptr;
    if (coordsMatrix == nullptr) {
        return 1;
    }
    // PPM加载实现
    MatrixLoader loader;
    return loader.load(*coordsMatrix, path);
}

Code CoordsMatrixXfLoader::save(IRowMatrixXf& matrix, const std::string& path) {
    CoordsMatrixXf* coordsMatrix = nullptr;
    // new CoordsMatrixXf(matrix.rows(), matrix.cols());
    if (coordsMatrix == nullptr) {
        return 1;
    }
    MatrixLoader loader;
    return loader.save(*coordsMatrix, path); // 保存为PPM格式
}
} // namespace Phoenix