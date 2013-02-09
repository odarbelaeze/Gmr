#include "../gmr.h"

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

    std::cout << dist_v_min(i, j, root) << std::endl;
    return 0;
}