#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Phoenix/shape/Bounds2f.hpp"

#include "../inside.hpp"

// command for detail
// ./test_Bounds2f --success -r compact

TEST_CASE("Bounds2f expand", "[Bounds2f]") {
    SECTION("Basic case") {
        Phoenix::Bounds2f bounds(glm::vec2(0.0f, 0.0f), glm::vec2(5.0f, 5.0f));
        bounds.expand(glm::vec2(6.0f, 6.0f));
        REQUIRE(bounds.b_min == glm::vec2(0.0f, 0.0f));
        REQUIRE(bounds.b_max == glm::vec2(6.0f, 6.0f));
    }

    SECTION("Boundary case") {
        Phoenix::Bounds2f bounds(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
        bounds.expand(glm::vec2(-2.0f, -2.0f));
        REQUIRE(bounds.b_min == glm::vec2(-2.0f, -2.0f));
        REQUIRE(bounds.b_max == glm::vec2(1.0f, 1.0f));
    }

    SECTION("Expand with other bounds") {
        Phoenix::Bounds2f bounds1;
        bounds1.b_min = {1.0f, 2.0f};
        bounds1.b_max = {3.0f, 4.0f};

        Phoenix::Bounds2f bounds2;
        bounds2.b_min = {0.5f, 1.5f};
        bounds2.b_max = {2.5f, 3.5f};

        bounds1.expand(bounds2);

        REQUIRE(bounds1.b_min == glm::vec2(0.5f, 1.5f));
        REQUIRE(bounds1.b_max == glm::vec2(3.0f, 4.0f));
    }
}
