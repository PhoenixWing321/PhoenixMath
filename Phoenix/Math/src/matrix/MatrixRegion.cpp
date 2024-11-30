#include "matrix/MatrixRegion.h"

namespace Phoenix {

//------------------------------------------
MatrixRegion::MatrixRegion(int cols, int rows, float left, float right, float bottom, float top)
    : left(left)
    , right(right)
    , bottom(bottom)
    , top(top) {
    matrix.resize(rows, cols); // Initialize matrix based on number of rows and columns
}
//------------------------------------------
int MatrixRegion::index_x(float x) const {
    return (x - left) / (right - left) * matrix.rows();
};
//------------------------------------------
int MatrixRegion::index_y(float y) const {
    return (y - bottom) / (top - bottom) * matrix.cols();
};
//------------------------------------------
bool MatrixRegion::inside(float x, float y) const {
    return x >= left && x <= right && y >= bottom && y <= top;
}
//------------------------------------------
bool MatrixRegion::interpolate(float x, float y, float& value) const {
    // Check if the given x and y coordinates are within the valid range
    if (!inside(x, y)) {
        return false; // Coordinates are outside the valid range
    }
    // Calculate the row and column indices based on the x and y coordinates
    int row = index_x(x);
    int col = index_y(y);

    // Perform interpolation here
    // For simplicity, let's assume nearest neighbor interpolation
    value = matrix(row, col);
    return true;
}
//------------------------------------------
float MatrixRegion::get_value(float x, float y) const {
    int row = index_x(x);
    int col = index_y(y);
    if (row < 0)
        row = 0;
    else if (row >= matrix.rows())
        row = matrix.rows() - 1;
    if (col < 0)
        col = 0;
    else if (col >= matrix.cols())
        col = matrix.cols() - 1;
    return matrix(row, col);
}
//------------------------------------------
bool MatrixRegion::get_value(float x, float y, float& value) const {
    // left/right is the outer boundary of the rectangular area
    // bottom/top is the outer boundary of the rectangular area
    // so inside has rows and cols blocks inside the rectangular area
    if (!inside(x, y)) {
        return false; // Coordinates are outside the valid range
    }

    int row = index_x(x);
    int col = index_y(y);
    value   = matrix(row, col);
    return true;
}
//------------------------------------------
Code MatrixRegion::calculate(const Bounds2f& bounds, ResultLimits& result) const {
    // TODO 假设您有一个方法可以获取矩阵中指定区域的最小和最大值
    // 这里我们简单地假设这些值是已知的
    float minValue = 0.0f;   // 实际的最小测量值
    float maxValue = 100.0f; // 实际的最大测量值

    // 将获取到的值存储在result结构体中
    result.min      = minValue;
    result.max      = maxValue;
    result.is_valid = true; // 假设获取的值是有效的

    return 0; // 返回成功
}

} // namespace Phoenix
