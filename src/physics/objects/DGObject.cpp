#include "physics/objects/DGObject.hpp"

namespace digamma::physics {

DGObject::DGObject(std::string name, geometry::Body body, Material material) : name_(std::move(name)), body_(std::move(body)), material_(std::move(material)) {}

const std::string& DGObject::name() const { return name_; }

const geometry::Body& DGObject::body() const { return body_; }

const Material& DGObject::material() const { return material_; }

}