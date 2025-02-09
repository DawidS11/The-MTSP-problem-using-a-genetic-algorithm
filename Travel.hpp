#ifndef TRAVEL_HPP
#define TRAVEL_HPP

#include <iostream>
#include <vector>

class Travel
{
public:
    struct City
    {
        City(int number, int x, int y);
        double calculateDistance(const City& c) const;
        bool operator == (const City& c) const;
        bool operator = (const City& c);

        uint8_t id;
        int x, y;
    };
    static const City startingPoint;

    Travel(size_t numCities, size_t numSalesmen, const std::vector<City>& cities, const std::vector<int>& salesmen);

    double getDistance() const;
    double getFitness() const;

private:
    size_t mNumCities;
    size_t mNumSalesmen;
    std::vector<City> mCities;
    std::vector<int> mSalesmen;
    double mDistance;
    double mFitness;

    void calculateDistance();
    void calculateFitness();
    void swapRandomCities();
    void swapRandomSalesmen();
    void swap(const int numSwaps);
    
};

#endif