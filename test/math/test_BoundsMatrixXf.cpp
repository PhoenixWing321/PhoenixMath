#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "shape/BoundsMatrixXf.h"

#include "../inside.hpp"

// REQUIRE(2.1 ==  Approx(2.1));//  Approx(2.1) =>2.1_a
using namespace Catch::literals; // for 1.0_a

TEST_CASE("BoundsMatrixXf Constructor", "[BoundsMatrixXf]") {
    SECTION("Normal case") {
        Phoenix::Bounds2f       bounds(0.0f, 0.0f, 100.0f, 200.0f);
        Phoenix::BoundsMatrixXf area(20, 10, bounds);
        REQUIRE(area.rows() == 20);
        REQUIRE(area.cols() == 10);
        REQUIRE(area.left == 0.0f);
        REQUIRE(area.bottom == 0.0f);
        REQUIRE(area.right == 100.0f);
        REQUIRE(area.top == 200.0f);
    }

    SECTION("Boundary case") {

        Phoenix::Bounds2f       bounds(-10.0f, -10.0f, 10.0f, 10.0f);
        Phoenix::BoundsMatrixXf area(2, 3, -10.0f, -10.0f, 10.0f, 10.0f);
        Phoenix::Bounds2f       bounds1 = area;
        REQUIRE(area.rows() == 2);
        REQUIRE(area.cols() == 3);
        REQUIRE(area.left == -10.0f);
        REQUIRE(area.bottom == -10.0f);
        REQUIRE(area.right == 10.0f);
        REQUIRE(area.top == 10.0f);
        REQUIRE(bounds1 == bounds);
    }
}

TEST_CASE("BoundsMatrixXf::fill_pattern", "[BoundsMatrixXf]") {
    Phoenix::BoundsMatrixXf area(5, 10, 0.0f, 0.0f, 100.0f, 200.0f);
    area.fill_pattern();

    SECTION("check (i,j) funcion to touch the matrix") {
        auto& matrix = area.matrix;
        std::cout << matrix << std::endl;
        // row 0:   0  1  2  3  4  5  6  7  8  9
        // row 1:   1  2  3  4  5  6  7  8  9 10
        // row 2:   2  3  4  5  6  7  8  9 10 11
        // row 3:   3  4  5  6  7  8  9 10 11 12
        // row 4:   4  5  6  7  8  9 10 11 12 13
        REQUIRE(matrix.rows() == 5);
        REQUIRE(matrix.cols() == 10);
        REQUIRE(matrix(0, 0) == 0);
        REQUIRE(matrix(0, 1) == 1);
        REQUIRE(matrix(0, 4) == 4);
        REQUIRE(matrix(0, 9) == 9);
        REQUIRE(matrix(3, 3) == 6);
        REQUIRE(matrix(3, 6) == 9);
        REQUIRE(matrix(4, 9) == 13);
    }
}

TEST_CASE("BoundsMatrixXf::calculate with glm::vec2", "[BoundsMatrixXf]") {
    Phoenix::BoundsMatrixXf area(5, 10, 0.f, 0.f, 50.f, 100.f);
    area.fill_pattern();

    SECTION("Point inside bounds") {
        glm::vec2              pt(50.0f - 0.01f, 100.0f - 0.01f);
        Phoenix::ValueIndexRst rst;
        area.calculate(pt, rst);
        cout << "Point inside bounds : {code,value,row,col} = " << rst << endl;

        REQUIRE(rst.code == 0); // Successful calculation
        REQUIRE(rst.value == 13);
        REQUIRE(rst.row == Approx(4.9995)); // [0,5)
        REQUIRE(rst.col == 9.998_a);        // [0,10)
        REQUIRE(static_cast<int>(rst.row) == 4);
        REQUIRE(static_cast<int>(rst.col) == 9);
    }

    SECTION("Point outside bounds") {
        Phoenix::ValueIndexRst rst;
        glm::vec2              pt(105.0f, 205.0f);
        area.calculate(pt, rst);
        cout << "Point outside bounds: {code,value,row,col} = " << rst << endl;
        REQUIRE(rst.code != 0); // Calculation failed
        REQUIRE(rst.value == Approx(3.40282e+38));
        REQUIRE(rst.row == Approx(10.25)); // [0,5)
        REQUIRE(rst.col == 21_a);          // [0,10)
    }

    SECTION("Point on boundary") {
        glm::vec2              pt(0.0f, 53.0f);
        Phoenix::ValueIndexRst rst;
        area.calculate(pt, rst);
        cout << "Point on boundary   : {code,value,row,col} = " << rst << endl;
        REQUIRE(rst.code == 0); // Successful calculation
        REQUIRE(rst.value == 2);
        REQUIRE(rst.row == Approx(2.65)); // [0,5)
        REQUIRE(rst.col == 0_a);          // [0,10)
    }
}
