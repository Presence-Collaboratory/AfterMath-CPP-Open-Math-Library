file(GLOB_RECURSE TEST_SOURCES_CPP CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE TEST_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

file(GLOB_RECURSE AFTERMATH_HEADERS
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.inl
)

add_executable(AfterMathTests
    ${TEST_SOURCES_CPP}
    ${TEST_HEADERS}
    ${AFTERMATH_HEADERS}
)

target_link_libraries(AfterMathTests PRIVATE AfterMath)

if(MSVC)
    target_compile_options(AfterMathTests PRIVATE /arch:SSE4.2)
else()
    target_compile_options(AfterMathTests PRIVATE -msse4.2)
endif()

target_compile_features(AfterMathTests PRIVATE cxx_std_20)

set_source_files_properties(
    ${TEST_HEADERS}
    ${AFTERMATH_HEADERS}
    PROPERTIES HEADER_FILE_ONLY TRUE
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Tests" FILES ${TEST_SOURCES_CPP} ${TEST_HEADERS})

source_group(TREE ${CMAKE_SOURCE_DIR}/include PREFIX "AfterMath" FILES ${AFTERMATH_HEADERS})

enable_testing()
add_test(NAME AfterMathTests COMMAND AfterMathTests)
