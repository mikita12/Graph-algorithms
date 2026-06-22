cmake_minimum_required(VERSION 3.16)
project(projekt2 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_compile_options(-Wall -Wextra -Werror) #warningi jako bledy

#lib
find_library(PARAM_LIB
    NAMES libparameters.so
    PATHS ${CMAKE_SOURCE_DIR}/lib
    REQUIRED
)


add_executable(projekt2 
    src/main.cpp
    util/Loader.cpp
)

target_include_directories(projekt2 PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/include/graph
    ${CMAKE_SOURCE_DIR}/include/structures
    ${CMAKE_SOURCE_DIR}/include/algorithms
    ${CMAKE_SOURCE_DIR}/util
)

target_link_libraries(projekt2 PRIVATE ${PARAM_LIB})

# Zeby binarka znalazla .so w runtime bez recznego LD_LIBRARY_PATH.
set_target_properties(projekt2 PROPERTIES
    BUILD_RPATH ${CMAKE_SOURCE_DIR}/lib
)