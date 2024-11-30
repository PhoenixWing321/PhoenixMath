#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "sensor/SensorArea.h"

TEST_CASE("SensorArea Constructor", "[SensorArea]") {
    SECTION("Normal case") {
        Phoenix::SensorArea area(10, 20, 0.0f, 100.0f, 0.0f, 200.0f);
        REQUIRE(area.cols() == 10);
        REQUIRE(area.rows() == 20);
        REQUIRE(area.left == 0.0f);
        REQUIRE(area.right == 100.0f);
        REQUIRE(area.bottom == 0.0f);
        REQUIRE(area.top == 200.0f);
    }

    SECTION("Boundary case") {
        Phoenix::SensorArea area(1, 1, -10.0f, 10.0f, -10.0f, 10.0f);
        REQUIRE(area.cols() == 1);
        REQUIRE(area.rows() == 1);
        REQUIRE(area.left == -10.0f);
        REQUIRE(area.right == 10.0f);
        REQUIRE(area.bottom == -10.0f);
        REQUIRE(area.top == 10.0f);
    }

    // SECTION("Exception case") {
    //     REQUIRE_THROWS_AS(Phoenix::SensorArea(-1, 10, 0.0f, 10.0f, 0.0f, 10.0f),
    //                       std::invalid_argument);
    //     REQUIRE_THROWS_AS(Phoenix::SensorArea(10, -1, 0.0f, 10.0f, 0.0f, 10.0f),
    //                       std::invalid_argument);
    // }
}
