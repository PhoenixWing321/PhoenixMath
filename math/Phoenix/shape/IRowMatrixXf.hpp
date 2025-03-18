#ifndef PHOENIX_IRowMatrixXf_H
#define PHOENIX_IRowMatrixXf_H
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

    /**
     * @brief Resize the matrix and the coordinates
     * @param rows: number of rows
     * @param cols: number of columns
     */
    virtual void resize(Eigen::Index rows, Eigen::Index cols) {
        RowMatrixXf::resize(rows, cols);
    }
};
} // namespace Phoenix
#endif // PHOENIX_IRowMatrixXf_H