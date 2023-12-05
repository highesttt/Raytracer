/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Config
*/

#pragma once

#include "Object.hpp"
#include "Point.hpp"
#include <libconfig.h++>
#include <memory>

class Config
{
    public:
    Config() = default;
    Config(std::string &fp);
    Config(const Config &config);
    ~Config();

    Config operator=(const Config &config);
    double aspect_ratio_;
    int image_width_;
    int image_height_;
    int samples_per_pixel_;
    int max_depth_;

    double fov_;
    double focal_length_;

    Math::Point3D camera_position_;
    Math::Point3D camera_look_at_;
    std::shared_ptr<RayTracer::ObjectList> objects_;
};
