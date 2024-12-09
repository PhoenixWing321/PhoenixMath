#ifndef PHOENIX_EigenDefine_H
#define PHOENIX_EigenDefine_H
#include <Eigen/Dense>
#include <vector>

namespace Phoenix {
/**
 * @brief Row-major dynamic matrix
 */
using RowMatrixXf = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

struct IRowMatrixXf : public RowMatrixXf {
    IRowMatrixXf(int rows = 0, int cols = 0)
        : RowMatrixXf(rows, cols){};
    virtual ~IRowMatrixXf() = default;
};
} // namespace Phoenix
#endif // PHOENIX_EigenDefine_H