cmake_minimum_required(VERSION 3.10)
project("phoenix_root" VERSION 1.0.0)

# 3rdParty======================
if(MSVC)
  add_compile_options(/utf-8)
endif()

include(read_config.cmake)

# print config
message(STATUS "Config loaded:")
message(STATUS "  ROOT_DIR_3rdParty: ${ROOT_DIR_3rdParty}") 


add_subdirectory(math)

# test 
enable_testing()
add_subdirectory(test/math) 