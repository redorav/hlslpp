cmake_minimum_required(VERSION 3.15)

project(hlslpp LANGUAGES CXX)

# Create an interface library for header-only usage
add_library(hlslpp INTERFACE)

# Specify include directories
target_include_directories(hlslpp
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # headers for this build
        $<INSTALL_INTERFACE:include>                           # headers for installed targets
)

# Installation rules
include(GNUInstallDirs)

install(TARGETS hlslpp
    EXPORT hlslppTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export config for find_package
install(EXPORT hlslppTargets
    FILE hlslppConfig.cmake
    NAMESPACE hlslpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/hlslpp
)