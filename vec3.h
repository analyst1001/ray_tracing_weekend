#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "rt_weekend.h"
using std::sqrt;

class Vec3 {
    private:
        double e[3];

    public:
        Vec3() : e{0,0,0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v) {
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= (1/t);
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
        }

        inline bool near_zero() const {
            const auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        inline static Vec3 random() {
            return Vec3(random_double(), random_double(), random_double());
        }

        inline static Vec3 random(double min, double max) {
            return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(const double t, const Vec3 &v) {
    return Vec3(t * v[0], t * v[1], t * v[2]);
}

inline Vec3 operator*(const Vec3 &v, const double t) {
    return t * v;
}

inline Vec3 operator/(const Vec3 &v, const double t) {
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return (u[0] * v[0]) + (u[1] * v[1]) + (u[2] * v[2]);
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3((u[1] * v[2]) - (u[2] * v[1]),
                (u[2] * v[0]) - (u[0] * v[2]),
                (u[0] * v[1]) - (u[1] * v[0]));
}

inline Vec3 unit_vector(const Vec3 &v) {
    return v / v.length();
}

Vec3 random_in_unit_sphere();
Vec3 random_in_unit_disk();
Vec3 random_unit_vector();
Vec3 random_in_hemisphere(const Vec3 &normal);
Vec3 refract(const Vec3 &uv, const Vec3 &n, const double etai_over_etat);
Vec3 reflect(const Vec3 &v, const Vec3 &n);
#endif
