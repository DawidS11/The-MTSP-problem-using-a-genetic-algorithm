#include "GA.hpp"
#include <random>

GA::GA(Population& population, size_t iterations)
    : mPopulation(population), mIterations(iterations)
{}

Travel GA::crossoverStandard(Travel& t1, Travel& t2)
{
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();
    std::vector<int> dadsSalesmen = t2.getSalesmen();

    Travel child;
    size_t numCities = t1.getNumCities();

    size_t r = rand() % (numCities - 1) + 1;
    std::vector<Travel::City> childCities(r);
    std::copy_n(momsCities.begin(), r, childCities.begin());

    size_t idx = 0;
    while (childCities.size() < numCities)
    {
        auto it = std::find(childCities.begin(), childCities.end(), dadsCities[idx]);
        if (it == childCities.end())
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

Travel GA::crossoverCarterAndRagsdale2006(Travel& t1, Travel& t2)
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
        if (it == momsPart.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    childCities.insert(childCities.end(), momsPart.begin(), momsPart.end());

    while (childCities.size() < numCities)
    {
        auto it = std::find(childCities.begin(), childCities.end(), dadsCities[idx]);
        if (it == childCities.end())
        {
            childCities.push_back(dadsCities[idx]);
        }
        ++idx;
    }

    r = rand() % numSalesmen;
    std::vector<int> childSalesmen;
    for (int i = r; i >= 0; --i)
    {
        childSalesmen.push_back(momsSalesmen[i]);
    }
    for (int i = numSalesmen-1; i >= r+1; --i)
    {
        childSalesmen.push_back(momsSalesmen[i]);
    }

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}

Travel GA::crossoverTCX(Travel& t1, Travel& t2)
{
    // Step 1: Initialise a pair of chromosomes as parents.
    std::vector<Travel::City> momsCities = t1.getCities();
    std::vector<Travel::City> dadsCities = t2.getCities();
    std::vector<int> momsSalesmen = t1.getSalesmen();
    std::vector<int> dadsSalesmen = t2.getSalesmen();

    Travel child;
    size_t numSalesmen = t1.getNumSalesmen();
    
    std::vector<Travel::City> childCities;
    std::vector<int> childSalesmen;

    // Step 2: Randomly select a gene segment for each salesman.
    int segmentBegin[numSalesmen], segmentEnd[numSalesmen], sumNumCities = 0;
    std::vector<Travel::City> momsPool;
    for (size_t i = 0; i < numSalesmen; ++i)
    {
       segmentBegin[i] = getRandomInt(sumNumCities, sumNumCities + momsSalesmen[i]);
       segmentEnd[i] = getRandomInt(segmentBegin[i], sumNumCities + momsSalesmen[i]);
       sumNumCities += momsSalesmen[i];
       momsPool.insert(momsPool.end(), momsCities.begin() + segmentBegin[i], momsCities.begin() + segmentEnd[i]);
       childSalesmen.push_back(segmentEnd[i] - segmentBegin[i] + 1);
    }

    // Step 3: Shuffle gene positions according to the first part of Dad’s chromosome.
    // Step 4: Add genes for each salesman.
    // Step 5 : Construct the Child’s two-part chromosome.
    sumNumCities = 0;
    for (size_t i = 0; i < numSalesmen; ++i)
    {
        childCities.insert(childCities.begin(), momsPool.begin() + segmentBegin[i], momsPool.begin() + segmentEnd[i]);
        for (auto it = dadsCities.begin() + sumNumCities; it != dadsCities.begin() + sumNumCities + dadsSalesmen[i]; ++it)
        {
            if (std::find(momsPool.begin(), momsPool.end(), *it) == momsPool.end())
            {
                childCities.push_back(*it);
                ++childSalesmen[i];
            }
        }
        sumNumCities += dadsSalesmen[i];
    }

    child.setCities(childCities);
    child.setSalesmen(childSalesmen);
    child.calculateFitness();
    child.calculateDistance();

    return child;
}

std::array<Travel, 2> GA::selectParents(const Population& p)
{
    std::array<Travel, 2> parents;
    std::vector<double> probability;
    std::vector<Travel> travels = p.getTravels();

    // Sort so the best ones are at the beginning.
    std::sort(travels.begin(), travels.end());

    double sumFitness = 0.0;
    double tmpSumFitness = 0.0;
    double offset = 0.0;
    size_t index = 0, index2 = 0;
    for (const Travel& travel : travels)
    {
        sumFitness += travel.getFitness();
    }

    double r = getRandomDouble(0.0, sumFitness);
    for (const Travel& travel : travels)
    {
        tmpSumFitness += travel.getFitness();
        if (tmpSumFitness >= r)
        {
            break;
        }
        ++index;
    }

    tmpSumFitness = 0.0;
    r = getRandomDouble(0.0, sumFitness);
    for (const Travel& travel : travels)
    {
        tmpSumFitness += travel.getFitness();
        if (tmpSumFitness >= r)
        {
            break;
        }
        ++index2;
    }

    if (index == index2)
    {
        if (index2 == 0)
        {
            ++index2;
        }
        else
        {
            --index2;
        }
    }
    parents[0] = travels[index];
    parents[1] = travels[index2];

    return parents;
}

void GA::mutation(const int probMutation, Travel& t)
{
    bool mutate = (rand() % 99 + 1) <= probMutation;
    if (mutate)
    {
        t.swapRandomCities();
        t.swapRandomSalesmen();
    }
}

void GA::evolution(Population& p, CROSSOVER crossover)
{
    std::array<Travel, 2> parents(selectParents(p));
    std::vector<Travel> travels(p.getTravels());
    size_t populationSize = p.getSize();
    int r = rand() % populationSize;
    int r2 = rand() % populationSize;
    while (r == r2)
    {
        r2 = rand() % populationSize;
    }
    
    if (crossover == CROSSOVER::STANDARD)
    {
        travels[r] = crossoverStandard(parents[0], parents[1]);
        travels[r2] = crossoverStandard(parents[0], parents[1]);
    }
    else if (crossover == CROSSOVER::CAR2006)
    {
        travels[r] = crossoverCarterAndRagsdale2006(parents[0], parents[1]);
        travels[r2] = crossoverCarterAndRagsdale2006(parents[0], parents[1]);
    }
    else if (crossover == CROSSOVER::TCX)
    {
        travels[r] = crossoverTCX(parents[0], parents[1]);
        travels[r2] = crossoverTCX(parents[0], parents[1]);
    }

    mutation(p.getProbMutation(), travels[r]);
    mutation(p.getProbMutation(), travels[r2]);
    travels[r].calculateDistance();
    travels[r].calculateFitness();
    travels[r2].calculateDistance();
    travels[r2].calculateFitness();
    p.setTravels(travels);
}

void GA::optimization(Population& p, CROSSOVER crossover)
{
    std::cout << "CROSSOVER ";
    if (crossover == CROSSOVER::STANDARD)
    {
        std::cout << "standard\n";
    }
    else if (crossover == CROSSOVER::CAR2006)
    {
        std::cout << "Carter And Ragsdale 2006\n";
    }
    else if (crossover == CROSSOVER::TCX)
    {
        std::cout << "tcx\n";
    }
    
    std::cout << "Starting shortest distance: " << p.getBestDistance() << std::endl;
    std::cout << "============================================\n";

    for (size_t i = 0; i < mIterations; ++i)
    {
        evolution(p, crossover);
        if (i == 99 || i == 499 || i == 999)
        {
            std::cout << "\nShortest distance after " << i + 1 << " iterations: " << p.getBestDistance() << std::endl;
            p.delNumMutation();
        }
    }

    std::cout << "\n============================================\n\n";
}