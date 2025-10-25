#ifndef DIGAMMA_WRITEOBJ_HPP
#define DIGAMMA_WRITEOBJ_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <initializer_list>

#include "geometry/kernel/Surface.hpp"

namespace digamma::io {

namespace internal {

template <typename T>
std::size_t writeSingleObject(const T&, std::ofstream&, int, std::size_t, const std::string&) {
    throw std::runtime_error("write_obj not implemented for this type");
}

template <>
inline std::size_t writeSingleObject<geometry::Surface>(const geometry::Surface& surf,
    std::ofstream& os,
    int id,
    std::size_t offset,
    const std::string& message)
{
    if (message == "")  os << "o surface" << id << "\n";
    else os << "o " << message << id << "\n";

    const auto& [V, F] = surf.data();

    for (int i = 0; i < V.rows(); ++i)
        os << "v "
            << V(i,0) << " "
            << V(i,1) << " "
            << V(i,2) << "\n";

    for (int i = 0; i < F.rows(); ++i)
        os << "f "
            << F(i,0)+1 + offset << " "
            << F(i,1)+1 + offset << " "
            << F(i,2)+1 + offset << "\n";

    return offset + V.rows();
}

template <>
inline std::size_t writeSingleObject<geometry::Body>(const geometry::Body& body,
    std::ofstream& os,
    int id,
    std::size_t offset,
    const std::string& message)
{
    if (message == "") return writeSingleObject(body.boundary(), os, id, offset, "body");
    return writeSingleObject(body.boundary(), os, id, offset, message);
}

}

template <typename T>
void writeOBJ(const std::vector<T>& objs, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("cannot open file");

    std::size_t offset = 0;
    int i = 0;
    for (const auto& obj : objs) {
        offset = internal::writeSingleObject(obj, out, i, offset, "");
        ++i;
    }
}

template <typename T>
void writeOBJ(std::initializer_list<T> objs, const std::string& filename) {
    writeOBJ(std::vector(objs), filename);
}


}

#endif // DIGAMMA_WRITEOBJ_HPP
