//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_UTIL_H
#define RAY_TRACER_UTIL_H

float lerp(float a, float b, float t) {
  return (1 - t) * a + t * b;
}

#endif //RAY_TRACER_UTIL_H
