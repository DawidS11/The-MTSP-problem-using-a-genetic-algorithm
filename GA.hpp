#ifndef GA_HPP
#define GA_HPP

#include <iostream>
#include "Travel.hpp"
#include "Population.hpp"

class GA
{
public:
    GA(const std::vector<Travel>& travels, size_t iterations);
    Travel crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2);
    Travel crossoverStandard(Travel& t1, Travel& t2);
    Travel crossoverTCX(Travel& t1, Travel& t2);

private:
    std::vector<Travel> mTravels;
    size_t mIterations;

    std::array<Travel, 2> selectParents(const Population& p);
    void mutation(Population& p, Travel& t);
    void evolution(Population& p, int crossover);
};

#endif