#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"
#include "rt_weekend.h"
#include "vec3.h"
#include "hittable.h"
#include <memory>

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3 cen, double r, shared_ptr<Material> m)
            : center(cen), radius(r), mat_ptr(m) {}

        virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    private:
        Point3 center;
        double radius;
        shared_ptr<Material> mat_ptr;
};

#endif
