#ifndef Phoenix_Code_H
#define Phoenix_Code_H

namespace Phoenix {
// error code, 0 is ok, other is error code
typedef unsigned int Code;

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
