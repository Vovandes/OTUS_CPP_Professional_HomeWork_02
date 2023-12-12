cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google test" OFF)

configure_file(resources/version.hpp.in version.hpp)
configure_file(resources/ip_filter.tsv.in ip_filter.tsv)

add_executable(ip_filter_cli source/main.cpp)

add_library(ip_filter source/ip_filter.cpp)

# Add source to the include directories for the test target
target_include_directories(ip_filter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter_cli PRIVATE
    ip_filter
)

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    enable_testing()

    add_executable(test_ip_filter_gtest tests/test_ip_filter_gtest.cpp)

    set_target_properties(test_ip_filter_gtest PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_ip_filter_gtest
	    GTest::gtest_main
        ip_filter
    )

    gtest_discover_tests(test_ip_filter_gtest)
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ip_filter_cli PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ip_filter_cli PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)