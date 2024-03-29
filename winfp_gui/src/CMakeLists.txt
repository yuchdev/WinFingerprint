project(antios_gui)
set(TARGET antios_gui)

message("Setting CMake&Qt main variables")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
message("Setting output directory " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

message("Setting Qt dependencies")
set(QT_DEPENDENCIES Core Gui Widgets Qml Quick)
find_package(Qt5 REQUIRED ${QT_DEPENDENCIES})

message("Collecting source files")
file(GLOB SOURCE *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/${TARGET}/*.h *.qml qss/*.qss)

qt5_add_resources(RC ${CMAKE_CURRENT_SOURCE_DIR}/../antios.qrc)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/winfp/include 
)

add_executable(${TARGET} WIN32 ${SOURCE} ${RC})
add_dependencies(${TARGET} winfp)

target_link_libraries(${TARGET} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::Quick winfp)

# Set debugger working directory same as as solution directory
# Must be after adding executebale!
set_target_properties(${TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
set_property(TARGET ${TARGET} PROPERTY VS_USER_PROPS ${CMAKE_SOURCE_DIR}/.vc140.props)
