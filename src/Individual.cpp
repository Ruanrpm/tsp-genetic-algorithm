#include "Individual.hpp"
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

Individual::Individual(const vector<int>& cityIds) : route(cityIds){
    random_device rd;
    mt19937 g(rd());

    // Embaralhar o vetor
    std::shuffle(route.begin() + 1, route.end(), g);
}
Individual::Individual() {}

double Individual::distenceCalc(const vector<vector<double>>& distanceMatrix){
    for (int i = 0; i < route.size()-1; i++){
        distance += distanceMatrix[route[i]][route[i+1]];
    }
    distance += distanceMatrix[route[route.size() - 1]][route[0]];
    return  distance;
}

double Individual::fitnessCalc(){
    return fitness = 1/distance;
}

double Individual::getFitness() const {
    return fitness;
}

const vector<int>& Individual::getRoute() const {
    return route;
}