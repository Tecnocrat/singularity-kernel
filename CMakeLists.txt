cmake_minimum_required(VERSION 3.16)
project(SingularityKernel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(OpenCV REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Restore library
add_library(restore_lib
    src/restore/restore_coherence.cpp
    src/seed.h
    src/coherence.h
    src/phantom.h
)
target_include_directories(restore_lib PUBLIC src src/restore)
target_link_libraries(restore_lib PUBLIC ${OpenCV_LIBS} nlohmann_json::nlohmann_json)

# Main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE restore_lib)

# Test executable
add_executable(test_coherence tests/test_coherence.cpp)
target_link_libraries(test_coherence PRIVATE restore_lib)

enable_testing()
add_test(NAME test_coherence COMMAND test_coherence)
