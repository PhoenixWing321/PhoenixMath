#ifndef PHOENIX_MatrixLoaderHandler_H
#define PHOENIX_MatrixLoaderHandler_H

#include "loader/IMatrixLoader.hpp"

namespace Phoenix {

// 策略模式

class MatrixLoaderHandler {
public:
    explicit MatrixLoaderHandler(std::unique_ptr<IMatrixLoader> loader)
        : loader(std::move(loader)) {}

    void set_loader(std::unique_ptr<IMatrixLoader> loader) {
        loader = std::move(loader);
    }

    Code load(IRowMatrixXf* matrix, const std::string& path,
              int format = IMatrixLoader::FORMAT_UNDEFINED) {
        return loader->load(matrix, path, format);
    }

    Code save(const IRowMatrixXf* matrix, const std::string& path,
              int format = IMatrixLoader::FORMAT_UNDEFINED) {
        return loader->save(matrix, path, format);
    }

private:
    std::unique_ptr<IMatrixLoader> loader;
};
} // namespace Phoenix
#endif
