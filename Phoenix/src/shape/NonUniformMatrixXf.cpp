#include "shape/NonUniformMatrixXf.h"
#include <fstream>

namespace Phoenix {

//------------------------------------------------------
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
//------------------------------------------------------
int NonUniformMatrixXf::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return FILE_NOT_OPEN;
    }

    // Read entire file content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();

    return load(buffer);
}
//------------------------------------------------------
int NonUniformMatrixXf::load(std::stringstream& buffer) {
    this->resize(0, 0);
    if (!buffer.good()) {
        return READ_ERROR;
    }

    // Read dimensions
    int rows, cols;
    buffer >> rows >> cols;

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
        buffer >> x_coords(j);
    }

    // Read y coordinates (row coordinates) and matrix values
    for (int i = 0; i < rows; ++i) {
        buffer >> y_coords(i);
        for (int j = 0; j < cols; ++j) {
            buffer >> (*this)(i, j);
        }
    }

    return buffer.good() ? SUCCESS : READ_ERROR;
}
//------------------------------------------------------
int NonUniformMatrixXf::save(const std::string& path) const {
    // DO NOT set output format
    std::stringstream stream;
    auto              code = save(stream);
    if (code != SUCCESS) return code;

    std::ofstream file(path);
    if (!file.is_open()) return FILE_NOT_OPEN;
    // Write entire content to file at once
    file << stream.str();

    return file.good() ? SUCCESS : WRITE_ERROR;
}
//------------------------------------------------------
int NonUniformMatrixXf::save(std::stringstream& stream) const {
    if (!stream.good()) return WRITE_ERROR;
    // DO NOT set output format

    // Write dimensions
    stream << rows() << "\t" << cols() << "\n";

    // Write x coordinates (column coordinates)
    for (int j = 0; j < cols(); ++j) {
        stream << "\t" << x_coords(j);
    }
    stream << "\n";

    // Write y coordinates (row coordinates) and matrix values
    for (int i = 0; i < rows(); ++i) {
        stream << y_coords(i);
        for (int j = 0; j < cols(); ++j) {
            stream << "\t" << (*this)(i, j);
        }
        stream << "\n";
    }

    return stream.good() ? SUCCESS : WRITE_ERROR;
}
} // namespace Phoenix
