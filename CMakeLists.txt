cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ray_tracer CXX)

add_executable(ray_tracer src/main.cpp src/file_formats/ImagePPM.h src/util/Color.h)