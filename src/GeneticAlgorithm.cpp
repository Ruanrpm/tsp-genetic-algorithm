#include "GeneticAlgorithm.hpp"
#include <cmath>
#include <vector>
#include "City.hpp"
#include "Individual.hpp"
#include <iostream>
#include <random>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(vector<City> cities, int populationSize, int generations, double mutationRate, int tournamentSize) 
    : cities(cities), distanceMatrix(cities.size(), vector<double>(cities.size(), 0.0)), populationSize(populationSize), generations(generations), mutationRate(mutationRate), tournamentSize(tournamentSize) {
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

Individual GeneticAlgorithm:: orderCrossover(const Individual& parent1, const Individual& parent2) {
    const vector<int>& pai1 = parent1.getRoute();
    const vector<int>& pai2 = parent2.getRoute();

    int routeSize = pai1.size();

    // Escole dois pontos de corte
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(1, routeSize - 1);

    int start = dist(gen);
    int end = dist(gen);

    if (start > end) {
        swap(start, end);
    }

    vector<int> childRoute(routeSize, -1);
    childRoute[0] = 0;

    // Copia o primeiro pai
    for (int i = start; i <= end; i++) {
        childRoute[i] = pai1[i];
    }

    // Começa do end pois começa preenchendo o restante seguindo a ordem do pai 2
    int currentPosition = end + 1;

    if (currentPosition >= routeSize) {
        currentPosition = 1;
    }

    // Percorre o segundo pai
    for (int i = 0; i < routeSize - 1; i++) {
        int city = pai2[(end + i) % (routeSize - 1) + 1];

        bool alreadyExists = false;

        // Verifica se a cidade já existe no segmento
        for (int j = start; j <= end; j++) {
            if (childRoute[j] == city) {
                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists) {
            childRoute[currentPosition] = city;

            currentPosition++;

            if (currentPosition >= routeSize) {
                currentPosition = 1;
            }
        }
    }
    
    return Individual(childRoute, false);
}

void GeneticAlgorithm::mutate(Individual& individual) {

    random_device rd;
    mt19937 gen(rd());

    // Verifica se o indivíduo vai sofrer mutação
    uniform_real_distribution<double> probability(0.0, 1.0);

    if (probability(gen) >= mutationRate) {
        return;
    }

    vector<int>& route = individual.getRoute();

    // Escolhe duas posições aleatórias
    uniform_int_distribution<int> position(1, route.size() - 1);

    int pos1 = position(gen);
    int pos2 = position(gen);

    // Garante que as posições sejam diferentes
    while (pos1 == pos2) {
        pos2 = position(gen);
    }

    // Swap mutation
    swap(route[pos1], route[pos2]);
}

Individual GeneticAlgorithm::getBestIndividual() {

    Individual best = population[0];

    for (int i = 1; i < population.size(); i++) {

        if (population[i].getFitness() > best.getFitness()) {
            best = population[i];
        }
    }

    return best;
}

void GeneticAlgorithm::nextGeneration() {
    vector<Individual> newPopulation;

    // Elitismo
    Individual best = getBestIndividual();

    newPopulation.push_back(best);

    // Filhos
    while (newPopulation.size() < populationSize) {
        Individual parent1 = tournamentSelection(tournamentSize);
        Individual parent2 = tournamentSelection(tournamentSize);

        // Crossover
        Individual child = orderCrossover(parent1, parent2);

        // mutação
        mutate(child);

        // Avaliação do filho
        child.distenceCalc(distanceMatrix);
        child.fitnessCalc();

        newPopulation.push_back(child);
    }

    population = newPopulation;
}