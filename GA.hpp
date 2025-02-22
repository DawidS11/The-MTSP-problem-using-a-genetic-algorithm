#ifndef GA_HPP
#define GA_HPP

#include <iostream>
#include "Travel.hpp"
#include "Population.hpp"

enum class CROSSOVER
{
    STANDARD = 0,
    CAR2006,
    TCX
};

class GA
{
public:
    GA(Population& population, size_t iterations);
    void optimization(Population& p, CROSSOVER crossover);

private:
    Population mPopulation;
    size_t mIterations;

    Travel crossoverStandard(Travel& t1, Travel& t2);
    Travel crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2);
    Travel crossoverTCX(Travel& t1, Travel& t2);

    /*
     * Rank-based roulette-wheel.
     */
    std::array<Travel, 2> selectParents(const Population& p);

    void mutation(const int probMutation, Travel& t);
    void evolution(Population& p, CROSSOVER crossover);
};

#endif