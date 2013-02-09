#include <fstream>
#include "../gmr.h"

using namespace boost::numeric::ublas;

float distancia(Particle a, Particle b)
{
    return norm_2(a.state.r - b.state.r);
}

int main(int argc, char const *argv[])
{
    std::vector<Particle> P;
    Json::Value root;
    Json::Reader reader;

    std::ifstream config_doc ("docs/descriptor_example.json");

    bool parsingSuccessful = reader.parse( config_doc, root, false );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
    }

    System A(root);
    P = A.getParticles();

    
    int cantidad_e = 0;
    int cantidad_I = 0;

    TR(i, P)
    {
        if ((*i).traits.name == "Ión")
        {
            cantidad_I++;
        }
        else if ((*i).traits.name == "Electrón")
        {
            cantidad_e++;
        }
    }


    std::string blabla;
    std::cout << "Cantidad Iones: " << cantidad_I << std::endl;
    std::cout << "Cantidad Electrones: " << cantidad_e << std::endl;
    blabla = ((cantidad_e == root["system"]["number_of_free_electrons"].asInt())? "true":"false");
    std::cout << "Cantidad correcta de electrones: " << blabla << std::endl;
    blabla = ((cantidad_I == (root["system"]["dimensions"]["width"].asInt()*root["system"]["dimensions"]["height"].asInt() * root["system"]["dimensions"]["lenght"].asInt()))? "true":"false");
    std::cout << "Cantidad correcta de iones: " << blabla << std::endl;

    std::cout << std::endl;
    
    bool problema = false;
    TR(i, P)
    {
        TR(j, (*i).nbh)
        {
            if (distancia(*i, **j) > root["system"]["cut_off_radius"].asFloat())
            {
                problema = true;
            }
        }
    }
    

    if (problema == true)
    {
        std::cout << "Hay problemas con los vecinos" << std::endl;
    }
    else
    {
        std::cout << "No hay problemas con los vecinos" << std::endl;   
    }

    std::cout   << "Nombre:" << "\t"
                << "Carga:" << "\t"
                << "Norma Spin:" << "\t"
                << "x:" << "\t"
                << "y:" << "\t"
                << "z:" << "\t"
                << "Cantidad nbh:"
                << std::endl;

    TR(i, P)
    {
        std::cout   << (*i).traits.name << "\t"
                    << (*i).traits.charge << "\t"
                    << (*i).traits.s_norm << "\t"
                    << (*i).state.r(0) << "\t"
                    << (*i).state.r(1) << "\t"
                    << (*i).state.r(2) << "\t"
                    << (*i).nbh.size()
                    << std::endl;
    }

    std::cout << std::endl;

    return 0;
}