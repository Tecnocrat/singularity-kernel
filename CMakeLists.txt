cmake_minimum_required(VERSION 3.16)
project(SingularityKernel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- VCPKG integration (auto-detect if not set) ---
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

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

# Threshold library
add_library(threshold_lib
    src/restore/threshold_manager.cpp
)
target_link_libraries(threshold_lib PRIVATE restore_lib)

# Main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE restore_lib threshold_lib)

# Test executable
add_executable(test_coherence tests/test_coherence.cpp)
target_link_libraries(test_coherence PRIVATE restore_lib threshold_lib)

target_include_directories(main PRIVATE src src/restore)
target_include_directories(test_coherence PRIVATE src src/restore)

# Add vcpkg include if available
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    get_filename_component(VCPKG_INCLUDE_DIR "${CMAKE_TOOLCHAIN_FILE}/../../installed/${VCPKG_TARGET_TRIPLET}/include" ABSOLUTE)
    include_directories(${VCPKG_INCLUDE_DIR})
endif()

enable_testing()
add_test(NAME test_coherence COMMAND test_coherence)

# Install schema files under ${CMAKE_INSTALL_BINDIR}/schema
install(DIRECTORY schema/ DESTINATION ${CMAKE_INSTALL_BINDIR}/schema)
