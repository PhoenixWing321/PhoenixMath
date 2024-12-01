#ifndef PHOENIX_BoundsMatrixXf_H
#define PHOENIX_BoundsMatrixXf_H

#include "glm/glm.hpp"
#include "shape/Bounds2f.hpp"
#include "utility/Code.hpp"
#include "utility/Result.hpp"
#include <Eigen/Dense>

namespace Phoenix {

class BoundsMatrixXf : public Bounds2f {
public:
    // Constructor
    BoundsMatrixXf(int rows, int cols, const Bounds2f& bounds); // Constructor
    BoundsMatrixXf(int rows, int cols, float left, float bottom, float right, float top);
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

    /**
     * @brief get the column index from x coordinate
     *
     * @param x horizontal coordinate
     * @return int, if x is outside the valid range, return -1
     */
    int col_int(double x) const;

    /**
     * @brief get the column index from x coordinate
     *
     * @param x horizontal coordinate
     * @return double, do not modify the index
     */
    inline double col_double(double x) const {
        return (x - left) / (right - left) * matrix.cols();
    };

    /**
     * @brief get the row index from y coordinate
     *
     * @param y vertical coordinate
     * @return int, if y is outside the valid range, return -1
     */
    int row_int(double y) const;

    /**
     * @brief get the row index from y coordinate
     *
     * @param y vertical coordinate
     * @return double, do not modify the index
     */
    inline double row_double(double y) const {
        return (y - bottom) / (top - bottom) * matrix.rows();
    }

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

    void calculate(const Bounds2f& bounds, LimitsRst& result) const;

    void calculate(const glm::vec2& pt, ValueIndexRst& result) const;

    void fill_pattern();

public:
    Eigen::MatrixXf matrix; ///< Used to store measurement data
};
} // namespace Phoenix

#endif