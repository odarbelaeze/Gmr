#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define TR(i, items) for(typeof(items.begin()) i = items.begin(); i != items.end(); i++)
#define REP(i, times) for(int i = 0; i < times; i++)

struct P
{
    short int s;
    std::vector<P*> nbh;
};

short int operator * (const P &p) {return p.s;}
short int operator * (const P &p, const P &other) {return p.s * other.s;}
// shor;t int operator * (const P *p, const P *other) {return p -> s * other -> s;}

float energia (std::vector<P> &sys)
{
    float e = 0;
    TR (i, sys) TR (j, i -> nbh) e -= (*i) * (**j);
    return e;
}

int main(int argc, char const *argv[])
{
    srand48(time(NULL));
    const int N = 1000;
    std::vector<P> sys(N);
    std::vector<P> sys_t(N);
    TR (p, sys) p -> s = (drand48() < 0.5)? 1: -1;
    float ET = 1.0f;

    TR (p, sys) 
    {
        if  (p + 5 == sys.end()) break;
        for (int i = 1; i < 5; i++) (*p).nbh.push_back (&(*(p + i)));
    }

    sys_t = sys;

    REP(k, 20) for (int i = 0; i < N; ++i)
    {
        sys_t[i].s *= -1;
        float deltaE = energia(sys_t) - energia(sys);
        if(deltaE < 0)
        {
            sys[i].s *= -1;
        }
        else
        {
            (drand48() < std::exp(- deltaE / ET))? sys[i].s *= -1: sys_t[i].s *= -1;
        }
        std::cout << energia(sys) << std::endl;
    }

    return 0;
}