CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(maybewm)

SET(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(Boost 1.78 COMPONENTS log REQUIRED)

SET(PROJECT_LIBS ${Boost_LIBRARIES} xcb xcb-util)

ADD_EXECUTABLE(maybewm main.cpp WindowManager.cpp WindowManager.h EventNames.h)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(maybewm ${PROJECT_LIBS})
