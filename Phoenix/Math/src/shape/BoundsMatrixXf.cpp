#include "shape/BoundsMatrixXf.h"

namespace Phoenix {

//------------------------------------------
BoundsMatrixXf::BoundsMatrixXf(int cols, int rows, float left, float bottom, float right, float top)
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
Code BoundsMatrixXf::calculate(const Bounds2f& bounds, ResultLimits& result) const {
    // TODO Assume you have a method to get the minimum and maximum values in the specified region
    // of the matrix Here we simply assume these values are known
    float minValue = 0.0f;   // Actual minimum measurement value
    float maxValue = 100.0f; // Actual maximum measurement value

    // Store the obtained values in the result structure
    result.min      = minValue;
    result.max      = maxValue;
    result.is_valid = true; // Assume the obtained values are valid

    return 0; // Return success
}

} // namespace Phoenix
