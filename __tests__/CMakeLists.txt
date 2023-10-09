
cmake_minimum_required(VERSION 3.15)
SET(PROJECT_NAME llama_tests)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(INCLUDE_DIR ./../party_llama)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

project(
  ${PROJECT_NAME}
)

add_executable(
  ${PROJECT_NAME}
  testing.cpp
)

add_subdirectory(immediate_events)
add_subdirectory(async_events)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
  GTest::gmock_main
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ./
  ${INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} )


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")