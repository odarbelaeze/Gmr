#include "gmr.h"

using namespace boost::numeric::ublas;

float H_PP(Particle & p1, Particle & p2, Json::Value & root);
float H_E_Field(Particle& p1, Field& E, Json::Value& interactionInfo);

int main(int argc, char const *argv[])
{
    Json::Value root;
    Json::Reader reader;

    std::ifstream config_doc ("docs/descriptor_example.json");

    bool parsingSuccessful = reader.parse( config_doc, root, false );

    return 0;
}

float H_PP(Particle & p1, Particle & p2, Json::Value & interactionInfo)
{
    float sum = 0;
    float J = interactionInfo["all"]["J"].asFloat();
    float K_0 = interactionInfo["all"]["K_0"].asFloat();
    float I_0 = interactionInfo["all"]["I_0"].asFloat();

    if (p1.traits.name == "Ión" && p2.traits.name == "Ión")
    {
        sum = -J * inner_prod(p1.state.s, p2.state.s);
    }
    else if (p1.traits.name == "Electrón" && p2.traits.name == "Electrón")
    {
        sum = K_0 * exp(-norm_2(p1.state.r - p2.state.r)) * inner_prod(p1.state.s, p2.state.s);
    }
    else if ((p1.traits.name == "Electrón" && p2.traits.name == "Ión") || (p1.traits.name == "Ión" && p2.traits.name == "Electrón"))
    {
        sum = I_0 * exp(-norm_2(p1.state.r - p2.state.r)) * inner_prod(p1.state.s, p2.state.s);
    }
    return sum;

}

float H_E_Field(Particle& p1, Field& E, Json::Value& interactionInfo)
{
    return - p1.traits.charge * inner_prod(E, p1.state.r);
}
