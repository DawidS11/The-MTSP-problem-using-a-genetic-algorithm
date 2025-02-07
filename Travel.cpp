#include "Travel.hpp"

#include <cmath>

const Travel::City Travel::startingPoint(0, 500, 500);

Travel::City::City(int _id, int _x, int _y)
    : id(_id), x(_x), y(_y) 
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

Travel::Travel(size_t _numCities, size_t _numSalesmen, const std::vector<City>& _cities, const std::vector<int>& _salesmen)
    : numCities(_numCities), numSalesmen(_numSalesmen), cities(_cities), salesmen(_salesmen)
{}

double Travel::getDistance() const
{
    return distance;
}

void Travel::calculateDistance()
{
    double totalDistance = 0.0;
    size_t idxSalesmen = 0, idxCities = 0;
    for (int idxSalesmen = 0; idxSalesmen < numSalesmen; ++idxSalesmen)
    {
        for (int i = 0; i < salesmen[idxSalesmen]; ++i)
        {
            if (i == 0) // starting point
            {
                totalDistance += cities[idxCities].calculateDistance(startingPoint);
            }
            else
            {
                totalDistance += cities[idxCities].calculateDistance(cities[idxCities-1]);
            }
            ++idxCities;
        }
    }

    distance = totalDistance;
}