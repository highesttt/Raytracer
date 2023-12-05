/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Raytracer
*/

#include "Raytracer.hpp"
#include "Object.hpp"
#include "Utils.hpp"
#include <algorithm>

namespace RayTracer {

    Ray &Ray::operator=(const Ray &ray)
    {
        if (this == &ray)
            return *this;
        this->origin_ = ray.origin_;
        this->direction_ = ray.direction_;
        return *this;
    }

    Ray &Ray::operator=(Ray &&ray) noexcept
    {
        this->origin_ = ray.origin_;
        this->direction_ = ray.direction_;
        return *this;
    }

    Screen &Screen::operator=(const Screen &old_screen)
    {
        if (this != &old_screen)
            *this = old_screen;
        this->origin_ = old_screen.origin_;
        this->horizontal_ = old_screen.horizontal_;
        this->vertical_ = old_screen.vertical_;
        this->lower_left_corner_ = old_screen.lower_left_corner_;
        return *this;
    }

    Screen &Screen::operator=(Screen &&old_screen) noexcept
    {
        this->origin_ = old_screen.origin_;
        this->horizontal_ = old_screen.horizontal_;
        this->vertical_ = old_screen.vertical_;
        this->lower_left_corner_ = old_screen.lower_left_corner_;
        return *this;
    }

    Camera &Camera::operator=(const Camera &old_camera)
    {
        if (this == &old_camera)
            return *this;
        this->screen = old_camera.screen;
        this->viewport_height_ = old_camera.viewport_height_;
        this->viewport_width_ = old_camera.viewport_width_;
        this->aspect_ratio_ = old_camera.aspect_ratio_;
        this->focal_length_ = old_camera.focal_length_;
        return *this;
    }

    Camera &Camera::operator=(Camera &&old_camera) noexcept
    {
        this->screen = old_camera.screen;
        this->viewport_height_ = old_camera.viewport_height_;
        this->viewport_width_ = old_camera.viewport_width_;
        this->aspect_ratio_ = old_camera.aspect_ratio_;
        this->focal_length_ = old_camera.focal_length_;
        return *this;
    }

    Math::Point3D Screen::getCorner() const
    {
        return this->lower_left_corner_;
    }

    Math::Vector3D Screen::getHorizontal() const
    {
        return this->horizontal_;
    }

    Math::Vector3D Screen::getVertical() const
    {
        return this->vertical_;
    }

    Math::Point3D Screen::getOrigin() const
    {
        return this->origin_;
    }

    Math::Point3D Ray::PointAt(const double &t) const
    {
        return this->origin_ + this->direction_ * t;
    }

    Camera::Camera(Math::Point3D pos, Math::Point3D lookAt, double fov, double aspect_ratio, double focal_length)
        : aspect_ratio_(aspect_ratio), focal_length_(focal_length)
    {
        this->fov_ = fov;
        double vertical_fov = fov / aspect_ratio;
        auto theta = degreesToRadian(vertical_fov);
        auto h = tan(theta / 2);
        this->viewport_height_ = 2.0 * h;
        this->viewport_width_ = aspect_ratio * viewport_height_;

        auto w = unitVector(pos - lookAt);// camera direction
        auto u = unitVector(Math::Vector3D{ 0, 1, 0 }.cross(w));// camera up
        auto v = w.cross(u);// camera right

        this->screen = Screen(pos, u * viewport_width_, v * viewport_height_, w);
    }

    Math::Color Camera::rayColor(const Ray &r, const std::shared_ptr<RayTracer::ObjectList> &objects, int depth)
    {
        hitInfo const shape_hits = (objects)->hits(r);

        if (depth <= 0)
            return { 0, 0, 0 };
        if (shape_hits.t > 0.001F) {
            RayTracer::Ray scattered;
            Math::Color attenuation;
            if (shape_hits.material->scatter(r, shape_hits, attenuation, scattered)) {
                return attenuation * rayColor(scattered, objects, depth - 1);
            }
            return { 0, 0, 0 };
        }
        Math::Vector3D const unit_direction = r.direction_.unitVector();
        double const t = 0.5 * (unit_direction.y + 1.0);
        return Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + Math::Color(0.5, 0.7, 1.0) * t;
    }

    Ray Camera::ray(double u, double v) const
    {
        return Ray(this->screen.getOrigin(),
                   { (this->screen.getCorner() + this->screen.getHorizontal() * u + this->screen.getVertical() * v
                      - this->screen.getOrigin()) });
    }


    Screen::Screen(const Math::Point3D &origin,
                   const Math::Vector3D &horizontal,
                   const Math::Vector3D &vertical,
                   const Math::Vector3D &direction)
        : origin_(origin), horizontal_(horizontal), vertical_(vertical)
    {
        this->lower_left_corner_ = this->origin_ - this->horizontal_ / 2 - this->vertical_ / 2 - direction;
    }
}// namespace RayTracer
