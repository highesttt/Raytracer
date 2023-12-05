/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Utils
*/

#include "Utils.hpp"
#include <cstdlib>

double randomNumber()
{
    return rand() / (RAND_MAX + 1.0);
}

double randomNumber(double min, double max)
{
    return min + (max - min) * randomNumber();
}

double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

Math::Vector3D randomVector()
{
    return { randomNumber(), randomNumber(), randomNumber() };
}

Math::Vector3D randomVector(double min, double max)
{
    return { randomNumber(min, max), randomNumber(min, max), randomNumber(min, max) };
}

Math::Vector3D unitVector(const Math::Vector3D &v)
{
    return v / v.length();
}

Math::Vector3D randomInUnitSphere()
{
    while (true) {
        auto p = randomVector(-1, 1);
        if (p.lengthSquared() >= 1)
            continue;
        return p;
    }
}

Math::Vector3D randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

Math::Vector3D randomInHemisphere(const Math::Vector3D &normal)
{
    Math::Vector3D const in_unit_sphere = randomInUnitSphere();

    if (in_unit_sphere.dot(normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

double degreesToRadian(double degrees)
{
    return degrees * M_PI / 180.0;
}