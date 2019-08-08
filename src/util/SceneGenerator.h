//
// Created by christoph on 08.08.19.
//

#ifndef RAY_TRACER_SCENEGENERATOR_H
#define RAY_TRACER_SCENEGENERATOR_H


#include "../shapes/HitableCollection.h"

class SceneGenerator {
public:
    SceneGenerator();
    void twoPerlinSpheres(HitableCollection& h);
    void earthScene(HitableCollection& h);
    void simpleLight(HitableCollection& h);
private:
    float getRandom();
    std::mt19937 rng_;
};


#endif //RAY_TRACER_SCENEGENERATOR_H
