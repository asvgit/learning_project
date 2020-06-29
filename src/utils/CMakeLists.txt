set(TCP_PROJECT lib_tcp)

include_directories(include)

add_library(${TCP_PROJECT} SHARED
    src/io_socket.cpp
)
set_target_properties(${TCP_PROJECT} PROPERTIES PUBLIC_HEADER
    include/tcp/io_socket.hpp
)