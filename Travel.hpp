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
        double calculateDistance(const City& c) const;
        bool operator == (const City& c) const;
        bool operator = (const City& c);

        uint8_t id;
        int x, y;
    };
    static const City startingPoint;

    Travel(size_t _numCities, size_t _numSalesmen, const std::vector<City>& _cities, const std::vector<int>& _salesmen);

    double getDistance() const;

private:
    size_t numCities;
    size_t numSalesmen;
    std::vector<City> cities;
    std::vector<int> salesmen;
    double distance;

    void calculateDistance();
};

#endif