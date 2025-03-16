cmake_minimum_required(VERSION 3.10)
project(backend)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Add Crow from local directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Crow)

# Add an executable
add_executable(backend main.cpp)

# Link libraries
target_link_libraries(backend PRIVATE 
    Crow
    Threads::Threads
    Boost::system
)

# Include directories
target_include_directories(backend PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Crow/include
)

# Install target
install(TARGETS backend DESTINATION bin)

# Output directory
set_target_properties(backend PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add compile options
target_compile_options(backend PRIVATE -Wall -Wextra)
