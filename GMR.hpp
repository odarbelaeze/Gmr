#ifndef GMR_HPP_
#define GMR_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cmath>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#define TR(i, its) for(typeof(its.begin()) i = its.begin(); i != its.end(); i++)
typedef boost::numeric::ublas::vector<float> vecf;

struct PState
{
    vecf r;
    vecf s;
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

    void update_spin();
    void update_r();
    void roll_bak();
};

typedef vecf Field; 

typedef float (*PFI)(Particle &, Field &);
typedef float (*PPI)(Particle &, Particle &);
typedef void (*OnEventCB)(const Particle &, float);//en verdad va a tomar otras vainas

struct Hamiltonian
{
    std::vector<PPI> pp_i;
    std::map<PFI, Field &> pf_i;
};

//acá va lo de las energías
float energy_contribution (Particle &p, Hamiltonian &H);


class System
{
private:
    Hamiltonian hamiltonian;
    std::vector<Particle> particles;
    float thermal_energy;

public:
    System(std::ifstream &); //toca mirar lo de JSON
    ~System();

    void mcStep_thermal(OnEventCB cb);//mirar argunmentos
    void mcStep_dynamic(OnEventCB cb);//mirar argunmentos
    void updateNBH();

    float energy();

    const Hamiltonian& getHamiltonian();
    const std::vector<Particle>& getParticles();
    float getThermalEnergy();

    void setThermalEnergy(const float);
    void setHamiltonian(const Hamiltonian&);
};

vecf rand_vec (float);

const PTraits eTraits = {name: "Electrón", charge: -1, s_norm: 1};
const PTraits iTraits = {name: "Ión", charge: +1, s_norm: 1};

#endif