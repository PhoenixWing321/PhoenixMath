#ifndef PHOENIX_MatrixFormatHandler_H
#define PHOENIX_MatrixFormatHandler_H

#include "loader/IMatrixLoader.hpp"

namespace Phoenix {

// 策略模式

class MatrixFormatHandler {
public:
    explicit MatrixFormatHandler(std::unique_ptr<IMatrixLoader> format)
        : format_(std::move(format)) {}

    void setFormat(std::unique_ptr<IMatrixLoader> format) {
        format_ = std::move(format);
    }

    Code load(IRowMatrixXf& matrix, const std::string& path) {
        return format_->load(matrix, path);
    }

    Code save(IRowMatrixXf& matrix, const std::string& path) {
        return format_->save(matrix, path);
    }
    // 在MatrixFormatHandler中添加新方法
    Code save_polar(IRowMatrixXf& matrix, const std::string& path) {
        return format_->save_polar(matrix, path);
    }

private:
    std::unique_ptr<IMatrixLoader> format_;
};
} // namespace Phoenix
#endif
