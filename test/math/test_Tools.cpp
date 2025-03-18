#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "Phoenix/utility/Tools.h"

#include "../inside.hpp"

using namespace Phoenix;

// command for detail
// ./test_Tools --success -r compact
//------------------------------------------------
int test_build(const std::string& startPath) {
    std::cout << "[trace] startPath   :" << startPath << std::endl;
    std::string buildPath = Tools::find_build_directory(startPath);

    if (buildPath == "") {
        std::cout << "[trace] No build directory found" << std::endl;
    }
    else {
        std::cout << "[trace] Build directory:" << buildPath << std::endl;
    }
    return 0;
}
//------------------------------------------------
TEST_CASE("util::find_build_directory()", "[find]") {
    test_build("/Users/xxx/workspace/PhoenixMath/build/test/math");

    std::cout << "[utility] " << Tools::path_project << std::endl;
    std::cout << "[utility] " << Tools::path_build << std::endl;
}
