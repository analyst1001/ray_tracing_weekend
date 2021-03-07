#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt_weekend.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"

struct HitRecord;

class Material {
    public:
        virtual bool scatter(
                const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered
        ) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Color &a) : albedo(a) {}

        virtual bool scatter(
                const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered
        ) const override;

    private:
        Color albedo;
};

class Metal : public Material {
    public:
        Metal(const Color &a, const double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
                const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered
        ) const override;

    private:
        Color albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(
                const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered
        ) const override;

    private:
        // Index of refraction
        double ir;

        static double reflectance(const double cosine, const double ref_idx);
};

#endif
