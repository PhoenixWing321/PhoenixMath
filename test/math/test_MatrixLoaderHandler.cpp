#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

// std
#include <filesystem>

// Phoenix
#include "loader/CoordsMatrixXfLoader.h"
#include "loader/MatrixLoaderHandler.hpp"
#include "loader/PpmLoader.h"
#include "shape/CoordsMatrixXf.h"

namespace Phoenix {
namespace Test {

TEST_CASE("MatrixLoaderHandler Basic Tests", "[loader]") {
    // 设置格式
    auto loader = std::make_unique<PpmLoader>(ColorRGB::LUMINANCE);
    // Test constructor with initial format
    MatrixLoaderHandler handler(std::move(loader));

    SECTION("Constructor and Format Setting") {
        // Test setting new format
        auto newFormat = std::make_unique<CoordsMatrixXfLoader>();
        handler.set_loader(std::move(newFormat));
    }
}

TEST_CASE("MatrixLoaderHandler Color Format Tests", "[loader]") {
    CoordsMatrixXf matrix;
    int            code;

    const std::vector<ColorRGB::ColorFormat> formats = {ColorRGB::GRAY_SCALE, ColorRGB::HEAT_MAP,
                                                        ColorRGB::LUMINANCE};

    const std::vector<std::string> format_names = {"GRAY_SCALE", "HEAT_MAP", "LUMINANCE"};

    // 测试所有颜色方案
    SECTION("Test all color formats") {
        for (size_t i = 0; i < formats.size(); ++i) {
            SECTION(format_names[ i ]) {
                // 为每种格式创建新的handler
                auto                loader = std::make_unique<PpmLoader>(formats[ i ]);
                MatrixLoaderHandler handler(std::move(loader));

                // 保存操作
                matrix.fill_pattern(300, 400);
                std::cout << "Original matrix pattern for " << format_names[ i ] << ":"
                          << std::endl;
                matrix.dump();

                std::string filename = "test_PpmLoader_" + format_names[ i ] + ".ppm";
                code                 = handler.save(&matrix, filename);
                REQUIRE(code == 0);

                // 清空矩阵
                matrix.setZero();

                // 加载操作
                code = handler.load(&matrix, filename);
                std::cout << "Matrix loaded from " << format_names[ i ] << " format:" << std::endl;
                matrix.dump();
                REQUIRE(code == 0);
            }
        }
    }

    SECTION("Format conversion test") {
        // 测试格式转换：保存为一种格式，用另一种格式加载
        const std::vector<ColorRGB::ColorFormat> formats = {
            ColorRGB::GRAY_SCALE, ColorRGB::HEAT_MAP, ColorRGB::LUMINANCE};

        // 先用GRAY_SCALE保存
        {
            auto                loader = std::make_unique<PpmLoader>(ColorRGB::GRAY_SCALE);
            MatrixLoaderHandler handler(std::move(loader));
            matrix.fill_pattern(300, 400);
            code = handler.save(&matrix, "test_conversion_source.ppm");
            REQUIRE(code == 0);
        }

        // 用其他格式加载
        for (auto format : formats) {
            if (format == ColorRGB::GRAY_SCALE) continue;

            SECTION("Converting from GRAY_SCALE to " + std::to_string(static_cast<int>(format))) {
                auto                loader = std::make_unique<PpmLoader>(format);
                MatrixLoaderHandler handler(std::move(loader));

                code = handler.load(&matrix, "test_conversion_source.ppm");
                REQUIRE(code == 0);

                std::string filename =
                    "test_conversion_to_" + std::to_string(static_cast<int>(format)) + ".ppm";
                code = handler.save(&matrix, filename, IMatrixLoader::FORMAT_PPM);
                REQUIRE(code == 0);
            }
        }
    }

    SECTION("Dynamic format switching") {
        // 测试动态切换格式
        auto                loader = std::make_unique<PpmLoader>(ColorRGB::GRAY_SCALE);
        MatrixLoaderHandler handler(std::move(loader));

        matrix.fill_pattern(300, 400);

        // 依次使用不同格式保存同一个矩阵
        for (auto format : {ColorRGB::GRAY_SCALE, ColorRGB::HEAT_MAP, ColorRGB::LUMINANCE}) {
            auto new_loader = std::make_unique<PpmLoader>(format);
            handler.set_loader(std::move(new_loader));

            std::string filename =
                "test_dynamic_switch_" + std::to_string(static_cast<int>(format)) + ".ppm";
            code = handler.save(&matrix, filename);
            REQUIRE(code == 0);
        }
    }
}
// 在测试代码中
TEST_CASE("Polar Plot Test") {
    CoordsMatrixXf matrix;
    matrix.fill_pattern(50, 360);

    auto                loader = std::make_unique<PpmLoader>(ColorRGB::HEAT_MAP);
    MatrixLoaderHandler handler(std::move(loader));

    int code = handler.save(&matrix, "polar_plot.ppm", IMatrixLoader::FORMAT_IMG_POLAR);
    REQUIRE(code == 0);
}
} // namespace Test
} // namespace Phoenix