#include "Individual.hpp"
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

Individual::Individual(const vector<int>& cityIds) : route(cityIds){
    random_device rd;
    mt19937 g(rd());

    // Embaralhar o vetor
    std::shuffle(route.begin(), route.end(), g);
}

double Individual::fitnessCalc(const vector<vector<double>>& distanceMatrix){
    for (int i = 0; i < route.size()-1; i++){
        fitness += distanceMatrix[route[i]][route[i+1]];
    }
    fitness += distanceMatrix[route[route.size() - 1]][route[0]];
    return fitness;
}

const vector<int>& Individual::getRoute() const {
    return route;
}