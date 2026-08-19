#include "GeneticAlgorithm.hpp"
#include <cmath>
#include <vector>
#include "City.hpp"
#include <iostream>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(vector<City> cities, int population, int generations, double mutationRate) 
    : cities(cities), distanceMatrix(cities.size(), vector<double>(cities.size(), 0.0)), population(population), generations(generations), mutationRate(mutationRate) {
        distanceMatrixCalc();
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

double GeneticAlgorithm:: euclideanDistance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double GeneticAlgorithm::getDistance(int i, int j){
    return distanceMatrix[i][j];
}