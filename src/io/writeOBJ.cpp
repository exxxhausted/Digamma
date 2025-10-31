#include "io/writeOBJ.hpp"

#include <fstream>

namespace digamma::io {

std::size_t writeOBJ(const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& F,
    std::ofstream& os,
    std::size_t offset)
{
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

}

