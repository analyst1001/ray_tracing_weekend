#include "sphere.h"
#include "hittable.h"

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Vec3 oc = r.origin() - center;
    const auto a = r.direction().length_squared();
    const auto half_b = dot(oc, r.direction());
    const auto c = oc.length_squared() - (radius * radius);
    const auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    const auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.mat_ptr = mat_ptr;
    const Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
