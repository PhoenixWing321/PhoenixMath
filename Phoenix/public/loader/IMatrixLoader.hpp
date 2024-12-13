#ifndef PHOENIX_IMatrixLoader_H
#define PHOENIX_IMatrixLoader_H

#include "shape/IRowMatrixXf.hpp"
#include "utility/Code.hpp"
#include <iostream>

namespace Phoenix {

struct IMatrixLoader {

    enum ErrorCode { // Error codes
        SUCCESS             = 0,
        FILE_NOT_OPEN       = 1,
        INVALID_DIMENSIONS  = 2,
        READ_ERROR          = 3,
        WRITE_ERROR         = 4,
        INVALID_FORMAT      = 5,
        INVALID_MATRIX_TYPE = 6, // matrix type is invalid
        UNKNOWN_ERROR       = 7,
        NOT_IMPLEMENTED     = 8,
        INVALID_POINTER     = 9,
    };

    enum Format {
        FORMAT_UNDEFINED       = 0, // undefined format
        FORMAT_ROW_DEFAULT     = 1, // default row-major format
        FORMAT_COL_COORD_FIRST = 2, // column-major format
        FORMAT_PPM             = 3, // PPM format
        FORMAT_IMG_POLAR       = 4, // PPM polar format
    };

    int format; ///< format of the matrix or target file

    IMatrixLoader(int format = FORMAT_UNDEFINED)
        : format(format) {}

    virtual ~IMatrixLoader() = default;

    /**
     * @brief Load from file
     * @param matrix Matrix to load
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int load(IRowMatrixXf* matrix, const std::string& path,
                     int format = FORMAT_UNDEFINED) const = 0;

    /**
     * @brief Save to file
     * @param matrix Matrix to save
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int save(const IRowMatrixXf* matrix, const std::string& path,
                     int format = FORMAT_UNDEFINED) const = 0;
};

} // namespace Phoenix
#endif // PHOENIX_IMatrixLoader_H