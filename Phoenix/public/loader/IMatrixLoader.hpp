#ifndef PHOENIX_IMatrixLoader_H
#define PHOENIX_IMatrixLoader_H

#include "shape/EigenDefine.hpp"

#include "utility/Code.hpp"

namespace Phoenix {

class IMatrixLoader {
public:
    virtual Code load(IRowMatrixXf& matrix, const std::string& path) = 0;
    virtual Code save(IRowMatrixXf& matrix, const std::string& path) = 0;

public:
    // Error codes
    enum ErrorCode {
        SUCCESS             = 0,
        FILE_NOT_OPEN       = 1,
        INVALID_DIMENSIONS  = 2,
        READ_ERROR          = 3,
        WRITE_ERROR         = 4,
        INVALID_FORMAT      = 5,
        INVALID_MATRIX_TYPE = 6, // matrix type is invalid
        UNKNOWN_ERROR       = 7,
        NOT_IMPLEMENTED     = 8
    };

    enum Format {
        FORMAT_ROW_DEFAULT     = 0, // default row-major format
        FORMAT_COL_COORD_FIRST = 1, // a kind of column-major format
        FORMAT_PPM             = 2  // a kind of PPM format
    };
};

} // namespace Phoenix
#endif // PHOENIX_IMatrixLoader_H