include_directories(include ../utils/include)

set(SIMPLE_SERV simple_serv)
add_executable(${SIMPLE_SERV}
    simple_serv.cpp
    $<TARGET_OBJECTS:lib_tcp>
    $<TARGET_OBJECTS:lib_fs>
)
target_link_libraries(${SIMPLE_SERV} ${CONAN_LIBS})
set_target_properties(${SIMPLE_SERV}
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

set(SIMPLE_CLIENT simple_client)
add_executable(${SIMPLE_CLIENT} simple_client.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${SIMPLE_CLIENT} ${CONAN_LIBS})
set_target_properties(${SIMPLE_CLIENT}
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)