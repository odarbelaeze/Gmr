#include "GMR.hpp"
#include "GMR.cpp"

using namespace boost::numeric::ublas;

float heisenberg (Particle & p1, Particle & p2)
{
    return 
        - exp (norm_2 (p1.state.r - p2.state.r)) * 
        inner_prod (p1.state.s, p2.state.s);
}

float electric (Particle & p, Field & e)
{
    return - p.traits.charge * inner_prod (e, p.state.r);
}

float el_primero (Particle & p1, Particle & p2){
    return - inner_prod (p1.state.s, p2.state.s);
}


float H_r (Particle & p1, vector<Particle> S){
    float sum = 0;
    for (int i = 0; i < S.size(); ++i)
    {
        sum += exp (norm_2 (p1.state.r - S[i].state.r) * inner_prod(p1.state.s, S[i].state.s));
    }

    return - sum;
}





int main(int argc, char const *argv[])
{
    return 0;
}