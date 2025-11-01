#ifndef DIGAMMA_WRITEOBJ_HPP
#define DIGAMMA_WRITEOBJ_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <concepts>
#include <Eigen/Core>
#include <fstream>

namespace digamma::io {

std::size_t writeOBJ(const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& F,
    std::ofstream& os,
    std::size_t offset = 0);

template <typename T>
concept HasWriteOBJ = requires(const T t, std::ofstream& os, std::size_t offset) {
    { t.writeOBJ(os, offset) } -> std::same_as<std::size_t>;
};

template <HasWriteOBJ T>
std::size_t saveOBJ(const std::vector<T>& vec, const std::string& filename, std::size_t offset = 0) {
    std::ofstream os(filename);
    for (const auto& t : vec) offset += t.writeOBJ(os, offset);
    return offset;
}

template <HasWriteOBJ T>
std::size_t saveOBJ(const std::initializer_list<T>& list, const std::string& filename, std::size_t offset = 0) {
    return saveOBJ(std::vector(list), filename, offset);
}

}
#endif // DIGAMMA_WRITEOBJ_HPP
