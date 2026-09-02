#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <vector>
#include "City.hpp"
#include "Individual.hpp"

class GeneticAlgorithm {
private:
    std::vector<City> cities;
    std::vector<std::vector<double>> distanceMatrix;
    std::vector<Individual> population;
    int populationSize;
    int generations;
    double mutationRate;
    int tournamentSize;

public:
    GeneticAlgorithm(std::vector<City> cities, int populationSize, int generations, double mutationRate, int tournamentSize);

    void distanceMatrixCalc();

    void initializePopulation(const std::vector<int>& cityIds);

    double euclideanDistance(double x1, double y1, double x2, double y2);

    double getDistance(int i, int j);

    std::vector<Individual>& getPopulation();

    const std::vector<std::vector<double>>& getDistanceMatrix() const;

    Individual tournamentSelection(int tournamentSize);

    Individual orderCrossover(const Individual& parent1, const Individual& parent2);

    void mutate(Individual& individual);

    Individual getBestIndividual();

    void nextGeneration();
};

#endif