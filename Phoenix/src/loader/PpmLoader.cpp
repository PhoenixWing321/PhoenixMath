// std
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

// Phoenix
#include "loader/PpmLoader.h"
#include "shape/CoordsMatrixXf.h"
#include "utility/PhoenixDefine.hpp"

namespace fs = std::filesystem;

// Phoenix
// #define PHOENIX_DEBUG_INFO
#include "utility/DebugMacro.h"

namespace Phoenix {

//----------------------------------
Code PpmLoader::load(IRowMatrixXf& matrix, const std::string& path) {
    // 是一个 RAII (Resource Acquisition Is Initialization)
    // 类型的对象，当它的生命周期结束时（即函数返回时），会自动调用析构函数，关闭文件流。
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return Code(ErrorCode::FILE_NOT_OPEN);
    }

    // Read PPM header
    std::string format;
    int         width, height, maxVal;

    // Read format identifier (P6)
    file >> format;
    if (format != "P6") {
        return Code(ErrorCode::INVALID_FORMAT);
    }

    // Skip comments
    char line[ 1024 ];
    while (file.peek() == '#') {
        file.getline(line, 1024);
    }

    // Read dimensions
    file >> width >> height;
    if (file.fail()) {
        return Code(ErrorCode::READ_ERROR);
    }

    // Read max color value
    file >> maxVal;
    if (file.fail() || maxVal != 255) {
        return Code(ErrorCode::INVALID_FORMAT);
    }

    // Skip single whitespace character after maxVal
    file.get();

    // Resize matrix to match image dimensions
    matrix.resize(height, width);

    CoordsMatrixXf* coords = dynamic_cast<CoordsMatrixXf*>(&matrix);
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
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Read RGB values
            file.read(buffer, 3);
            if (file.fail()) return READ_ERROR;

            matrix(i, j) = ColorRGB::color_to_ratio(color, sub_type);
        }
    }

    file.close();
    return SUCCESS;
}
//----------------------------------
Code PpmLoader::save(IRowMatrixXf& matrix, const std::string& path) {
    // PHOENIX_DEBUG(std::cout << "save path: " << fs::absolute(path) << std::endl;)
    // PPM保存实现
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return FILE_NOT_OPEN;

    auto rows = matrix.rows();
    auto cols = matrix.cols();

    // 写入PPM头部信息
    file << "P6\n";
    file << cols << " " << rows << "\n";
    file << "255\n";

    // 检索最大值用于归一化
    float    max_value = matrix.maxCoeff();
    ColorRGB color;
    char*    pixel = reinterpret_cast<char*>(&color);

    // 写入像素数据
    const float ratio = 1.f / max_value; // 归一化系数
    for (int i = 0; i < rows; ++i) {
        PHOENIX_DEBUG(std::cout << std::setw(5) << i << " |")
        for (int j = 0; j < cols; ++j) {
            // 归一化并转换为RGB值
            color = ColorRGB::ratio_to_color(matrix(i, j) * ratio, sub_type);
            file.write(pixel, 3); // 写入3个字节
            PHOENIX_DEBUG(std::cout << " " << std::setw(3) << "(" << (int)color.r << ","
                                    << (int)color.g << "," << (int)color.b << ")")
        }
        PHOENIX_DEBUG(std::cout << std::endl;)
    }

    if (file.fail()) return WRITE_ERROR;

    file.close();
    return SUCCESS;
}

} // namespace Phoenix