#ifndef Phoenix_BoundsMatrixXf_H
#define Phoenix_BoundsMatrixXf_H

#include "shape/Bounds2f.hpp"
#include "utility/Code.h"
#include <Eigen/Dense>

namespace Phoenix {

struct ResultLimits {
    float min;
    float max;
    bool  is_valid;
};

class BoundsMatrixXf : public Bounds2f {
public:
    // Constructor
    BoundsMatrixXf(int cols, int rows, float left, float right, float bottom, float top);
    virtual ~BoundsMatrixXf() = default;

public:
    // Number of columns in the detector (pixels)
    int cols() const {
        return matrix.cols();
    };
    // Number of rows in the detector (pixels)
    int rows() const {
        return matrix.rows();
    };

    int index_x(float x) const;
    int index_y(float y) const;

    bool inside(float x, float y) const;

    bool interpolate(float x, float y, float& value) const;

    bool get_value(float x, float y, float& value) const;

    /**
     * @brief Get the value object
     *
     * @param x x-coordinate
     * @param y y-coordinate
     * @return float, if x or y are outside the valid range,
     *  return the boudary value
     */
    float get_value(float x, float y) const;

    Code calculate(const Bounds2f& bounds, ResultLimits& result) const;

private:
    Eigen::MatrixXf matrix; ///< Used to store measurement data
};
} // namespace Phoenix

#endif