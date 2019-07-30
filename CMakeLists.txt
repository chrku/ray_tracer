cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ray_tracer CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

add_executable(ray_tracer src/main.cpp
        src/file_formats/ImagePPM.h src/math/Vec3.h src/file_formats/ImagePPM.cpp
        src/math/Ray.h src/util/ColorBuffer.cpp src/util/ColorBuffer.h src/math/Sphere.h src/math/Hitable.h src/math/Camera.h src/SimpleRecursiveRayTracer.cpp src/SimpleRecursiveRayTracer.h src/math/HitableCollection.h src/math/Material.h src/math/Lambertian.h src/math/Metal.h src/math/Vec3.cpp src/math/Dielectric.h src/math/MovingSphere.h src/math/AABB.h)