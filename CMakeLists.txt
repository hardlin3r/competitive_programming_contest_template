cmake_minimum_required(VERSION 4.2 FATAL_ERROR)
project(yandex_algo_training LANGUAGES CXX)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)

# Disable compiler-specific extensions
# (e.g., use -std=c++20 instead of -std=gnu++20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make C++20 a requirement;
# the build will fail if the compiler doesn't support it
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

file(GLOB TEST_CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

foreach(SRC ${TEST_CPP_SOURCES})
  get_filename_component(TARGET_NAME ${SRC} NAME_WE)
  add_executable(${TARGET_NAME} ${SRC})
  target_link_libraries(${TARGET_NAME} PRIVATE GTest::gtest GTest::gtest_main)
  target_include_directories(${TARGET_NAME} PRIVATE src)
  gtest_discover_tests(${TARGET_NAME})
endforeach()

file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(SRC ${CPP_SOURCES})
  get_filename_component(TARGET_NAME ${SRC} NAME_WE)
  add_executable(${TARGET_NAME} ${SRC})
  target_include_directories(${TARGET_NAME} PRIVATE src)
endforeach()

file(GLOB CONTEST_CPP_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(SRC ${CONTEST_CPP_SOURCES})
  get_filename_component(NAME ${SRC} NAME_WE)

  set(SUBMIT_FILE ${CMAKE_BINARY_DIR}/submit_${NAME}.cpp)

  add_custom_command(
        OUTPUT ${SUBMIT_FILE}

        # Write header
        COMMAND ${CMAKE_COMMAND} -E cat
                ${CMAKE_SOURCE_DIR}/src/${NAME}.hpp
                > ${SUBMIT_FILE}

        # Append cpp without first line
        COMMAND sed 1d
                ${CMAKE_SOURCE_DIR}/src/${NAME}.cpp
                >> ${SUBMIT_FILE}

        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/${NAME}.cpp
            ${CMAKE_SOURCE_DIR}/src/${NAME}.hpp

        COMMENT "Generating submit_${NAME}.cpp"
        VERBATIM
    )

  add_custom_target(submit_${NAME} ALL
        DEPENDS ${SUBMIT_FILE}
    )
endforeach()

