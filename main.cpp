#include <iostream>
#include <fstream>
#include "GA.hpp"

int main()
{
    size_t populationSize;
    size_t numCities;
    size_t numSalesmen;

    std::ifstream file("./data/100_50_20.txt");
    if(!file.is_open())
    {
        std::cout << "ERROR\n\n";
        return 1;
    }

    std::vector<Travel::City> cities;
    int id;
    int x, y;
    while(!file.eof())
    {
        file >> populationSize >> numCities >> numSalesmen;
        for(size_t i = 0; i < numCities; ++i)
        {
            file >> id >> x >> y;
            cities.emplace_back(id, x, y);
        }
    }
    file.close();

    Population population(cities, populationSize, numCities, numSalesmen);
    GA ga(population, 1000);
    ga.optimization(population, 0);
}