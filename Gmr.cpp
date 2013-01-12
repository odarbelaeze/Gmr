#include "Gmr.hpp"

namespace Gmr
{
    void Particle::update_state (State (*new_state)(State &))
    {
        this -> new_state = new_state(this -> state);
    }
    
    void Particle::commit_state ()
    {
        this -> state = this -> new_state;
    }
}

int main(int argc, char const *argv[])
{
    
    return 0;
}