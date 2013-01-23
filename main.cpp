#include "Gmr.hpp"

using namespace Gmr;
using namespace boost::numeric::ublas;

float heisenberg (Particle & p1, Particle & p2)
{
    return 
        - exp (norm_2 (p1.state.r - p2.state.r)) * 
        inner_prod (p1.state.s, p2.state.s);
}

float electric (Particle & p, Field & e)
{
    return 
        - p.traits.charge * e.intensity * 
        inner_prod (e.direction, p.state.r);
}

int main(int argc, char const *argv[])
{
    boost::numeric::ublas::vector<float> r;
    for (int i = 0; i < 100; ++i)
    {
        r = rand_unit_vec ();
        std::cout << r << "\t" 
            << norm_2 (r) << std::endl;
    }
    return 0;
}