#include "GMR.hpp"
#include "GMR.cpp"

using namespace boost::numeric::ublas;

float H_II(Particle & p1, Json::Value & root);
float H_EE(Particle & p1, Json::Value & root);
float H_IE(Particle & p1, Json::Value & root);
float H_E_Field(Particle & p1, Field & E, Json::Value & root);
// float H_gradient_concentration(Particle & p1, Json::Value & root);



int main(int argc, char const *argv[])
{
    Json::Value root;
    Json::Reader reader;

    std::ifstream config_doc ("docs/descriptor_example.json");

    bool parsingSuccessful = reader.parse( config_doc, root, false );

    // std::cout << root["interaction_info"]["all"]["J"].asFloat() << std::endl;
    return 0;
}


float H_II(Particle & p1, Json::Value & root)
{
    float J = root["interaction_info"]["all"]["J"].asFloat();
    float sum = 0;

    TR(i, p1.nbh)
    {
        sum += inner_prod(p1.state.s, ((**i)).state.s);
    }

    return -J * sum;
}

float H_EE(Particle & p1, Json::Value & root)
{
    float K_0 = root["interaction_info"]["all"]["K_0"].asFloat();
    float sum = 0;

    TR(i, p1.nbh)
    {
        sum += K_0 * exp(-norm_2(p1.state.r - ((**i)).state.r)) * inner_prod(p1.state.s, ((**i)).state.s);
    }

    return - sum;
}

float H_IE(Particle & p1, Json::Value & root)
{
    float I_0 = root["interaction_info"]["all"]["I_0"].asFloat();
    float sum = 0;

    TR(i, p1.nbh)
    {
        sum += I_0 * exp(-norm_2(p1.state.r - ((**i)).state.r)) * inner_prod(p1.state.s, ((**i)).state.s);
    }

    return - sum;
}

float H_E_Field(Particle & p1, Field & E, Json::Value & root)
{
    return - p1.traits.charge * inner_prod(E, p1.state.r);
}

// float H_gradient_concentration(Particle & p1, Json::Value & root)
// {

// }