#include "City.hpp"
#include "GeneticAlgorithm.hpp"
#include "Individual.hpp"

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;


// =========================================================
// CONFIGURAÇÃO DO ALGORITMO
// =========================================================

const int TOTAL_CIDADES = 25;
const int POPULATION_SIZE = 100;
const int GENERATIONS = 500;
const double MUTATION_RATE = 0.10;
const int TOURNAMENT_SIZE = 4;


int main() {

    // =====================================================
    // GERAR CIDADES
    // =====================================================

    vector<City> listaCidades;

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> distCoord(0.0, 100.0);

    for (int id = 0; id < TOTAL_CIDADES; id++) {

        double x = distCoord(gen);
        double y = distCoord(gen);

        listaCidades.push_back(
            City(id, x, y)
        );
    }


    // =====================================================
    // CRIAR ALGORITMO GENÉTICO
    // =====================================================

    GeneticAlgorithm ga(
        listaCidades,
        POPULATION_SIZE,
        GENERATIONS,
        MUTATION_RATE
    );


    // =====================================================
    // AVALIAR POPULAÇÃO INICIAL
    // =====================================================

    auto& population = ga.getPopulation();

    for (Individual& individual : population) {

        individual.distenceCalc(
            ga.getDistanceMatrix()
        );

        individual.fitnessCalc();
    }


    // =====================================================
    // MELHOR INDIVÍDUO INICIAL
    // =====================================================

    Individual best = ga.getBestIndividual();

    double bestFitness = best.getFitness();

    double bestDistance =
        best.distenceCalc(
            ga.getDistanceMatrix()
        );


    // =====================================================
    // EXECUÇÃO DAS GERAÇÕES
    // =====================================================

    cout << fixed << setprecision(6);

    cout << "Melhor inicial | "
         << "Geracao: 0 | "
         << "Fitness: "
         << bestFitness
         << endl;


    for (int generation = 1;
         generation <= GENERATIONS;
         generation++) {

        // Cria a próxima geração
        ga.nextGeneration();


        // Pega o melhor indivíduo da geração
        Individual currentBest =
            ga.getBestIndividual();

        double currentFitness =
            currentBest.getFitness();


        // Verifica se houve melhoria
        if (currentFitness > bestFitness) {

            bestFitness = currentFitness;

            bestDistance =
                currentBest.distenceCalc(
                    ga.getDistanceMatrix()
                );

            cout << "Melhoria       | "
                 << "Geracao: "
                 << generation
                 << " | Fitness: "
                 << bestFitness
                 << endl;
        }
    }


    // =====================================================
    // RESULTADO FINAL
    // =====================================================

    Individual finalBest =
        ga.getBestIndividual();

    double finalDistance =
        finalBest.distenceCalc(
            ga.getDistanceMatrix()
        );

    double finalFitness =
        finalBest.fitnessCalc();


    cout << "\n========================================"
         << endl;

    cout << "RESULTADO FINAL"
         << endl;

    cout << "Geracoes: "
         << GENERATIONS
         << endl;

    cout << "Melhor distancia: "
         << fixed
         << setprecision(2)
         << finalDistance
         << endl;

    cout << "Melhor fitness: "
         << fixed
         << setprecision(6)
         << finalFitness
         << endl;

    cout << "Melhor rota: ";

    for (int city : finalBest.getRoute()) {
        cout << city << " -> ";
    }

    cout << finalBest.getRoute()[0]
         << endl;

    cout << "========================================"
         << endl;


    return 0;
}