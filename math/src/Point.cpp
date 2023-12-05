/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Point
*/

#include "Utils.hpp"
#include <cmath>

namespace Math {

    Point3D &Point3D::operator=(const Point3D &point)
    {
        if (this == &point)
            return *this;
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
        return *this;
    }

    Point3D &Point3D::operator=(Point3D &&old_point) noexcept
    {
        if (this != &old_point) {
            x = old_point.x;
            y = old_point.y;
            z = old_point.z;
        }
        return *this;
    }

    Point3D Point3D::operator-() const
    {
        return { -this->x, -this->y, -this->z };
    }

    Point3D Point3D::operator+(const Point3D &point) const
    {
        return { this->x + point.x, this->y + point.y, this->z + point.z };
    }

    Point3D Point3D::operator-(const Point3D &point) const
    {
        return { this->x - point.x, this->y - point.y, this->z - point.z };
    }

    Point3D Point3D::operator-(double &t) const
    {
        return { this->x - t, this->y - t, this->z - t };
    }

    Point3D Point3D::operator*(const double &value) const
    {
        return { this->x * value, this->y * value, this->z * value };
    }

    Point3D Point3D::operator*(const Point3D &point) const
    {
        return { this->x * point.x, this->y * point.y, this->z * point.z };
    }

    Point3D Point3D::operator/(double t) const
    {
        double const k = 1.0F / t;

        return { this->x * k, this->y * k, this->z * k };
    }

    double Point3D::operator[](int i)
    {
        switch (i) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
        default:
            return 0;
        }
    }

    double Point3D::operator[](int &i) const
    {
        switch (i) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
        default:
            return 0;
        }
    }

    bool Point3D::operator==(const Point3D &point) const
    {
        return (this->x == point.x && this->y == point.y && this->z == point.z);
    }

    double Point3D::length() const
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    double Point3D::lengthSquared() const
    {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    double Point3D::dot(const Point3D &point) const
    {
        return this->x * point.x + this->y * point.y + this->z * point.z;
    }

    Point3D Point3D::cross(const Point3D &point) const
    {
        double const Pointx = this->y * point.z - this->z * point.y;
        double const Pointy = -(this->x * point.z - this->z * point.x);
        double const Pointz = this->x * point.y - this->y * point.x;

        return { Pointx, Pointy, Pointz };
    }

    double Point3D::distanceSquared(const Point3D &point) const
    {
        return (this->x - point.x) * (this->x - point.x) + (this->y - point.y) * (this->y - point.y)
               + (this->z - point.z) * (this->z - point.z);
    }

    double Point3D::distance(const Point3D &point) const
    {
        return sqrt(this->distanceSquared(point));
    }

    Point3D Point3D::unitVector() const
    {
        return *this / this->length();
    }

    bool Point3D::nearZero() const
    {
        const auto s = 1e-8;

        return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
    }

    Point3D Point3D::reflect(const Point3D &n)
    {
        return *this - ((n * this->dot(n)) * 2);
    }

    Point3D Point3D::refract(const Point3D &n, double etaiOverEtat)
    {
        double cosTheta = fmin((-(*this)).dot(n), 1.0);
        Point3D rOutPerp = (*this + (n * cosTheta)) * etaiOverEtat;
        Point3D rOutParallel = n * (-sqrt(fabs(1.0 - rOutPerp.lengthSquared())));
        return rOutPerp + rOutParallel;
    }

    Point3D Point3D::normalize()
    {
        double const k = 1.0F / sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

        this->x *= k;
        this->y *= k;
        this->z *= k;
        return *this;
    }
}// namespace Math
