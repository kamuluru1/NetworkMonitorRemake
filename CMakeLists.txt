cmake_minimum_required(VERSION 3.15)
project(NetworkMonitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Find dependencies
find_package(nlohmann_json REQUIRED)

# Create executable
add_executable(myapp src/main.cpp)

# Link libraries
target_link_libraries(myapp 
    nlohmann_json::nlohmann_json
    pcap
)