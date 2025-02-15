#include "Population.hpp"
#include <vector>
#include <algorithm>
#include <random>

Population::Population(const std::vector<Travel::City> cities, size_t populationSize, size_t numCities, size_t numSalesmen)
    : mPopulationSize(populationSize), mNumMutation(0), mProbMutation(20)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> salesmen;
    for (size_t populationIndex = 0; populationIndex < populationSize; ++populationIndex)
    {
        int remainingCities = numCities;
        int remainingSalesmen = numSalesmen;
        for (int salesmanIndex = 0; salesmanIndex < numSalesmen - 1; ++salesmanIndex)
        {
            int num = 1 + std::rand() % (remainingCities - (remainingSalesmen - 1)); // Random number in [1, max_value]
            salesmen.push_back(num);
            remainingCities -= num;
            --remainingSalesmen;
        }
        salesmen.push_back(numCities - remainingCities);
        std::shuffle(salesmen.begin(), salesmen.end(), gen);

        Travel travel;
        travel.setCities(cities);
        travel.setSalesmen(salesmen);
        travel.swap(swapsNumber);
        travel.calculateDistance();
        travel.calculateFitness();
        travels.push_back(travel);
     }
}

Population::Population() 
    : mNumMutation(0), mProbMutation(20) 
{}

std::vector<Travel> Population::getTravels()
{ 
    return travels;
}

int Population::getSize()
{
    return mPopulationSize;
}

double Population::getBestDistance()
{
    return getBestTravel().getDistance();
}

Travel Population::getBestTravel()
{
    Travel bestTravel;
    double bestFitness = 0.0;
    for (auto it = travels.begin(); it != travels.end(); ++it)
    {
        if (bestFitness <= it->getDistance())
        {
            bestTravel = *it;
        }
    }
    return bestTravel;
}

void Population::setTravels(const std::vector<Travel> travels)
{
    Population::travels = travels;
}

int Population::getNumMutation()
{
    return mNumMutation;
}

void Population::incNumMutation()
{
    mNumMutation++; setPmutation();
}

void Population::delNumMutation()
{
    mNumMutation = 0; setPmutation();
}

void Population::setPmutation()
{ 
    if (mNumMutation == 0)
        mProbMutation = 20;
    else if (mNumMutation < 2)
        mProbMutation = 17;
    else if (mNumMutation < 5)
        mProbMutation = 13;
    else if (mNumMutation < 10)
        mProbMutation = 10;
    else 
        mProbMutation = 5;
}

int Population:: getPmutation()
{ 
    return mProbMutation;
}

Population& Population::operator = (Population& p)
{
    travels = p.travels;
    mNumMutation = p.mNumMutation;
    mProbMutation = p.mProbMutation;
    return *this;
}