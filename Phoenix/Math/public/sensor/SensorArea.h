#ifndef PhoenixSensorArea_H
#define PhoenixSensorArea_H

#include <Eigen/Dense>

namespace Phoenix {

class SensorArea {
public:
    // Constructor
    SensorArea(int cols, int rows, float left, float right, float bottom, float top);
    virtual ~SensorArea() = default;

public:
    // Number of columns in the detector (pixels)
    int cols() const {
        return matrix.cols();
    };
    // Number of rows in the detector (pixels)
    int rows() const {
        return matrix.rows();
    };

public:
    float left;   ///< Left boundary of the rectangular area (x-coordinate)
    float right;  ///< Right boundary of the rectangular area (x-coordinate)
    float bottom; ///< Bottom boundary of the rectangular area (y-coordinate)
    float top;    ///< Top boundary of the rectangular area (y-coordinate)

    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> matrix; ///< Used to store measurement data
};
} // namespace Phoenix

#endif