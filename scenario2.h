#include <cmath>
#include <iostream>
#include "Vec3.h"

using namespace std;

class Point {
public:
    float x;
    float y;
    float z;
    Point(const Point&);
    Point(float, float, float);
    void plus(const Vec3&);
};

Point::Point (const Point& p) {
    x = p.x;
    y = p.y;
    z = p.z;
};

Point::Point (float cx, float cy, float cz) {
    x = cx;
    y = cy;
    z = cz;
};

void Point::plus (const Vec3& v) {
    x += v[0];
    y += v[1];
    z += v[2];
};


class Material {
public:
    Vec3 env_material;
    Vec3 dif_material;
    Vec3 spe_material;
    Material(Vec3, Vec3, Vec3);
};

Material::Material(Vec3 envMaterial, Vec3 difMaterial, Vec3 speMaterial)
    : env_material(envMaterial), dif_material(difMaterial), spe_material(speMaterial) {}


class Sphere {
public:
    Point center;
    float radius;
    Material material;
    Sphere(Point, float, const Material&);
    float checkInterception(bool&, Vec3, Point, const bool&);
};

Sphere::Sphere(Point pcenter, float sradius, const Material& smaterial) 
: center(pcenter), material(smaterial.env_material, smaterial.dif_material, smaterial.spe_material) {
    radius = sradius;
};

float Sphere::checkInterception(bool& intercept, Vec3 V, Point O, const bool& isShadow = false) {
    // Checking if the ball is intercepted by ray
    // This check uses the square equation delta
    float alpha = Vec3::dot(V, V);

    Vec3 Wshadow(center.x - O.x, center.y - O.y, center.z - O.z);
    Vec3 WNonShadow(-center.x, -center.y, -center.z);
    Vec3 W = isShadow ? Wshadow : WNonShadow;

    float beta = 2 * Vec3::dot(V, W);

    float gamma = Vec3::dot(W, W) - radius * radius;

    // Calculating the delta from 'alpha', 'beta' and 'gamma';
    float delta = beta * beta - 4 * alpha * gamma;

    // Scalar that stretch the 'V' vector from camera to intercepted point
    float t_int = 0;
    if (isShadow) {
        t_int = max((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
    } else {
        t_int = min((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
    }

    intercept = delta >= 0;

    return t_int;
}

class Light {
public:
    Point center;
    Vec3 color;
    Light(Point, Vec3);
};

Light::Light(Point lcenter, Vec3 lcolor) : center(lcenter), color(lcolor) {}
