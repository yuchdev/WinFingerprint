cmake_minimum_required(VERSION 3.0)
project(win_fingerprint)

set(TARGET win_fingerprint)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

if(WIN32)
    message("Windows configuraion: enable all exceptions, all warnings")
    set(MY_BOOST_DIR ${WINDOWS_BOOST_DIR})
    set(CMAKE_CXX_FLAGS "/EHa /W1 /MP")    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

    # define WIN32 macro version
    macro(get_WIN32_WINNT version)
        if (WIN32 AND CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REPLACE "." "" ver ${ver})
            string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})

            set(${version} "0x${ver}")
        endif()
    endmacro()

    message("Set WINVER: " ver)
    message("Set SCL_SECURE_NO_WARNINGS")
    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)

    # Use folders to sort out projects in VS solution
    SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
else()
    message(FATAL_ERROR "This is Windows only project") 
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE *.cpp *.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/Fingerprints/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/Fingerprints/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/plog/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/plog/Appenders/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/plog/Converters/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/plog/Formatters/*.h )

add_executable(${TARGET} ${SOURCE})
target_link_libraries(${TARGET} advapi32 rpcrt4 shell32 kernel32)
