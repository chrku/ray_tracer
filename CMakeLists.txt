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
        src/math/Ray.h src/util/ColorBuffer.cpp src/util/ColorBuffer.h src/shapes/Sphere.h src/shapes/Hitable.h src/math/Camera.h src/SimpleRecursiveRayTracer.cpp src/SimpleRecursiveRayTracer.h src/shapes/HitableCollection.h src/materials/Material.h src/materials/Lambertian.h src/materials/Metal.h src/math/Vec3.cpp src/materials/Dielectric.h src/shapes/MovingSphere.h src/math/AABB.h src/math/BVH.h src/util/Texture.cpp src/util/Texture.h src/math/PerlinNoiseGenerator.cpp src/math/PerlinNoiseGenerator.h src/util/SceneGenerator.cpp src/util/SceneGenerator.h src/util/stb_image.h src/util/stb_image.cpp src/materials/DiffuseLight.h src/shapes/AARect.h src/shapes/Box.h src/shapes/transformations/FlipNormals.h src/shapes/transformations/Translate.h)