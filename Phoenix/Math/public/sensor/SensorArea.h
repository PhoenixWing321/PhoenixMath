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
    int   cols;   ///< Number of columns in the detector (pixels)
    float left;   ///< Left boundary of the rectangular area (x-coordinate)
    float right;  ///< Right boundary of the rectangular area (x-coordinate)
    int   rows;   ///< Number of rows in the detector (pixels)
    float bottom; ///< Bottom boundary of the rectangular area (y-coordinate)
    float top;    ///< Top boundary of the rectangular area (y-coordinate)

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
        matrix; ///< Used to store measurement data
};
} // namespace Phoenix

#endif