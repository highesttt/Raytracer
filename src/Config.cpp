/*
** EPITECH PROJECT, 2023
** Raytracer-C++ [WSL: Manjaro]
** File description:
** Config
*/

#include "Config.hpp"
#include "Factory.hpp"
#include "Object.hpp"
#include "Shapes.hpp"
#include <iostream>
#include <libconfig.h++>

Config::Config(std::string &fp)
{
    libconfig::Config config;

    try {
        config.readFile(fp.c_str());
    } catch (const libconfig::FileIOException &e) {
        throw std::invalid_argument("Error reading JSON file");
    } catch (const libconfig::ParseException &e) {
        throw std::invalid_argument("Error parsing JSON file");
    }

    try {
        image_width_ = config.lookup("settings.output_resolution.width");
        image_height_ = config.lookup("settings.output_resolution.height");
        aspect_ratio_ = image_width_ / image_height_;

        samples_per_pixel_ = config.lookup("settings.samples_per_pixel");
        max_depth_ = config.lookup("settings.max_depth");

        fov_ = config.lookup("camera.fov");
        focal_length_ = config.lookup("camera.focal_length");

        camera_position_ = Math::Point3D(
            config.lookup("camera.position.x"), config.lookup("camera.position.y"), config.lookup("camera.position.z"));

        camera_look_at_ = Math::Point3D(
            config.lookup("camera.look_at.x"), config.lookup("camera.look_at.y"), config.lookup("camera.look_at.z"));
    } catch (const libconfig::SettingNotFoundException &e) {
        throw std::invalid_argument("Error parsing JSON file: Missing setting");
    } catch (const libconfig::SettingTypeException &e) {
        throw std::invalid_argument("Error parsing JSON file: Wrong setting type");
    } catch (...) {
        throw std::invalid_argument("Error parsing JSON file");
    }

    // load objects

    Factory factory;
    SphereBuilder sphereBuilder = factory.createSphereBuilder();
    PlaneBuilder planeBuilder = factory.createPlaneBuilder();
    CylinderBuilder cylinderBuilder = factory.createCylinderBuilder();

    objects_ = std::make_shared<RayTracer::ObjectList>();

    try {
        const libconfig::Setting &primitives_setting = config.lookup("primitives");

        for (int i = 0; i < primitives_setting.getLength(); ++i) {
            const libconfig::Setting &primitive_setting = primitives_setting[i];
            const std::string primitive_type = primitive_setting["type"];

            const libconfig::Setting &material_setting = primitive_setting["material"];
            const std::string material_type = material_setting["type"];

            std::shared_ptr<RayTracer::Object> object;
            std::shared_ptr<Math::Material> material;

            const double x = primitive_setting["center"]["x"];
            const double y = primitive_setting["center"]["y"];
            const double z = primitive_setting["center"]["z"];

            if (material_type == "matte" || material_type == "mirror") {
                const double color_x = material_setting["color"]["r"];
                const double color_y = material_setting["color"]["g"];
                const double color_z = material_setting["color"]["b"];
                const double blur = material_type == "mirror" ? material_setting["blur"] : 0.0;
                if (material_type == "matte")
                    material = std::make_shared<Math::Matte>(Math::Color(color_x, color_y, color_z));
                else
                    material = std::make_shared<Math::Mirror>(Math::Color(color_x, color_y, color_z), blur);
            } else if (material_type == "transparency") {
                const double refraction = material_setting["level"];
                material = std::make_shared<Math::Glass>(refraction);
            }

            if (primitive_type == "sphere") {
                const double radius = primitive_setting["radius"];

                object = sphereBuilder.setCenter(Math::Point3D(x, y, z))
                             .setRadius(radius)
                             .setMaterial(material)
                             .buildSphere();
            } else if (primitive_type == "plane") {

                std::string axis = primitive_setting["axis"];
                Math::Vector3D normal;
                if (axis == "X") {
                    normal = Math::Vector3D(1, 0, 0);
                } else if (axis == "Y") {
                    normal = Math::Vector3D(0, 1, 0);
                } else if (axis == "Z") {
                    normal = Math::Vector3D(0, 0, 1);
                }

                object =
                    planeBuilder.setPoint(Math::Point3D(x, y, z)).setNormal(normal).setMaterial(material).buildPlane();
            } else if (primitive_type == "cylinder") {
                const double radius = primitive_setting["radius"];
                const double height = primitive_setting["height"];
                object = cylinderBuilder.setCenter(Math::Point3D(x, y, z))
                             .setRadius(radius)
                             .setHeight(height)
                             .setMaterial(material)
                             .buildCylinder();
            }
            objects_->add(object);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        throw std::invalid_argument("Error parsing JSON file: Missing setting");
    } catch (const libconfig::SettingTypeException &e) {
        throw std::invalid_argument("Error parsing JSON file: Wrong setting type");
    } catch (...) {
        throw std::invalid_argument("Error parsing JSON file");
    }
}

Config::~Config() {}

Config::Config(const Config &config)
{
    this->aspect_ratio_ = config.aspect_ratio_;
    this->image_width_ = config.image_width_;
    this->image_height_ = config.image_height_;
    this->samples_per_pixel_ = config.samples_per_pixel_;
    this->max_depth_ = config.max_depth_;
    this->fov_ = config.fov_;
    this->focal_length_ = config.focal_length_;
    this->camera_position_ = config.camera_position_;
    this->camera_look_at_ = config.camera_look_at_;
    this->objects_ = config.objects_;
}

Config Config::operator=(const Config &config)
{
    if (this == &config)
        return *this;
    this->aspect_ratio_ = config.aspect_ratio_;
    this->image_width_ = config.image_width_;
    this->image_height_ = config.image_height_;
    this->samples_per_pixel_ = config.samples_per_pixel_;
    this->max_depth_ = config.max_depth_;
    this->fov_ = config.fov_;
    this->focal_length_ = config.focal_length_;
    this->camera_position_ = config.camera_position_;
    this->camera_look_at_ = config.camera_look_at_;
    this->objects_ = config.objects_;
    return *this;
}
