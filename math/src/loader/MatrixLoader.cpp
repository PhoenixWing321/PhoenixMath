#include "Phoenix/loader/MatrixLoader.h"
#include "Phoenix/utility/StreamTools.hpp"
#include <fstream>
#include <iomanip> // For std::setw and std::setprecision
#include <limits>

namespace Phoenix {

//------------------------------------------------------
int MatrixLoader::load(CoordsMatrixXf& matrix, const std::string& path, Format format) const {
    std::ifstream file(path);
    if (!file.is_open()) return FILE_NOT_OPEN;

    // Read dimensions
    int rows, cols;
    file >> rows >> cols;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore rest of the line

    if (!file.good() || rows <= 0 || cols <= 0) {
        return INVALID_DIMENSIONS;
    }

    // Resize containers
    matrix.resize(rows, cols);
    matrix.x_coords.resize(cols);
    matrix.y_coords.resize(rows);

    // a buffer to read from file
    std::stringstream buffer;
    // read from current position to end of file
    buffer << file.rdbuf();

    // load data from buffer
    return load(matrix, buffer, format);
}
//------------------------------------------------------
int MatrixLoader::load(CoordsMatrixXf& matrix, std::stringstream& buffer, Format format) const {
    if (!buffer.good()) return READ_ERROR;
    // check dimensions: x<==>cols, y<==>rows
    if (matrix.y_coords.size() != matrix.rows() || matrix.x_coords.size() != matrix.cols()) {
        return INVALID_DIMENSIONS;
    }

    switch (format) {
    case FORMAT_ROW_DEFAULT: {
        // Read x coordinates (column coordinates)
        for (int x = 0; x < matrix.x_coords.size(); ++x) {
            buffer >> matrix.x_coords(x);
            if (!buffer.good()) return READ_ERROR;
        }

        // Read y coordinates (row coordinates) and matrix values
        for (int y = 0; y < matrix.y_coords.size(); ++y) {
            buffer >> matrix.y_coords(y);
            for (int x = 0; x < matrix.cols(); ++x) {
                buffer >> matrix(y, x);
                if (!buffer.good()) return READ_ERROR;
            }
        }
    } break;
    case FORMAT_COL_COORD_FIRST: {
        // 01. Read y coordinates (column coordinates)
        for (int y = 0; y < matrix.y_coords.size(); ++y) {
            buffer >> matrix.y_coords(y);
            if (!buffer.good()) return READ_ERROR;
        }

        // 02. Read x coordinates (row coordinates)
        for (int x = 0; x < matrix.x_coords.size(); ++x) {
            buffer >> matrix.x_coords(x);
            if (!buffer.good()) return READ_ERROR;
        }

        // 03. Read matrix values: column-major
        for (int x = 0; x < matrix.x_coords.size(); ++x) {
            for (int y = 0; y < matrix.y_coords.size(); ++y) {
                buffer >> matrix(y, x);
                if (!buffer.good()) return READ_ERROR;
            }
        }
    } break;
    default:
        return INVALID_FORMAT;
    }
    return buffer.good() ? SUCCESS : READ_ERROR;
}
//------------------------------------------------------
int MatrixLoader::save(CoordsMatrixXf& matrix, const std::string& path, Format format) const {
    std::stringstream stream;
    // 01. Write dimensions
    stream << matrix.rows() << "\t" << matrix.cols() << "\n";

    // 02. Save data to stringstream
    auto code = save(matrix, stream, format);
    if (code != SUCCESS) return code;

    // 03. Save to file
    std::ofstream file(path);
    if (!file.is_open()) return FILE_NOT_OPEN;
    file << stream.str(); // Write entire content to file at once

    return file.good() ? SUCCESS : WRITE_ERROR;
}
//------------------------------------------------------
int MatrixLoader::save(CoordsMatrixXf& matrix, std::stringstream& stream, Format format) const {
    if (!stream.good()) return WRITE_ERROR;
    // DO NOT set output format

    // check dimensions: x<==>cols, y<==>rows
    if (matrix.y_coords.size() != matrix.rows() || matrix.x_coords.size() != matrix.cols()) {
        return INVALID_DIMENSIONS;
    }

    switch (format) {
    case FORMAT_ROW_DEFAULT: {
        // Write x coordinates (column coordinates)
        for (int x = 0; x < matrix.x_coords.size(); ++x) {
            stream << "\t" << matrix.x_coords(x);
        }
        stream << "\n";

        // Write y coordinates (row coordinates) and matrix values
        for (int y = 0; y < matrix.y_coords.size(); ++y) {
            stream << matrix.y_coords(y);
            for (int x = 0; x < matrix.x_coords.size(); ++x) {
                stream << "\t" << matrix.coeff(y, x);
            }
            stream << "\n";
        }
    } break;
    case FORMAT_COL_COORD_FIRST: {
        const size_t last_y = matrix.y_coords.size() - 1;
        const size_t last_x = matrix.x_coords.size() - 1;

        // 01. Write y coordinates (column coordinates)
        for (size_t y = 0; y <= last_y; ++y) {
            stream << matrix.y_coords(y);
            StreamTools::write_delimiter(stream, y, last_y, break_count);
        }

        // 02. Write x coordinates (row coordinates)
        for (size_t x = 0; x <= last_x; ++x) {
            stream << matrix.x_coords(x);
            StreamTools::write_delimiter(stream, x, last_x, break_count);
        }

        // 03. Write matrix values: column-major
        for (int x = 0; x < matrix.x_coords.size(); ++x) {
            for (int y = 0; y < matrix.y_coords.size(); ++y) {
                stream << matrix.coeff(y, x);
                StreamTools::write_delimiter(stream, y, last_y, break_count - 1);
            }
        }

    } break;
    default:
        return INVALID_FORMAT;
    }

    return stream.good() ? SUCCESS : WRITE_ERROR;
}
} // namespace Phoenix
