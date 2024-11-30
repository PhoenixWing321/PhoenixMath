#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "matrix/MatrixRegion.h"

#include "../inside.hpp"

TEST_CASE("MatrixRegion Constructor", "[MatrixRegion]") {
    SECTION("Normal case") {
        Phoenix::MatrixRegion area(10, 20, 0.0f, 100.0f, 0.0f, 200.0f);
        REQUIRE(area.cols() == 10);
        REQUIRE(area.rows() == 20);
        REQUIRE(area.left == 0.0f);
        REQUIRE(area.right == 100.0f);
        REQUIRE(area.bottom == 0.0f);
        REQUIRE(area.top == 200.0f);
    }

    SECTION("Boundary case") {
        Phoenix::MatrixRegion area(1, 1, -10.0f, 10.0f, -10.0f, 10.0f);
        REQUIRE(area.cols() == 1);
        REQUIRE(area.rows() == 1);
        REQUIRE(area.left == -10.0f);
        REQUIRE(area.right == 10.0f);
        REQUIRE(area.bottom == -10.0f);
        REQUIRE(area.top == 10.0f);
    }

    // SECTION("Exception case") {
    //     REQUIRE_THROWS_AS(Phoenix::MatrixRegion(-1, 10, 0.0f, 10.0f, 0.0f, 10.0f),
    //                       std::invalid_argument);
    //     REQUIRE_THROWS_AS(Phoenix::MatrixRegion(10, -1, 0.0f, 10.0f, 0.0f, 10.0f),
    //                       std::invalid_argument);
    // }
}
