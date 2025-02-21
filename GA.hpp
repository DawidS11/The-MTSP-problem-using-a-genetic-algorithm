#ifndef GA_HPP
#define GA_HPP

#include <iostream>
#include "Travel.hpp"
#include "Population.hpp"

class GA
{
public:
    GA(Population& population, size_t iterations);
    void optimization(Population& p, int crossover);

private:
    Population mPopulation;
    size_t mIterations;

    Travel crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2);
    Travel crossoverStandard(Travel& t1, Travel& t2);
    Travel crossoverTCX(Travel& t1, Travel& t2);

    /*
     * Rank-based roulette-wheel.
     */
    std::array<Travel, 2> selectParents(const Population& p);
    
    void mutation(Population& p, Travel& t);
    void evolution(Population& p, int crossover);
};

#endif