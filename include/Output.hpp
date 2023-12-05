/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Output
*/

#pragma once

#include "Config.hpp"
#include "Raytracer.hpp"
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

class Output
{
    public:
    Output(const Config &config);
    ~Output() = default;

    Output(const Output &old_output) = default;
    Output(Output &&old_output) noexcept = default;
    Output &operator=(const Output &old_output);
    Output &operator=(Output &&old_output) noexcept;

    void writeInFile(const std::string &filename);
    void generateImage();

    protected:
    std::vector<std::vector<int>> pixels_;
    Config config_;

    private:
};
