#include "vec3.h"
#include "rt_weekend.h"

Vec3 random_in_unit_sphere() {
    while (true) {
        const auto p = Vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_in_unit_disk() {
    while (true) {
        const auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3 &normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) {
        return in_unit_sphere;
    }
    else {
        return -in_unit_sphere;
    }
}

Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2*dot(v, n)*n;
}

Vec3 refract(const Vec3 &uv, const Vec3 &n, const double etai_over_etat) {
    const auto cos_theta = fmin(dot(-uv, n), 1.0);
    const Vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    const Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
