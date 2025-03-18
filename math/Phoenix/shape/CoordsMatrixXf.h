#ifndef PHOENIX_CoordsMatrixXf_H
#define PHOENIX_CoordsMatrixXf_H

#include "Phoenix/shape/IRowMatrixXf.hpp"
#include "Phoenix/utility/ColorOutput.h"
#include <iomanip> // For std::setw and std::setprecision
#include <iostream>

namespace Phoenix {
class BoundedMatrixXf;

class CoordsMatrixXf : public IRowMatrixXf {
public:
    CoordsMatrixXf()
        : IRowMatrixXf(0, 0)
        , x_coords(0)
        , y_coords(0) {}

    virtual ~CoordsMatrixXf() = default;

public:
    /**
     * @brief Convert to BoundedMatrixXf
     * @param out: output matrix
     */
    int convert(BoundedMatrixXf& out) const;

    // Fill with sample data
    void fill_pattern(int rows = 10, int cols = 6);

    void dump(int format = 0, int rows = 20, int cols = 6) const;

    /**
     * @brief Resize the matrix and the coordinates
     * @param rows: number of rows
     * @param cols: number of columns
     */
    virtual void resize(Eigen::Index rows, Eigen::Index cols) {
        RowMatrixXf::resize(rows, cols);
        x_coords.resize(cols);
        y_coords.resize(rows);
    }

public:
    Eigen::VectorXf y_coords; // Row coordinates of center, V-direction
    Eigen::VectorXf x_coords; // Column coordinates of center, U-direction
};

} // namespace Phoenix
#endif