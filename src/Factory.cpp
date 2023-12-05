/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Factory
*/

#include "Factory.hpp"

SphereBuilder Factory::createSphereBuilder()
{
    return SphereBuilder();
}

PlaneBuilder Factory::createPlaneBuilder()
{
    return PlaneBuilder();
}

CylinderBuilder Factory::createCylinderBuilder()
{
    return CylinderBuilder();
}

Builder &SphereBuilder::setMaterial(std::shared_ptr<Math::Material> material)
{
    this->material_ = material;
    return *this;
}

Builder &SphereBuilder::setCenter(Math::Point3D center)
{
    this->center_ = center;
    return *this;
}

Builder &SphereBuilder::setRadius(double radius)
{
    this->radius_ = radius;
    return *this;
}

std::shared_ptr<Math::Sphere> SphereBuilder::buildSphere() const
{
    std::shared_ptr<Math::Sphere> sphere = std::make_shared<Math::Sphere>();
    sphere->center = this->center_;
    sphere->material = this->material_;
    sphere->radius = this->radius_;
    return sphere;
}

Builder &PlaneBuilder::setMaterial(std::shared_ptr<Math::Material> material)
{
    this->material_ = material;
    return *this;
}

Builder &PlaneBuilder::setPoint(Math::Vector3D point)
{
    this->point_ = point;
    return *this;
}

Builder &PlaneBuilder::setNormal(Math::Vector3D normal)
{
    this->normal_ = normal;
    return *this;
}

std::shared_ptr<Math::Plane> PlaneBuilder::buildPlane() const
{
    std::shared_ptr<Math::Plane> plane = std::make_shared<Math::Plane>();
    plane->point_ = this->point_;
    plane->normal_ = this->normal_;
    plane->material_ = this->material_;
    return plane;
}

Builder &CylinderBuilder::setMaterial(std::shared_ptr<Math::Material> material)
{
    this->material_ = material;
    return *this;
}

Builder &CylinderBuilder::setCenter(Math::Point3D center)
{
    this->center_ = center;
    return *this;
}

Builder &CylinderBuilder::setRadius(double radius)
{
    this->radius_ = radius;
    return *this;
}

Builder &CylinderBuilder::setHeight(double height)
{
    this->height_ = height;
    return *this;
}

std::shared_ptr<Math::Cylinder> CylinderBuilder::buildCylinder() const
{
    std::shared_ptr<Math::Cylinder> cylinder = std::make_shared<Math::Cylinder>();
    cylinder->material_ = this->material_;
    cylinder->center_ = this->center_;
    cylinder->radius_ = this->radius_;
    cylinder->height_ = this->height_;
    return cylinder;
}