#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "loader/MatrixLoader.h"
#include "shape/CoordsMatrixXf.h"

#include "../inside.hpp"

using namespace Phoenix;

TEST_CASE("CoordsMatrixXf fill_pattern test", "[matrix]") {
    SECTION("Default constructor") {
        CoordsMatrixXf matrix;
        CHECK(matrix.rows() == 0);
        CHECK(matrix.cols() == 0);
        CHECK(matrix.x_coords.size() == 0);
        CHECK(matrix.y_coords.size() == 0);
    }

    SECTION("fill_pattern") {

        CoordsMatrixXf matrix;
        matrix.fill_pattern();

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

TEST_CASE("CoordsMatrixXf file operations [format 0 Row-major]", "[matrix]") {
    CoordsMatrixXf matrix1;
    matrix1.fill_pattern();

    SECTION("Save and load success") {
        MatrixLoader loader;
        // Save to temporary file
        const std::string temp_file_format = "CoordsMatrixXf_format_0.txt";
        std::cout << "[Row-major]" << fs::absolute(temp_file_format).string() << std::endl;
        std::cout << " Display: (rows,cols)=", matrix1.dump(0);
        REQUIRE(loader.save(matrix1, temp_file_format, MatrixLoader::FORMAT_ROW_DEFAULT) ==
                MatrixLoader::SUCCESS);

        // load into new matrix
        CoordsMatrixXf matrix2;
        REQUIRE(loader.load(matrix2, temp_file_format, MatrixLoader::FORMAT_ROW_DEFAULT) ==
                MatrixLoader::SUCCESS);

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
        CoordsMatrixXf matrix;
        MatrixLoader   loader;

        // Test FILE_NOT_OPEN error
        CHECK(loader.load(matrix, "non_existent_file.txt") == MatrixLoader::FILE_NOT_OPEN);
        CHECK(loader.save(matrix1, "/invalid/path/file.txt") == MatrixLoader::FILE_NOT_OPEN);

        // Test INVALID_DIMENSIONS error
        {
            std::ofstream bad_file("bad_dimensions.txt");
            bad_file << "-1\t-1\n";
            bad_file.close();
            CHECK(loader.load(matrix, "bad_dimensions.txt") == MatrixLoader::INVALID_DIMENSIONS);
            std::remove("bad_dimensions.txt");
        }

        // Test READ_ERROR with corrupted file
        {
            std::ofstream bad_file("corrupted.txt");
            bad_file << "6\t11\nnotanumber";
            bad_file.close();
            CHECK(loader.load(matrix, "corrupted.txt") == MatrixLoader::READ_ERROR);
            std::remove("corrupted.txt");
        }
    }
}

TEST_CASE("CoordsMatrixXf file operations [format 1 Column-major]", "[matrix]") {
    CoordsMatrixXf matrix1;
    matrix1.fill_pattern();

    SECTION("Save and load success") {
        MatrixLoader loader;

        const std::string temp_file = "CoordsMatrixXf_format_1.txt";
        REQUIRE(loader.save(matrix1, temp_file, MatrixLoader::FORMAT_COL_COORD_FIRST) ==
                MatrixLoader::SUCCESS);

        // load into new matrix
        CoordsMatrixXf matrix2;
        REQUIRE(loader.load(matrix2, temp_file, MatrixLoader::FORMAT_COL_COORD_FIRST) ==
                MatrixLoader::SUCCESS);

        std::cout << "[Column-major]" << fs::absolute(temp_file).string() << std::endl;
        std::cout << " Display : (rows,cols)=", matrix2.dump(1);
    }
}

TEST_CASE("CoordsMatrixXf data validation", "[CoordsMatrixXf]") {
    CoordsMatrixXf matrix;
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