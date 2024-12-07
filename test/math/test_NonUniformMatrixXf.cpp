#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "shape/NonUniformMatrixXf.h"

#include "../inside.hpp"

using namespace Phoenix;

TEST_CASE("NonUniformMatrixXf fill_pattern test", "[NonUniformMatrixXf]") {
    NonUniformMatrixXf matrix;
    matrix.fill_pattern();

    // 检查矩阵尺寸是否正确
    {
        CHECK(matrix.rows() == 6);
        CHECK(matrix.cols() == 11);
        std::cout << matrix << std::endl;
    }

    // 检查x坐标值
    {
        CHECK(matrix.x_coords(0) == 0.0f);
        CHECK(matrix.x_coords(1) == 2.0f);
        CHECK(matrix.x_coords(10) == 90.0f);
    }

    // 检查y坐标值
    {
        CHECK(matrix.y_coords(0) == 0.0f);
        CHECK(matrix.y_coords(1) == 1.0f);
        CHECK(matrix.y_coords(5) == 45.0f);
    }

    // 检查一些关键位置的值
    {
        CHECK(matrix(0, 0) == 0.0f);   // 左上角
        CHECK(matrix(0, 10) == 18.0f); // 第一行最后一个
        CHECK(matrix(5, 10) == 20.0f); // 右下角

        // 检查一些中间值
        CHECK(matrix(2, 3) == 7.5f);
        CHECK(matrix(3, 5) == 16.0f);
    }

    // 检查行方向单调性
    {
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 1; j < matrix.cols(); ++j) {
                CHECK(matrix(i, j) >= matrix(i, j - 1));
            }
        }

        // 检查列方向单调性
        for (int j = 0; j < matrix.cols(); ++j) {
            for (int i = 1; i < matrix.rows(); ++i) {
                CHECK(matrix(i, j) >= matrix(i - 1, j));
            }
        }
    }

    // 检查所有值是否在0-20范围内
    {
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.cols(); ++j) {
                CHECK(matrix(i, j) >= 0.0f);
                CHECK(matrix(i, j) <= 20.0f);
            }
        }
    }
}