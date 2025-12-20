cmake_minimum_required(VERSION 3.22)

include(cmake/modules.cmake)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # as root project
    include(cmake/AppBuild.cmake)
else()
    # when included in another project
    include(cmake/LibBuild.cmake)
endif()