#include "City.hpp"
#include "GeneticAlgorithm.hpp"
#include "Individual.hpp"

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;


// =========================================================
// CONFIGURAÇÃO DO ALGORITMO
// =========================================================

const int TOTAL_CIDADES = 65;
const int POPULATION_SIZE = 1000;
const int GENERATIONS = 1500;
const double MUTATION_RATE = 0.3;
const int TOURNAMENT_SIZE = 2;

const int EXECUTION_ID = 3;


int main() {

    // =====================================================
    // PASTA DE RESULTADOS
    // =====================================================

    filesystem::path resultadoDir =
        "../resultados/execucao_" +
        to_string(EXECUTION_ID);

    filesystem::create_directories(resultadoDir);


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


    // =====================================================
    // HISTÓRICO DA EVOLUÇÃO
    // =====================================================

    vector<int> generationHistory;
    vector<double> fitnessHistory;

    generationHistory.push_back(0);
    fitnessHistory.push_back(bestFitness);


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


        // Melhor indivíduo da geração
        Individual currentBest =
            ga.getBestIndividual();

        double currentFitness =
            currentBest.getFitness();


        // Guarda o melhor fitness da geração
        generationHistory.push_back(
            generation
        );

        fitnessHistory.push_back(
            currentFitness
        );


        // Verifica se houve melhoria
        if (currentFitness > bestFitness) {

            bestFitness = currentFitness;

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


    // =====================================================
    // SALVAR EVOLUÇÃO
    // =====================================================

    ofstream evolutionFile(
        resultadoDir / "evolucao.csv"
    );

    evolutionFile
        << "generation,fitness\n";

    for (size_t i = 0;
         i < generationHistory.size();
         i++) {

        evolutionFile
            << generationHistory[i]
            << ","
            << fitnessHistory[i]
            << "\n";
    }

    evolutionFile.close();


    // =====================================================
    // SALVAR ROTA FINAL
    // =====================================================

    ofstream routeFile(
        resultadoDir / "rota_final.csv"
    );

    routeFile
        << "city_id,x,y,route_position\n";

    const vector<int>& finalRoute =
        finalBest.getRoute();

    for (size_t position = 0;
         position < finalRoute.size();
         position++) {

        int cityId = finalRoute[position];

        const City& city =
            listaCidades[cityId];

        routeFile
            << city.getId()
            << ","
            << city.getX()
            << ","
            << city.getY()
            << ","
            << position
            << "\n";
    }

    routeFile.close();


    // =====================================================
    // FINAL
    // =====================================================

    cout << "\nResultados salvos em: "
         << resultadoDir
         << endl;


    return 0;
}