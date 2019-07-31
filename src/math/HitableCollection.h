//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_HITABLECOLLECTION_H
#define RAY_TRACER_HITABLECOLLECTION_H

#include <memory>
#include <vector>
#include <limits>
#include <algorithm>

#include "Hitable.h"

class HitableCollection : public Hitable {
public:
    HitableCollection() = default;

    template<typename HITABLE_IMPL>
    void addHitable(HITABLE_IMPL &&hitable) {
        hitables.push_back(std::make_shared<HITABLE_IMPL>(hitable));
    }
    std::size_t length() const {
        return hitables.size();
    }

    bool hit(const Ray &ray, float t_min, float t_max, HitRecord &record) const override {
        return Hitable::hitCollection(hitables.begin(), hitables.end(), ray,
                                      t_min, t_max, record);
    }
    bool boundingBox(float t0, float t1, AABB& box) const override {
        if (hitables.empty())
            return false;
        else {
            AABB initial_box{};
            hitables[0]->boundingBox(t0, t1, initial_box);
            for (int i = 1; i < hitables.size(); ++i) {
                AABB current_box;
                hitables[i]->boundingBox(t0, t1, current_box);
                initial_box = AABB::surroundingBox(initial_box, current_box);
            }
            box = initial_box;
            return true;
        }
    }

    void sortByXAxis() {
        std::sort(hitables.begin(), hitables.end(),
                  [](auto a, auto b) -> bool {
                      AABB box_left{}, box_right{};
                      a->boundingBox(0, 0, box_left);
                      b->boundingBox(0, 0, box_right);
                      return box_left.min().x() < box_right.min().x();
                  });
    }

    void sortByYAxis() {
        std::sort(hitables.begin(), hitables.end(),
                  [](auto a, auto b) -> bool {
                      AABB box_left{}, box_right{};
                      a->boundingBox(0, 0, box_left);
                      b->boundingBox(0, 0, box_right);
                      return box_left.min().y() < box_right.min().y();
                  });
    }

    void sortByZAxis() {
        std::sort(hitables.begin(), hitables.end(),
                  [](auto a, auto b) -> bool {
                      AABB box_left{}, box_right{};
                      a->boundingBox(0, 0, box_left);
                      b->boundingBox(0, 0, box_right);
                      return box_left.min().z() < box_right.min().z();
                  });
    }

    std::shared_ptr<Hitable> operator[](std::size_t index) {
        return hitables[index];
    }

private:
    std::vector<std::shared_ptr<Hitable>> hitables;
};


#endif //RAY_TRACER_HITABLECOLLECTION_H
