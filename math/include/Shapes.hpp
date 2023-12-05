/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Sphere
*/

#include "Material.hpp"
#include "Object.hpp"
#include "Point.hpp"

#include <memory>

#pragma once

namespace RayTracer {
    class Ray;
}

namespace Math {
    class Sphere : public RayTracer::Object
    {
        public:
        Sphere() = default;
        Sphere(const Sphere &sphere) = delete;
        ~Sphere() = default;

        Sphere operator=(const Sphere &sphere) = delete;

        hitInfo hits(const RayTracer::Ray &ray) const override;

        std::shared_ptr<Material> material;
        Point3D center;
        double radius;

        protected:
        private:
    };

    class Plane : public RayTracer::Object
    {
        public:
        Plane() = default;
        Plane(const Plane &plane) = delete;
        ~Plane() = default;

        Plane operator=(const Plane &plane) = delete;

        hitInfo hits(const RayTracer::Ray &ray) const;

        Vector3D point_;
        Vector3D normal_;
        std::shared_ptr<Material> material_;
    };
    class Cylinder : public RayTracer::Object
    {
        public:
        Cylinder() = default;
        Cylinder(const Cylinder &cylinder) = delete;
        ~Cylinder() = default;

        Cylinder operator=(const Cylinder &cylinder) = delete;

        hitInfo hits(const RayTracer::Ray &ray) const;

        Point3D center_;
        double radius_;
        double height_;
        std::shared_ptr<Material> material_;
    };
}// namespace Math