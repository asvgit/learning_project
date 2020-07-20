include_directories(include ../utils/include)

SET(ASYNC_MISC_PROJECT misc_async)
add_executable(${ASYNC_MISC_PROJECT}
    async.cpp
    $<TARGET_OBJECTS:lib_fs>
)
target_link_libraries(${ASYNC_MISC_PROJECT} ${CONAN_LIBS})
set_target_properties(${ASYNC_MISC_PROJECT}
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)