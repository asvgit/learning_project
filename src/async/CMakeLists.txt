SET(MT_PROJECT async_serv)

add_executable(${PROJECT_NAME} async_serv.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
include_directories(include ../utils/include)