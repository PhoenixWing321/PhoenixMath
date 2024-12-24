// std
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#define _USE_MATH_DEFINES // 必须在包含 cmath 之前定义
#include <cmath>

// Phoenix
#include "Phoenix/loader/PpmLoader.h"
#include "Phoenix/shape/CoordsMatrixXf.h"
#include "Phoenix/utility/PhoenixDefine.hpp"

namespace fs = std::filesystem;

#define FLT_PI 3.14159265358979323846f

// Phoenix
// #define PHOENIX_DEBUG_INFO
#include "Phoenix/utility/DebugMacro.h"

namespace Phoenix {

//----------------------------------
int PpmLoader::load(IRowMatrixXf* matrix, const std::string& path, int format) {
    if (matrix == nullptr) return PW_E_POINTER;
    // 是一个 RAII (Resource Acquisition Is Initialization)
    // 类型的对象，当它的生命周期结束时（即函数返回时），会自动调用析构函数，关闭文件流。
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return ErrorCode::Code_FILE_NOT_OPEN;
    }

    // Read PPM header
    std::string strFormat;
    int         cols, rows, maxVal;

    // Read format identifier (P6)
    file >> strFormat;
    if (strFormat != "P6") {
        return ErrorCode::Code_INVALID_FORMAT;
    }

    // Skip comments
    char line[ 1024 ];
    while (file.peek() == '#') {
        file.getline(line, 1024);
    }

    // Read dimensions
    file >> cols >> rows;
    if (file.fail()) {
        return ErrorCode::Code_READ_ERROR;
    }

    // Read max color value
    file >> maxVal;
    if (file.fail() || maxVal != 255) {
        return ErrorCode::Code_INVALID_FORMAT;
    }

    // Skip single whitespace character after maxVal
    file.get();

    // Resize matrix to match image dimensions
    matrix->resize(rows, cols);

    CoordsMatrixXf* coords = dynamic_cast<CoordsMatrixXf*>(matrix);
    // 如果矩阵是CoordsMatrixXf，则设置x和y坐标
    if (coords) {
        // set x coords

        for (int y = 0; y < coords->y_coords.size(); ++y) {
            coords->y_coords[ y ] = static_cast<float>(y);
        }

        for (int x = 0; x < coords->x_coords.size(); ++x) {
            coords->x_coords[ x ] = static_cast<float>(x);
        }
    }

    // Read pixel data
    ColorRGB color; // RGB buffer
    char*    buffer = reinterpret_cast<char*>(&color);

    // check flip_rows
    const int start = flip_rows ? rows - 1 : 0;
    const int end   = flip_rows ? 0 : rows - 1;
    const int step  = flip_rows ? -1 : 1;
    for (int i = start; i <= end; i += step) {
        for (int j = 0; j < cols; ++j) {
            // Read RGB values
            file.read(buffer, 3);
            if (file.fail()) return ErrorCode::Code_READ_ERROR;

            matrix->coeffRef(i, j) = ColorRGB::color_to_ratio(color, color_format);
        }
    }

