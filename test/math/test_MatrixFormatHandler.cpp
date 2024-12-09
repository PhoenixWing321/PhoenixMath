#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

// std
#include <filesystem>

// Phoenix
#include "loader/MatrixFormatHandler.hpp"
#include "loader/PpmLoader.h"
#include "shape/CoordsMatrixXf.h"

namespace Phoenix {
namespace Test {

// Mock format class for testing
class MockFormat : public IMatrixLoader {
public:
    Code load(IRowMatrixXf& matrix, const std::string& path) override {
        // Record that load was called
        loadCalled = true;
        return Code(ErrorCode::SUCCESS);
    }

    Code save(IRowMatrixXf& matrix, const std::string& path) override {
        // Record that save was called
        saveCalled = true;
        return Code(ErrorCode::SUCCESS);
    }

    bool loadCalled = false;
    bool saveCalled = false;
};

TEST_CASE("MatrixFormatHandler Basic Tests", "[MatrixFormatHandler]") {
    SECTION("Constructor and Format Setting") {

        auto loader = std::make_unique<PpmLoader>();
        // Test constructor with initial format
        MatrixFormatHandler handler(std::move(loader));

        // Test setting new format
        auto newFormat = std::make_unique<MockFormat>();
        handler.setFormat(std::move(newFormat));
    }

    SECTION("Save Operation") {
        auto loader = std::make_unique<PpmLoader>(PpmLoader::HEATMAP);

        // 设置格式
        MatrixFormatHandler handler(std::move(loader));
        CoordsMatrixXf      matrix;
        matrix.fill_pattern();

        auto code = handler.save(matrix, "test_PpmLoader_save.ppm");

        // Verify that save was called on the format
        REQUIRE(code == 0);
    }

    SECTION("Load Operation") {
        auto loader = std::make_unique<PpmLoader>();
        // Test constructor with initial format
        MatrixFormatHandler handler(std::move(loader));

        IRowMatrixXf matrix;
        auto         code = handler.load(matrix, "test_PpmLoader_save.ppm");

        // Verify that load was called on the format
        REQUIRE(code == IMatrixLoader::NOT_IMPLEMENTED);
    }
}

} // namespace Test
} // namespace Phoenix