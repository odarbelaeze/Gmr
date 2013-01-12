#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <string>
#include <vector>

namespace Arg
{
    template <typename T>
    struct FIELD
    {
        boost::numeric::ublas::vector<T> electric_field;
        boost::numeric::ublas::vector<T> magnetic_field;
        T temperature;
    };

    template <typename T>
    struct PTYPE
    {
        std::string name;
        T charge;
        T spin_norm;
    };

    template <typename T>
    struct PSTATE
    {
        boost::numeric::ublas::vector<T> rvec;
        boost::numeric::ublas::vector<T> spin;
        T energy;
    };

    template <typename T>
    class Particle
    {
        PTYPE<T> *type;
        PSTATE<T> state;
        PSTATE<T> new_state;
        std::vector<Particle<T>*> nbh;

    public:
        Particle();
        Particle(const PTYPE<T> &, const PSTATE<T> &, const std::vector<Particle*> &);
        ~Particle();

        const PTYPE<T> *get_type();
        const PSTATE<T> get_state();
        const std::vector<Particle*> *get_nbh_ptr();

        void set_type (const PTYPE<T> &);
        void set_state (const PSTATE<T> &);
        void set_nbh (const std::vector<Particle<T>*> &);

        void update_state (PSTATE<T> (*new_state)(PSTATE<T> &));
        void commit_state ();
    };
}

#endif