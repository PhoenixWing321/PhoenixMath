cmake_minimum_required(VERSION 3.10)

# 设置C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

# 使用来全局设置运行时库。
if(WIN32) 
elseif(APPLE)
  # add_compile_options(-Wall -Wextra -Werror) # 开启编译警告
endif()

# 包含的目录
include_directories(${ROOT_3rdParty} 
${ROOT_3rdParty}/glm)
