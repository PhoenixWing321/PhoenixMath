include(../../common.cmake)
project("PhoenixMath" VERSION 1.0.0)
message(">>============START phoenix/" ${PROJECT_NAME} " ===================")

file(GLOB_RECURSE SRC_DIR_LIST "*.cpp")

add_library(PhoenixMath STATIC ${SRC_DIR_LIST})
target_include_directories(PhoenixMath PUBLIC ./public ${ROOT_3rdParty}/eigen ${ROOT_3rdParty}/glm)

message("<<============END phoenix/" ${PROJECT_NAME} " ===================")
