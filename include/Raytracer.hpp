/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Raytracer
*/

#pragma once

#include "Color.hpp"
#include "Point.hpp"
#include <memory>

namespace RayTracer {
    class ObjectList;
    class Ray
    {
        public:
        Ray() = default;
        Ray(const Math::Point3D &origin, const Math::Vector3D &dir) : origin_(origin), direction_(dir) {}
        Ray(const Ray &ray) = default;
        ~Ray() = default;
        Ray(Ray &&old_screen) noexcept = default;
        Ray &operator=(Ray &&ray) noexcept;


        Ray &operator=(const Ray &ray);

        [[nodiscard]] Math::Point3D PointAt(const double &t) const;
        Math::Point3D origin_;
        Math::Vector3D direction_;
    };

    class Screen
    {
        public:
        Screen() = default;
        Screen(const Math::Point3D &origin,
               const Math::Vector3D &horizontal,
               const Math::Vector3D &vertical,
               const Math::Vector3D &direction);
        ~Screen() = default;
        Screen(const Screen &old_screen) = default;
        Screen(Screen &&old_screen) noexcept = default;
        Screen &operator=(const Screen &old_screen);
        Screen &operator=(Screen &&old_screen) noexcept;

        [[nodiscard]] Math::Point3D getCorner() const;
        [[nodiscard]] Math::Vector3D getHorizontal() const;
        [[nodiscard]] Math::Vector3D getVertical() const;
        [[nodiscard]] Math::Point3D getOrigin() const;

        private:
        Math::Point3D origin_;
        Math::Vector3D horizontal_;
        Math::Vector3D vertical_;
        Math::Point3D lower_left_corner_;
    };

    class Camera
    {
        public:
        Camera(const Math::Point3D pos,
               const Math::Point3D lookAt,
               double fov,
               double aspect_ratio,
               double focal_length);
        ~Camera() = default;
        Camera(const Camera &old_camera) = default;
        Camera(Camera &&old_camera) noexcept = default;
        Camera &operator=(const Camera &old_camera);
        Camera &operator=(Camera &&old_camera) noexcept;

        Math::Color rayColor(const Ray &r, const std::shared_ptr<RayTracer::ObjectList> &objects, int depth);

        [[nodiscard]] Ray ray(double u, double v) const;

        Screen screen;

        private:
        double viewport_height_;
        double viewport_width_;
        double aspect_ratio_;
        double focal_length_;
        double fov_;
    };
}// namespace RayTracer
