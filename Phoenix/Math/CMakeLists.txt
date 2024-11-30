include(../../common.cmake)
project("PhoenixMath" VERSION 1.0.0)
message(">>============START phoenix/" ${PROJECT_NAME} " ===================")

include_directories(
  ${ROOT_3rdParty}/spdlog/include
  ${ROOT_3rdParty}/json/include
  ${ROOT_3rdParty}/eigen
  ./public
)

file(GLOB_RECURSE SRC_DIR_LIST "*.cpp")

add_library(PhoenixMath ${SRC_DIR_LIST})
target_include_directories(PhoenixMath PUBLIC ./public)

message("<<============END phoenix/" ${PROJECT_NAME} " ===================")
