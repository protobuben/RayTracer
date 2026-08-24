#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

struct hittable_list : public hittable {
    std::vector<std::shared_ptr<hittable>> objects;
    hittable_list() {};
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        hit_record temp;
        bool hit_anything = false;
        double closest = t_max;
        for (const auto& object : objects) {
            if (!object->hit(r, t_min, closest, temp)) { continue; }
            closest = temp.t;
            rec = temp;
            hit_anything = true;
        } 
        return hit_anything;
    }
};