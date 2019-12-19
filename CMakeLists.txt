cmake_minimum_required(VERSION 3.5)

project(LogicGame LANGUAGES CXX)


set (CMAKE_PREFIX_PATH "C:\\Qt\\5.13.1\\msvc2017_64")


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
map.h map.cpp click.cpp click.h player.cpp player.h levels.h levels.cpp 
levels.ui resources.qrc icon/icon.rc)



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


target_link_libraries(LogicGame Qt5::Widgets)


add_custom_command(TARGET LogicGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:LogicGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:LogicGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:LogicGame>
    )



