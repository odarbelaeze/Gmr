#include <fstream>
#include "GMR.hpp"
#include "GMR.cpp"

using namespace boost::numeric::ublas;

<<<<<<< HEAD
float distancia(Particle a, Particle b)
{
    float dist;
    dist = norm_2(a.state.r - b.state.r);
    return dist;
}

=======
>>>>>>> e29359eab86452b9a1b77c2d7079086d90975496
int main(int argc, char const *argv[])
{
    std::vector<Particle> P;
    Json::Value root;
    Json::Reader reader;

    throw BadDescriptor("Ay juemadre!");

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

    // TR(i, P)
    // {
    //     std::cout << (*i).state.r(0) << "\t" << (*i).state.r(1) << "\t" << (*i).state.r(2) << std::endl;
    // }

    // TR(i, P)
    // {
    //     std::cout << (*i).traits.name << "\t" << (*i).traits.charge << "\t" << (*i).traits.s_norm << "\t" << (*i).state.r(0) << "\t" << (*i).state.r(1) << "\t" << (*i).state.r(2) << std::endl;
    // }

    float banderita;
    float radio;

    radio = system_info["cut_off"].asFloat();
    TR(i, P)
    {
        TR(j, (*i).nbh)
        {
            banderita = distancia(*i, **j);
        }
    }


    return 0;
}