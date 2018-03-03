cmake_minimum_required (VERSION 2.6)
project(webserver)

# debug flags
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g3 -Wall")

# includes
include_directories(src)
include_directories(asio-1.11.0/include)

# definitions
add_definitions(-DASIO_STANDALONE)

# sourses
file(GLOB SOURCES "src/*.cpp")

add_executable(final ${SOURCES})

# link libraries
target_link_libraries(final pthread)