SET(MT_PROJECT mt_serv)

add_executable(${MT_PROJECT} mt_serv.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${MT_PROJECT} ${CONAN_LIBS})
include_directories(include ../utils/include)