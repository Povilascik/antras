cmake_minimum_required(VERSION 3.29)
project(pirmas)

set(CMAKE_CXX_STANDARD 14)

add_executable(saugojimas_masyve
    saugojimas_masyve.cpp
    saugojimas_masyve.h)
add_executable(programa
    pirma_uzd.cpp
        duomenys.cpp
        duomenys.h
        zmogus.h
)
# Set Release build type with optimizations
set(CMAKE_BUILD_TYPE Release)

# Add compiler-specific optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/")
target_compile_definitions(programa PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")

#-----------------------------------------------------------------

# Include FetchContent module
include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(Studentai_tests
        Studentai_test.cpp
        duomenys.cpp
        zmogus.h
)

# Link against Google Test
target_link_libraries(Studentai_tests PRIVATE
        gtest
        gtest_main
)

set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/")
target_compile_definitions(Studentai_tests PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")

enable_testing()
add_test(NAME StudentaiTests COMMAND studentai_tests)