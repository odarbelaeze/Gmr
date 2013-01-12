#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define TR(i, items) for(typeof(items.begin()) i = items.begin(); i != items.end(); i++)
#define REP(i, times) for(int i = 0; i < times; i++)

typedef double (*FUNCIONCITA)(double);

int main(int argc, char const *argv[])
{
    std::vector<FUNCIONCITA> funcioncitas;

    funcioncitas.push_back(sin);
    funcioncitas.push_back(cos);
    funcioncitas.push_back(tan);

    TR (funcion, funcioncitas) 
        std::cout << (*funcion)(M_PI) << "    " 
            << (*funcion)(0.5 * M_PI) << std::endl;

    return 0;
}