#include <iostream>
#include <cstdlib>
#include <vector>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>


#define TR(i, items) for (typeof(items.begin()) i = items.begin(); i != items.end(); ++i)


using namespace boost::numeric::ublas;

int main(int argc, char const *argv[])
{
    srand48(time(NULL));
    int x = 3;
    int y = 3;
    int z = 3;

    vector<float> r(3);
    std::vector<typeof(r)> rs;
    
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            for (int k = 0; k < z; ++k)
            {
                r(0) = i;
                r(1) = j;
                r(2) = k;
                rs.push_back(r);
            }
        }
    }
    
    // TR(i, rs){
    //     std::cout << *i << std::endl;
    // }

    std::vector<typeof(r)> e;

    int cantidad_e = 10;

    for (int i = 0; i < cantidad_e; ++i)
    {
        r(0) = drand48() * x;
        r(1) = drand48() * y;
        r(2) = drand48() * z;
        e.push_back(r);
    }

    TR(i, e){
        std::cout << *i << std::endl;
    }


    return 0;
}