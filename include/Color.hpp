/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Color
*/

#pragma once

#include "Point.hpp"
#include "Utils.hpp"
#include <iostream>
#include <vector>

std::vector<int> writeColor(const Math::Color &pixel_color, int samples_per_pixel);