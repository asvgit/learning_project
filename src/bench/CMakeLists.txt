include_directories(include ../utils/include)

set(BENCH_NAME bench)
add_executable(${BENCH_NAME} mt.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${BENCH_NAME} ${CONAN_LIBS})

set(BENCH_ASYNC_NAME bench_async)
add_executable(${BENCH_ASYNC_NAME} async.cpp $<TARGET_OBJECTS:lib_tcp>)
target_link_libraries(${BENCH_ASYNC_NAME} ${CONAN_LIBS})