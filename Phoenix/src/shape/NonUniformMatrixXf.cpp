#include "shape/NonUniformMatrixXf.h"
#include <iostream>
namespace Phoenix {

void NonUniformMatrixXf::fill_pattern() {
    // 设置尺寸
    x_coords = Eigen::VectorXf(11);
    y_coords = Eigen::VectorXf(6);
    this->resize(6, 11);

    // 设置x坐标
    x_coords << 0, 2, 4, 10, 20, 40, 60, 80, 85, 88, 90;

    // 设置y坐标
    y_coords << 0, 1, 5, 10, 30, 45;

    // 设置值矩阵
    (*this) << 0.0f, 0.5f, 1.2f, 3.4f, 8.1f, 9.2f, 9.8f, 10.0f, 12.0f, 15.0f, 18.0f, // 0
        0.3f, 1.1f, 2.5f, 4.8f, 9.3f, 10.0f, 11.0f, 13.0f, 14.0f, 16.0f, 19.0f,      // 1
        1.5f, 2.8f, 4.2f, 7.5f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 19.0f,     // 2
        3.2f, 4.5f, 6.8f, 11.0f, 15.0f, 16.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f,    // 3
        8.5f, 9.2f, 11.0f, 14.0f, 17.0f, 18.0f, 18.0f, 19.0f, 19.0f, 20.0f, 20.0f,   // 4
        12.0f, 13.0f, 15.0f, 16.0f, 18.0f, 19.0f, 19.0f, 20.0f, 20.0f, 20.0f, 20.0f; // 5
}
} // namespace Phoenix
