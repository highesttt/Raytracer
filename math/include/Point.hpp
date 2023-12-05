/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Point
*/

#pragma once

#include <cmath>
#include <iostream>

namespace Math {
    class Point3D
    {
        public:
        Point3D() : x(0), y(0), z(0) {}
        constexpr Point3D(double x, double y, double z) noexcept : x(x), y(y), z(z) {}
        Point3D(const Point3D &point) : x(point.x), y(point.y), z(point.z) {}
        ~Point3D() = default;
        Point3D(Point3D &&old_point) noexcept = default;

        Point3D &operator=(Point3D &&old_point) noexcept;
        Point3D &operator=(const Point3D &point);
        Point3D operator+(const Point3D &point) const;
        Point3D operator-(const Point3D &point) const;
        Point3D operator-(double &t) const;
        Point3D operator*(const double &t) const;
        Point3D operator*(const Point3D &point) const;
        Point3D operator/(double t) const;
        Point3D operator-() const;
        double operator[](int i);
        double operator[](int &i) const;
        bool operator==(const Point3D &point) const;

        [[nodiscard]] double dot(const Point3D &point) const;
        [[nodiscard]] Point3D cross(const Point3D &point) const;

        [[nodiscard]] double length() const;
        [[nodiscard]] double lengthSquared() const;

        [[nodiscard]] double distance(const Point3D &point) const;
        [[nodiscard]] double distanceSquared(const Point3D &point) const;

        [[nodiscard]] bool nearZero() const;
        Point3D reflect(const Point3D &n);
        Point3D refract(const Point3D &n, double etaiOverEtat);

        Point3D normalize();

        [[nodiscard]] Point3D unitVector() const;
        double x;
        double y;
        double z;

        protected:
        private:
    };

using Vector3D = Math::Point3D;
using Color = Math::Point3D;

}// namespace Math