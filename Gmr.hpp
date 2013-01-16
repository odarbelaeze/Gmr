#ifndef GMR_HPP_
#define GMR_HPP_

#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#define TR(i, its) for(typeof(its.begin()) i = its.begin(); i != its.end(); i++)

namespace Gmr
{
    struct PState
    {
        boost::numeric::ublas::vector<float> r;//r es la posición
        boost::numeric::ublas::vector<float> s;//s es el spin
    };
    
    struct PTraits
    {
        std::string name;
        float charge;
        float s_norm;
    };

    struct Particle
    {
        PState state;
        PState old_state;
        PTraits &traits;
        std::vector<Particle*> nbh;

        void update_state (PState (*new_state)(PState &));
        void rollback_state ();
    };

    struct Field
    {
        float intensity;
        boost::numeric::ublas::vector<float> direction;
    };

    typedef float (*PFInteraction)(Particle &, Field &);
    typedef float (*PPInteraction)(Particle &, Particle &);
    typedef bool (*NBHTest)(Particle &, Particle &);
    typedef void  (*OnEventCB)(const Particle&, float);
    typedef std::pair<PFInteraction, Field &> IFPair;

    struct Hamiltonian
    {
        std::vector<PPInteraction> pp_interactions;
        std::map<PFInteraction, Field &> pf_interactions;
    };

    float energy_contribution (Particle &p, Hamiltonian &H);

    class System
    {
        Hamiltonian hamiltonian;
        std::vector<Particle> particles;
        float thermal_energy;

    public:
        System();
        System(int, int);
        ~System();
    
        void mcStep (PState (*new_state)(PState &), OnEventCB);
        void updateNBH (NBHTest);
        float energy ();

        const Hamiltonian& getHamiltonian();
        const std::vector<Particle>& getParticles();
        float getThermalEnergy();

        void setHamiltonian (const Hamiltonian&);
        // void setParticles   (const std::vector<Particle>&);
        void setThermalEnergy (const float);
    };

    const PTraits eTraits = {name: "Electrón", charge: -1, s_norm: 1};
    const PTraits iTraits = {name: "Ión", charge: +1, s_norm: 1};
}

#endif