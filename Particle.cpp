#include "Particle.hpp"

namespace Arg
{
    template <typename T>
    Particle<T>::Particle()
    {

    }

    template <typename T>
    Particle(
        const PTYPE<T> &type,
        const PSTATE<T> &state,
        const std::vector<Particle*> &nbh
        )
    {
        this -> type = type;
        this -> state = state;
        this -> new_state = state;
        this -> nbh = nbh;
    }


    template <typename T>
    Particle<T>::~Particle()
    {

    }

    template <typename T>
    const PTYPE<T> *Particle<T>::get_type()
    {
        return this -> type;
    }

    template <typename T>
    const PSTATE<T> Particle<T>::get_state()
    {
        return this -> state;
    }

    template <typename T>
    const std::vector<Particle<T>*> *Particle<T>::get_nbh_ptr()
    {
        return &(this -> nbh);
    }

    template <typename T>
    void Particle<T>::set_type (const PTYPE<T> & type)
    {
        this -> type = type;
    }

    template <typename T>
    void Particle<T>::set_state (const PSTATE<T> & state)
    {
        this -> state = state;
    }

    template <typename T>
    void Particle<T>::set_nbh (const std::vector<Particle<T>*> &)
    {
        this -> nbh = nbh;
    }

    template <typename T>
    void Particle<T>::update_state (PSTATE<T> (*new_state)(PSTATE<T> &))
    {
        this -> new_state = new_state(this -> state);
    }

    template <typename T>
    void Particle<T>::commit_state ()
    {
        this -> state = new_state;
    }

}
