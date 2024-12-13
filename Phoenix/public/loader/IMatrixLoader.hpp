#ifndef PHOENIX_IMatrixLoader_H
#define PHOENIX_IMatrixLoader_H

#include "shape/IRowMatrixXf.hpp"
#include "utility/Code.hpp"
#include <iostream>

namespace Phoenix {

struct IMatrixLoader {

    enum ErrorCode {               // Error codes
        Code_SUCCESS         = 0,  ///< Operation completed successfully
        Code_E_FAIL          = 1,  ///< Unspecified error
        Code_E_INVALIDARG    = 2,  ///< One or more arguments are invalid
        Code_E_POINTER       = 3,  ///< Invalid pointer, Pointer is NULL
        Code_E_NULL_VAR      = 4,  ///< Smart pointer is NULL_var
        Code_E_UNEXPECTED    = 5,  ///< unexpected failure
        Code_E_OUT_OF_MEMORY = 6,  ///< Range out of memory
        Code_E_OUT_OF_INTMAX = 7,  ///< Range out of int
        Code_E_OUT_OF_RANGE  = 8,  ///< Value is out of valid range
        Code_E_FLOAT_NAN     = 9,  ///< float/double nan
        Code_E_FLOAT_INF     = 10, ///< float/double inf
        NOT_IMPLEMENTED      = 11, ///< Function is not implemented
        FILE_NOT_OPEN        = 12, ///< Failed to open file
        INVALID_DIMENSIONS   = 13, ///< Matrix dimensions are invalid
        READ_ERROR           = 14, ///< Error occurred during read operation
        WRITE_ERROR          = 15, ///< Error occurred during write operation
        Code_INVALID_FORMAT  = 16, ///< File format is invalid
        INVALID_MATRIX_TYPE  = 17  ///< matrix type is invalid
    };

    enum Format {
        FORMAT_UNDEFINED       = 0, ///< undefined format
        FORMAT_ROW_DEFAULT     = 1, ///< default row-major format
        FORMAT_COL_COORD_FIRST = 2, ///< column-major format
        FORMAT_PPM             = 3, ///< PPM format
        FORMAT_IMG_POLAR       = 4, ///< PPM polar format
    };

    int format; ///< format of the matrix or target file

    IMatrixLoader(int format = FORMAT_UNDEFINED)
        : format(format) {}

    virtual ~IMatrixLoader() = default;

    /**
     * @brief Load from file
     * @param matrix Matrix to load
     * @param path File path
     * @param format Format of the matrix or file，0 means undefined format
     * @return int Error code
     */
    virtual int load(IRowMatrixXf* matrix, const std::string& path, int format) const = 0;

    /**
     * @brief Save to file
     * @param matrix Matrix to save
     * @param path File path
     * @param format Format of the matrix or file，0 means undefined format
     * @return int Error code
     */
    virtual int save(const IRowMatrixXf* matrix, const std::string& path, int format) const = 0;
};

} // namespace Phoenix
#endif // PHOENIX_IMatrixLoader_H