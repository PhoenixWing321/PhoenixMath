cmake_minimum_required(VERSION 3.10)

# 设置C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

# 包含的目录
include_directories(${ROOT_DIR_3rdParty} 
${ROOT_DIR_3rdParty}/glm
${ROOT_DIR_3rdParty}/eigen
${ROOT_DIR_3rdParty}/Catch2_Single)
