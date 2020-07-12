SET(MT_PROJECT mt_serv)

add_executable(${MT_PROJECT} mt_serv.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${MT_PROJECT} ${CONAN_LIBS})
include_directories(include ../utils/include)
set_target_properties(${MT_PROJECT}
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)