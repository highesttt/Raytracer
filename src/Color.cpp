/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Color
*/

#include "Color.hpp"

std::vector<int> writeColor(const Math::Color &pixel_color, int samples_per_pixel)
{
    std::vector<int> pixel(3);
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;
    double const scale = 1.0F / static_cast<float>(samples_per_pixel);

    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    pixel[0] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    pixel[1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    pixel[2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
    return pixel;
}
