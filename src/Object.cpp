/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Object
*/

#include "Object.hpp"
#include <limits>

namespace RayTracer {
    ObjectList::ObjectList(const std::shared_ptr<Object> &object)
    {
        this->add(object);
    }

    void ObjectList::add(const std::shared_ptr<Object> &object)
    {
        this->objects.push_back(object);
    }

    void ObjectList::clear()
    {
        this->objects.clear();
    }

    hitInfo ObjectList::hits(const Ray &ray) const
    {
        hitInfo hit{ { 0, 0, 0 }, { 0, 0, 0 }, 0, false, false, nullptr };
        double closest = 1e32;
        for (const std::shared_ptr<RayTracer::Object> &object : this->objects) {
            hitInfo temp = (object.get())->hits(ray);
            // if (temp.t != 0)
            //     std::cerr << temp.t << std::endl;
            if (temp.hit && temp.t < closest) {
                hit = temp;
                closest = temp.t;
            }
        }
        return hit;
    }
}// namespace RayTracer