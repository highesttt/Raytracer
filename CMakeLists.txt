cmake_minimum_required(VERSION 3.24)

project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_library(${PROJECT_NAME}_lib STATIC

        src/Raytracer.cpp
        src/Object.cpp
        src/Output.cpp
        src/Utils.cpp
        src/Color.cpp
        src/Factory.cpp
        src/Config.cpp

        math/src/Point.cpp
        math/src/Material.cpp
        math/src/Shapes.cpp
)


target_include_directories(${PROJECT_NAME}_lib PUBLIC include math/include output/include)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE config++)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_executable(${PROJECT_NAME}_test EXCLUDE_FROM_ALL test/test.cpp)

#     target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME}_lib)
#     target_include_directories(${PROJECT_NAME}_test PRIVATE include)

#     #GoogleTest
#     include(FetchContent)
#     FetchContent_Declare(
#         googletest
#         GIT_REPOSITORY https://github.com/google/googletest.git
#         GIT_VERSION v1.13.0
#     )
#     FetchContent_MakeAvailable(googletest)
#     include(GoogleTest)
#     target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest_main)
#     gtest_discover_tests(${PROJECT_NAME}_test)
# endif()