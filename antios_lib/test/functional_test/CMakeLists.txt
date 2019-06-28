set(TARGET antios_lib_functional_test)

find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS unit_test_framework date_time REQUIRED) 

file(GLOB SOURCES *.cpp)
 
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} ${Boost_LIBRARIES} antios_lib)
add_test(NAME ${TARGET} COMMAND ${TARGET})
