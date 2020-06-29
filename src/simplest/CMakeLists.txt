include_directories(include ../utils/include)

set(SIMPLE_SERV simple_serv)
add_executable(${SIMPLE_SERV} simple_serv.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${SIMPLE_SERV} ${CONAN_LIBS})

set(SIMPLE_CLIENT simple_client)
add_executable(${SIMPLE_CLIENT} simple_client.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${SIMPLE_CLIENT} ${CONAN_LIBS})