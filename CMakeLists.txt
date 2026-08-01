cmake_minimum_required(VERSION 3.14)
project(AfterMath VERSION 1.0.0 LANGUAGES CXX)

add_library(AfterMath INTERFACE)
target_include_directories(AfterMath INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(AfterMath INTERFACE cxx_std_14)

if(MSVC)
    target_compile_options(AfterMath INTERFACE /W3)
else()
    target_compile_options(AfterMath INTERFACE -Wall -Wextra)
endif()

include(GNUInstallDirs)
install(TARGETS AfterMath EXPORT AfterMathTargets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

enable_testing()
add_subdirectory(tests)
