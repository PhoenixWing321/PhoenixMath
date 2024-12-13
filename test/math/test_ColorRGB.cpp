#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "utility/ColorRGB.h"

#include "../inside.hpp"

using namespace Phoenix;

TEST_CASE("ColorRGB conversion tests", "[ColorRGB]") {
    SECTION("GRAY_SCALE format") {
        // 测试一些典型值
        SECTION("ratio_to_color - grayscale") {
            // 黑色
            auto color = ColorRGB::ratio_to_color(0.0f, ColorRGB::GRAY_SCALE);
            CHECK(color.r == 0);
            CHECK(color.g == 0);
            CHECK(color.b == 0);

            // 白色
            color = ColorRGB::ratio_to_color(1.0f, ColorRGB::GRAY_SCALE);
            CHECK(color.r == 255);
            CHECK(color.g == 255);
            CHECK(color.b == 255);

            // 灰色 (50%)
            color = ColorRGB::ratio_to_color(0.5f, ColorRGB::GRAY_SCALE);
            CHECK((color.r == 127 || color.r == 128));
            CHECK((color.g == 127 || color.g == 128));
            CHECK((color.b == 127 || color.b == 128));
        }

        SECTION("color_to_ratio - grayscale") {
            // 黑色
            ColorRGB color{0, 0, 0};
            CHECK(ColorRGB::color_to_ratio(color, ColorRGB::GRAY_SCALE) == Approx(0.0f));

            // 白色
            color = ColorRGB{255, 255, 255};
            CHECK(ColorRGB::color_to_ratio(color, ColorRGB::GRAY_SCALE) == Approx(1.0f));
        }
    }

    SECTION("HEAT_MAP format") {
        SECTION("ratio_to_color - heat map") {
            // 蓝色 (0.0)
            auto color = ColorRGB::ratio_to_color(0.0f, ColorRGB::HEAT_MAP);
            CHECK(color.r == 0);
            CHECK(color.g == 0);
            CHECK(color.b == 255);

            // 青色 (0.25)
            color = ColorRGB::ratio_to_color(0.25f, ColorRGB::HEAT_MAP);
            CHECK(color.r == 0);
            CHECK(color.g == 255);
            CHECK(color.b == 255);

            // 绿色 (0.5)
            color = ColorRGB::ratio_to_color(0.5f, ColorRGB::HEAT_MAP);
            CHECK(color.r == 0);
            CHECK(color.g == 255);
            CHECK(color.b == 0);

            // 黄色 (0.75)
            color = ColorRGB::ratio_to_color(0.75f, ColorRGB::HEAT_MAP);
            CHECK(color.r == 255);
            CHECK(color.g == 255);
            CHECK(color.b == 0);

            // 红色 (1.0)
            color = ColorRGB::ratio_to_color(1.0f, ColorRGB::HEAT_MAP);
            CHECK(color.r == 255);
            CHECK(color.g == 0);
            CHECK(color.b == 0);
        }

        SECTION("color_to_ratio - heat map") {
            // 测试关键颜色点的转换
            ColorRGB blue{0, 0, 255};
            CHECK(ColorRGB::color_to_ratio(blue, ColorRGB::HEAT_MAP) == Approx(0.0f));

            ColorRGB cyan{0, 255, 255};
            CHECK(ColorRGB::color_to_ratio(cyan, ColorRGB::HEAT_MAP) == Approx(0.25f));

            ColorRGB green{0, 255, 0};
            CHECK(ColorRGB::color_to_ratio(green, ColorRGB::HEAT_MAP) == Approx(0.5f));

            ColorRGB yellow{255, 255, 0};
            CHECK(ColorRGB::color_to_ratio(yellow, ColorRGB::HEAT_MAP) == Approx(0.75f));

            ColorRGB red{255, 0, 0};
            CHECK(ColorRGB::color_to_ratio(red, ColorRGB::HEAT_MAP) == Approx(1.0f));
        }
    }

    SECTION("LUMINANCE format") {
        SECTION("ratio_to_color - luminance") {
            // 测试黑白两端
            auto color = ColorRGB::ratio_to_color(0.0f, ColorRGB::LUMINANCE);
            CHECK(color.r == 0);
            CHECK(color.g == 0);
            CHECK(color.b == 0);

            color = ColorRGB::ratio_to_color(1.0f, ColorRGB::LUMINANCE);
            // 当比率为1时，需要确保总亮度为1
            // L = 0.299R + 0.587G + 0.114B = 1.0
            // 其中G=255，求R和B
            CHECK(int(color.r) == Approx(255).margin(1));
            CHECK(int(color.g) == 255);
            CHECK(int(color.b) == Approx(255).margin(1));
        }

        SECTION("color_to_ratio - luminance") {
            // 测试标准亮度转换
            ColorRGB color{255, 255, 255};
            float    ratio = ColorRGB::color_to_ratio(color, ColorRGB::LUMINANCE);
            CHECK(ratio == Approx(1.0f));

            color = ColorRGB{0, 0, 0};
            ratio = ColorRGB::color_to_ratio(color, ColorRGB::LUMINANCE);
            CHECK(ratio == Approx(0.0f));

            // 测试中间值
            color = ColorRGB{128, 128, 128};
            ratio = ColorRGB::color_to_ratio(color, ColorRGB::LUMINANCE);
            CHECK(ratio == Approx(0.50196f));
        }
    }

    SECTION("边界值测试") {
        // 测试比率超出范围的情况
        auto color = ColorRGB::ratio_to_color(-0.5f, ColorRGB::GRAY_SCALE);
        CHECK(color.r == 0);
        CHECK(color.g == 0);
        CHECK(color.b == 0);

        color = ColorRGB::ratio_to_color(1.5f, ColorRGB::GRAY_SCALE);
        CHECK(color.r == 255);
        CHECK(color.g == 255);
        CHECK(color.b == 255);
    }
}