#ifndef POPULATION_HPP
#define POPULATION_HPP
#include <iostream>

#include "Travel.hpp"

class Population
{
public:
    Population(const std::vector<Travel::City> cities, size_t populationSize, size_t numCities, size_t numSalesmen);
    Population();
    
    std::vector<Travel> getTravels() const;
    size_t getSize() const;
    double getBestDistance();
    Travel getBestTravel();
    void setTravels(const std::vector<Travel> travels);
    int getNumMutation();
    void incNumMutation();
    void delNumMutation();
    void setPmutation();
    int getPmutation();
    Population& operator = (Population& p);

private:
    constexpr static size_t swapsNumber = 100;
    size_t mPopulationSize;
    std::vector<Travel> travels;
    size_t mNumMutation;
    int mProbMutation;
};

#endif