cmake_minimum_required(VERSION 3.0)
project(tests-reg_file-wrapper CXX C)

set(BOOST_MIN_VERSION "1.61.0")
set(Boost_USE_STATIC_LIBS ON)
set(BOOST_ROOT "C:/Boost")

find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

if(${WIN32})
    set(CMAKE_CXX_FLAGS "/EHsc")
    set(MY_BOOST_DIR ${BOOST_ROOT})
    add_compile_options(/w4006)
    add_link_options("/FORCE:MULTIPLE")
    add_link_options("/IGNORE:4006")
    add_link_options("/IGNORE:4088")
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-DDEBUG)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
else()
    message(FATAL_ERROR "Non-windows configurations do not supported")
endif()

include_directories(C:/Boost/include)
include_directories(../)

link_directories(C:/Boost/lib/x86/lib)

add_executable(test_reg_file
        main.cpp
        ../regfile.cpp
        ../regfile.h
        ../utils/keys.h
        ../utils/types.h
        ../utils/utils.cpp
        ../utils/utils.h
        ../utils/win_registry_helper.cpp
        ../utils/win_registry_helper.h
        ../utils/win_system_information.cpp
        ../utils/win_system_information.h
        ../utils/win_errors.h
        ../utils/win_ptrs.h)

target_link_libraries(test_reg_file
        advapi32.lib
        rpcrt4.lib
        shell32.lib
        kernel32.lib
        libboost_unit_test_framework-vc142-mt-gd-x32-1_70.lib)