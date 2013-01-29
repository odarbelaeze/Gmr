#include <iostream>
#include <cstdlib>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>


using namespace boost::numeric::ublas;

int main(int argc, char const *argv[])
{
    srand48(time(NULL));
    int x = 3;
    int y = 3;
    int z = 3;

    vector<float> r(3);
    vector<typeof(r)> rs;
    
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
    std::cout << rs << std::endl;
    return 0;
}