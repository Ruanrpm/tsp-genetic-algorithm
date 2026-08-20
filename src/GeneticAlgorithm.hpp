#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <vector>
#include "City.hpp"

class GeneticAlgorithm {
private:
    std::vector<City> cities;
    std::vector<std::vector<double>> distanceMatrix;
    int population;
    int generations;
    double mutationRate;

public:
    GeneticAlgorithm(std::vector<City> cities, int population, int generations, double mutationRate);

    void distanceMatrixCalc();

    double euclideanDistance(double x1, double y1, double x2, double y2);

    double getDistance(int i, int j);

    const std::vector<std::vector<double>>& getDistanceMatrix() const;
};

#endif