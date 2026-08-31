#include "City.hpp"
#include "GeneticAlgorithm.hpp"
#include "Individual.hpp"

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <string>

#define POPULATION_SIZE 10

using namespace std;

int main() {

    int totalCidades = 10;

    vector<City> listaCidades;

    // Gerador de números aleatórios
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> distCoord(0.0, 100.0);

    // Preenche o vetor com cidades contendo IDs de 0 até N-1
    for (int id = 0; id < totalCidades; id++) {

        double x = distCoord(gen);
        double y = distCoord(gen);

        listaCidades.push_back(
            City(id, x, y)
        );
    }


    // =========================================================
    // CIDADES
    // =========================================================

    cout << "=== TABELA DE CIDADES ALEATORIAS ===" << endl;

    cout << "ID\t\tX\t\tY" << endl;
    cout << "------------------------------------" << endl;

    for (const auto& city : listaCidades) {

        cout << city.getId() << "\t\t"
             << city.getX() << "\t\t"
             << city.getY() << endl;
    }


    // =========================================================
    // ALGORITMO GENETICO
    // =========================================================

    GeneticAlgorithm ga(
        listaCidades,
        POPULATION_SIZE,
        100,
        0.05
    );


    // =========================================================
    // MATRIZ DE DISTANCIAS
    // =========================================================

    cout << fixed << setprecision(3);

    cout << "\n================ MATRIZ DE DISTANCIAS ================"
         << endl;

    cout << setw(10) << "ID Cidades";

    for (const auto& city : listaCidades) {

        cout << setw(10)
             << ("ID " + to_string(city.getId()));
    }

    cout << "\n----------------------------------------------------"
         << endl;

    for (size_t i = 0; i < listaCidades.size(); i++) {

        cout << setw(10)
             << ("ID " + to_string(listaCidades[i].getId()));

        for (size_t j = 0; j < listaCidades.size(); j++) {

            cout << setw(10)
                 << ga.getDistance(i, j);
        }

        cout << endl;
    }


    // =========================================================
    // POPULAÇÃO
    // =========================================================

    cout << "\n================ POPULACAO ================="
         << endl;

    auto& population = ga.getPopulation();

    for (size_t i = 0; i < population.size(); i++) {

        Individual& individual = population[i];

        double distance =
            individual.distenceCalc(
                ga.getDistanceMatrix()
            );

        double fitness =
            individual.fitnessCalc();


        cout << "\nIndividual " << i + 1 << endl;

        cout << "Rota: ";

        for (int cityId : individual.getRoute()) {
            cout << cityId << " -> ";
        }

        cout << individual.getRoute()[0] << endl;

        cout << fixed << setprecision(2)
             << "Distancia: " << distance << endl;

        cout << fixed << setprecision(6)
             << "Fitness: " << fitness << endl;
    }


    // =========================================================
    // SELEÇÃO POR TORNEIO
    // =========================================================

    cout << "\n================ TORNEIO ================="
         << endl;

    for (int i = 0; i < 5; i++) {

        Individual vencedor =
            ga.tournamentSelection(3);

        cout << "\nTorneio " << i + 1 << endl;

        cout << "Rota: ";

        for (int cityId : vencedor.getRoute()) {
            cout << cityId << " -> ";
        }

        cout << vencedor.getRoute()[0] << endl;

        cout << fixed << setprecision(6)
             << "Fitness: "
             << vencedor.fitnessCalc()
             << endl;
    }


    // =========================================================
    // ORDER CROSSOVER
    // =========================================================

    Individual parent1 = population[0];
    Individual parent2 = population[1];

    Individual child =
        ga.orderCrossover(parent1, parent2);


    cout << "\n================ CROSSOVER ================="
         << endl;


    cout << "\nPai 1: ";

    for (int city : parent1.getRoute()) {
        cout << city << " -> ";
    }

    cout << parent1.getRoute()[0] << endl;


    cout << "\nPai 2: ";

    for (int city : parent2.getRoute()) {
        cout << city << " -> ";
    }

    cout << parent2.getRoute()[0] << endl;


    cout << "\nFilho: ";

    for (int city : child.getRoute()) {
        cout << city << " -> ";
    }

    cout << child.getRoute()[0] << endl;


    // Avaliação do filho

    double childDistance =
        child.distenceCalc(
            ga.getDistanceMatrix()
        );

    double childFitness =
        child.fitnessCalc();

    cout << fixed << setprecision(2)
         << "Distancia: "
         << childDistance << endl;

    cout << fixed << setprecision(6)
         << "Fitness: "
         << childFitness << endl;


    return 0;
}