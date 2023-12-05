/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Material
*/

#pragma once

#include "Point.hpp"
#include <iostream>

namespace RayTracer {
    class Ray;
}

struct hitInfo;

namespace Math {
    class Material
    {
        public:
        Material() = default;
        virtual ~Material() = default;
        Material(const Material &old_output) = default;
        Material(Material &&old_output) noexcept = default;
        Material &operator=(const Material &old_output);
        Material &operator=(Material &&old_output) noexcept;

        virtual bool scatter(const RayTracer::Ray &ray,
                             const hitInfo &hit,
                             Color &attenuation,
                             RayTracer::Ray &scattered) const = 0;

        Color color_;
        double fuzz_ = 0;

        protected:
        private:
    };

    class Matte : public Material
    {
        public:
        explicit Matte(const Color &color) : albedo_(color) {}
        bool scatter(const RayTracer::Ray &r_in,
                     const hitInfo &records,
                     Color &attenuation,
                     RayTracer::Ray &scattered) const override;

        Color albedo_;

        protected:
        private:
    };

    class Mirror : public Material
    {
        public:
        Mirror(const Color &color, double f) : albedo_(color), blur_(f < 1 ? f : 1) {}
        bool scatter(const RayTracer::Ray &r_in,
                     const hitInfo &records,
                     Color &attenuation,
                     RayTracer::Ray &scattered) const override;

        Color albedo_;
        double blur_;

        protected:
        private:
    };

    class Glass : public Material
    {
        public:
        Glass(double index) : index_(index){};
        bool scatter(const RayTracer::Ray &r_in,
                     const hitInfo &records,
                     Color &attenuation,
                     RayTracer::Ray &scattered) const override;

        double index_;
    };
}// namespace Math
