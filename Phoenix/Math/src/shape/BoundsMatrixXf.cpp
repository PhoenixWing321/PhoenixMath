#include "shape/BoundsMatrixXf.h"

namespace Phoenix {

//------------------------------------------
BoundsMatrixXf::BoundsMatrixXf(int rows, int cols, const Bounds2f& bounds)
    : Bounds2f{bounds}
    , matrix(rows, cols) {
    // empty
}
//------------------------------------------
BoundsMatrixXf::BoundsMatrixXf(int rows, int cols, float left, float bottom, float right, float top)
    : Bounds2f{left, bottom, right, top}
    , matrix(rows, cols) {
    // empty
}
//------------------------------------------
int BoundsMatrixXf::col_int(double x) const {
    const int count = matrix.cols();
    if (count == 0) return -1;

    // here use x/left/right to calculate the index (double ratio)
    double value = col_double(x);

    if (value < 0) return -1;
    auto index = static_cast<int>(value);
    if (index >= count) return -1;
    return index;
}
//------------------------------------------
int BoundsMatrixXf::row_int(double y) const {
    // get row form y if outside the bounds, return -1
    const int count = matrix.rows();
    if (count == 0) return -1;

    // here use y/bottom/top to calculate the index (double ratio)
    double value = row_double(y);

    if (value < 0) return -1;
    auto index = static_cast<int>(value);
    if (index >= count) return -1;
    return index;
}
//------------------------------------------
bool BoundsMatrixXf::inside(float x, float y) const {
    return x >= left && x < right && y >= bottom && y < top;
}
//------------------------------------------
bool BoundsMatrixXf::interpolate(float x, float y, float& value) const {
    // Check if the given x and y coordinates are within the valid range
    if (!inside(x, y)) {
        return false; // Coordinates are outside the valid range
    }
    // Calculate the row and column indices based on the x and y coordinates
    int row = row_int(y);
    int col = col_int(x);

    // Perform interpolation here
    // For simplicity, let's assume nearest neighbor interpolation
    value = matrix(row, col);
    return true;
}
//------------------------------------------
float BoundsMatrixXf::get_value(float x, float y) const {
    int row = row_int(y);
    int col = col_int(x);
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

    int row = row_int(y);
    int col = col_int(x);
    value   = matrix(row, col);
    return true;
}
//------------------------------------------
void BoundsMatrixXf::calculate(const Bounds2f& bounds, LimitsRst& result) const {
    // Calculate the indices for the bounding box
    int startCol = col_int(bounds.left);
    int endCol   = col_int(bounds.right);

    int startRow = row_int(bounds.bottom);
    int endRow   = row_int(bounds.top);

    // Ensure the indices are within the matrix bounds
    if (startCol < 0 || startRow < 0 || endCol < 0 || endRow < 0) {
        result.min  = std::numeric_limits<float>::max();
        result.max  = std::numeric_limits<float>::lowest();
        result.code = 1; // Indices out of bounds;
        return;
    }

    // Initialize min and max values
    float minValue = std::numeric_limits<float>::max();
    float maxValue = std::numeric_limits<float>::lowest();

    int rows = static_cast<int>(startRow + 1);
    // Iterate over the specified region of the matrix
    for (int y = startRow; y <= endRow; ++y) {
        for (int x = startCol; x <= endCol; ++x) {
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
void BoundsMatrixXf::calculate(const glm::vec2& pos, ValueIndexRst& result) const {
    // Calculate the indices for the bounding box
    result.row = row_double(pos.y);
    result.col = col_double(pos.x);

    // to int
    int col = static_cast<int>(result.col);
    int row = static_cast<int>(result.row);

    // check  index
    if (result.row < 0 || result.col < 0 || col >= matrix.cols() || row >= matrix.rows()) {
        result.value = std::numeric_limits<float>::max();
        result.code  = 1; // Indices out of bounds;
        return;
    }

    // Store the obtained values in the result structure
    result.value = matrix(row, col);
    result.code  = 0;
}
//------------------------------------------
void BoundsMatrixXf::fill_pattern() {
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = static_cast<float>(i + j);
        }
    }
}
} // namespace Phoenix
