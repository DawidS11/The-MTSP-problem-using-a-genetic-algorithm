#include "Travel.hpp"

#include <cmath>
#include <random>

const Travel::City Travel::startingPoint(0, 500, 500);

int getRandomInt(const int a, const int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(a, b);

    return dist(gen);
}

double getRandomDouble(const double a, const double b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(a, b);

    return dist(gen);
}

Travel::City::City(int id, int x, int y)
    : id(id), x(x), y(y)
{}

Travel::City::City()
    : id(0), x(0), y(0)
{}

Travel::City::City(City& c)
    : id(c.id), x(c.x), y(c.y)
{}

Travel::City::City(City const& c)
    : id(c.id), x(c.x), y(c.y)
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

Travel::City& Travel::City::operator = (const City& c)
{
    id = c.id;
    x = c.x;
    y = c.y;
    return *this;
}

Travel::Travel(size_t numCities, size_t numSalesmen, const std::vector<City>& cities, const std::vector<int>& salesmen)
    : mNumCities(numCities), mNumSalesmen(numSalesmen), mCities(cities), mSalesmen(salesmen)
{}

Travel::Travel()
    : mNumCities(0), mNumSalesmen(0), mCities(std::vector<City>()), mSalesmen(std::vector<int>())
{}

/*Travel::Travel(Travel const& t) 
    : mNumCities(t.mNumCities), mNumSalesmen(t.mNumSalesmen), mCities(t.mCities), mSalesmen(t.mSalesmen), mDistance(t.mDistance), mFitness(t.mFitness)
{}
*/
/*Travel::Travel(Travel&& t) 
    : mCities(std::move(t.mCities)), mSalesmen(std::move(t.mSalesmen)), mDistance(t.mDistance), mFitness(t.mFitness)
{}*/

Travel::Travel(const Travel& t)
    : mNumCities(t.mNumCities), mNumSalesmen(t.mNumSalesmen), mCities(t.mCities), mSalesmen(t.mSalesmen), mDistance(t.mDistance), mFitness(t.mFitness)
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
    mNumCities = cities.size();
    mCities = cities;
}

void Travel::setSalesmen(const std::vector<int>& salesmen)
{
    mNumSalesmen = salesmen.size();
    mSalesmen = salesmen;
}

void Travel::calculateDistance()
{
    double totalDistance = 0.0;
    size_t idxCities = 0;
    for (size_t idxSalesmen = 0; idxSalesmen < mNumSalesmen; ++idxSalesmen)
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

void Travel::swap(const size_t numSwaps)
{
    for (size_t i = 0; i < numSwaps; ++i)
    {
        swapRandomCities();
        swapRandomSalesmen();
    }
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

bool Travel::operator < (const Travel& t) const
{
    return mFitness> t.mFitness;
}

bool Travel::operator > (const Travel& t) const
{
    return mFitness > t.mFitness;
}

Travel& Travel::operator = (const Travel& t)
{
    mNumCities = t.mNumCities;
    mNumSalesmen = t.mNumSalesmen;
    mCities = t.mCities;
    mSalesmen = t.mSalesmen;
    mDistance = t.mDistance;
    mFitness = t.mFitness;
    return *this;
}