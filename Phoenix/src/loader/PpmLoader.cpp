
// std
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

// Phoenix
#include "loader/PpmLoader.h"
#include "utility/PhoenixDefine.hpp"

namespace fs = std::filesystem;

// Phoenix
#define PHOENIX_DEBUG_INFO
#include "utility/DebugMacro.h"

namespace Phoenix {

// Helper function to convert value to RGB color using heat map
ColorRGB valueToHeatMapColor(float value) {
    // Ensure value is in [0,1]
    value = std::clamp(value, 0.0f, 1.0f);

    ColorRGB color;
    // Blue to Cyan to Green to Yellow to Red
    if (value < 0.25f) {
        // Blue to Cyan (0.0 - 0.25)
        float t = value * 4;
        color.r = 0;
        color.g = static_cast<unsigned char>(255 * t);
        color.b = 255;
    }
    else if (value < 0.5f) {
        // Cyan to Green (0.25 - 0.5)
        float t = (value - 0.25f) * 4;
        color.r = 0;
        color.g = 255;
        color.b = static_cast<unsigned char>(255 * (1 - t));
    }
    else if (value < 0.75f) {
        // Green to Yellow (0.5 - 0.75)
        float t = (value - 0.5f) * 4;
        color.r = static_cast<unsigned char>(255 * t);
        color.g = 255;
        color.b = 0;
    }
    else {
        // Yellow to Red (0.75 - 1.0)
        float t = (value - 0.75f) * 4;
        color.r = 255;
        color.g = static_cast<unsigned char>(255 * (1 - t));
        color.b = 0;
    }
    return color;
}

Code PpmLoader::load(IRowMatrixXf& matrix, const std::string& path) {
    // PPM加载实现
    // TODO: 实现PPM文件的加载逻辑
    PHOENIX_DEBUG(std::cout << "PpmLoader::load NOT_IMPLEMENTED" << std::endl;)

    return NOT_IMPLEMENTED;
}

Code PpmLoader::save(IRowMatrixXf& matrix, const std::string& path) {
    // PPM保存实现
    // TODO: 实现PPM文件的保存逻辑
    // PHOENIX_DEBUG(std::cout << "PpmLoader::save NOT_IMPLEMENTED :" << path << std::endl)

    PHOENIX_DEBUG(std::cout << "save path: " << fs::absolute(path) << std::endl;)
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return Code(ErrorCode::FILE_NOT_OPEN);
    }

    auto rows = matrix.rows();
    auto cols = matrix.cols();

    // 写入PPM头部信息
    file << "P6\n";
    file << cols << " " << rows << "\n";
    file << "255\n";

    // 检索最大值用于归一化
    float max_value = matrix.maxCoeff();
    float min_value = matrix.minCoeff();
    float range     = max_value - min_value;

    // 写入像素数据
    switch (sub_type) {
    case 0: {
        float ratio = 255.0f / max_value;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                unsigned char pixel =
                    static_cast<unsigned char>(std::clamp(matrix(i, j) * ratio, 0.0f, 255.0f));
                file.write(reinterpret_cast<char*>(&pixel), 1);
                file.write(reinterpret_cast<char*>(&pixel), 1);
                file.write(reinterpret_cast<char*>(&pixel), 1);
            }
        }
    } break;
    case 1: {
        ColorRGB color;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Normalize value to [0,1]
                float normalized = (matrix(i, j) - min_value) / range;
                color            = valueToHeatMapColor(normalized);

                // Write RGB values
                file.write(reinterpret_cast<char*>(&color.r), 1);
                file.write(reinterpret_cast<char*>(&color.g), 1);
                file.write(reinterpret_cast<char*>(&color.b), 1);
            }
        }
    } break;
    default:
        break;
    }

    if (file.fail()) {
        file.close();
        return WRITE_ERROR;
    }

    file.close();
    return 0;
}

} // namespace Phoenix