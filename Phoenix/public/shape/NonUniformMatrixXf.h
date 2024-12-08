#ifndef PHOENIX_NonUniformMatrixXf_H
#define PHOENIX_NonUniformMatrixXf_H

#include "shape/EigenDefine.hpp"
#include <Eigen/Dense>
#include <iomanip> // For std::setw and std::setprecision
#include <iostream>

namespace Phoenix {

class NonUniformMatrixXf : public RowMatrixXf {
public:
    // Error codes
    enum ErrorCode {
        SUCCESS            = 0,
        FILE_NOT_OPEN      = 1,
        INVALID_DIMENSIONS = 2,
        READ_ERROR         = 3,
        WRITE_ERROR        = 4,
        INVALID_FORMAT     = 5
    };

    enum Format {
        FORMAT_0 = 0, // default row-major format
        FORMAT_1 = 1  // a kind of column-major format
    };

    NonUniformMatrixXf()
        : RowMatrixXf(0, 0)
        , x_coords(0)
        , y_coords(0) {}

    ~NonUniformMatrixXf() = default;

    // Fill with sample data
    void fill_pattern();

    friend std::ostream& operator<<(std::ostream& os, const NonUniformMatrixXf& matrix);

    /**
     * @brief Load from file
     * @param path File path
     * @return int Error code
     */
    int load(const std::string& path, Format format = FORMAT_0);

    /**
     * @brief Load from stringstream
     * @param stream stringstream object to load from
     * @return int Error code
     */
    int load(std::stringstream& stream, Format format = FORMAT_0);

    /**
     * @brief Save to file
     * @param path File path
     * @return int Error code
     */
    int save(const std::string& path, Format format = FORMAT_0) const;

    /**
     * @brief Save to stringstream
     * @param stream stringstream object to save to
     * @return int Error code
     */
    int save(std::stringstream& stream, Format format = FORMAT_0) const;

public:
    Eigen::VectorXf y_coords; // Row coordinates of center, V-direction
    Eigen::VectorXf x_coords; // Column coordinates of center, U-direction
};

inline std::ostream& operator<<(std::ostream& os, const NonUniformMatrixXf& matrix) {
    // Save original format settings
    auto old_flags     = os.flags();
    auto old_precision = os.precision();

    // Set new format: fixed width, right-aligned, 1 decimal place
    os << std::fixed << std::setprecision(1);

    // Output dimensions
    os << matrix.rows() << "\t" << matrix.cols() << "\n";

    // Output x coordinates row
    os << "  y \\x\t";
    for (int j = 0; j < matrix.cols(); ++j) {
        os << std::setw(5) << matrix.x_coords(j);
    }
    os << "\n";

    // Output y coordinates and matrix values
    for (int i = 0; i < matrix.rows(); ++i) {
        os << std::setw(5) << matrix.y_coords(i) << "\t";
        for (int j = 0; j < matrix.cols(); ++j) {
            os << std::setw(5) << matrix(i, j);
        }
        os << "\n";
    }

    // Restore original format settings
    os.flags(old_flags);
    os.precision(old_precision);

    return os;
}
} // namespace Phoenix
#endif