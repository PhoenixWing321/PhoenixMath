include(../../common.cmake)

add_executable(test_Tools "test_Tools.cpp")
target_link_libraries(test_Tools PhoenixMath)
add_test(NAME "test_Tools" COMMAND test_Tools)

# test_MatrixRegion
add_executable(test_MatrixRegion "test_MatrixRegion.cpp")
target_link_libraries(test_MatrixRegion PhoenixMath)
add_test(NAME "test_MatrixRegion" COMMAND test_MatrixRegion)

# Bounds2f
add_executable(test_Bounds2f "test_Bounds2f.cpp")
target_link_libraries(test_Bounds2f PhoenixMath)
add_test(NAME "test_Bounds2f" COMMAND test_Bounds2f)
