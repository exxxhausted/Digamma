#ifndef DIGAMMA_SERIALIZABLE_HPP
#define DIGAMMA_SERIALIZABLE_HPP

#include <string>

namespace digamma::geometry {

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual void saveOBJ(const std::string& filename) const = 0;
};

}

#endif // DIGAMMA_SERIALIZABLE_HPP
