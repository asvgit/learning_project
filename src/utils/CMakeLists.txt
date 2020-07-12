set(TCP_PROJECT lib_tcp)

include_directories(include)

add_library(${TCP_PROJECT} SHARED
    src/io_socket.cpp
)
set_target_properties(${TCP_PROJECT} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    PUBLIC_HEADER
    include/tcp/io_socket.hpp
)