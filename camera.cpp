#include "camera.h"
#include "vec3.h"

Ray Camera::get_ray(double s, double t) const {
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset = u*rd.x() + v*rd.y();
    return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}
