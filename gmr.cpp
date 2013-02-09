#include "gmr.h"


void Particle::update_spin(float radius)
{
    this -> old_state = state; 
    this -> state.s += radius * rand_vec();
    this -> state.s /= norm_2(this -> state.s);
    this -> state.s *= this -> traits.s_norm;
}

void Particle::roll_bak()
{
    this -> state = this -> old_state;
}

void Particle::update_r(float radius)
{
    this -> old_state = state; 
    this -> state.r += radius * rand_vec();
    // this -> state.r /= norm_2(this -> state.s);
    // this -> state.r *= this -> traits.s_norm;
}

float energy_contribution(Particle &p, Hamiltonian &H, Json::Value &info)
{
    float energy = 0;
    TR(nb, p.nbh) TR (ppi, H.pp_i) energy += (*ppi)(**nb, p, info);
    TR(pfi, H.pf_i) energy += pfi -> first (p, pfi -> second, info);
    return energy;
}

float total_energy_contribution (Particle &p, Hamiltonian &H, Json::Value &info)
{
    float totalEnergy = 0;
    TR(nb, p.nbh) TR (ppi, H.pp_i) totalEnergy += 2.0 * (*ppi)(**nb, p, info);
    TR(pfi, H.pf_i) totalEnergy += pfi -> first (p, pfi -> second, info);
    return totalEnergy;
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
        old_energy = total_energy_contribution(*p, this -> hamiltonian, this -> interaction_info);
        p -> update_spin(this -> update_policy["radius_s"].asFloat());
        energy_delta = total_energy_contribution(*p, this -> hamiltonian, this -> interaction_info) - old_energy;

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
    float cut_off = this -> system_info["cut_off_radius"].asFloat();
    TR(p, this -> particles)
    {
        p -> nbh.clear();
        TR(other, this -> particles)
            if (p != other)
                if (dist_v_min((*p).state.r, (*other).state.r, this -> system_info) <= cut_off)
                    p -> nbh.push_back(&(*other));
    }
}

void System::create_system(Json::Value & root)
{
    this -> system_info = root["system"];
    this -> interaction_info = root["interaction_info"];
    this -> update_policy = root["update_policy"];

    int width = 0;
    int lenght = 0;
    int height = 0;
    int l = 0;

    try {
        width = this -> system_info["dimensions"]["width"].asInt();
        lenght = this -> system_info["dimensions"]["lenght"].asInt();
        height = this -> system_info["dimensions"]["height"].asInt();
        l = this -> system_info["scale"].asInt();
    }
    catch (std::exception &e) {
        std::cout << e.what();
        throw BadDescriptorException("Your system dimensions and scale are bad configured.");
    }


    std::string structure = this -> system_info["structure"].asString();


    Particle p_template;
    
    p_template.traits = iTraits;
    this -> particles.clear();
    if (structure == "sc")
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < lenght; ++j)
            {
                for (int k = 0; k < height; ++k)
                {
                    p_template.state.r(0) = (i + 0.0f) * l;
                    p_template.state.r(1) = (j + 0.0f) * l;
                    p_template.state.r(2) = (k + 0.0f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);

                }
            }
        }
    }
    else if (structure == "bcc")
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < lenght; ++k)
                {
                    p_template.state.r(0) = (i + 0.0f) * l;
                    p_template.state.r(1) = (j + 0.0f) * l;
                    p_template.state.r(2) = (k + 0.0f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);
                    

                    p_template.state.r(0) = (i + 0.5f) * l;
                    p_template.state.r(1) = (j + 0.5f) * l;
                    p_template.state.r(2) = (k + 0.5f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);
                    
                }
            }
        }
    }
    else if (structure == "fcc")
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < lenght; ++k)
                {
                    p_template.state.r(0) = (i + 0.0f) * l;
                    p_template.state.r(1) = (j + 0.0f) * l;
                    p_template.state.r(2) = (k + 0.0f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);
                    

                    p_template.state.r(0) = (i + 0.5f) * l;
                    p_template.state.r(1) = (j + 0.5f) * l;
                    p_template.state.r(2) = (k + 0.0f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);
                    

                    p_template.state.r(0) = (i + 0.0f) * l;
                    p_template.state.r(1) = (j + 0.5f) * l;
                    p_template.state.r(2) = (k + 0.5f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);
                    

                    p_template.state.r(0) = (i + 0.5f) * l;
                    p_template.state.r(1) = (j + 0.0f) * l;
                    p_template.state.r(2) = (k + 0.5f) * l;
                    p_template.state.s = rand_vec();
                    this -> particles.push_back(p_template);
                    
                }
            }
        }
    }
    else
    {
        throw BadDescriptorException("The system structure " + structure + " is not supprted yet.");
    }
    
    int e_count = 0;
    try {
        e_count = this -> system_info["number_of_free_electrons"].asInt();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw BadDescriptorException("You must especify number_of_free_electrons in the Json descriptor.");
    }

    p_template.traits = eTraits;
    for (int i = 0; i < e_count; ++i)
    {
        p_template.state.r(0) = drand48() * width * l;
        p_template.state.r(1) = drand48() * lenght * l;
        p_template.state.r(2) = drand48() * height * l;
        this -> particles.push_back(p_template);
    }

    this -> updateNBH();
}

