#ifndef PHOENIX_CoordsMatrixXfLoader_H
#define PHOENIX_CoordsMatrixXfLoader_H

#include "loader/IMatrixLoader.hpp"
#include "shape/CoordsMatrixXf.h"

namespace Phoenix {

class CoordsMatrixXfLoader : public IMatrixLoader {
public:
    CoordsMatrixXfLoader()
        : IMatrixLoader(IMatrixLoader::FORMAT_UNDEFINED)
        , break_count(8) {}

    virtual ~CoordsMatrixXfLoader() = default;

public: // override
    /**
     * @brief Load from file
     * @param matrix Matrix to load
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int load(IRowMatrixXf* matrix, const std::string& path,
                     int format = FORMAT_ROW_DEFAULT) override;
    /**
     * @brief Save to file
     * @param matrix Matrix to save
     * @param path File path
     * @param format Format of the matrix or file
     * @return int Error code
     */
    virtual int save(const IRowMatrixXf* matrix, const std::string& path,
                     int format = FORMAT_ROW_DEFAULT) const override;

public:
    /**
     * @brief Load from file
     * @param path File path
     * @param format Format of the matrix or target file
     * @return int Error code
     */
    int load(CoordsMatrixXf* matrix, const std::string& path, int format);

    /**
     * @brief Load from stringstream
     * @param stream stringstream object to load from
     * @return int Error code
     */
    int parse(CoordsMatrixXf* matrix, std::stringstream& stream, int format);

    /**
     * @brief Save to file
     * @param path File path
     * @return int Error code
     */
    int save(const CoordsMatrixXf* matrix, const std::string& path, int format) const;

    /**
     * @brief Save to PPM file
     * @param path File path
     * @return int Error code
     */
    int save_ppm(const CoordsMatrixXf* matrix, const std::string& path, int format) const;

    /**
     * @brief Save to stringstream
     * @param stream stringstream object to save to
     * @return int Error code
     */
    int serialize(const CoordsMatrixXf* matrix, std::stringstream& stream, int format) const;

private:
    int break_count{8}; // break count for delimiter
};

} // namespace Phoenix
#endif