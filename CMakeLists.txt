cmake_minimum_required(VERSION 3.15)
project(tcp_server VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp io_socket.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

set(CLIENT_NAME tcp_client)
add_executable(${CLIENT_NAME} client.cpp io_socket.cpp)
target_link_libraries(${CLIENT_NAME} ${CONAN_LIBS})
