#include "GA.hpp"

GA::GA(const std::vector<Travel>& travels, size_t iterations)
    : mTravels(travels), mIterations(iterations)
{}

Travel& GA::crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2)
{
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();
    std::vector<int> dadsSalesmen = t2.getSalesmen();

    Travel child;
    size_t numCities = t1.getNumCities();
    size_t numSalesmen = t1.getNumSalesmen();

    size_t r = numCities / 3;
    std::vector<Travel::City> momsPart(momsCities.begin() + r, momsCities.begin() + 2*r);
    std::vector<Travel::City> childCities;
    
    size_t idx = 0;
    while (childCities.size() < r)
    {
        auto it = std::find(momsPart.begin(), momsPart.end(), dadsCities[idx]);
        if(it == momsPart.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    childCities.insert(childCities.end(), momsPart.begin(), momsPart.end());

    while (childCities.size() < numCities)
    {
        auto it = std::find(childCities.begin(), childCities.end(), dadsCities[idx]);
        if(it == childCities.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    r = rand() % numSalesmen;
    std::vector<int> childSalesmen;
    for (size_t i = r+1; i >= 0; --i)
    {
        childSalesmen.push_back(momsSalesmen[i]);
    }
    for (size_t i = numSalesmen-1; i >= r+1; --i)
    {
        childSalesmen.push_back(momsSalesmen[i]);
    }

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}

Travel& GA::crossoverStandard(Travel& t1, Travel& t2)
{
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();
    std::vector<int> dadsSalesmen = t2.getSalesmen();

    Travel child;
    size_t numCities = t1.getNumCities();

    size_t r = rand() % (numCities - 1) + 1;
    std::vector<Travel::City> childCities(momsCities.begin(), momsCities.begin() + r);
    
    size_t idx = 0;
    while (childCities.size() < numCities)
    {
        auto it = std::find(childCities.begin(), childCities.end(), dadsCities[idx]);
        if(it == childCities.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    std::vector<int> childSalesmen = rand() % 2 ? momsSalesmen : dadsSalesmen;

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}