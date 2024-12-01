#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "shape/BoundsMatrixXf.h"

#include "../inside.hpp"

TEST_CASE("BoundsMatrixXf Constructor", "[BoundsMatrixXf]") {
    SECTION("Normal case") {
        Phoenix::BoundsMatrixXf area(20, 10, 0.0f, 0.0f, 100.0f, 200.0f);
        REQUIRE(area.cols() == 10);
        REQUIRE(area.rows() == 20);
        REQUIRE(area.left == 0.0f);
        REQUIRE(area.bottom == 0.0f);
        REQUIRE(area.right == 100.0f);
        REQUIRE(area.top == 200.0f);
    }

    SECTION("Boundary case") {
        Phoenix::BoundsMatrixXf area(1, 1, -10.0f, -10.0f, 10.0f, 10.0f);
        REQUIRE(area.cols() == 1);
        REQUIRE(area.rows() == 1);
        REQUIRE(area.left == -10.0f);
        REQUIRE(area.bottom == -10.0f);
        REQUIRE(area.right == 10.0f);
        REQUIRE(area.top == 10.0f);
    }

    // SECTION("Exception case") {
    //     REQUIRE_THROWS_AS(Phoenix::BoundsMatrixXf(-1, 10, 0.0f, 10.0f, 0.0f, 10.0f),
    //                       std::invalid_argument);
    //     REQUIRE_THROWS_AS(Phoenix::BoundsMatrixXf(10, -1, 0.0f, 10.0f, 0.0f, 10.0f),
    //                       std::invalid_argument);
    // }
}

TEST_CASE("BoundsMatrixXf::calculate with Bounds2f", "[BoundsMatrixXf]") {
    Phoenix::BoundsMatrixXf area(5, 10, 0.0f, 0.0f, 100.0f, 200.0f);
    area.fill_pattern();
    Phoenix::ResultLimits result;

    SECTION("Point inside bounds") {

        Phoenix::Bounds2f bounds(25.0f, 50.0f, 75.0f, 150.0f);
        area.calculate(bounds, result);
        REQUIRE(result.code == 0); // Successful calculation
        REQUIRE(result.min == 2);
        REQUIRE(result.max == 15);
    }

    SECTION("Point outside bounds") {
        Phoenix::Bounds2f bounds(105.0f, 205.0f, 110.0f, 210.0f);
        area.calculate(bounds, result);
        REQUIRE(result.code != 0); // Calculation failed
        REQUIRE(result.min == -1);
        REQUIRE(result.max == -1);
    }

    SECTION("Point on boundary") {
        Phoenix::Bounds2f bounds(0.0f, 0.0f, 100.0f, 200.0f);
        area.calculate(bounds, result);
        REQUIRE(result.min == 0);
        REQUIRE(result.max == 19);
        REQUIRE(result.code == 0); // Successful calculation
    }

    SECTION("Partially within bounds") {
        Phoenix::Bounds2f bounds(-10.0f, 50.0f, 110.0f, 150.0f);
        area.calculate(bounds, result);
        REQUIRE(result.code == 0); // Successful calculation
        REQUIRE(result.min == 0);
        REQUIRE(result.max == 15);
    }
}

TEST_CASE("BoundsMatrixXf::calculate with glm::vec2", "[BoundsMatrixXf]") {
    Phoenix::BoundsMatrixXf area(10, 20, 0.0f, 100.0f, 0.0f, 200.0f);
    Phoenix::ResultLimits   result;

    SECTION("Point inside bounds") {
        glm::vec2 pt(50.0f, 100.0f);
        area.calculate(pt, result);
        REQUIRE(result.code == 0); // Successful calculation
        REQUIRE(result.min == 5);
        REQUIRE(result.max == 10);
    }

    SECTION("Point outside bounds") {
        glm::vec2 pt(105.0f, 205.0f);
        area.calculate(pt, result);
        REQUIRE(result.code != 0); // Calculation failed
        REQUIRE(result.min == -1);
        REQUIRE(result.max == -1);
    }

    SECTION("Point on boundary") {
        glm::vec2 pt(0.0f, 0.0f);
        area.calculate(pt, result);
        REQUIRE(result.code == 0); // Successful calculation
        REQUIRE(result.min == 0);
        REQUIRE(result.max == 0);
    }
}
