/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** main
*/

#include "Config.hpp"
#include "Output.hpp"

#include <iostream>

int errorHandling(int ac, char **av)
{
    if (ac != 2 && ac != 3) {
        std::cerr << "Usage: " << av[0] << " <cfg_file> (filename)" << std::endl;
        return 84;
    }
    if (std::string(av[1]) == "-h" || std::string(av[1]) == "--help") {
        std::cout << "USAGE:\n\t" << av[0] << " <cfg_file> (filename)\n\nDESCRIPTION:\n\t"
                  << "Raytracer-C++ is a raytracer written in C++\n\t"
                  << "It takes a CONFIG file as input and outputs a PPM image of name filename.ppm (output.ppm by default)\n\nOPTIONS:\n\t"
                  << "-h, --help\tDisplay this help message" << std::endl;
        return 0;
    }
    return -1;
}

int main(int ac, char **av)
{
    int return_value = 0;
    if ((return_value = errorHandling(ac, av)) != -1)
        return return_value;

    Config config;
    try {
        std::string file_path(av[1]);
        config = Config(file_path);
    } catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 84;
    }

    std::string filename = ac == 3 ? av[2] + std::string(".ppm") : "./output.ppm";
    Output output(std::move(config));
    output.generateImage();
    output.writeInFile(filename);

    return 0;
}
