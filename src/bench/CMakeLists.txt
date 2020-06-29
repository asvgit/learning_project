set(BENCH_NAME bench)
add_executable(${BENCH_NAME} mt.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${BENCH_NAME} ${CONAN_LIBS})
include_directories(include ../utils/include)