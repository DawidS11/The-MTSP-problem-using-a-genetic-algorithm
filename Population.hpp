#ifndef POPULATION_HPP
#define POPULATION_HPP
#include <iostream>

#include "Travel.hpp"

class Population
{
public:
    Population(const std::vector<Travel::City> cities, size_t populationSize, size_t numCities, size_t numSalesmen);
    Population();
    Population(Population& p);

    std::vector<Travel> getTravels() const;
    size_t getSize() const;
    double getBestDistance() const;
    void setTravels(const std::vector<Travel>& travels);
    int getNumMutation();
    void incNumMutation();
    void delNumMutation();
    void setProbMutation();
    int getProbMutation();
    Population& operator = (Population& p);

private:
    constexpr static size_t swapsNumber = 100;
    size_t mPopulationSize;
    std::vector<Travel> mTravels;
    size_t mNumMutation;
    int mProbMutation;
};

#endif