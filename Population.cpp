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
        for (size_t salesmanIndex = 0; salesmanIndex < numSalesmen - 1; ++salesmanIndex)
        {
            int num = 1 + std::rand() % (remainingCities - (remainingSalesmen - 1)); // Random number in [1, max_value]
            salesmen.push_back(num);
            remainingCities -= num;
            --remainingSalesmen;
        }
        salesmen.push_back(numCities - remainingCities);
        std::shuffle(salesmen.begin(), salesmen.end(), gen);

        Travel travel(numCities, numSalesmen, cities, salesmen);
        travel.swap(swapsNumber);
        travel.calculateDistance();
        travel.calculateFitness();
        mTravels.push_back(travel);
     }
}

Population::Population() 
    : mNumMutation(0), mProbMutation(20) 
{}

Population::Population(Population& p)
{
    mPopulationSize = p.mPopulationSize;
    mTravels = p.mTravels;
    mNumMutation = p.mNumMutation;
    mProbMutation = p.mProbMutation;
}

std::vector<Travel> Population::getTravels() const
{ 
    return mTravels;
}

size_t Population::getSize() const
{
    return mPopulationSize;
}

double Population::getBestDistance() const
{
    double bestDistance = 1000000.0;
    for (auto it = mTravels.begin(); it != mTravels.end(); ++it)
    {
        if (bestDistance > it->getDistance())
        {
            bestDistance = it->getDistance();
        }
    }

    return bestDistance;
}

void Population::setTravels(const std::vector<Travel>& travels)
{
    mTravels = travels;
}

int Population::getNumMutation()
{
    return mNumMutation;
}

void Population::incNumMutation()
{
    ++mNumMutation;
    setProbMutation();
}

void Population::delNumMutation()
{
    mNumMutation = 0; setProbMutation();
}

void Population::setProbMutation()
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

int Population:: getProbMutation()
{ 
    return mProbMutation;
}

Population& Population::operator = (Population& p)
{
    mTravels = p.mTravels;
    mNumMutation = p.mNumMutation;
    mProbMutation = p.mProbMutation;
    return *this;
}