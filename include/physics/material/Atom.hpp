#ifndef DIGAMMA_ATOM_HPP
#define DIGAMMA_ATOM_HPP

#include <string>
#include <functional>

namespace digamma::physics {

class Atom {
public:

    Atom(const std::string& symbol);

    explicit Atom(std::string symbol,
        int z,
        double a,
        std::function<double(double)> photo,
        std::function<double(double)> compton,
        std::function<double(double)> pair);

    const std::string& symbol() const;
    int Z() const;
    double A() const;
    double sigmaPhoto(double E) const;
    double sigmaCompton(double E) const;
    double sigmaPair(double E) const;
    double sigmaTotal(double E) const;

private:

    const std::string symbol_;
    const int Z_;
    const double A_;
    const std::function<double(double)> photo_;
    const std::function<double(double)> compton_;
    const std::function<double(double)> pair_;

};

}

#endif // DIGAMMA_ATOM_HPP
