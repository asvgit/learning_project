include_directories(include ./include)
include_directories(include ../utils/include)

SET(ASYNC_PROJECT async_serv)
add_executable(${ASYNC_PROJECT} async_serv.cpp async.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${ASYNC_PROJECT} ${CONAN_LIBS})

SET(ASYNC_MT_PROJECT async_mt_serv)
add_executable(${ASYNC_MT_PROJECT} async_mt_serv.cpp async.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${ASYNC_MT_PROJECT} ${CONAN_LIBS})