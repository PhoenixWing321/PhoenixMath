#ifndef PHOENIX_ErrorCode_H
#define PHOENIX_ErrorCode_H

#include "utility/PhoenixDefine.hpp"

namespace Phoenix {

/**
 * @brief Error codes Enum class
 */
struct ErrorCode {
    enum {
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

    static const char* get_string(int code) {
        switch (code) {
        case ErrorCode::Code_SUCCESS:
            return "Success";
        case ErrorCode::Code_E_FAIL:
            return "Operation failed";
        case ErrorCode::Code_E_INVALIDARG:
            return "Invalid argument";
        case ErrorCode::Code_E_POINTER:
            return "Invalid pointer";
        case ErrorCode::Code_E_NULL_VAR:
            return "Null variable";
        case ErrorCode::Code_E_UNEXPECTED:
            return "Unexpected error";
        case ErrorCode::Code_E_OUT_OF_MEMORY:
            return "Out of memory";
        case ErrorCode::Code_E_OUT_OF_INTMAX:
            return "Out of integer maximum";
        case ErrorCode::Code_E_OUT_OF_RANGE:
            return "Out of range";
        case ErrorCode::Code_E_FLOAT_NAN:
            return "Float is NaN";
        case ErrorCode::Code_E_FLOAT_INF:
            return "Float is infinite";
        case ErrorCode::NOT_IMPLEMENTED:
            return "Not implemented";
        case ErrorCode::FILE_NOT_OPEN:
            return "Failed to open file";
        case ErrorCode::INVALID_DIMENSIONS:
            return "Invalid matrix dimensions";
        case ErrorCode::READ_ERROR:
            return "Read error";
        case ErrorCode::WRITE_ERROR:
            return "Write error";
        case ErrorCode::Code_INVALID_FORMAT:
            return "Invalid format";
        case ErrorCode::INVALID_MATRIX_TYPE:
            return "Invalid matrix type";
        default:
            return "Unknown error";
        }
    }
};

#define PW_SUCCEEDED(Status) ((unsigned int)(Status) == 0)

#define PW_FAILED(Status) ((unsigned int)(Status) > 0)

#define PW_S_OK 0

/** @brief Unspecified error */
#define PW_E_FAIL 1

/** @brief One or more arguments are invalid */
#define PW_E_INVALIDARG 2

/** @brief Invalid pointer, Pointer is NULL. */
#define PW_E_POINTER 3

/** @brief Smart pointer is NULL_var. */
#define PW_E_NULL_VAR 4

/** @brief unexpected failure */
#define PW_E_UNEXPECTED 5

/** @brief Range out of memory */
#define PW_E_OUT_OF_MEMORY 6

/** @brief Range out of int */
#define PW_E_OUT_OF_INTMAX 7

/** @brief out of Range */
#define PW_E_OUT_OF_RANGE 8

/** @brief float/double nan */
#define PW_E_FLOAT_NAN 9

/** @brief float/double inf */
#define PW_E_FLOAT_INF 10

}; // namespace Phoenix
#endif
