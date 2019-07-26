set(TARGET winfp)
 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../bin")

file(GLOB SOURCES *.cpp ../include/${TARGET}/*.h)
 
include_directories(
    ${Boost_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/winapi_helpers/include
)
 
add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} Secur32)
