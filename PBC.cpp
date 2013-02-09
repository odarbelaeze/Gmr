#include "gmr.h"

float dist_v_min(vecf ri, vecf rj, Json::Value & root){
    vecf e1 = (rj - ri);

    vecf W(3);
    W(0) = root["system"]["dimensions"]["width"].asFloat() / root["system"]["scale"].asFloat();
    W(1) = root["system"]["dimensions"]["lenght"].asFloat() / root["system"]["scale"].asFloat();
    W(2) = root["system"]["dimensions"]["height"].asFloat() / root["system"]["scale"].asFloat();

    vecf P(3);
    P(0) = root["system"]["P"]["x"].asFloat();
    P(1) = root["system"]["P"]["y"].asFloat();
    P(2) = root["system"]["P"]["z"].asFloat();

    vecf e2(3);
    e2(0) = P(0) * W(0) - e1(0);
    e2(1) = P(1) * W(1) - e1(1);
    e2(2) = P(2) * W(2) - e1(2);


    e1(0) = abs(e1(0));
    e1(1) = abs(e1(1));
    e1(2) = abs(e1(2));

    e2(0) = abs(e2(0));
    e2(1) = abs(e2(1));
    e2(2) = abs(e2(2));

    vecf salida(3);

    salida(0) = (e1(0) <= e2(0))? e1(0): e2(0);
    salida(1) = (e1(1) <= e2(1))? e1(1): e2(1);
    salida(2) = (e1(2) <= e2(2))? e1(2): e2(2);

    return norm_2(salida);
}

int main(int argc, char const *argv[])
{
    Json::Value root;
    Json::Reader reader;

    std::ifstream config_doc ("docs/descriptor_example.json");

    bool parsingSuccessful = reader.parse( config_doc, root, false );

    vecf i(3);
    vecf j(3);

    i(0) = 10;
    i(1) = 10;
    i(2) = 10;

    j(0) = 80;
    j(1) = 7;
    j(2) = 3;

    std::cout << dist_v_min___(i, j, root) << std::endl;
    return 0;
}