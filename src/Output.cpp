/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Output
*/

#include "Output.hpp"
#include "Config.hpp"
#include <utility>

Output::Output(const Config &config)
{
    this->config_ = config;
    std::vector<std::vector<int>> image(static_cast<size_t>(config_.image_height_ * config_.image_width_));
    this->pixels_ = std::move(image);
}

Output &Output::operator=(const Output &old_output)
{
    if (this == &old_output)
        return *this;
    pixels_ = old_output.pixels_;
    return *this;
}

Output &Output::operator=(Output &&old_output) noexcept
{
    if (this == &old_output)
        return *this;
    pixels_ = old_output.pixels_;
    return *this;
}

void Output::writeInFile(const std::string &filename)
{
    std::cout << std::endl << "\033[4mGenerating image...\033[0m" << std::endl;

    std::ofstream file(filename);

    file << "P3\n" << config_.image_width_ << " " << config_.image_height_ << "\n255\n";
    for (const auto &v : this->pixels_) {
        file << v[0] << ' ' << v[1] << ' ' << v[2] << "\n";
    }
    file.close();

    std::cout << "Output generated in \033[1m" << filename << "\033[0m" << std::endl;
}

void Output::generateImage()
{
    std::cout << "\033[4mGenerating image...\033[0m" << std::endl;

    RayTracer::Camera cam(
        config_.camera_position_, config_.camera_look_at_, config_.fov_, config_.aspect_ratio_, config_.focal_length_);

    for (int j = 0; j < config_.image_height_; ++j) {
        std::string progress_bar = "\r[";
        for (int i = 0; i < 10; ++i) {
            if (i <= ((j + 1) * 10) / config_.image_height_ - 1)
                progress_bar += "\033[32m█\033[0m";
            else
                progress_bar += "\033[30m█\033[0m";
        }
        progress_bar += "] ";
        std::cout << progress_bar << static_cast<int>((j * 100) / (config_.image_height_ - 1)) << "%"
                  << " (" << j << "/" << config_.image_height_ - 1 << ")" << std::flush;
        for (int i = 0; i < config_.image_width_; ++i) {
            Math::Color pixel_color(0, 0, 0);
            for (int s = 0; s < config_.samples_per_pixel_; ++s) {
                double const u = (i + randomNumber()) / (config_.image_width_ - 1);
                double const v = (j + randomNumber()) / (config_.image_height_ - 1);
                pixel_color = pixel_color + cam.rayColor(cam.ray(u, v), config_.objects_, config_.max_depth_);
            }
            std::vector<int> const pixel = writeColor(pixel_color, static_cast<int>(config_.samples_per_pixel_));
            pixels_[(config_.image_height_ - j - 1) * config_.image_width_ + i] = pixel;
        }
    }

    std::cout << std::endl;
}