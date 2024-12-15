#include "shape/CoordsMatrixXf.h"
#include "shape/BoundedMatrixXf.h"
#include "utility/StreamTools.hpp"
#include <fstream>

namespace Phoenix {

//------------------------------------------------------
int CoordsMatrixXf::convert(BoundedMatrixXf& out) const {

    if (cols() < 2 || rows() < 2) {
        return ErrorCode::Code_INVALID_SIZE;
    }

    out.resize(rows(), cols());
    (RowMatrixXf&)out = *this;

    // calculate gap
    float gap_x = (x_coords(cols() - 1) - x_coords(0)) / (cols() - 1);
    float gap_y = (y_coords(rows() - 1) - y_coords(0)) / (rows() - 1);

    Bounds2f bounds;
    auto     b_min = glm::vec2(x_coords(0) - gap_x * 0.5f, y_coords(0) - gap_y * 0.5f);
    auto     b_max =
        glm::vec2(x_coords(cols() - 1) + gap_x * 0.5f, y_coords(rows() - 1) + gap_y * 0.5f);

    // expand bounds
    bounds.expand(b_min);
    bounds.expand(b_max);
    out.bounds = bounds; // copy bounds
    return 0;
}
//------------------------------------------------------
void CoordsMatrixXf::dump(int format, int rows0, int cols0) const {
    if (rows0 > rows()) rows0 = (int)rows();
    if (cols0 > cols()) cols0 = (int)cols();
    // 保存当前格式状态
    std::ios_base::fmtflags oldFlags     = std::cout.flags();
    std::streamsize         oldPrecision = std::cout.precision();
    std::cout << std::defaultfloat;

    static int width = 10;

    // Output dimensions
    std::cout << Color::GREEN << rows() << Color::RESET << " x " << Color::YELLOW << cols()
              << Color::RESET << ((format == 0) ? "\tRow-major" : "\tColumn-major") << std::endl;

    if (format == 0) {
        std::cout << Color::YELLOW << "\t";
        for (int x = 0; x < cols0; ++x) {
            std::cout << "\t" << std::setw(width) << x;
        }
        if (cols0 < cols()) std::cout << "\t...";
        std::cout << std::endl;
        // Output x coordinates row
        std::cout << Color::GREEN << "\t"
                  << "y" << Color::MAGENTA << " \\ " << Color::YELLOW << "x";

        for (int x = 0; x < cols0; ++x) {
            std::cout << "\t" << std::setw(width) << x_coords(x);
        }
        std::cout << std::endl;

        // Output y coordinates and matrix values
        for (int y = 0; y < rows0; ++y) {
            std::cout << Color::GREEN << y << "\t" << y_coords(y) << Color::MAGENTA;
            for (int x = 0; x < cols0; ++x) {
                std::cout << "\t" << std::setw(width) << coeff(y, x);
            }
            std::cout << std::endl;
        }
        if (rows0 < rows()) std::cout << Color::GREEN << "..." << std::endl;
    }
    else {
        std::cout << Color::GREEN << "\t";
        for (int x = 0; x < rows0; ++x) {
            std::cout << "\t" << x;
        }
        std::cout << std::endl;
        // Output y coordinates
        std::cout << Color::YELLOW << "\t"
                  << "x" << Color::MAGENTA << " \\ " << Color::GREEN << "y";
        for (int y = 0; y < rows0; ++y) {
            std::cout << "\t" << y_coords(y);
        }
        if (rows0 < rows()) std::cout << "\t..." << std::endl;
        std::cout << std::endl;

        // Output y coordinates and matrix values
        for (int x = 0; x < cols0; ++x) {
            std::cout << Color::YELLOW << x << "\t" << x_coords(x) << Color::MAGENTA;
            for (int y = 0; y < rows0; ++y) {
                std::cout << "\t" << std::setw(width) << coeff(y, x);
            }
            std::cout << std::endl;
        }
        if (cols0 < cols()) std::cout << Color::YELLOW << "..." << std::endl;
    }
    std::cout << Color::RESET;

    // 恢复原来的格式状态
    std::cout.flags(oldFlags);
    std::cout.precision(oldPrecision);
}
//------------------------------------------------------
void CoordsMatrixXf::fill_pattern(int rows, int cols) {

    if (rows == 0 || cols == 0) {
        rows = 10;
        cols = 6;
    }

    // Set dimensions
    CoordsMatrixXf::resize(rows, cols);

    // Set x coordinates
    // 根据 cols 的值自动生成非均匀分布的 x 坐标
    for (int i = 0; i < cols; ++i) {
        if (i < cols / 4) {
            // 前四分之一区域密集
            x_coords[ i ] = static_cast<float>(i * 2); // 小步长
        }
        else if (i < 3 * cols / 4) {
            // 中间一半区域稀疏
            x_coords[ i ] = static_cast<float>(10 + (i - cols / 4) * 5); // 大步长
        }
        else {
            // 后四分之一区域密集
            x_coords[ i ] = static_cast<float>(50 + (i - 3 * cols / 4) * 2); // 小步长
        }
    }

    // Set y coordinates
    // 根据 rows 的值自动生成非均匀分布的 y 坐标
    for (int i = 0; i < rows; ++i) {
        if (i < rows / 4) {
            // 前四分之一区域密集
            y_coords[ i ] = static_cast<float>(i * 1); // 小步长
        }
        else if (i < 3 * rows / 4) {
            // 中间一半区域稀疏
            y_coords[ i ] = static_cast<float>(5 + (i - rows / 4) * 3); // 大步长
        }
        else {
            // 后四分之一区域密集
            y_coords[ i ] = static_cast<float>(20 + (i - 3 * rows / 4) * 1); // 小步长
        }
    }

    // Set matrix values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            coeffRef(i, j) = static_cast<float>(i + j); // 简单的线性关系
        }
    }
}
} // namespace Phoenix
