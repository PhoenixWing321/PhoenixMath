include(../../common.cmake)

add_executable(test_Tools "test_Tools.cpp")
target_link_libraries(test_Tools PhoenixMath)
add_test(NAME "test_Tools" COMMAND test_Tools)

# test_SensorArea
add_executable(test_SensorArea "test_SensorArea.cpp")
target_link_libraries(test_SensorArea PhoenixMath)
add_test(NAME "test_SensorArea" COMMAND test_SensorArea)
