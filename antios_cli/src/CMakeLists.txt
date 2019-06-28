set(TARGET antios_cli)

find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS program_options REQUIRED) 
file(GLOB SOURCES *.cpp ../include/${TARGET}/*.h)
 
include_directories(${Boost_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/antios_lib/include 
    ${CMAKE_SOURCE_DIR}
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} 
    ${Boost_LIBRARIES} 
    antios_lib
)

add_dependencies(${TARGET} antios_lib)