    file.close();
    return ErrorCode::Code_SUCCESS;
}
//----------------------------------
int PpmLoader::save(const IRowMatrixXf* matrix, const std::string& path, int format) const {
    switch (format) {
    case IMatrixLoader::FORMAT_IMG_POLAR:
        return save_polar(matrix, path);
    case IMatrixLoader::FORMAT_PPM:
        return save_ppm(matrix, path);
    }
    return save_ppm(matrix, path);
    // return IMatrixLoader::Code_INVALID_FORMAT;
}
//----------------------------------
int PpmLoader::save_ppm(const IRowMatrixXf* matrix, const std::string& path) const {
    if (matrix == nullptr) return PW_E_POINTER;
    // PHOENIX_DEBUG(std::cout << "save path: " << fs::absolute(path) << std::endl;)
    // PPM保存实现
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return ErrorCode::Code_FILE_NOT_OPEN;

    auto rows = matrix->rows();
    auto cols = matrix->cols();

    // 写入PPM头部信息
    file << "P6\n";
    file << cols << " " << rows << "\n";
    file << "255\n";

    // 检索最大值用于归一化
    float    max_value = matrix->maxCoeff();
    ColorRGB color;
    char*    pixel = reinterpret_cast<char*>(&color);

    // 写入像素数据
    const float ratio = 1.f / max_value; // 归一化系数

    // check flip_rows
    const int start = flip_rows ? rows - 1 : 0;
    const int end   = flip_rows ? 0 : rows - 1;
    const int step  = flip_rows ? -1 : 1;

    for (int i = start; i <= end; i += step) {
        PHOENIX_DEBUG(std::cout << std::setw(5) << i << " |")
        for (int j = 0; j < cols; ++j) {
            // 归一化并转换为RGB值
            color = ColorRGB::ratio_to_color(matrix->coeff(i, j) * ratio, color_format);
            file.write(pixel, 3); // 写入3个字节
            PHOENIX_DEBUG(std::cout << " " << std::setw(3) << "(" << (int)color.r << ","
                                    << (int)color.g << "," << (int)color.b << ")")
        }
        PHOENIX_DEBUG(std::cout << std::endl;)
    }

    if (file.fail()) return ErrorCode::Code_WRITE_ERROR;

    file.close();
    return ErrorCode::Code_SUCCESS;
}
//----------------------------------
int PpmLoader::save_polar(const IRowMatrixXf* matrix, const std::string& path) const {
    if (matrix == nullptr) return PW_E_POINTER;
    if (matrix->rows() == 0 || matrix->cols() == 0) return ErrorCode::Code_INVALID_SIZE;

    // 创建一个圆形图像
    int image_size = static_cast<int>(matrix->cols() * 2); // 图像大小
    int center_x   = image_size / 2;
    int center_y   = image_size / 2;
    int max_radius = (image_size - 40) / 2; // 留出边距

    // 创建输出图像矩阵
    Eigen::MatrixXf polar_image = Eigen::MatrixXf::Zero(image_size, image_size);

    // 获取原始矩阵的维度
    int rows = static_cast<int>(matrix->rows()); // 对应极坐标中的r (0-90度)
    int cols = static_cast<int>(matrix->cols()); // 对应极坐标中的θ (0-360度)

    // 对每个像素进行极坐标映射
    for (int y = 0; y < image_size; ++y) {
        for (int x = 0; x < image_size; ++x) {
            // 计算相对于中心的位置
            float dx = static_cast<float>(x - center_x);
            float dy = static_cast<float>(y - center_y);

            // 计算极坐标
            float radius = std::sqrt(dx * dx + dy * dy);
            float theta  = std::atan2(dy, dx);

            // 转换为度数
            theta = theta * 180.0f / FLT_PI;
            if (theta < 0) theta += 360.0f;

            // 将radius映射到矩阵的行索引 (0-90度)
            float r_normalized = radius / max_radius * 90.0f;

            // 如果在有效范围内
            if (radius <= max_radius) {
                // 计算在原始矩阵中的位置（需要插值）
                float row_f = r_normalized * (rows - 1) / 90.0f;
                float col_f = theta * (cols - 1) / 360.0f;

                // 双线性插值
                int row = static_cast<int>(row_f);
                int col = static_cast<int>(col_f);

                if (row < rows - 1 && col < cols - 1) {
                    float t = row_f - row;
                    float s = col_f - col;

                    float value = (1 - t) * (1 - s) * matrix->coeff(row, col) +
                                  t * (1 - s) * matrix->coeff(row + 1, col) +
                                  (1 - t) * s * matrix->coeff(row, col + 1) +
                                  t * s * matrix->coeff(row + 1, col + 1);

                    polar_image(y, x) = value;
                }
            }
        }
    }

    // 保存为PPM文件
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return ErrorCode::Code_FILE_NOT_OPEN;

    // 写入PPM头部信息
    file << "P6\n";
    file << image_size << " " << image_size << "\n";
    file << "255\n";

    // 写入像素数据
    float    max_value = polar_image.maxCoeff();
    ColorRGB color;
    char*    pixel = reinterpret_cast<char*>(&color);

    for (int i = 0; i < image_size; ++i) {
        for (int j = 0; j < image_size; ++j) {
            if (std::sqrt(std::pow(i - center_y, 2) + std::pow(j - center_x, 2)) <= max_radius) {
                // 在圆内的像素
                color = ColorRGB::ratio_to_color(polar_image(i, j) / max_value, color_format);
            }
            else {
                // 圆外的像素设为白色
                color = ColorRGB{255, 255, 255};
            }
            file.write(pixel, 3);
        }
    }

    // 添加刻度和网格（可选）
    // TODO: 添加角度刻度和径向网格线

    file.close();
    return ErrorCode::Code_SUCCESS;
}

} // namespace Phoenix