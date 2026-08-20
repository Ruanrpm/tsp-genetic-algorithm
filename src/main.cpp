#include "City.hpp"
#include "GeneticAlgorithm.hpp"
#include "Individual.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <string>

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
    GeneticAlgorithm ga(listaCidades, 50, 100, 0.05);
    ga.distanceMatrixCalc();

    // Configuração de precisão para imprimir valores com 2 casas decimais
    cout << fixed << setprecision(2);

    // 1. IMPRIMIR LISTA DE CIDADES
    cout << "================= CIDADES GENERADAS =================" << endl;
    cout << setw(8) << "ID" << setw(12) << "X" << setw(12) << "Y" << endl;
    cout << "----------------------------------------------------" << endl;
    for (const auto& city : listaCidades) {
        cout << setw(8) << city.getId() 
             << setw(12) << city.getX() 
             << setw(12) << city.getY() << endl;
    }

    cout << "\n================ MATRIZ DE DISTANCIAS ================" << endl;
    
    // Cabecalho da tabela de distancias (IDs das Cidades)
    cout << setw(10) << "ID Cidades";
    for (const auto& city : listaCidades) {
        cout << setw(10) << ("ID " + to_string(city.getId()));
    }
    cout << "\n----------------------------------------------------" << endl;

    // Linhas com as distancias obtidas da classe
    for (size_t i = 0; i < listaCidades.size(); i++) {
        cout << setw(10) << ("ID " + to_string(listaCidades[i].getId()));
        for (size_t j = 0; j < listaCidades.size(); j++) {
            cout << setw(10) << ga.getDistance(i, j); // Método para retornar a distância
        }
        cout << endl;
    }

    cout << "\n================ INDIVIDUO =================" << endl;

    vector<int> cityIds;

    for (const auto& city : listaCidades) {
        cityIds.push_back(city.getId());
    }

    Individual individuo(cityIds);

    // Calcula o fitness usando a matriz de distâncias
    double fitness = individuo.fitnessCalc(ga.getDistanceMatrix());

    cout << "Rota: ";

    for (int cityId : individuo.getRoute()) {
        cout << cityId << " -> ";
    }

    // Retorna para a primeira cidade
    cout << individuo.getRoute()[0] << endl;

    cout << "Fitness: " << fitness << endl;

    return 0;
}