System::System(Json::Value & root)
{
    
    this -> create_system(root);
}

System::~System(){}

vecf rand_vec ()
{
    vecf r(3);
    float theta = 2.0f * M_PI * drand48();
    float phi   = 1.0f * M_PI * drand48();
    r(0) = sin (theta) * cos (phi);
    r(1) = sin (theta) * sin (phi);
    r(2) = cos (theta);
    return r;
}



float electric (Particle & p, Field & e)
{
    
    return - p.traits.charge * inner_prod (e, p.state.r);
}

float el_primero (Particle & p1, Particle & p2)
{
    
    return - inner_prod (p1.state.s, p2.state.s);
}

float H_r (Particle & p1, std::vector<Particle> S)
{
    float sum = 0;
    for (int i = 0; i < S.size(); ++i)
    {
        sum += exp (norm_2 (p1.state.r - S[i].state.r) * inner_prod(p1.state.s, S[i].state.s));
    }

    return - sum;
}

float heisenberg (Particle & p1, Particle & p2, Json::Value&)
{
    return 
        - exp (norm_2 (p1.state.r - p2.state.r)) * 
        inner_prod (p1.state.s, p2.state.s);
}



float dist_v_min(vecf ri, vecf rj, Json::Value & sys){
    vecf dims(3);
    dims(0) = sys["dimensions"]["width"].asFloat() * sys["scale"].asFloat();
    dims(1) = sys["dimensions"]["lenght"].asFloat() * sys["scale"].asFloat();
    dims(2) = sys["dimensions"]["height"].asFloat() * sys["scale"].asFloat();

    boost::numeric::ublas::vector<int> P(3);
    P(0) = sys["periodic_boundary_conditions"]["x"].asInt();
    P(1) = sys["periodic_boundary_conditions"]["y"].asInt();
    P(2) = sys["periodic_boundary_conditions"]["z"].asInt();

    vecf e1 = (rj - ri);
    e1(0) = abs(e1(0));
    e1(1) = abs(e1(1));
    e1(2) = abs(e1(2));
    
    vecf e2(3);
    e2(0) = abs(P(0) * dims(0) - e1(0));
    e2(1) = abs(P(1) * dims(1) - e1(1));
    e2(2) = abs(P(2) * dims(2) - e1(2));

    vecf salida(3);

    salida(0) = (e1(0) <= e2(0))? e1(0): e2(0);
    salida(1) = (e1(1) <= e2(1))? e1(1): e2(1);
    salida(2) = (e1(2) <= e2(2))? e1(2): e2(2);

    return norm_2(salida);
}

