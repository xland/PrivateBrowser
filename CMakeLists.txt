cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(PrivateBrowser LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/tool/FUCK/6.7.0/msvc2019_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Widgets WebEngineWidgets) # Qt COMPONENTS

qt6_add_resources(QRC_FILES ./res/res.qrc)
aux_source_directory(./src srcs)

# Specify MSVC UTF-8 encoding
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    ${srcs}
    ${QRC_FILES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Network Qt6::WebEngineWidgets Dwmapi kernel32 user32 shell32)