#include "loader/CoordsMatrixXfLoader.h"
#include "loader/PpmLoader.h"
#include "utility/StreamTools.hpp"
#include <fstream>
#include <iomanip> // For std::setw and std::setprecision
#include <limits>

namespace Phoenix {
//------------------------------------------------------
int CoordsMatrixXfLoader::load(IRowMatrixXf* matrix, const std::string& path, int format) {
    CoordsMatrixXf* coordsMatrix = dynamic_cast<CoordsMatrixXf*>(matrix);
    if (coordsMatrix == nullptr) return PW_E_POINTER;
    return load(coordsMatrix, path, format);
}
//------------------------------------------------------
int CoordsMatrixXfLoader::save(const IRowMatrixXf* matrix, const std::string& path,
                               int format) const {
    const CoordsMatrixXf* coordsMatrix = dynamic_cast<const CoordsMatrixXf*>(matrix);
    if (coordsMatrix == nullptr) return PW_E_POINTER;

    return save(coordsMatrix, path, format);
}
//------------------------------------------------------
int CoordsMatrixXfLoader::load(CoordsMatrixXf* matrix, const std::string& path, int format) {
    if (matrix == nullptr) return PW_E_POINTER;
    std::ifstream file(path);
    if (!file.is_open()) return ErrorCode::Code_FILE_NOT_OPEN;

    // Read dimensions
    int rows, cols;
    file >> rows >> cols;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore rest of the line

    if (!file.good() || rows <= 0 || cols <= 0) {
        return ErrorCode::Code_INVALID_SIZE;
    }

    // Resize containers
    matrix->resize(rows, cols);

    // a buffer to read from file
    std::stringstream buffer;
    // read from current position to end of file
    buffer << file.rdbuf();

    // load data from buffer
    return parse(matrix, buffer, format);
}
//------------------------------------------------------
int CoordsMatrixXfLoader::parse(CoordsMatrixXf* matrix, std::stringstream& buffer, int format) {
    if (matrix == nullptr) return PW_E_POINTER;
    if (!buffer.good()) return ErrorCode::Code_READ_ERROR;
    // check dimensions: x<==>cols, y<==>rows
    if (matrix->y_coords.size() != matrix->rows() || matrix->x_coords.size() != matrix->cols()) {
        return ErrorCode::Code_INVALID_SIZE;
    }

    switch (format) {
    case FORMAT_ROW_DEFAULT: {
        // Read x coordinates (column coordinates)
        for (int x = 0; x < matrix->x_coords.size(); ++x) {
            buffer >> matrix->x_coords(x);
            if (!buffer.good()) return ErrorCode::Code_READ_ERROR;
        }

        // Read y coordinates (row coordinates) and matrix values
        for (int y = 0; y < matrix->y_coords.size(); ++y) {
            buffer >> matrix->y_coords(y);
            for (int x = 0; x < matrix->cols(); ++x) {
                buffer >> matrix->coeffRef(y, x);
                if (!buffer.good()) return ErrorCode::Code_READ_ERROR;
            }
        }
    } break;
    case FORMAT_COL_COORD_FIRST: {
        // 01. Read y coordinates (column coordinates)
        for (int y = 0; y < matrix->y_coords.size(); ++y) {
            buffer >> matrix->y_coords(y);
            if (!buffer.good()) return ErrorCode::Code_READ_ERROR;
        }

        // 02. Read x coordinates (row coordinates)
        for (int x = 0; x < matrix->x_coords.size(); ++x) {
            buffer >> matrix->x_coords(x);
            if (!buffer.good()) return ErrorCode::Code_READ_ERROR;
        }

        // 03. Read matrix values: column-major
        for (int x = 0; x < matrix->x_coords.size(); ++x) {
            for (int y = 0; y < matrix->y_coords.size(); ++y) {
                buffer >> matrix->coeffRef(y, x);
                if (!buffer.good()) return ErrorCode::Code_READ_ERROR;
            }
        }
    } break;
    default:
        return ErrorCode::Code_INVALID_FORMAT;
    }
    return buffer.good() ? ErrorCode::Code_SUCCESS : ErrorCode::Code_READ_ERROR;
}
//------------------------------------------------------
int CoordsMatrixXfLoader::save(const CoordsMatrixXf* matrix, const std::string& path,
                               int format) const {
    switch (format) {
    case IMatrixLoader::FORMAT_IMG_POLAR:
    case IMatrixLoader::FORMAT_PPM:
        return save_ppm(matrix, path, format);
    }

    if (matrix == nullptr) return PW_E_POINTER;
    std::stringstream stream;
    // 01. Write dimensions
    stream << matrix->rows() << "\t" << matrix->cols() << "\n";

    // 02. Save data to stringstream
    auto code = serialize(matrix, stream, format);
    if (code != ErrorCode::Code_SUCCESS) return code;

    // 03. Save to file
    std::ofstream file(path);
    if (!file.is_open()) return ErrorCode::Code_FILE_NOT_OPEN;
    file << stream.str(); // Write entire content to file at once

    return file.good() ? ErrorCode::Code_SUCCESS : ErrorCode::Code_WRITE_ERROR;
}
//------------------------------------------------------
int CoordsMatrixXfLoader::serialize(const CoordsMatrixXf* matrix, std::stringstream& stream,
                                    int format) const {
    if (matrix == nullptr) return PW_E_POINTER;
    if (!stream.good()) return ErrorCode::Code_WRITE_ERROR;
    // DO NOT set output format

    // check dimensions: x<==>cols, y<==>rows
    if (matrix->y_coords.size() != matrix->rows() || matrix->x_coords.size() != matrix->cols()) {
        return ErrorCode::Code_INVALID_SIZE;
    }

    switch (format) {
    case FORMAT_ROW_DEFAULT: {
        // Write x coordinates (column coordinates)
        for (int x = 0; x < matrix->x_coords.size(); ++x) {
            stream << "\t" << matrix->x_coords(x);
        }
        stream << "\n";

        // Write y coordinates (row coordinates) and matrix values
        for (int y = 0; y < matrix->y_coords.size(); ++y) {
            stream << matrix->y_coords(y);
            for (int x = 0; x < matrix->x_coords.size(); ++x) {
                stream << "\t" << matrix->coeff(y, x);
            }
            stream << "\n";
        }
    } break;
    case FORMAT_COL_COORD_FIRST: {
        const size_t last_y = matrix->y_coords.size() - 1;
        const size_t last_x = matrix->x_coords.size() - 1;

        // 01. Write y coordinates (column coordinates)
        for (size_t y = 0; y <= last_y; ++y) {
            stream << matrix->y_coords(y);
            StreamTools::write_delimiter(stream, y, last_y, break_count);
        }

        // 02. Write x coordinates (row coordinates)
        for (size_t x = 0; x <= last_x; ++x) {
            stream << matrix->x_coords(x);
            StreamTools::write_delimiter(stream, x, last_x, break_count);
        }

        // 03. Write matrix values: column-major
        for (int x = 0; x < matrix->x_coords.size(); ++x) {
            for (int y = 0; y < matrix->y_coords.size(); ++y) {
                stream << matrix->coeff(y, x);
                StreamTools::write_delimiter(stream, y, last_y, break_count - 1);
            }
        }

    } break;
    default:
        return ErrorCode::Code_INVALID_FORMAT;
    }

    return stream.good() ? ErrorCode::Code_SUCCESS : ErrorCode::Code_WRITE_ERROR;
}
//----------------------------------
int CoordsMatrixXfLoader::save_ppm(const CoordsMatrixXf* matrix, const std::string& path,
                                   int format) const {
    PpmLoader loader;
    return loader.save(matrix, path, format);
}
} // namespace Phoenix
