//
// Created by christoph on 31.07.19.
//

#ifndef RAY_TRACER_BVH_H
#define RAY_TRACER_BVH_H

#include <cstdlib>
#include "HitableCollection.h"

namespace BVH {
    class BVHNode : public Hitable {
    public:
        BVHNode() = default;

        BVHNode(HitableCollection& collection, int index_start, int index_end, float t0, float t1) {
            // Choose random axis to sort along
            /*
            int axis = rand() % 3;
            switch (axis) {
                case 0:
                    collection.sortByXAxis();
                    break;
                case 1:
                    collection.sortByYAxis();
                    break;
                case 2:
                    collection.sortByZAxis();
                default:;
            }
             */

            if ((index_end - index_start) == 1) {
                left_ = collection[index_start];
                right_ = collection[index_start];
            }
            else if ((index_end - index_start) == 2) {
                left_ = collection[index_start];
                right_ = collection[index_start + 1];
            }
            else {
                int len = index_end - index_start;
                left_ = std::make_shared<BVHNode>(collection, index_start, index_start + (len / 2), t0, t1);
                right_ = std::make_shared<BVHNode>(collection, index_start + (len / 2), index_end, t0, t1);
            }

            AABB box_left{}, box_right{};
            left_->boundingBox(t0, t1, box_left);
            right_->boundingBox(t0, t1, box_right);
            boundingBox_ = AABB::surroundingBox(box_left, box_right);
        }

        bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const override {
            if (boundingBox_.hit(r, t_min, t_max)) {
                HitRecord left_record{}, right_record{};
                bool left_hit, right_hit;
                // Check if left and right exist, if yes, check which are hit by ray
                if (left_ == nullptr)
                    left_hit = false;
                else
                    left_hit = left_->hit(r, t_min, t_max, left_record);
                if (right_ == nullptr)
                    right_hit = false;
                else
                    right_hit = right_->hit(r, t_min, t_max, right_record);
                // If both hit, return the one which has smaller t
                if (left_hit && right_hit) {
                    if (left_record.t < right_record.t)
                        record = left_record;
                    else
                        record = right_record;
                    return true;
                }
                    // Else return the respective record
                else if (left_hit) {
                    record = left_record;
                    return true;
                } else if (right_hit) {
                    record = right_record;
                    return true;
                }
            }
            return false;
        }

        bool boundingBox(float t0, float t1, AABB &box) const override {
            box = boundingBox_;
            return true;
        }

    private:
        std::shared_ptr<Hitable> left_;
        std::shared_ptr<Hitable> right_;
        AABB boundingBox_;
    };
} // namespace BVH


#endif //RAY_TRACER_BVH_H
