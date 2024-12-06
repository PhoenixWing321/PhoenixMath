#ifndef PHOENIX_BoundedMatrixXf_H
#define PHOENIX_BoundedMatrixXf_H

#include "glm/glm.hpp"
#include "shape/Bounds2f.hpp"
#include "utility/Code.hpp"
#include "utility/Result.hpp"
#include <Eigen/Dense>

namespace Phoenix {

using RowMatrixXf = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

class BoundedMatrixXf : public RowMatrixXf {
public:
    BoundedMatrixXf()
        : RowMatrixXf(0, 0)
        , bounds{} {}

    BoundedMatrixXf(size_t rows, size_t cols)
        : RowMatrixXf(rows, cols)
        , bounds{} {}
    // constructor
    BoundedMatrixXf(size_t rows, size_t cols, const Bounds2f& bounds)
        : RowMatrixXf(rows, cols)
        , bounds(bounds) {
        // do not initialize matrix
    }

    BoundedMatrixXf(int rows, int cols, float left, float bottom, float right, float top);

    ~BoundedMatrixXf() = default;

public:
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
        return (x - bounds.left) / (bounds.right - bounds.left) * cols();
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
        return (y - bounds.bottom) / (bounds.top - bounds.bottom) * rows();
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
     *  return the boundary value
     */
    float get_value(float x, float y) const;

    void calculate(const Bounds2f& bounds, LimitsRst& result) const;

    void calculate(const glm::vec2& pt, ValueIndexRst& result) const;

    /**
     * @brief fill the matrix with pattern
     *
     * @param type 0: linear increase, 1: random, otherwise: not realized
     */
    void fill_pattern(int type = 0);

public:
    Bounds2f bounds; // 2d bounds
};
} // namespace Phoenix
#endif