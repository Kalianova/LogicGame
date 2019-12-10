cmake_minimum_required(VERSION 3.5)

project(LogicGame LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_BINARY_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SRC_FILES createmap.cpp createmap.h createmap.ui gamewindow.cpp gamewindow.h gamewindow.ui
globals.cpp globals.h main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
map.h map.cpp click.cpp click.h player.cpp player.h dialog.cpp
dialog.h dialog.ui levels.h levels.cpp levels.ui resources.qrc)



if (WIN32)
  add_executable(LogicGame WIN32 ${SRC_FILES})
else()
  add_executable(LogicGame ${SRC_FILES})
endif()

if(DEFINED DATA_INSTALL_DIR)
	set(relResPath ${DATA_INSTALL_DIR})
	add_definitions(-DDATA_INSTALL_DIR="${DATA_INSTALL_DIR}/")
else(DEFINED DATA_INSTALL_DIR)
	set(relResPath res/)
endif(DEFINED DATA_INSTALL_DIR)

install(DIRECTORY
       image
DESTINATION ${relResPath})

target_link_libraries(LogicGame Qt5::Widgets)



