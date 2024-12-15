#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "shape/BoundedMatrixXf.h"

#include "../inside.hpp"

// command for detail
// ./test_BoundedMatrixXf --success -r compact

// REQUIRE(2.1 ==  Approx(2.1));//  Approx(2.1) =>2.1_a
using namespace Catch::literals; // for 1.0_a

TEST_CASE("BoundedMatrixXf Constructor", "[matrix]") {
    SECTION("Normal case") {
        Phoenix::Bounds2f        bounds(0.f, 0.f, 100.f, 50.f);
        Phoenix::BoundedMatrixXf area(20, 10, bounds);
        REQUIRE(area.rows() == 20);
        REQUIRE(area.cols() == 10);
        REQUIRE(area.bounds.left == 0.f);
        REQUIRE(area.bounds.bottom == 0.f);
        REQUIRE(area.bounds.right == bounds.right);
        REQUIRE(area.bounds.top == bounds.top);
    }

    SECTION("Boundary case") {
        Phoenix::Bounds2f        bounds(-10.f, -10.f, 10.f, 10.f);
        Phoenix::BoundedMatrixXf area(2, 3, -10.f, -10.f, 10.f, 10.f);
        Phoenix::Bounds2f        bounds1 = area.bounds;
        REQUIRE(area.rows() == 2);
        REQUIRE(area.cols() == 3);
        REQUIRE(area.bounds.left == -10.f);
        REQUIRE(area.bounds.bottom == -10.f);
        REQUIRE(area.bounds.right == 10.f);
        REQUIRE(area.bounds.top == 10.f);
        REQUIRE(bounds1 == bounds);
    }
}

TEST_CASE("BoundedMatrixXf::fill_pattern", "[matrix]") {
    Phoenix::BoundedMatrixXf area(5, 10, 0.f, 0.f, 100.f, 50.f);
    area.fill_pattern();

    SECTION("check (i,j) function to touch the matrix") {
        auto& matrix = area;
        cout << " Bounds Matrix:" << endl;
        cout << "Bounds : " << area.bounds << endl;
        cout << "x segment = " << (area.bounds.right - area.bounds.left) / area.cols()
             << ", cols = " << matrix.cols() << endl;
        cout << "y segment = " << (area.bounds.top - area.bounds.bottom) / area.rows()
             << ", rows = " << matrix.rows() << endl;
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

TEST_CASE("BoundedMatrixXf::calculate with glm::vec2", "[matrix]") {
    Phoenix::BoundedMatrixXf area(5, 10, 0.f, 0.f, 50.f, 100.f);
    area.fill_pattern();

    SECTION("Point inside bounds") {
        glm::vec2              pt(50.f - 0.01f, 100.f - 0.01f);
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
        glm::vec2              pt(105.f, 205.f);
        area.calculate(pt, rst);
        cout << "Point outside bounds: {code,value,row,col} = " << rst << endl;
        REQUIRE(rst.code != 0); // Calculation failed
        REQUIRE(rst.value == std::numeric_limits<float>::lowest());
        REQUIRE(rst.row == Approx(10.25)); // [0,5)
        REQUIRE(rst.col == 21_a);          // [0,10)
    }

    SECTION("Point on boundary") {
        glm::vec2              pt(0.f, 53.f);
        Phoenix::ValueIndexRst rst;
        area.calculate(pt, rst);
        cout << "Point on boundary   : {code,value,row,col} = " << rst << endl;
        REQUIRE(rst.code == 0); // Successful calculation
        REQUIRE(rst.value == 2);
        REQUIRE(rst.row == Approx(2.65)); // [0,5)
        REQUIRE(rst.col == 0_a);          // [0,10)
    }
}

TEST_CASE("BoundedMatrixXf::calculate with specific bounds", "[matrix]") {
    Phoenix::BoundedMatrixXf area(5, 10, {0.f, 0.f, 100.f, 50.f});
    area.fill_pattern();

    SECTION("Bounds inside bounds") {
        Phoenix::Bounds2f  bounds(5.f, 5.f, 80.f, 35.f);
        Phoenix::LimitsRst rst;
        area.calculate(bounds, rst);
        cout << "Bounds inside bounds : {code,min,max} = " << rst << endl;

        REQUIRE(rst.code == 0); // Successful calculation
        REQUIRE(rst.min == 0);
        REQUIRE(rst.max == 11);
    }

    SECTION("Bounds outside bounds") {
        Phoenix::Bounds2f  bounds(22.f, 30.f, 80.f, 170.f);
        Phoenix::LimitsRst rst;
        area.calculate(bounds, rst);
        cout << "Bounds outside bounds: {code,min,max} = " << rst << endl;
        REQUIRE(rst.code != 0);
        REQUIRE(rst.min == std::numeric_limits<float>::max());    // Approx(3.40282e+38)
        REQUIRE(rst.max == std::numeric_limits<float>::lowest()); // Approx(-3.40282e+38)
    }

    SECTION("Bounds on boundary") {
        Phoenix::Bounds2f  bounds(0.f, 0.f, 59.9999f, 29.9999f);
        Phoenix::LimitsRst rst;
        area.calculate(bounds, rst);
        cout << "bounds on boundary   : {code,min,max} = " << rst << endl;
        REQUIRE(rst.code == 0); // Successful calculation
        REQUIRE(rst.min == 0);
        REQUIRE(rst.max == 7);
    }
}
