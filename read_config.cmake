# 检查my.config文件是否存在
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my.config")
    # 读取配置文件
    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/my.config" CONFIG_CONTENTS)

    # 解析配置
    foreach(LINE ${CONFIG_CONTENTS})
        # 跳过注释和空行
        if(NOT LINE MATCHES "^#" AND NOT LINE MATCHES "^[\t ]*$")
            # 分割KEY=VALUE
            string(REGEX MATCH "^([^=]+)=(.*)$" MATCH "${LINE}")

            if(MATCH)
                set(KEY ${CMAKE_MATCH_1})
                set(VALUE ${CMAKE_MATCH_2})

                # 去除空格
                string(STRIP "${KEY}" KEY)
                string(STRIP "${VALUE}" VALUE)
                
                # 处理环境变量
                if(VALUE MATCHES "\\$[A-Za-z0-9_]+")
                    string(REGEX MATCHALL "\\$([A-Za-z0-9_]+)" ENV_VARS "${VALUE}")
                    foreach(ENV_VAR ${ENV_VARS})
                        string(SUBSTRING ${ENV_VAR} 1 -1 ENV_NAME)
                        if(DEFINED ENV{${ENV_NAME}})
                            string(REPLACE ${ENV_VAR} $ENV{${ENV_NAME}} VALUE "${VALUE}")
                        endif()
                    endforeach()
                endif()
                
                # 设置变量
                set(${KEY} "${VALUE}" CACHE STRING "" FORCE)
            endif()
        endif()
    endforeach()
endif()

# 检查必要的变量是否设置
if(NOT DEFINED ROOT_DIR_EXPORT)
    set(ROOT_DIR_EXPORT ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

if(NOT DEFINED ROOT_DIR_3rdParty)
    set(ROOT_DIR_3rdParty ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

if(NOT DEFINED ROOT_DIR_BUILD)
    set(ROOT_DIR_BUILD ./build)
endif()

if(NOT DEFINED ROOT_DIR_EXPORT_LIB)
    set(ROOT_DIR_EXPORT_LIB ${ROOT_DIR_EXPORT}/Phoenix)
endif()
