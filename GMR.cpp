#include "GMR.hpp"


vecf rand_vec ()
{
    boost::numeric::ublas::vector<float> r(3);
    float theta = 2.0f * M_PI * drand48();
    float phi   = 1.0f * M_PI * drand48();
    r(0) = sin (theta) * cos (phi);
    r(1) = sin (theta) * sin (phi);
    r(2) = cos (theta);
    return r;
}


void Particle::update_spin()
{
    this -> old_state = state; 
    this -> state.s += rand_vec();
    this -> state.s /= norm_2(this -> state.s);
    this -> state.s *= this -> traits.s_norm;
}

void Particle::roll_bak()
{
    this -> state = this -> old_state;
}

float energy_contribution(Particle &p, Hamiltonian &H, Json::Value &info)
{
    float energy = 0;
    TR(nb, p.nbh) TR (ppi, H.pp_i) energy += (*ppi)(**nb, p, info);
    TR(pfi, H.pf_i) pfi -> first (p, pfi -> second, info);
    return energy;
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

void System::setHamiltonian(const Hamiltonian& hamiltonian)
{
    this -> hamiltonian = hamiltonian;
}

void System::setThermalEnergy(const float thermal_energy)
{
    this -> thermal_energy = thermal_energy;
}

void System::mcStep_thermal (OnEventCB cb)
{
    float old_energy;
    float energy_delta;
    float random;
    TR (p, this -> particles)
    {
        old_energy = energy_contribution(*p, this -> hamiltonian, this -> interaction_info);
        p -> update_spin();
        energy_delta = energy_contribution (*p, this -> hamiltonian, this -> interaction_info) - old_energy;

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

 float System::energy()
 {
    float energy = 0;
    TR (p, this -> particles) energy += energy_contribution(*p, this -> hamiltonian, this -> interaction_info);
    return energy;
}


void System::updateNBH()
{
    // Nothe the usage of a parameter stored in the Json Value :)
    float cut_off = this -> system_info["cut_off"].asFloat();
    TR(p, this -> particles)
    {
        p -> nbh.clear();
        TR(other, this -> particles)
        {
            if (p != other)
            {
                if (norm_2(p -> state.r - other -> state.r) <= cut_off)
                {
                    p -> nbh.push_back(&(*other));
                }
            }
        }
    }
}

void System::create_system(Json::Value & File){
    Json::Value root;
    Json::Reader reader;

    std::ifstream config_doc ("docs/descriptor_example.json");

    int width = root["system"]["dimensions"]["width"].asInt();
    int lenght = root["system"]["dimensions"]["lenght"].asInt();
    int height = root["system"]["dimensions"]["height"].asInt();

    Particle P;
    

    //para los iones
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < lenght; ++j)
        {
            for (int k = 0; k < height; ++k)
            {
                P.state.r(0) = i;
                P.state.r(1) = j;
                P.state.r(2) = k;
                P.traits = iTraits;

                this -> particles.push_back(P);
            }
        }
    }

    int cantidad_e = 10;

    for (int i = 0; i < cantidad_e; ++i)
    {
        P.state.r(0) = drand48() * width;
        P.state.r(1) = drand48() * lenght;
        P.state.r(2) = drand48() * height;
        P.traits = eTraits;
        this -> particles.push_back(P);
    }
}


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}