#ifndef PHOENIX_CoordsMatrixXf_H
#define PHOENIX_CoordsMatrixXf_H

#include "shape/EigenDefine.hpp"
#include "utility/ColorOutput.h"
#include <iomanip> // For std::setw and std::setprecision
#include <iostream>

namespace Phoenix {

class CoordsMatrixXf : public RowMatrixXf {
public:
    CoordsMatrixXf()
        : RowMatrixXf(0, 0)
        , x_coords(0)
        , y_coords(0) {}

    ~CoordsMatrixXf() = default;

public:
    // Fill with sample data
    void fill_pattern();

    void dump(int format) const;

    friend std::ostream& operator<<(std::ostream& os, const CoordsMatrixXf& matrix);

public:
    Eigen::VectorXf y_coords; // Row coordinates of center, V-direction
    Eigen::VectorXf x_coords; // Column coordinates of center, U-direction
};

inline std::ostream& operator<<(std::ostream& os, const CoordsMatrixXf& matrix) {
    // Save original format settings
    auto old_flags     = os.flags();
    auto old_precision = os.precision();

    // Set new format: fixed width, right-aligned, 1 decimal place
    os << std::fixed << std::setprecision(1);

    // Output dimensions
    os << Color::GREEN << matrix.rows() << "\t" << Color::YELLOW << matrix.cols() << "\n";

    // Output x coordinates row
    os << Color::GREEN << "y" << Color::MAGENTA << " \\ " << Color::YELLOW << "x";

    for (int j = 0; j < matrix.cols(); ++j) {
        os << "\t" << matrix.x_coords(j);
    }
    os << "\n";

    // Output y coordinates and matrix values
    for (int i = 0; i < matrix.rows(); ++i) {
        os << Color::GREEN << matrix.y_coords(i) << Color::MAGENTA;
        for (int j = 0; j < matrix.cols(); ++j) {
            os << "\t" << matrix(i, j);
        }
        os << "\n";
    }

    std::cout << Color::RESET;
    // Restore original format settings
    os.flags(old_flags);
    os.precision(old_precision);

    return os;
}
} // namespace Phoenix
#endif