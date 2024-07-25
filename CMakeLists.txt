cmake_minimum_required(VERSION 3.10)

project(Plush VERSION 1.0 LANGUAGES C)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src/config
                    ${PROJECT_SOURCE_DIR}/src/core-utils
                    ${PROJECT_SOURCE_DIR}/src/def-plugins
                    ${PROJECT_SOURCE_DIR}/src/history)

# Find LuaJIT
find_package(PkgConfig REQUIRED)
pkg_search_module(LUAJIT REQUIRED luajit)

# Add the executable
add_executable(main
    src/main.c
    src/shell.c
    src/config/ApplyInit.c
    src/config/CheckConfigFile.c
    src/history/History.c
    src/config/ExistsInConfig.c
    src/def-plugins/autocomplete/autocomplete.c
    src/core-utils/ExposeCoreUtils.c
)

# Link libraries
target_link_libraries(main
    ${LUAJIT_LIBRARIES}
    dl
    m
)

# Include LuaJIT headers
target_include_directories(main PRIVATE ${LUAJIT_INCLUDE_DIRS})

