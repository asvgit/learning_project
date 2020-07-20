cmake_minimum_required(VERSION 3.15)
project(tcp_server VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

LIST(APPEND SKIP_LIST
    async
    multithread
    bench
    simplest
)

MACRO(ADD_SUBDIRS CURDIR)
    FILE(GLOB CHILDREN RELATIVE ${CURDIR} ${CURDIR}/*)
    FOREACH(CHILD ${CHILDREN})
        IF(NOT ${CHILD} IN_LIST SKIP_LIST)
            MESSAGE("MSG " ${CHILD})
        ENDIF()
        SET(DIR_ITEM ${CURDIR}/${CHILD})
        IF(IS_DIRECTORY ${DIR_ITEM}
                AND NOT ("${DIR_ITEM}" STREQUAL "${PROJECT_SOURCE_DIR}/src/utils"))
            ADD_SUBDIRECTORY(${DIR_ITEM})
        ENDIF()
    ENDFOREACH()
ENDMACRO()

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src/utils)
LIST(APPEND SKIP_LIST utils)
ADD_SUBDIRS(${PROJECT_SOURCE_DIR}/src)