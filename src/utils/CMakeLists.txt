include_directories(include)

set(TCP_PROJECT lib_tcp)
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

set(FS_PROJECT lib_fs)
add_library(${FS_PROJECT} SHARED
    src/io_file.cpp
)
target_link_libraries(${FS_PROJECT} ${CONAN_LIBS})
set_target_properties(${FS_PROJECT} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    PUBLIC_HEADER
    include/fs/io_file.hpp
)