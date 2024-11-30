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
};

} // namespace Phoenix
