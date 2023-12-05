/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Utils
*/

#pragma once

#include "Point.hpp"

double randomNumber();
double randomNumber(double min, double max);
double clamp(double x, double min, double max);

Math::Vector3D randomVector();
Math::Vector3D randomVector(double min, double max);
Math::Vector3D randomInUnitSphere();
Math::Vector3D unitVector(const Math::Vector3D &v);
Math::Vector3D randomUnitVector();
Math::Vector3D randomInHemisphere(const Math::Vector3D &normal);
double degreesToRadian(double degrees);