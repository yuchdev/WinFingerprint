set(TARGET antios_lib)
 
file(GLOB SOURCES 
    *.cpp 
    ../include/${TARGET}/*.h
    # TEMPORARY
    ${CMAKE_SOURCE_DIR}/utils/*.cpp
)
 
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}
)
 
add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} advapi32 rpcrt4 shell32 kernel32)
