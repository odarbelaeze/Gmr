#ifndef GMR_HPP_
#define GMR_HPP_

#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>

#define TR(i, its) for(typeof(its.begin()) i = its.begin(); i != its.end(); i++)
typedef boost::numeric::ublas::vector<float> vecf;

class BadDescriptorException: public std::exception
{
public:
    BadDescriptorException(): error("Unknown error") {}
    BadDescriptorException(const std::string _error): error(_error) {}
    virtual ~BadDescriptorException() throw() {}

    virtual const char* what() const throw()
    {
        return ("The descriptor was bad configured: " + this -> error).data();
    }

private:
    const std::string error;
};

struct PState
{
    vecf r;
    vecf s;
    PState(): r(3), s(3) {}
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
    PTraits traits;
    std::vector<Particle*> nbh;

    void update_spin(float);
    void update_r(float);
    void roll_bak();
};

typedef vecf Field; 

typedef float (*PFI)(Particle &, Field &, Json::Value&);
typedef float (*PPI)(Particle &, Particle &, Json::Value&);
typedef void (*OnEventCB)(const Particle &, float);

struct Hamiltonian
{
    std::vector<PPI> pp_i;
    std::map<PFI, Field &> pf_i;
};

float energy_contribution (Particle &p, Hamiltonian &H, Json::Value &info);

float total_energy_contribution (Particle &p, Hamiltonian &H, Json::Value &info);

class System
{
private:
    Hamiltonian hamiltonian;
    Json::Value interaction_info;
    Json::Value system_info;
    Json::Value update_policy;
    std::vector<Particle> particles;
    float thermal_energy;

    void create_system (const Json::Value &);     // This will be the actual function in wich the system is created.

public:
    System(const char*);
    System(const std::string);
    System(std::ifstream &);
    System(std::istream &);
    System(const Json::Value &);
    ~System();

    void mcStep_thermal(OnEventCB cb);      // Mirar argunmentos
    void mcStep_dynamic(OnEventCB cb);      // Mirar argunmentos
    void updateNBH();

    float energy();

    const Hamiltonian& getHamiltonian();
    const std::vector<Particle>& getParticles();
    float getThermalEnergy();

    void setThermalEnergy(const float);
    void setHamiltonian(const Hamiltonian&);

};

vecf  rand_vec ();
float dist_v_min(vecf, vecf, Json::Value &);

const PTraits eTraits = {name: "Electrón", charge: -1, s_norm: 1};
const PTraits iTraits = {name: "Ión", charge: +1, s_norm: 1};

#endif