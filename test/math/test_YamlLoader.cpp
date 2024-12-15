#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "loader/YamlLoader.h"
#include <fstream>

#include "../inside.hpp"

using namespace Phoenix;

// Helper function to create a test YAML file
void create_test_yaml(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    file << content;
    file.close();
}

TEST_CASE("YamlLoader::load_properties", "[YamlLoader]") {
    Phoenix::YamlLoader loader;
    std::string         testFilePath = "test.yaml";

    SECTION("Load properties from a valid YAML file") {
        create_test_yaml(testFilePath, "in: d:\\projects\\input\n"
                                       "out: d:\\projects\\output\n"
                                       "key1: value1\nkey2: value2");

        int result = loader.load_properties(testFilePath);
        REQUIRE(result == 0);

        REQUIRE(loader.get_data() != nullptr);
        auto properties = loader.get_properties();
        REQUIRE(properties != nullptr);
        REQUIRE(properties->get_property("key1") == "value1");
        REQUIRE(properties->get_property("key2") == "value2");
    }

    SECTION("Handle non-existent file") {
        int result = loader.load_properties("non_existent.yaml");
        REQUIRE(result == ErrorCode::Code_FILE_NOT_OPEN);
    }
}

TEST_CASE("YamlLoader::save_properties", "[YamlLoader]") {
    Phoenix::YamlLoader loader;
    std::string         testFilePath = "output.yaml";

    SECTION("Save properties to a YAML file") {
        auto properties = std::make_shared<PropertiesData>();
        properties->add_property("key1", "value1");
        properties->add_property("key2", "value2");
        properties->add_property("in", "d:\\projects\\input");
        properties->add_property("out", "d:\\projects\\output");

        loader.set_data(properties);

        int result = loader.save_properties(testFilePath);
        REQUIRE(result == 0);

        std::ifstream file(testFilePath);
        std::string   line;
        std::getline(file, line);
        REQUIRE(line == "key1: value1");
        std::getline(file, line);
        REQUIRE(line == "key2: value2");
        file.close();
    }

    SECTION("Handle null data") {
        loader.set_data(nullptr);
        int result = loader.save_properties(testFilePath);
        REQUIRE(result == ErrorCode::Code_E_POINTER);
    }
}