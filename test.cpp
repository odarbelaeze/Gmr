#include <fstream>
#include "GMR.hpp"
#include "GMR.cpp"

using namespace boost::numeric::ublas;

float distancia(Particle a, Particle b)
{
    float dist;
    dist = norm_2(a.state.r - b.state.r);
    return dist;
}

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

    float banderita;
    float radio;


    return 0;
}