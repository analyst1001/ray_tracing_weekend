#include "material.h"
#include "rt_weekend.h"
#include "vec3.h"

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();
    if (scatter_direction.near_zero()) {
        scatter_direction = rec.normal;
    }
    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const {
    const Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz*random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    const double refraction_ratio = rec.front_face ? (1.0/ir) : ir;
    const Vec3 unit_direction = unit_vector(r_in.direction());

    const double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    const double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio*sin_theta > 1.0;

    Vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
        direction = reflect(unit_direction, rec.normal);
    }
    else {
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }
    scattered = Ray(rec.p, direction);
    return true;
}

double Dielectric::reflectance(const double cosine, const double ref_idx) {
    // Use Schlick's approximation for reflectance
    const auto r0 = ((1-ref_idx)/(1+ref_idx))*((1-ref_idx)/(1+ref_idx));
    return r0 + (1-r0)*pow((1 - cosine), 5);
}
