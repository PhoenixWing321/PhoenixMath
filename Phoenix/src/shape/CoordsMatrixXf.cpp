#include "shape/CoordsMatrixXf.h"
#include "utility/StreamTools.hpp"
#include <fstream>

namespace Phoenix {

//------------------------------------------------------
void CoordsMatrixXf::dump(int format) const {
    if (format == 0) {

        std::cout << (*this) << std::endl;
    }
    else {
        // Set new format: fixed width, right-aligned, 1 decimal place
        std::cout << std::fixed << std::setprecision(3);

        // Output dimensions
        std::cout << Color::GREEN << rows() << "\t" << Color::YELLOW << cols() << "\n";

        // Output y coordinates
        std::cout << Color::YELLOW << "x" << Color::MAGENTA << " \\ " << Color::GREEN << "y";
        for (int y = 0; y < rows(); ++y) {
            std::cout << "\t" << y_coords(y);
        }
        std::cout << "\n";

        // Output y coordinates and matrix values
        for (int x = 0; x < cols(); ++x) {
            std::cout << Color::YELLOW << x_coords(x) << Color::MAGENTA;
            for (int y = 0; y < rows(); ++y) {
                std::cout << "\t" << coeff(y, x);
            }
            std::cout << "\n";
        }
    }
    std::cout << Color::RESET;
}
//------------------------------------------------------
void CoordsMatrixXf::fill_pattern() {
    // Set dimensions
    x_coords = Eigen::VectorXf(11);
    y_coords = Eigen::VectorXf(6);
    this->resize(6, 11);

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
