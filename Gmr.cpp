#include "Gmr.hpp"

namespace Gmr
{
    void Particle::update_state (State (*new_state)(State &))
    {
        this -> old_state = state;
        this -> state = new_state(this -> state);
    }
    
    void Particle::rollback_state ()
    {
        this -> state = this -> old_state;
    }

    float energy_contribution (Particle &p, Hamiltonian &H)
    {
        float energy = 0;
        TR(nb, p.nbh) TR (ppi, H.pp_interactions) energy += ppi(*nb, p);
        TR(pfi, H.pf_interactions) pfi -> first (p, pfi -> second);
        return energy;
    }

    System::System (): thermal_energy(0)
    {

    }

    System::~System ()
    {

    }

    const Hamiltonian& System::getHamiltonian()
    {
        return this -> hamiltonian;
    }
    const std::vector<Particle>& System::getParticles()
    {
        return this -> particles;
    }
    float System::getThermalEnergy()
    {
        return this -> thermal_energy;
    }
    void System::setHamiltonian (const Hamiltonian&)
    {

    }
    void System::setParticles   (const std::vector<Particle>&)
    {

    }
    void System::setThermalEnergy (const float)
    {

    }

}

int main(int argc, char const *argv[])
{
    
    return 0;
}