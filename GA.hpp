#ifndef GA_HPP
#define GA_HPP

#include <iostream>
#include "Travel.hpp"

class GA
{
public:
    GA(const std::vector<Travel>& travels, size_t iterations);

private:
    std::vector<Travel> mTravels;
    size_t mIterations;
};

#endif