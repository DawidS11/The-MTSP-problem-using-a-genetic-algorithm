#include "GA.hpp"

GA::GA(const std::vector<Travel>& travels, size_t iterations)
    : mTravels(travels), mIterations(iterations)
{}

Travel& GA::crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2)
{
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();
    std::vector<int> dadsSalesmen = t2.getSalesmen();

    Travel child;
    size_t numCities = t1.getNumCities();
    size_t numSalesmen = t1.getNumSalesmen();

    size_t r = numCities / 3;
    std::vector<Travel::City> momsPart(momsCities.begin() + r, momsCities.begin() + 2*r);
    std::vector<Travel::City> childCities;
    
    size_t idx = 0;
    while (childCities.size() < r)
    {
        auto it = std::find(momsPart.begin(), momsPart.end(), dadsCities[idx]);
        if(it == momsPart.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    childCities.insert(childCities.end(), momsPart.begin(), momsPart.end());

    while (childCities.size() < numCities)
    {
        auto it = std::find(childCities.begin(), childCities.end(), dadsCities[idx]);
        if(it == childCities.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    r = rand() % numSalesmen;
    std::vector<int> childSalesmen;
    for (size_t i = r+1; i >= 0; --i)
    {
        childSalesmen.push_back(momsSalesmen[i]);
    }
    for (size_t i = numSalesmen-1; i >= r+1; --i)
    {
        childSalesmen.push_back(momsSalesmen[i]);
    }

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}

Travel& GA::crossoverStandard(Travel& t1, Travel& t2)
{
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();
    std::vector<int> dadsSalesmen = t2.getSalesmen();

    Travel child;
    size_t numCities = t1.getNumCities();

    size_t r = rand() % (numCities - 1) + 1;
    std::vector<Travel::City> childCities(momsCities.begin(), momsCities.begin() + r);
    
    size_t idx = 0;
    while (childCities.size() < numCities)
    {
        auto it = std::find(childCities.begin(), childCities.end(), dadsCities[idx]);
        if(it == childCities.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    std::vector<int> childSalesmen = rand() % 2 ? momsSalesmen : dadsSalesmen;

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}

Travel GA::crossoverTCX(Travel& t1, Travel& t2)
{
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();

    Travel child;
    size_t numCities = t1.getNumCities();
    size_t numSalesmen = t1.getNumSalesmen();
    
    std::vector<Travel::City> childCities;
    std::vector<int> childSalesmen;
    int i, k, index = 0, index2;
    int segment[numSalesmen], segment2[numSalesmen], starting[numSalesmen], totalSavedGenes = 0, totalUnsavedGenes = 0;
    std::vector<Travel::City> savedGenesPool, unsavedGenesPool, unsavedGenesPool2;

    int segSum = 0;
    for(i = 0; i < numSalesmen; ++i)
    {
        segment[i] = rand() % momsSalesmen[i] + 1;
        segSum += segment[i];
        while(segSum + numSalesmen - i - 1 > numCities)
        {
            segSum -= segment[i];
            segment[i] = rand() % momsSalesmen[i] + 1;
            segSum += segment[i];
        }

        if(momsSalesmen[i] > segment[i])
        {
            starting[i] = rand() % (momsSalesmen[i] - segment[i]) + index;
            for(k = starting[i]; k < starting[i] + segment[i]; ++k)
            {
                savedGenesPool.push_back(momsCities[k]);
                ++totalSavedGenes;
            }
        }
        else
        {
            for(k = index; k < index + segment[i]; ++k)
            {
                savedGenesPool.push_back(momsCities[k]); 
                ++totalSavedGenes;
            }
        }
        index += momsSalesmen[i];
    }

    totalUnsavedGenes = numCities - totalSavedGenes;
    auto it = savedGenesPool.begin();
    for(i = 0; i < numCities; ++i)
    {                                              
        it = std::find(savedGenesPool.begin(), savedGenesPool.end(), momsCities[i]);
        if(it == savedGenesPool.end()) 
            unsavedGenesPool.push_back(momsCities[i]);
    }

    for(k = 0; k < numCities; ++k)
    {
        for(i = 0; i < totalUnsavedGenes; ++i {
            if(unsavedGenesPool[i] == dadsCities[k]) {
                unsavedGenesPool2.push_back(unsavedGenesPool[i]);
                break;
            }
        }
    }
    k = 0;
    segSum = 0;
    for(i = 0; i < numSalesmen; ++i)
    {
        if(i != numSalesmen - 1) {
            if(segSum == totalUnsavedGenes)
                segment2[i] = 0;
            else
                segment2[i] = rand() % (totalUnsavedGenes - segSum) + 1;
            segSum += segment2[i];
        }
        else 
            segment2[i] = totalUnsavedGenes - segSum;
    }
    index = 0;
    index2 = 0;

    for(i = 0; i < numSalesmen; ++i)
    {
        for(k = index; k < index + segment[i]; ++k) 
            childCities.push_back(savedGenesPool[k]);
        index += segment[i];
        for(k = index2; k < index2 + segment2[i]; ++k)
            childCities.push_back(unsavedGenesPool2[k]);
        index2 += segment2[i];
        childSalesmen.push_back(segment[i] + segment2[i]);
    }

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}