cmake_minimum_required(VERSION 3.10)
project("phoenix_root" VERSION 1.0.0)

# 3rdParty======================
set(ROOT_3rdParty ${CMAKE_CURRENT_SOURCE_DIR}/../Phoenix3rdParty)

add_subdirectory(Phoenix)

# test 
enable_testing()
add_subdirectory(test/math) 