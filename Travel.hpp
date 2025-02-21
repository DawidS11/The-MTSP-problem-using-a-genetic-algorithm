#ifndef TRAVEL_HPP
#define TRAVEL_HPP

#include <iostream>
#include <vector>

int getRandomInt(const int a, const int b);
getRandomDouble(const double a, const double b);

class Travel
{
public:
    struct City
    {
        City(int id, int x, int y);
        City();
        City(City& c);
        City(City const& c);
        double calculateDistance(const City& c) const;
        bool operator == (const City& c) const;
        City& operator = (const City& c);

        int id;
        int x, y;
    };
    static const City startingPoint;

    Travel(size_t numCities, size_t numSalesmen, const std::vector<City>& cities, const std::vector<int>& salesmen);
    Travel();
    Travel(Travel const& t);
    ~Travel() = default;

    double getDistance() const;
    double getFitness() const;
    size_t getNumCities() const;
    size_t getNumSalesmen() const;
    std::vector<City> getCities() const;
    std::vector<int> getSalesmen() const;
    void setCities(const std::vector<City>& cities);
    void setSalesmen(const std::vector<int>& salesmen);
    void calculateDistance();
    void calculateFitness();
    void swap(const size_t numSwaps);
    void swapRandomCities();
    void swapRandomSalesmen();

    bool operator<(const Travel& t) const;
    bool operator>(const Travel& t) const;
    Travel& operator = (const Travel& t);

private:
    size_t mNumCities;
    size_t mNumSalesmen;
    std::vector<City> mCities;
    std::vector<int> mSalesmen;
    double mDistance;
    double mFitness;
};

#endif