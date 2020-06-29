cmake_minimum_required(VERSION 3.15)
project(tcp_server VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

MACRO(ADD_SUBDIRS curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  FOREACH(child ${children})
    SET(DIR_ITEM ${curdir}/${child})
    IF(IS_DIRECTORY ${DIR_ITEM}
            AND NOT ("${DIR_ITEM}" STREQUAL "${PROJECT_SOURCE_DIR}/src/utils"))
        ADD_SUBDIRECTORY(${DIR_ITEM})
    ENDIF()
  ENDFOREACH()
ENDMACRO()

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src/utils)
ADD_SUBDIRS(${PROJECT_SOURCE_DIR}/src)