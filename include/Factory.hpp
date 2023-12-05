/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Factory
*/

#pragma once
#include "Material.hpp"
#include "Point.hpp"
#include "Shapes.hpp"
#include <memory>

class Builder
{
    public:
    Builder() = default;
    ~Builder() = default;
    virtual Builder &setMaterial(std::shared_ptr<Math::Material> material) = 0;
    virtual Builder &setCenter(Math::Point3D center) = 0;
    virtual Builder &setRadius(double radius) = 0;
    virtual Builder &setSize(Math::Vector3D size) = 0;
    virtual Builder &setPoint(Math::Vector3D point) = 0;
    virtual Builder &setNormal(Math::Vector3D normal) = 0;
    virtual Builder &setHeight(double height) = 0;
    virtual std::shared_ptr<Math::Sphere> buildSphere() const = 0;
    virtual std::shared_ptr<Math::Plane> buildPlane() const = 0;
    virtual std::shared_ptr<Math::Cylinder> buildCylinder() const = 0;
};

class SphereBuilder : public Builder
{
    public:
    Builder &setMaterial(std::shared_ptr<Math::Material> material) override;
    Builder &setCenter(Math::Point3D center) override;
    Builder &setRadius(double radius) override;
    Builder &setSize(Math::Vector3D size) override
    {
        return *this;
    };
    Builder &setPoint(Math::Vector3D point) override
    {
        return *this;
    };
    Builder &setNormal(Math::Vector3D normal) override
    {
        return *this;
    };
    Builder &setHeight(double height) override
    {
        return *this;
    };
    std::shared_ptr<Math::Sphere> buildSphere() const override;
    std::shared_ptr<Math::Plane> buildPlane() const override
    {
        return nullptr;
    };
    std::shared_ptr<Math::Cylinder> buildCylinder() const override
    {
        return nullptr;
    };

    std::shared_ptr<Math::Material> material_;
    Math::Point3D center_;
    double radius_;
};

class PlaneBuilder : public Builder
{
    public:
    Builder &setMaterial(std::shared_ptr<Math::Material> material) override;
    Builder &setPoint(Math::Vector3D point) override;
    Builder &setNormal(Math::Vector3D normal) override;
    Builder &setCenter(Math::Point3D center) override
    {
        return *this;
    };
    Builder &setRadius(double radius) override
    {
        return *this;
    };
    Builder &setSize(Math::Vector3D size) override
    {
        return *this;
    };
    Builder &setHeight(double height) override
    {
        return *this;
    };
    std::shared_ptr<Math::Plane> buildPlane() const override;
    std::shared_ptr<Math::Sphere> buildSphere() const override
    {
        return nullptr;
    };
    std::shared_ptr<Math::Cylinder> buildCylinder() const override
    {
        return nullptr;
    };

    std::shared_ptr<Math::Material> material_;
    Math::Vector3D point_;
    Math::Vector3D normal_;
};

class CylinderBuilder : public Builder
{
    public:
    Builder &setMaterial(std::shared_ptr<Math::Material> material) override;
    Builder &setCenter(Math::Point3D center) override;
    Builder &setRadius(double radius) override;
    Builder &setHeight(double height) override;
    Builder &setSize(Math::Vector3D size) override
    {
        return *this;
    };
    Builder &setPoint(Math::Vector3D point) override
    {
        return *this;
    };
    Builder &setNormal(Math::Vector3D normal) override
    {
        return *this;
    };
    std::shared_ptr<Math::Cylinder> buildCylinder() const override;
    std::shared_ptr<Math::Sphere> buildSphere() const override
    {
        return nullptr;
    };
    std::shared_ptr<Math::Plane> buildPlane() const override
    {
        return nullptr;
    };

    std::shared_ptr<Math::Material> material_;
    Math::Point3D center_;
    double radius_;
    double height_;
};

class Factory
{
    public:
    SphereBuilder createSphereBuilder();
    PlaneBuilder createPlaneBuilder();
    CylinderBuilder createCylinderBuilder();
};
