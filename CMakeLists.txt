cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google test" ON)

configure_file(version.hpp.in version.hpp)
include_directories(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(ip_filter_cli source/main.cpp)

add_library(ip_filter source/ip_filter.cpp)

# Add source to the include directories for the test target
target_include_directories(ip_filter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_include_directories(ip_filter PRIVATE "${CMAKE_BINARY_DIR}")

set_target_properties(ip_filter_cli ip_filter PROPERTIES
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

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT akms@bk.ru)
include(CPack)