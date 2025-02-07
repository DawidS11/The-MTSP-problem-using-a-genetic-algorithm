#ifndef TRAVEL_HPP
#define TRAVEL_HPP

#include <iostream>
#include <vector>

class Travel
{
public:
    struct City
    {
        City(int _number, int _x, int _y);
        double calculateDistance(City& c) const;
        bool operator == (const City& c) const;

        uint8_t id;
        int x, y;
    };

Travel(size_t _numCities, const std::vector<City>& _cities, const std::vector<int>& _salesmen);

private:
    size_t numCities;
    std::vector<City> cities;
    std::vector<int> salesmen;
    double distance;
};

#endif