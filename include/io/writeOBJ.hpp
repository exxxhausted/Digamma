#ifndef DIGAMMA_WRITEOBJ_HPP
#define DIGAMMA_WRITEOBJ_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <concepts>
#include <Eigen/Core>

namespace digamma::io {

std::size_t writeOBJ(const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& F,
    std::ofstream& os,
    std::size_t offset = 0);

template <typename T>
concept HasSaveOBJ = requires(const T t, const std::string& filename, std::size_t offset) {
    { t.saveOBJ(filename, offset) } -> std::same_as<std::size_t>;
};

template <HasSaveOBJ T>
std::size_t saveOBJ(const std::vector<T>& vec, const std::string& filename, std::size_t offset = 0) {
    for (const auto& t : vec) offset += t.saveOBJ(filename, offset);
    return offset;
}

template <HasSaveOBJ T>
std::size_t saveOBJ(const std::initializer_list<T>& list, const std::string& filename, std::size_t offset = 0) {
    return saveOBJ(std::vector(list), filename, offset);
}

}
#endif // DIGAMMA_WRITEOBJ_HPP
