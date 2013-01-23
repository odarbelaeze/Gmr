#include "Gmr.hpp"

namespace Gmr 
{
    void Particle::update_state (PState (*new_state)(PState &))
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
        TR(nb, p.nbh) TR (ppi, H.pp_interactions) energy += (*ppi)(**nb, p);
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

    void System::setHamiltonian (const Hamiltonian& hamiltonian)
    {
        this -> hamiltonian = hamiltonian;
    }

    // TODO: Set the appropiate copy constructor for the struct Particle
    // void System::setParticles   (const std::vector<Particle>& particles)
    // {
    //     this -> particles = particles;
    // }
    void System::setThermalEnergy (const float thermal_energy)
    {
        this -> thermal_energy = thermal_energy;
    }

     void System::mcStep (PState (*new_state)(PState &), OnEventCB cb)
     {
        float old_energy;
        float energy_delta;
        float r;
        TR (p, this -> particles)
        {
            old_energy = energy_contribution (*p, this -> hamiltonian);
            p -> update_state (new_state);
            energy_delta = energy_contribution (*p, this -> hamiltonian) - old_energy;

            if (energy_delta <= 0)
            {
                cb (*p, energy_delta);
            }
            else
            {
                r = (float) drand48();
                if (r <= std::exp (- energy_delta / this -> thermal_energy))
                {
                    cb (*p, energy_delta);
                }
                else
                {
                    p -> rollback_state ();
                }
            }   
        }
     }

    float System::energy ()
    {
        float energy = 0;
        TR (p, this -> particles) energy += energy_contribution(*p, this -> hamiltonian);
        return energy;
    }

    void System::updateNBH (NBHTest nbht)
    {
        TR (p, this -> particles)
        {
            p -> nbh .clear();
            TR (o, this -> particles) if (nbht(*p, *o)) p -> nbh .push_back (&(*o));
        }
    }

    boost::numeric::ublas::vector<float> rand_unit_vec ()
    {
        boost::numeric::ublas::vector<float> r(3);
        float theta = 2.0f * M_PI * drand48();
        float phi   = 1.0f * M_PI * drand48();
        r(0) = sin (theta) * cos (phi);
        r(1) = sin (theta) * sin (phi);
        r(2) = cos (theta);
        return r;
    }
}

// int main(int argc, char const *argv[])
// {
//     std::cout << Gmr::eTraits.name << std::endl;
//     std::cout << Gmr::iTraits.name << std::endl;
//     return 0;
// }