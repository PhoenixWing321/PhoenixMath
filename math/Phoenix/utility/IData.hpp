#ifndef PHOENIX_IData_H
#define PHOENIX_IData_H
#include <Eigen/Dense>
#include <vector>

namespace Phoenix {
enum FileFormat {
    FileFormat_UNDEFINED = 0, ///< undefined format
    FileFormat_YAML      = 1, ///< default row-major format
    FileFormat_JSON      = 2, ///< column-major format
    FileFormat_PPM       = 3, ///< PPM format
};

struct IData {
    IData()          = default;
    virtual ~IData() = default;
};
} // namespace Phoenix
#endif // PHOENIX_IData_H