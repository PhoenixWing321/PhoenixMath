#ifndef PHOENIX_IMatrixLoader_H
#define PHOENIX_IMatrixLoader_H

#include "Phoenix/shape/IRowMatrixXf.hpp"
#include "Phoenix/utility/ErrorCode.hpp"
#include <iostream>

namespace Phoenix {

struct IMatrixLoader {

    enum Format {
        FORMAT_UNDEFINED       = 0, ///< undefined format
        FORMAT_ROW_DEFAULT     = 1, ///< default row-major format
        FORMAT_COL_COORD_FIRST = 2, ///< column-major format
        FORMAT_PPM             = 3, ///< PPM format
        FORMAT_IMG_POLAR       = 4, ///< PPM polar format
    };

    int format_; ///< format of the matrix or target file

    IMatrixLoader(int format = FORMAT_UNDEFINED)
        : format_(format) {}

    virtual ~IMatrixLoader() = default;

    /**
     * @brief Load from file
     * @param matrix Matrix to load
     * @param path File path
     * @param format Format of the matrix or file，0 means undefined format
     * @return int Error code
     */
    virtual int load(IRowMatrixXf* matrix, const std::string& path, int format) = 0;

    /**
     * @brief Save to file
     * @param matrix Matrix to save
     * @param path File path
     * @param format Format of the matrix or file，0 means undefined format
     * @return int Error code
     */
    virtual int save(const IRowMatrixXf* matrix, const std::string& path, int format) const = 0;

    inline void set_format(int format) {
        format_ = format;
    }

    inline int get_format() const {
        return format_;
    }
};

} // namespace Phoenix
#endif // PHOENIX_IMatrixLoader_H