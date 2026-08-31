#include "GeneticAlgorithm.hpp"
#include <cmath>
#include <vector>
#include "City.hpp"
#include "Individual.hpp"
#include <iostream>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(vector<City> cities, int populationSize, int generations, double mutationRate) 
    : cities(cities), distanceMatrix(cities.size(), vector<double>(cities.size(), 0.0)), populationSize(populationSize), generations(generations), mutationRate(mutationRate) {
        distanceMatrixCalc();

        vector<int> cityIds;

        for(int i = 0; i < cities.size(); i++) {
            cityIds.push_back(cities[i].getId());
        }

        initializePopulation(cityIds);
    }

void GeneticAlgorithm::initializePopulation(const vector<int>& cityIds) {
    for (int i = 0; i < populationSize; i++) {
        population.push_back(Individual(cityIds));
    }
}

void GeneticAlgorithm::distanceMatrixCalc(){
    for (int i = 0; i < cities.size(); i++) {
        for (int j = 0; j < cities.size(); j++) {
            if (cities[i].getId() == cities[j].getId()) {
                distanceMatrix[i][j] = 0;
            } else {
                distanceMatrix[i][j] = euclideanDistance(
                    cities[i].getX(), cities[i].getY(),
                    cities[j].getX(), cities[j].getY()
                );
            }
        }
    }
}

vector<Individual>& GeneticAlgorithm::getPopulation() {
    return population;
}

double GeneticAlgorithm:: euclideanDistance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double GeneticAlgorithm::getDistance(int i, int j){
    return distanceMatrix[i][j];
}

const vector<vector<double>>& GeneticAlgorithm::getDistanceMatrix() const {
    return distanceMatrix;
}

Individual GeneticAlgorithm::tournamentSelection(int tournamentSize) {
    Individual best;

    for (int i = 0; i < tournamentSize; i++) {
        int index = rand() % populationSize;

        Individual candidate = population[index];

        if (i == 0 || candidate.fitnessCalc() > best.fitnessCalc()) {
            best = candidate;
        }
    }

    return best;
}