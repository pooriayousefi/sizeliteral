cmake_minimum_required(VERSION 3.20)
project(sizeliteral
    VERSION 1.0.0
    DESCRIPTION "Modern C++ header-only library"
    HOMEPAGE_URL "https://github.com/pooriayousefi/sizeliteral"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only library target
add_library(sizeliteral INTERFACE)
target_include_directories(sizeliteral INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Set interface properties
target_compile_features(sizeliteral INTERFACE cxx_std_20)

# Platform-specific compile definitions
if(WIN32)
    target_compile_definitions(sizeliteral INTERFACE _WIN32_WINNT=0x0601)
endif()

# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS sizeliteral
    EXPORT sizeliteralTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/sizeliteral.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    OPTIONAL
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/sizeliteral.ixx
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    OPTIONAL
)

# Export targets
install(EXPORT sizeliteralTargets
    FILE sizeliteralTargets.cmake
    NAMESPACE sizeliteral::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sizeliteral
)

# Create package config
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sizeliteralConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sizeliteralConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sizeliteral
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/sizeliteralConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/sizeliteralConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/sizeliteralConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sizeliteral
)

# Configuration summary
message(STATUS "sizeliteral Configuration Summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
