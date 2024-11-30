
#include "sensor/SensorArea.h"

namespace Phoenix {

SensorArea::SensorArea(int cols, int rows, float left, float right, float bottom, float top)
    : cols(cols)
    , rows(rows)
    , left(left)
    , right(right)
    , bottom(bottom)
    , top(top) {
    matrix.resize(rows, cols); // Initialize matrix based on number of rows and columns
}
} // namespace Phoenix