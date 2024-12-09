#include "shape/CoordsMatrixXf.h"
#include "utility/StreamTools.hpp"
#include <fstream>

namespace Phoenix {

//------------------------------------------------------
void CoordsMatrixXf::dump(int format, int rows0, int cols0) const {
    if (rows0 > rows()) rows0 = (int)rows();
    if (cols0 > cols()) cols0 = (int)cols();
    // 保存当前格式状态
    std::ios_base::fmtflags oldFlags     = std::cout.flags();
    std::streamsize         oldPrecision = std::cout.precision();
    std::cout << std::defaultfloat;

    // Output dimensions
    std::cout << Color::GREEN << rows() << Color::RESET << " x " << Color::YELLOW << cols()
              << Color::RESET << ((format == 0) ? "\tRow-major" : "\tColumn-major") << std::endl;

    if (format == 0) {
        std::cout << Color::YELLOW << "\t";
        for (int x = 0; x < cols0; ++x) {
            std::cout << "\t" << x;
        }
        if (cols0 < cols()) std::cout << "\t...";
        std::cout << std::endl;
        // Output x coordinates row
        std::cout << Color::GREEN << "\t"
                  << "y" << Color::MAGENTA << " \\ " << Color::YELLOW << "x";

        for (int x = 0; x < cols0; ++x) {
            std::cout << "\t" << x_coords(x);
        }
        std::cout << std::endl;

        // Output y coordinates and matrix values
        for (int y = 0; y < rows0; ++y) {
            std::cout << Color::GREEN << y << "\t" << y_coords(y) << Color::MAGENTA;
            for (int x = 0; x < cols0; ++x) {
                std::cout << "\t" << coeff(y, x);
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
                std::cout << "\t" << coeff(y, x);
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
void CoordsMatrixXf::fill_pattern() {
    // Set dimensions
    CoordsMatrixXf::resize(6, 11);

    // Set x coordinates
    x_coords << 0, 2, 4, 10, 20, 40, 60, 80, 85, 88, 90;

    // Set y coordinates
    y_coords << 0, 1, 5, 10, 30, 45;

    // Set matrix values
    (*this) << 0.0f, 0.5f, 1.2f, 3.4f, 8.1f, 9.2f, 9.8f, 10.0f, 12.0f, 15.0f, 18.0f, // Row 0
        0.3f, 1.1f, 2.5f, 4.8f, 9.3f, 10.0f, 11.0f, 13.0f, 14.0f, 16.0f, 19.0f,      // Row 1
        1.5f, 2.8f, 4.2f, 7.5f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 19.0f,     // Row 2
        3.2f, 4.5f, 6.8f, 11.0f, 15.0f, 16.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f,    // Row 3
        8.5f, 9.2f, 11.0f, 14.0f, 17.0f, 18.0f, 18.0f, 19.0f, 19.0f, 20.0f, 20.0f,   // Row 4
        12.0f, 13.0f, 15.0f, 16.0f, 18.0f, 19.0f, 19.0f, 20.0f, 20.0f, 20.0f, 20.0f; // Row 5
}
} // namespace Phoenix
