#include "shape/BoundsMatrixXf.h"

namespace Phoenix {

//------------------------------------------
BoundsMatrixXf::BoundsMatrixXf(int rows, int cols, float left, float bottom, float right, float top)
    : Bounds2f{left, bottom, right, top}
    , matrix(rows, cols) {
    // empty
}
//------------------------------------------
int BoundsMatrixXf::index_x(float x) const {
    return (x - left) / (right - left) * matrix.rows();
};
//------------------------------------------
int BoundsMatrixXf::index_y(float y) const {
    return (y - bottom) / (top - bottom) * matrix.cols();
};
//------------------------------------------
bool BoundsMatrixXf::inside(float x, float y) const {
    return x >= left && x <= right && y >= bottom && y <= top;
}
//------------------------------------------
bool BoundsMatrixXf::interpolate(float x, float y, float& value) const {
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
float BoundsMatrixXf::get_value(float x, float y) const {
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
bool BoundsMatrixXf::get_value(float x, float y, float& value) const {
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
void BoundsMatrixXf::calculate(const Bounds2f& bounds, ResultLimits& result) const {
    // Calculate the indices for the bounding box
    int startX = index_x(bounds.left);
    int startY = index_y(bounds.bottom);
    int endX   = index_x(bounds.right);
    int endY   = index_y(bounds.top);

    // Ensure the indices are within the matrix bounds
    if (startX < 0 || startY < 0 || endX >= matrix.cols() || endY >= matrix.rows()) {
        result.min  = std::numeric_limits<float>::max();
        result.max  = std::numeric_limits<float>::lowest();
        result.code = 1; // Indices out of bounds;
        return;
    }

    // Initialize min and max values
    float minValue = std::numeric_limits<float>::max();
    float maxValue = std::numeric_limits<float>::lowest();

    // Iterate over the specified region of the matrix
    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            float value = matrix(y, x);
            if (value < minValue) {
                minValue = value;
            }
            if (value > maxValue) {
                maxValue = value;
            }
        }
    }

    // Store the obtained values in the result structure
    result.min  = minValue;
    result.max  = maxValue;
    result.code = 0; // Assume the obtained values are valid
}
//------------------------------------------
void BoundsMatrixXf::calculate(const glm::vec2& pos, ResultLimits& result) const {
    // Calculate the indices for the bounding box
    int col = index_x(pos.x);
    int row = index_y(pos.y);

    // Ensure the indices are within the matrix bounds
    if (col < 0 || row < 0 || col >= matrix.cols() || row >= matrix.rows()) {

        result.min  = std::numeric_limits<float>::max();
        result.max  = std::numeric_limits<float>::lowest();
        result.code = 1; // Indices out of bounds;
        return;
    }

    float value = matrix(row, col);

    // Store the obtained values in the result structure
    result.min  = value;
    result.max  = value;
    result.code = 0; // Assume the obtained values are valid
}
//------------------------------------------
void BoundsMatrixXf::fill_pattern() {
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = static_cast<float>(i + j);
        }
    }

    std::cout << matrix << std::endl;
}
} // namespace Phoenix
