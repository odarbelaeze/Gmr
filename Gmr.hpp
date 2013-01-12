#ifndef GMR_HPP_
#define GMR_HPP_

#include <vector>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace Gmr
{
    struct State
    {
        boost::numeric::ublas::vector<float> r;//r es la posición
        boost::numeric::ublas::vector<float> s;//s es el spin
        float s_norm;
    };
    
    struct Traits
    {
        std::string nombre;
        float charge;
        float s_norm;
    };

    struct Particle
    {
        State state;
        State new_state;
        Traits &traits;
        std::vector<Particle*> nbh;//el asterisco es por si modifico uno se modifiquen todos

        void update_state (State (*new_state)(State &));
        void commit_state ();
    };

    struct Field
    {
        float intensity;
        boost::numeric::ublas::vector<float> direction;
    };

    typedef float (*FPInteraction)(Particle &, Field &);

    typedef float (*PPInteraction)(Particle &, Particle &);

    struct hamiltonian
    {
        std::vector<PPInteraction> pp_interactions;
        std::vector<FPInteraction> fp_interactions;
    };


}

#endif