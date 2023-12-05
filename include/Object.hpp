/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Object
*/

#pragma once

#include "hitInfo.hpp"
#include <memory>


namespace RayTracer {
    class Object
    {
        public:
        Object() = default;
        virtual ~Object() = default;

        virtual hitInfo hits(const Ray &ray) const = 0;

        protected:
        private:
    };

    class ObjectList : public Object
    {
        public:
        ObjectList() = default;
        ObjectList(const std::shared_ptr<Object> &object);
        ~ObjectList() {
            clear();
        }

        void add(const std::shared_ptr<Object> &object);
        void clear();
        hitInfo hits(const Ray &ray) const;

        std::vector<std::shared_ptr<Object>> objects;

        protected:
        private:
    };
}// namespace RayTracer