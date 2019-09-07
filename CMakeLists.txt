cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(FinalProject LANGUAGES CXX)
add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp mainwindow.hpp mainwindow.ui)
include(FindPkgConfig)
pkg_check_modules(ImageMagick IMPORTED_TARGET Magick++)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_std_17)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets PkgConfig::ImageMagick)
