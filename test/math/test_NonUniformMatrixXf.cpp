#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "shape/NonUniformMatrixXf.h"

#include "../inside.hpp"

using namespace Phoenix;

TEST_CASE("NonUniformMatrixXf fill_pattern test", "[matrix]") {
    SECTION("Default constructor") {
        NonUniformMatrixXf matrix;
        CHECK(matrix.rows() == 0);
        CHECK(matrix.cols() == 0);
        CHECK(matrix.x_coords.size() == 0);
        CHECK(matrix.y_coords.size() == 0);
    }

    SECTION("fill_pattern") {

        NonUniformMatrixXf matrix;
        matrix.fill_pattern();
        std::cout << matrix << std::endl;

        // Check dimensions
        CHECK(matrix.rows() == 6);
        CHECK(matrix.cols() == 11);
        CHECK(matrix.x_coords.size() == 11);
        CHECK(matrix.y_coords.size() == 6);

        // Check x coordinates
        CHECK(matrix.x_coords(0) == 0.0f);
        CHECK(matrix.x_coords(1) == 2.0f);
        CHECK(matrix.x_coords(10) == 90.0f);

        // Check y coordinates
        CHECK(matrix.y_coords(0) == 0.0f);
        CHECK(matrix.y_coords(1) == 1.0f);
        CHECK(matrix.y_coords(5) == 45.0f);

        // Check some matrix values
        CHECK(matrix(0, 0) == 0.0f);   // Top-left
        CHECK(matrix(0, 10) == 18.0f); // Top-right
        CHECK(matrix(5, 10) == 20.0f); // Bottom-right
        CHECK(matrix(2, 3) == 7.5f);   // Middle value

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
}

TEST_CASE("NonUniformMatrixXf file operations", "[matrix]") {
    NonUniformMatrixXf matrix1;
    matrix1.fill_pattern();

    SECTION("Save and load success") {
        // Save to temporary file
        const std::string temp_file = "NonUniformMatrixXf.txt";
        std::cout << "temp_file: " << fs::absolute(temp_file).string() << std::endl;
        REQUIRE(matrix1.save(temp_file) == NonUniformMatrixXf::SUCCESS);

        // load into new matrix
        NonUniformMatrixXf matrix2;
        REQUIRE(matrix2.load(temp_file) == NonUniformMatrixXf::SUCCESS);

        // Verify dimensions
        CHECK(matrix2.rows() == matrix1.rows());
        CHECK(matrix2.cols() == matrix1.cols());

        // Verify x coordinates
        for (int j = 0; j < matrix1.cols(); ++j) {
            CHECK(matrix2.x_coords(j) == matrix1.x_coords(j));
        }

        // Verify y coordinates
        for (int i = 0; i < matrix1.rows(); ++i) {
            CHECK(matrix2.y_coords(i) == matrix1.y_coords(i));
        }

        // Verify matrix values
        for (int i = 0; i < matrix1.rows(); ++i) {
            for (int j = 0; j < matrix1.cols(); ++j) {
                CHECK(matrix2(i, j) == matrix1(i, j));
            }
        }

        // Cleanup
        // std::remove(temp_file.c_str());
    }

    SECTION("File operation errors") {
        NonUniformMatrixXf matrix;

        // Test FILE_NOT_OPEN error
        CHECK(matrix.load("non_existent_file.txt") == NonUniformMatrixXf::FILE_NOT_OPEN);
        CHECK(matrix1.save("/invalid/path/file.txt") == NonUniformMatrixXf::FILE_NOT_OPEN);

        // Test INVALID_DIMENSIONS error
        {
            std::ofstream bad_file("bad_dimensions.txt");
            bad_file << "-1\t-1\n";
            bad_file.close();
            CHECK(matrix.load("bad_dimensions.txt") == NonUniformMatrixXf::INVALID_DIMENSIONS);
            std::remove("bad_dimensions.txt");
        }

        // Test READ_ERROR with corrupted file
        {
            std::ofstream bad_file("corrupted.txt");
            bad_file << "6\t11\nnotanumber";
            bad_file.close();
            CHECK(matrix.load("corrupted.txt") == NonUniformMatrixXf::READ_ERROR);
            std::remove("corrupted.txt");
        }
    }
}

TEST_CASE("NonUniformMatrixXf output format", "[NonUniformMatrixXf]") {
    NonUniformMatrixXf matrix;
    matrix.fill_pattern();

    std::ostringstream oss;
    oss << matrix;
    std::string output = oss.str();

    // Check first line (dimensions)
    CHECK(output.substr(0, output.find('\n')) == "6\t11");

    // Check if output contains specific values
    CHECK(output.find("0.0") != std::string::npos);
    CHECK(output.find("90.0") != std::string::npos);
    CHECK(output.find("45.0") != std::string::npos);

    // Check formatting
    CHECK(output.find("\t") != std::string::npos); // Contains tabs
    CHECK(output.find(".0") != std::string::npos); // Contains decimal points
}

TEST_CASE("NonUniformMatrixXf data validation", "[NonUniformMatrixXf]") {
    NonUniformMatrixXf matrix;
    matrix.fill_pattern();

    SECTION("Monotonicity check") {
        // Check x coordinates are increasing
        for (int j = 1; j < matrix.x_coords.size(); ++j) {
            CHECK(matrix.x_coords(j) > matrix.x_coords(j - 1));
        }

        // Check y coordinates are increasing
        for (int i = 1; i < matrix.y_coords.size(); ++i) {
            CHECK(matrix.y_coords(i) > matrix.y_coords(i - 1));
        }
    }

    SECTION("Value range check") {
        // All values should be between 0 and 20
        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.cols(); ++j) {
                CHECK(matrix(i, j) >= 0.0f);
                CHECK(matrix(i, j) <= 20.0f);
            }
        }
    }
}