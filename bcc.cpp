#include <iostream>
#include <vector>
#include <cstdlib>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>

#define TR(i, items) for (typeof(items.begin()) i = items.begin(); i != items.end(); ++i)

using namespace boost::numeric::ublas;

int main(int argc, char const *argv[])
{
    int l = 1;
    srand48(time(NULL));
    int x = 2;
    int y = 2;
    int z = 2;

    vector<float> r(3);
    std::vector<typeof(r)> rs;


    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            for (int k = 0; k < z; ++k)
            {
                r(0) = i * l;
                r(1) = j * l;
                r(2) = k * l;
                rs.push_back(r);

                r(0) = (i + 0.5) * l;
                r(1) = (j + 0.5) * l;
                r(2) = (k + 0.5) * l;
                rs.push_back(r);
            }
        }
    }

    TR(i, rs){
        std::cout << *i << std::endl;
    }

    
    return 0;
}