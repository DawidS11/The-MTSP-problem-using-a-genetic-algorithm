#ifndef GA_HPP
#define GA_HPP

#include <iostream>
#include "Travel.hpp"

class GA
{
public:
    GA(const std::vector<Travel>& travels, size_t iterations);
    Travel& crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2);
    Travel& crossoverStandard(Travel& t1, Travel& t2);

private:
    std::vector<Travel> mTravels;
    size_t mIterations;
};

#endif