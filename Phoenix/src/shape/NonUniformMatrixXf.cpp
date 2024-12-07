#include "shape/NonUniformMatrixXf.h"
#include <fstream>

namespace Phoenix {

void NonUniformMatrixXf::fill_pattern() {
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

int NonUniformMatrixXf::read(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return FILE_NOT_OPEN;
    }
    return read(file);
}

int NonUniformMatrixXf::read(std::ifstream& file) {
    if (!file.good()) {
        return READ_ERROR;
    }

    // Read dimensions
    int rows, cols;
    file >> rows >> cols;

    // Validate dimensions
    if (rows <= 0 || cols <= 0) {
        return INVALID_DIMENSIONS;
    }

    // Resize containers
    this->resize(rows, cols);
    x_coords.resize(cols);
    y_coords.resize(rows);

    // Read x coordinates (column coordinates)
    for (int j = 0; j < cols; ++j) {
        file >> x_coords(j);
    }

    // Read y coordinates (row coordinates) and matrix values
    for (int i = 0; i < rows; ++i) {
        file >> y_coords(i);
        for (int j = 0; j < cols; ++j) {
            file >> (*this)(i, j);
        }
    }

    return file.good() ? SUCCESS : READ_ERROR;
}

int NonUniformMatrixXf::save(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        return FILE_NOT_OPEN;
    }

    // Save original format settings
    auto old_flags     = file.flags();
    auto old_precision = file.precision();

    // Set output format
    file << std::fixed << std::setprecision(1);

    // Write dimensions
    file << rows() << "\t" << cols() << "\n";

    // Write x coordinates (column coordinates)
    file << "\t";
    for (int j = 0; j < cols(); ++j) {
        file << std::setw(5) << x_coords(j);
    }
    file << "\n";

    // Write y coordinates (row coordinates) and matrix values
    for (int i = 0; i < rows(); ++i) {
        file << std::setw(3) << y_coords(i) << "\t";
        for (int j = 0; j < cols(); ++j) {
            file << std::setw(5) << (*this)(i, j);
        }
        file << "\n";
    }

    // Restore original format settings
    file.flags(old_flags);
    file.precision(old_precision);

    return file.good() ? SUCCESS : WRITE_ERROR;
}

} // namespace Phoenix
