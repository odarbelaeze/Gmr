#include "GMR.hpp"


vecf rand_vec (float radius)
{
    boost::numeric::ublas::vector<float> r(3);
    float theta = 2.0f * M_PI * drand48();
    float phi   = 1.0f * M_PI * drand48();
    r(0) = radius * sin (theta) * cos (phi);
    r(1) = radius * sin (theta) * sin (phi);
    r(2) = radius * cos (theta);
    return r;
}


void Particle::update_spin(){
    this -> old_state = state; 
    this -> state.s += rand_vec(1);
    this -> state.s /= norm_2(this -> state.s);
    this -> state.s *= this -> traits.s_norm;
}

void Particle::roll_bak(){
    this -> state = this -> old_state;
}

float energy_contribution(Particle &p, Hamiltonian &H){
    float energy = 0;
    TR(nb, p.nbh) TR (ppi, H.pp_i) energy += (*ppi)(**nb, p);
    TR(pfi, H.pf_i) pfi -> first (p, pfi -> second);
    return energy;
}


const Hamiltonian& System::getHamiltonian(){
    return this -> hamiltonian;
 }

 const std::vector<Particle>& System::getParticles(){
    return this -> particles;
 }
 float System::getThermalEnergy(){
    return this -> thermal_energy;
}

void System::setHamiltonian(const Hamiltonian& hamiltonian){
    this -> hamiltonian = hamiltonian;
}

void System::setThermalEnergy(const float thermal_energy){
    this -> thermal_energy = thermal_energy;
}

void System::mcStep_thermal (OnEventCB cb){
    float old_energy;
    float energy_delta;
    float random;
    TR (p, this -> particles)
    {
        old_energy = energy_contribution(*p, this -> hamiltonian);
        p -> update_spin();
        energy_delta = energy_contribution (*p, this -> hamiltonian) - old_energy;

        if (energy_delta <= 0)
        {
            cb(*p, energy_delta);
        }
        else
        {
            random = drand48();
            if (random <= exp(- energy_delta / this -> thermal_energy))
            {
                cb (*p, energy_delta);
            }
            else
            {
                p -> roll_bak();
            }
        }   
    }
}

 float System::energy(){
    float energy = 0;
    TR (p, this -> particles) energy += energy_contribution(*p, this -> hamiltonian);
    return energy;
}


void System::updateNBH(){
    float un_radio_cualquiera = 0.5;
    TR(p, this -> particles){
        p -> nbh.clear();
        TR(other, this -> particles){
            if (p != other)
            {
                if (norm_2(p -> state.r - other -> state.r) < un_radio_cualquiera)
                {
                    p -> nbh.push_back(&(*other));
                }
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}