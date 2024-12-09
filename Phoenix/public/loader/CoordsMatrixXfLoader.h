#ifndef PHOENIX_CoordsMatrixXfLoader_H
#define PHOENIX_CoordsMatrixXfLoader_H

#include "loader/IMatrixLoader.hpp"

namespace Phoenix {

class CoordsMatrixXfLoader : public IMatrixLoader {
public:
    Code load(IRowMatrixXf& matrix, const std::string& path) override;

    Code save(IRowMatrixXf& matrix, const std::string& path) override;
};

} // namespace Phoenix
#endif