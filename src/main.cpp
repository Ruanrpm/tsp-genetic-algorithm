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
    int totalCidades = 10; // Defina a quantidade N de cidades desejada
    vector<City> listaCidades;

    // Configuração do gerador de números aleatórios do C++ moderno
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distCoord(0.0, 100.0); // Coordenadas X e Y entre 0.0 e 100.0

    // Preenche o vetor com cidades contendo IDs de 1 até N e coordenadas aleatórias
    for (int id = 0; id < totalCidades; id++) {
        double x = distCoord(gen);
        double y = distCoord(gen);
        listaCidades.push_back(City(id, x, y));
    }

    // Exibe a tabela de cidades geradas
    cout << "=== TABELA DE CIDADES ALEATORIAS ===" << endl;
    cout << "ID\t\tX\t\tY" << endl;
    cout << "------------------------------------" << endl;
    for (const auto& city : listaCidades) {
        cout << city.getId() << "\t\t" 
             << city.getX() << "\t\t" 
             << city.getY() << endl;
    }

    // Exemplo de instanciação do seu Algoritmo Genético
    // GeneticAlgorithm ga(listaCidades, 50, 100, 0.05);

    // Instancia o Algoritmo Genético e calcula as distâncias
    GeneticAlgorithm ga(listaCidades, POPULATION_SIZE, 100, 0.05);
    ga.distanceMatrixCalc();

    // Configuração de precisão para imprimir valores com 2 casas decimais
    cout << fixed << setprecision(3);

    cout << "\n================ MATRIZ DE distanceS ================" << endl;
    
    // Cabecalho da tabela de distances (IDs das Cidades)
    cout << setw(10) << "ID Cidades";
    for (const auto& city : listaCidades) {
        cout << setw(10) << ("ID " + to_string(city.getId()));
    }
    cout << "\n----------------------------------------------------" << endl;

    // Linhas com as distances obtidas da classe
    for (size_t i = 0; i < listaCidades.size(); i++) {
        cout << setw(10) << ("ID " + to_string(listaCidades[i].getId()));
        for (size_t j = 0; j < listaCidades.size(); j++) {
            cout << setw(10) << ga.getDistance(i, j); // Método para retornar a distância
        }
        cout << endl;
    }

    cout << "\n================ POPULACAO =================" << endl;

    auto& population = ga.getPopulation();

    for (size_t i = 0; i < population.size(); i++) {

        Individual& individual = population[i];

        double distance = individual.distenceCalc(ga.getDistanceMatrix());
        double fitness = individual.fitnessCalc();

        cout << "\nIndividual " << i + 1 << endl;

        cout << "Rota: ";

        for (int cityId : individual.getRoute()) {
            cout << cityId << " -> ";
        }

        cout << individual.getRoute()[0] << endl;

        cout << setprecision(2) << "Distancia: " << distance << endl;
        cout << setprecision(6) << "Fitness: " << fitness << endl;
    }

    cout << "\n================ TORNEIO =================" << endl;

    for (int i = 0; i < 5; i++) {

        Individual vencedor = ga.tournamentSelection(3);

        cout << "\nTorneio " << i + 1 << endl;

        cout << "Rota: ";

        for (int cityId : vencedor.getRoute()) {
            cout << cityId << " -> ";
        }

        cout << vencedor.getRoute()[0] << endl;

        cout << "Fitness: "
            << fixed << setprecision(6)
            << vencedor.fitnessCalc()
            << endl;
    }
}