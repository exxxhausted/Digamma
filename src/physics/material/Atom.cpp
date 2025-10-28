#include "physics/material/Atom.hpp"
#include "io/AtomLoader.hpp"

namespace digamma::physics {

Atom::Atom(const std::string& symb) :  Atom(std::move(io::AtomLoader::loadJSON("./Database/Atoms/" + symb + ".json"))) {}

Atom::Atom(std::string symbol,
           int z,
           double a,
           std::function<double(double)> photo,
           std::function<double(double)> compton,
           std::function<double(double)> pair) :
    symbol_(std::move(symbol)),
    Z_(z),
    A_(a),
    photo_(std::move(photo)),
    compton_(std::move(compton)),
    pair_(std::move(pair)) {}

const std::string& Atom::symbol() const { return symbol_; }

int Atom::Z() const { return Z_; }

double Atom::A() const { return A_; }

double Atom::sigmaPhoto(double E) const { return photo_(E); }

double Atom::sigmaCompton(double E) const { return compton_(E); }

double Atom::sigmaPair(double E) const { return pair_(E); }

double Atom::sigmaTotal(double E) const { return sigmaPhoto(E) + sigmaCompton(E) + sigmaPair(E); }

}
