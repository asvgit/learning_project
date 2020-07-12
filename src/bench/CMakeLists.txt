include_directories(include ../utils/include)
include_directories(include ./include)

set(BENCH_NAME bench)
add_executable(${BENCH_NAME} mt.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${BENCH_NAME} ${CONAN_LIBS})
set_target_properties(${BENCH_NAME}
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)