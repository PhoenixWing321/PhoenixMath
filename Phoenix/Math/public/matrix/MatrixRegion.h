#ifndef PhoenixMatrixRegion_H
#define PhoenixMatrixRegion_H

#include <Eigen/Dense>

namespace Phoenix {

class MatrixRegion {
public:
    // Constructor
    MatrixRegion(int cols, int rows, float left, float right, float bottom, float top);
    virtual ~MatrixRegion() = default;

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

public:
    float left;   ///< Left boundary of the rectangular area (x-coordinate)
    float right;  ///< Right boundary of the rectangular area (x-coordinate)
    float bottom; ///< Bottom boundary of the rectangular area (y-coordinate)
    float top;    ///< Top boundary of the rectangular area (y-coordinate)

private:
    Eigen::MatrixXf matrix; ///< Used to store measurement data
};
} // namespace Phoenix

#endif