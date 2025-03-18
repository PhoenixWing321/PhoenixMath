include(../common.cmake)
project("PhoenixMath" VERSION 1.0.0)
message(">>============START phoenix/" ${PROJECT_NAME} " ===================")

file(GLOB_RECURSE SRC_DIR_LIST "*.cpp")

# 输出c++标准版本
message(">> C++ Standard: ${CMAKE_CXX_STANDARD}")  

add_library(PhoenixMath STATIC ${SRC_DIR_LIST})
target_include_directories(PhoenixMath PUBLIC ./ ${ROOT_DIR_3rdParty}/eigen ${ROOT_DIR_3rdParty}/glm)

message("<<============END phoenix/" ${PROJECT_NAME} " ===================")
