/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Sphere
*/

#include "Shapes.hpp"
#include <cmath>
#include <iostream>

namespace Math {
    // methods
    hitInfo Sphere::hits(const RayTracer::Ray &ray) const
    {
        double a = ray.direction_.lengthSquared();
        double b = 2 * ray.direction_.dot(ray.origin_ - this->center);
        double half_b = b / 2;
        double c = (ray.origin_ - this->center).lengthSquared() - pow(this->radius, 2);
        double delta = half_b * half_b - a * c;

        if (delta < 0)
            return { { 0, 0, 0 }, { 0, 0, 0 }, 0, false, false, nullptr };

        double sqrt_delta = sqrt(delta);
        double root = (-half_b - sqrt_delta) / a;
        hitInfo hit;

        if (root < 0.001) {
            root = (-half_b + sqrt_delta) / a;
        }
        if (root < 0.001)
            return { { 0, 0, 0 }, { 0, 0, 0 }, 0, false, false, nullptr };

        hit.hitPoint = ray.PointAt(root);
        hit.t = root;
        hit.hit = true;
        Vector3D outNormal = (hit.hitPoint - this->center) / this->radius;
        hit.setNormalFace(ray, outNormal);
        hit.material = this->material;

        return hit;
    }

    hitInfo Plane::hits(const RayTracer::Ray &ray) const
    {
        double denominator = normal_.dot(ray.direction_);
        if (std::abs(denominator) > 1e-6) {
            double t = normal_.dot(point_ - ray.origin_) / denominator;
            if (t >= 0) {
                Vector3D hit_point = ray.PointAt(t);
                return { hit_point, normal_, t, true, normal_.dot(ray.direction_) < 0, material_ };
            }
        }
        return { Vector3D(0, 0, 0), Vector3D(0, 0, 0), 0, false, false, nullptr };
    }

    hitInfo Cylinder::hits(const RayTracer::Ray &ray) const
    {
        hitInfo hit;
        hit.hit = false;

        Vector3D OC = ray.origin_ - center_;
        Vector3D D = ray.direction_;
        double a = D.x * D.x + D.z * D.z;
        double b = 2 * OC.x * D.x + 2 * OC.z * D.z;
        double c = OC.x * OC.x + OC.z * OC.z - radius_ * radius_;
        double delta = b * b - 4 * a * c;

        if (delta < 0) {
            return hit;
        }

        double t0 = (-b - sqrt(delta)) / (2 * a);
        double t1 = (-b + sqrt(delta)) / (2 * a);
        double minY = center_.y - height_ / 2;
        double maxY = center_.y + height_ / 2;
        bool intersects_caps = false;

        // Check intersection with top cap
        double t_cap = (maxY - ray.origin_.y) / ray.direction_.y;
        Vector3D p_cap = ray.PointAt(t_cap);
        if (t_cap > 0 && (p_cap - center_).lengthSquared() <= radius_ * radius_) {
            intersects_caps = true;
            if (!hit.hit || t_cap < hit.t) {
                hit.t = t_cap;
                hit.hitPoint = p_cap;
                hit.material = material_;
                hit.normal = Vector3D(0, 1, 0);
                hit.setNormalFace(ray, hit.normal);
                hit.hit = true;
            }
        }

        // Check intersection with bottom cap
        t_cap = (minY - ray.origin_.y) / ray.direction_.y;
        p_cap = ray.PointAt(t_cap);
        if (t_cap > 0 && (p_cap - center_).lengthSquared() <= radius_ * radius_) {
            intersects_caps = true;
            if (!hit.hit || t_cap < hit.t) {
                hit.t = t_cap;
                hit.hitPoint = p_cap;
                hit.material = material_;
                hit.normal = Vector3D(0, -1, 0);
                hit.setNormalFace(ray, hit.normal);
                hit.hit = true;
            }
        }

        // Check intersection with cylinder body
        if (t1 > 0 && minY < ray.PointAt(t1).y && ray.PointAt(t1).y < maxY) {
            if (!hit.hit || t1 < hit.t) {
                hit.t = t1;
                hit.hitPoint = ray.PointAt(t1);
                hit.material = material_;
                hit.normal = Vector3D(hit.hitPoint.x - center_.x, 0, hit.hitPoint.z - center_.z).normalize();
                hit.setNormalFace(ray, hit.normal);
                hit.hit = true;
            }
        }

        if (t0 > 0 && minY < ray.PointAt(t0).y && ray.PointAt(t0).y < maxY) {
            if (!hit.hit || t0 < hit.t) {
                hit.t = t0;
                hit.hitPoint = ray.PointAt(t0);
                hit.material = material_;
                hit.normal = Vector3D(hit.hitPoint.x - center_.x, 0, hit.hitPoint.z - center_.z).normalize();
                hit.setNormalFace(ray, hit.normal);
                hit.hit = true;
            }
        }

        return hit;
    }
}// namespace Math
