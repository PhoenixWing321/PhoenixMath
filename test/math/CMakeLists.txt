include(../../common.cmake)

# === test ===
add_executable(test_Tools "test_Tools.cpp")
target_link_libraries(test_Tools PhoenixMath)
add_test(NAME "test_Tools" COMMAND test_Tools)

# === test ===
add_executable(test_BoundedMatrixXf "test_BoundedMatrixXf.cpp")
target_link_libraries(test_BoundedMatrixXf PhoenixMath)
add_test(NAME "test_BoundedMatrixXf" COMMAND test_BoundedMatrixXf)

# === test ===
add_executable(test_Bounds2f "test_Bounds2f.cpp")
target_link_libraries(test_Bounds2f PhoenixMath)
add_test(NAME "test_Bounds2f" COMMAND test_Bounds2f)

# === test ===
add_executable(test_CoordsMatrixXf "test_CoordsMatrixXf.cpp")
target_link_libraries(test_CoordsMatrixXf PhoenixMath)
add_test(NAME "test_CoordsMatrixXf" COMMAND test_CoordsMatrixXf)

# === test ===
add_executable(test_MatrixFormatHandler "test_MatrixFormatHandler.cpp")
target_link_libraries(test_MatrixFormatHandler PhoenixMath)
add_test(NAME "test_MatrixFormatHandler" COMMAND test_MatrixFormatHandler)
