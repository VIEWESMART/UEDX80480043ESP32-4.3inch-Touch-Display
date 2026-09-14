cmake_minimum_required(VERSION 3.16)
set(SDKCONFIG_DEFAULTS
    "${CMAKE_CURRENT_LIST_DIR}/sdkconfig.defaults"
)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(07_squareline_coffee)
