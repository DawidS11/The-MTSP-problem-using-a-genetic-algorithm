#include "Travel.hpp"

#include <cmath>

Travel::City::City(int _id, int _x, int _y)
    : id(_id), x(_x), y(_y) 
{}

double Travel::City::calculateDistance(City& c) const
{
    int distX = std::abs(x - c.x);
    int distY = std::abs(y - c.y);
    return sqrt(pow((double)distX, 2) + pow((double)distY, 2));
}

bool Travel::City::operator == (const City& c) const
{
    return (id == c.id);
}

Travel::Travel(size_t _numCities, const std::vector<City>& _cities, const std::vector<int>& _salesmen)
    : numCities(_numCities), cities(_cities), salesmen(_salesmen)
{}