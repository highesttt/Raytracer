/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** hitInfo
*/

#pragma once

#include "Material.hpp"
#include "Point.hpp"
#include "Raytracer.hpp"
#include <iostream>
#include <memory>

struct hitInfo
{
    Math::Point3D hitPoint;
    Math::Vector3D normal;
    double t;
    bool frontFace;
    bool hit;
    std::shared_ptr<Math::Material> material;

    void setNormalFace(const RayTracer::Ray &r, const Math::Vector3D &outwardNormal)
    {
        frontFace = r.direction_.dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
