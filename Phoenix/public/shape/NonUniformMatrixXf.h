#ifndef PHOENIX_NonUniformMatrixXf_H
#define PHOENIX_NonUniformMatrixXf_H

#include "shape/EigenDefine.hpp"
#include <Eigen/Dense>
#include <iomanip> // 为 std::setw 和 std::setprecision
#include <iostream>

namespace Phoenix {

class NonUniformMatrixXf : public RowMatrixXf {
public:
    // Error codes
    enum ErrorCode {
        SUCCESS            = 0,
        FILE_NOT_OPEN      = 1,
        INVALID_DIMENSIONS = 2,
        READ_ERROR         = 3,
        WRITE_ERROR        = 4
    };

    NonUniformMatrixXf()
        : RowMatrixXf(0, 0)
        , x_coords(0)
        , y_coords(0) {}

    ~NonUniformMatrixXf() = default;

    // fill data
    void fill_pattern();

    friend std::ostream& operator<<(std::ostream& os, const NonUniformMatrixXf& matrix);

    int read(const std::string& path);

    int save(const std::string& path) const;

public:
    Eigen::VectorXf y_coords; // row coordinates of center, V- direction
    Eigen::VectorXf x_coords; // column coordinates of center, U- direction
};

inline std::ostream& operator<<(std::ostream& os, const NonUniformMatrixXf& matrix) {
    // 保存原始格式
    auto old_flags     = os.flags();
    auto old_precision = os.precision();

    // 设置新格式：固定宽度，右对齐，保留1位小数
    os << std::fixed << std::setprecision(1);

    // 输出维度
    os << matrix.rows() << "\t" << matrix.cols() << "\n";

    // 输出x坐标行
    os << "\t";
    for (int j = 0; j < matrix.cols(); ++j) {
        os << std::setw(5) << matrix.x_coords(j);
    }
    os << "\n";

    // 输出y坐标和值矩阵
    for (int i = 0; i < matrix.rows(); ++i) {
        os << std::setw(3) << matrix.y_coords(i) << "\t";
        for (int j = 0; j < matrix.cols(); ++j) {
            os << std::setw(5) << matrix(i, j);
        }
        os << "\n";
    }

    // 恢复原始格式
    os.flags(old_flags);
    os.precision(old_precision);

    return os;
}
} // namespace Phoenix
#endif