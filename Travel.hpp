#ifndef TRAVEL_HPP
#define TRAVEL_HPP

#include <iostream>

class Travel
{
public:
    struct City
    {
        uint8_t id;
        int x, y;

        City(int _number, int _x, int _y);
        double calculateDistance(City& c) const;
        bool operator == (const City& c) const;
    };

};

#endif