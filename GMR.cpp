#include "GMR.hpp"

float heisenberg (Particle & p1, Particle & p2, Json::Value&)
{
    return 
        - exp (norm_2 (p1.state.r - p2.state.r)) * 
        inner_prod (p1.state.s, p2.state.s);
}

float energy_contribution(Particle &p, Hamiltonian &H, Json::Value &info)
{
    float energy = 0;
    TR(nb, p.nbh) TR (ppi, H.pp_i) energy += (*ppi)(**nb, p, info);
    TR(pfi, H.pf_i) pfi -> first (p, pfi -> second, info);
    return energy;
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
        energy_delta = energy_contribution(*p, this -> hamiltonian, this -> interaction_info) - old_energy;

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
    float cut_off = this -> system_info["cut_off_radius"].asFloat();
    std::cout << "cut_off: " << cut_off << std::endl;
    TR(p, this -> particles)
    {
        p -> nbh.clear();

        
        TR(other, this -> particles)
        {
            // if (p == other) std::cout << p->state.r << " == " << other->state.r  << std::endl;
            if (p != other)
            {
                // if (norm_2(p -> state.r - other -> state.r) <= cut_off)
                if (dist_v_min((*p).state.r, (*other).state.r, this -> system_info) <= cut_off)
                {
                    // std::cout << norm_2(p -> state.r - other -> state.r) << std::endl;
                    p -> nbh.push_back(&(*other));
                    // std::cout << (*p).nbh.size() << std::endl;
                }
            }
            // std::cout << p->nbh.size() << std::endl;
        }
    }
}

void System::create_system(Json::Value & root)
{
    int width = 0;
    int lenght = 0;
    int height = 0;
    int l = 0;

    try {
        width = root["system"]["dimensions"]["width"].asInt();
        lenght = root["system"]["dimensions"]["lenght"].asInt();
        height = root["system"]["dimensions"]["height"].asInt();
        l = root["system"]["scale"].asInt();
    }
    catch (std::exception &e) {
        std::cout << e.what();
        throw BadDescriptor("Your system dimensions are bad configured.");
    }

    std::string structure = root["system"]["structure"].asString();

    this -> system_info = root["system"];
    this -> interaction_info = root["interaction_info"];


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
        
        std::cout << "You should specific the structure in the Json file" << std::endl;
    }
    
    
    // Fetch this from the root
    int e_count = root["system"]["number_of_free_electrons"].asInt();

    p_template.traits = eTraits;
    for (int i = 0; i < e_count; ++i)
    {
        p_template.state.r(0) = drand48() * width;
        p_template.state.r(1) = drand48() * lenght;
        p_template.state.r(2) = drand48() * height;
        this -> particles.push_back(p_template);  
    }

    Hamiltonian h_template;

    // h_template.pp_i.push_back(heisenberg);
    // this -> hamiltonian
    updateNBH();
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


// energies
// {

//     float electric (Particle & p, Field & e)
//     {
        
//         return - p.traits.charge * inner_prod (e, p.state.r);
//     }

//     float el_primero (Particle & p1, Particle & p2)
//     {
        
//         return - inner_prod (p1.state.s, p2.state.s);
//     }

//     float H_r (Particle & p1, std::vector<Particle> S)
//     {
//         float sum = 0;
//         for (int i = 0; i < S.size(); ++i)
//         {
//             sum += exp (norm_2 (p1.state.r - S[i].state.r) * inner_prod(p1.state.s, S[i].state.s));
//         }

//         return - sum;
//     }

//     float dist_v_min(vecf ri, vecf rj, Json::Value & sys){
//         vecf e1 = (rj - ri);

//         vecf W(3);
//         W(0) = sys["dimensions"]["width"].asFloat() / sys["scale"].asFloat();
//         W(1) = sys["dimensions"]["lenght"].asFloat() / sys["scale"].asFloat();
//         W(2) = sys["dimensions"]["height"].asFloat() / sys["scale"].asFloat();

//         vecf P(3);
//         P(0) = sys["P"]["x"].asFloat();
//         P(1) = sys["P"]["y"].asFloat();
//         P(2) = sys["P"]["z"].asFloat();

//         vecf e2(3);
//         e2(0) = P(0) * W(0) - e1(0);
//         e2(1) = P(1) * W(1) - e1(1);
//         e2(2) = P(2) * W(2) - e1(2);


//         e1(0) = abs(e1(0));
//         e1(1) = abs(e1(1));
//         e1(2) = abs(e1(2));

//         e2(0) = abs(e2(0));
//         e2(1) = abs(e2(1));
//         e2(2) = abs(e2(2));

//         vecf salida(3);

//         salida(0) = (e1(0) <= e2(0))? e1(0): e2(0);
//         salida(1) = (e1(1) <= e2(1))? e1(1): e2(1);
//         salida(2) = (e1(2) <= e2(2))? e1(2): e2(2);

//         return norm_2(salida);
//     }
// }