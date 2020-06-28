cmake_minimum_required(VERSION 3.15)
project(tcp_server VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp io_socket.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

set(CLIENT_NAME tcp_client)
add_executable(${CLIENT_NAME} client.cpp io_socket.cpp)
target_link_libraries(${CLIENT_NAME} ${CONAN_LIBS})

set(BENCH_NAME bench)
add_executable(${BENCH_NAME} bench_client.cpp io_socket.cpp)
target_link_libraries(${BENCH_NAME} ${CONAN_LIBS})

set(FIRST_SERV one_tserv)
add_executable(${FIRST_SERV} one_tserv.cpp io_socket.cpp)
target_link_libraries(${FIRST_SERV} ${CONAN_LIBS})