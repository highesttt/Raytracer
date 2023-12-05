/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Material
*/

#include "Material.hpp"
#include "Raytracer.hpp"
#include "Utils.hpp"
#include "hitInfo.hpp"

namespace Math {

    Material &Material::operator=(const Material &old_output)
    {
        if (this != &old_output) {
            color_ = old_output.color_;
            fuzz_ = old_output.fuzz_;
        }
        return *this;
    }
    Material &Material::operator=(Material &&old_output) noexcept
    {
        if (this != &old_output) {
            color_ = old_output.color_;
            fuzz_ = old_output.fuzz_;
        }
        return *this;
    }

    bool Matte::scatter(const RayTracer::Ray &r_in,
                        const hitInfo &records,
                        Color &attenuation,
                        RayTracer::Ray &scattered) const
    {
        auto direction = records.normal + randomUnitVector();

        if (direction.nearZero())
            direction = records.normal;
        scattered = RayTracer::Ray(records.hitPoint, direction);
        attenuation = this->albedo_;
        return true;
    }

    bool Mirror::scatter(const RayTracer::Ray &r_in,
                         const hitInfo &records,
                         Color &attenuation,
                         RayTracer::Ray &scattered) const
    {
        Point3D const reflected = unitVector(r_in.direction_).reflect(records.normal);

        scattered = RayTracer::Ray(records.hitPoint, reflected + randomInUnitSphere() * blur_);
        attenuation = this->albedo_;
        return (scattered.direction_.dot(records.normal) > 0);
    }

    bool Glass::scatter(const RayTracer::Ray &r_in,
                        const hitInfo &records,
                        Color &attenuation,
                        RayTracer::Ray &scattered) const
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractionRatio = records.frontFace ? (1.0 / index_) : index_;
        Vector3D unitDirection = unitVector(r_in.direction_);
        double cosTheta = fmin(-unitDirection.dot(records.normal), 1.0);
        double sinTheta = sqrt(1.0 - (cosTheta * cosTheta));
        bool noRefract = refractionRatio * sinTheta > 1.0;
        Vector3D direction;

        if (noRefract)
            direction = unitDirection.reflect(records.normal);
        else
            direction = unitDirection.refract(records.normal, refractionRatio);
        scattered = RayTracer::Ray(records.hitPoint, direction);
        return true;
    }
}// namespace Math
