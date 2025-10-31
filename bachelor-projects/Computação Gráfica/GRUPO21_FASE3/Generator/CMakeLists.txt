cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} src/main.cpp src/box.cpp include/box.hpp src/cone.cpp include/cone.hpp src/model.cpp include/model.hpp src/plane.cpp include/plane.hpp src/point.cpp include/point.hpp src/sphere.cpp include/sphere.hpp src/cylinder.cpp include/cylinder.hpp src/torus.cpp include/torus.hpp src/bezier.cpp include/bezier.hpp src/util.cpp include/util.hpp)
