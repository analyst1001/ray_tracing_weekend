#ifndef CAMERA_H
#define CAMERA_H

#include "rt_weekend.h"
#include "vec3.h"
#include "ray.h"

class Camera {
    public:
        Camera(
            Point3 lookfrom,
            Point3 lookat,
            Vec3 vup,
            const double vfov,
            const double aspect_ratio,
            double aperture,
            double focus_dist
        ) {
            const auto theta = degrees_to_radians(vfov);
            const auto h = tan(theta/2);
            const auto viewport_height = 2.0 * h;
            const auto viewport_width = aspect_ratio * viewport_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w*focus_dist;

            lens_radius = aperture / 2;
        }

        Ray get_ray(double s, double t) const;

    private:
        Point3 origin, lower_left_corner;
        Vec3 horizontal, vertical;
        Vec3 u, v, w;
        double lens_radius;
};

#endif
