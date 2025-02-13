#include "Travel.hpp"

#include <cmath>
#include <random>

const Travel::City Travel::startingPoint(0, 500, 500);

Travel::City::City(int id, int x, int y)
    : id(id), x(x), y(y) 
{}

double Travel::City::calculateDistance(const City& c) const
{
    int distX = std::abs(x - c.x);
    int distY = std::abs(y - c.y);
    return sqrt(pow((double)distX, 2) + pow((double)distY, 2));
}

bool Travel::City::operator == (const City& c) const
{
    return (id == c.id);
}

bool Travel::City::operator = (const City& c)
{
    id == c.id;
    x = c.x;
    y = c.y;
}

Travel::Travel(size_t numCities, size_t numSalesmen, const std::vector<City>& cities, const std::vector<int>& salesmen)
    : mNumCities(numCities), mNumSalesmen(numSalesmen), mCities(cities), mSalesmen(salesmen)
{}

Travel::Travel()
    : mNumCities(0), mNumSalesmen(0), mCities(std::vector<City>()), mSalesmen(std::vector<int>())
{}

double Travel::getDistance() const
{
    return mDistance;
}

double Travel::getFitness() const
{
    return mFitness;
}

size_t Travel::getNumCities() const
{
    return mNumCities;
}

size_t Travel::getNumSalesmen() const
{
    return mNumSalesmen;
}

std::vector<Travel::City> Travel::getCities() const
{
    return mCities;
}

std::vector<int> Travel::getSalesmen() const
{
    return mSalesmen;
}

void Travel::setCities(const std::vector<Travel::City>& cities)
{
    mCities = cities;
}

void Travel::setSalesmen(const std::vector<int>& salesmen)
{
    mSalesmen = salesmen;
}

void Travel::calculateDistance()
{
    double totalDistance = 0.0;
    size_t idxSalesmen = 0, idxCities = 0;
    for (int idxSalesmen = 0; idxSalesmen < mNumSalesmen; ++idxSalesmen)
    {
        for (int i = 0; i < mSalesmen[idxSalesmen]; ++i)
        {
            if (i == 0) // starting point
            {
                totalDistance += mCities[idxCities].calculateDistance(startingPoint);
            }
            else
            {
                totalDistance += mCities[idxCities].calculateDistance(mCities[idxCities-1]);
            }
            ++idxCities;
        }
    }

    mDistance = totalDistance;
}

void Travel::calculateFitness()
{
    mFitness = (1.0 / mDistance) * 10000;
}

void Travel::swapRandomCities()
{
    if (mNumCities <= 1)
    {
        return;
    }

    int posA = rand() % mNumCities;
    int posB = rand() % mNumCities;
    while (posA == posB)
    {
        posB = rand() % mNumCities;
    }
    std::swap(mCities.at(posA), mCities.at(posB));
}

void Travel::swapRandomSalesmen()
{
    if (mNumSalesmen <= 1)
    {
        return;
    }

    int posA = rand() % mNumSalesmen;
    int posB = rand() % mNumSalesmen;
    while (posA == posB)
    {
        posB = rand() % mNumSalesmen;
    }
    std::swap(mSalesmen.at(posA), mSalesmen.at(posB));
}

void Travel::swap(const int numSwaps)
{
    for (int i = 0; i < numSwaps; ++i)
    {
        swapRandomCities();
        swapRandomSalesmen();
    }
}