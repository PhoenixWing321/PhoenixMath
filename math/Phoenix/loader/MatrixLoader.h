#ifndef PHOENIX_MatrixLoader_H
#define PHOENIX_MatrixLoader_H

#include "Phoenix/shape/CoordsMatrixXf.h"
#include <iostream>

namespace Phoenix {

class MatrixLoader {
public:
    MatrixLoader()
        : break_count(8) {}

    ~MatrixLoader() = default;

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
        FORMAT_ROW_DEFAULT     = 0, // default row-major format
        FORMAT_COL_COORD_FIRST = 1  // a kind of column-major format
    };

public:
    /**
     * @brief Load from file
     * @param path File path
     * @return int Error code
     */
    int load(CoordsMatrixXf& matrix, const std::string& path,
             Format format = FORMAT_ROW_DEFAULT) const;

    /**
     * @brief Load from stringstream
     * @param stream stringstream object to load from
     * @return int Error code
     */
    int load(CoordsMatrixXf& matrix, std::stringstream& stream,
             Format format = FORMAT_ROW_DEFAULT) const;

    /**
     * @brief Save to file
     * @param path File path
     * @return int Error code
     */
    int save(CoordsMatrixXf& matrix, const std::string& path,
             Format format = FORMAT_ROW_DEFAULT) const;

    /**
     * @brief Save to stringstream
     * @param stream stringstream object to save to
     * @return int Error code
     */
    int save(CoordsMatrixXf& matrix, std::stringstream& stream,
             Format format = FORMAT_ROW_DEFAULT) const;

public:
    int break_count{8}; // break count for delimiter
};

} // namespace Phoenix
#endif