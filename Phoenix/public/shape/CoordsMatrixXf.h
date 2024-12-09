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

    void dump(int format, int rows = 20, int cols = 10) const;

    friend std::ostream& operator<<(std::ostream& os, const CoordsMatrixXf& matrix);

public:
    Eigen::VectorXf y_coords; // Row coordinates of center, V-direction
    Eigen::VectorXf x_coords; // Column coordinates of center, U-direction
};

} // namespace Phoenix
#endif