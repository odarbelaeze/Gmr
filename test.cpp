#include <fstream>
#include "GMR.hpp"
#include "GMR.cpp"

using namespace boost::numeric::ublas;



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

    TR(i, P)
    {
        std::cout << (*i).state.r << std::endl;
    }


    return 0;
}