cmake_minimum_required(VERSION 3.15)
project(tcp_server VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

LIST(APPEND SKIP_LIST
    async
    simplest
    multithread
    misc
    bench
)

MACRO(ADD_SUBDIRS CURDIR)
    FILE(GLOB CHILDREN RELATIVE ${CURDIR} ${CURDIR}/*)
    FOREACH(CHILD ${CHILDREN})
        SET(DIR_ITEM ${CURDIR}/${CHILD})
        IF(IS_DIRECTORY ${DIR_ITEM} AND (NOT ${CHILD} IN_LIST SKIP_LIST))
            ADD_SUBDIRECTORY(${DIR_ITEM})
        ENDIF()
    ENDFOREACH()
ENDMACRO()

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src/utils)
LIST(APPEND SKIP_LIST utils)
ADD_SUBDIRS(${PROJECT_SOURCE_DIR}/src)