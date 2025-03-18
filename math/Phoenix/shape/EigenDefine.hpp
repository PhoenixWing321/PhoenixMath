#ifndef PHOENIX_EigenDefine_H
#define PHOENIX_EigenDefine_H
#include <Eigen/Dense>
#include <vector>

namespace Phoenix {
/**
 * @brief Row-major dynamic matrix
 */
using RowMatrixXf = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

} // namespace Phoenix
#endif // PHOENIX_EigenDefine_H