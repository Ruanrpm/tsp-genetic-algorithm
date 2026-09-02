# TSP - Solução com Algoritmo Genético

![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue)
![Status](https://img.shields.io/badge/Status-Ativo-brightgreen)
![Licença](https://img.shields.io/badge/Licença-MIT-green)

## 📋 Descrição

Implementação eficiente em **C++** de uma solução para o **Problema do Caixeiro Viajante (TSP - Traveling Salesman Problem)** utilizando **Algoritmo Genético**. O projeto otimiza rotas de veículos aplicando simulação de seleção natural, crossover e mutação para encontrar caminhos próximos do ótimo de forma eficiente.

## 🎯 Motivação

O Problema do Caixeiro Viajante é um desafio clássico em otimização combinatória, amplamente aplicado em:
- 🚚 Logística e roteamento de veículos
- 📍 Otimização de rotas de entrega
- 🔧 Problemas de planejamento industrial
- 🧬 Estudo de algoritmos bioinspirados

Algoritmos genéticos são especialmente eficazes neste tipo de problema por encontrarem boas soluções em tempo computacional viável, mesmo para instâncias de grande porte.

## 🔧 Características

- ✅ **Algoritmo Genético Robusto**: Implementação completa com seleção por torneio, crossover OX e mutação adaptativa
- ✅ **Matriz de Distâncias Pré-calculada**: Otimização de performance através de pré-cálculo
- ✅ **Cálculo de Fitness**: Avaliação automática da qualidade das soluções
- ✅ **Múltiplas Execuções**: Capacidade de executar e comparar várias rodadas
- ✅ **Exportação de Dados**: Resultados em CSV para análise e visualização
- ✅ **Visualização de Resultados**: Geração de gráficos com Python

## 📊 Metodologia

### Operadores Genéticos Implementados

| Operador | Descrição |
|----------|-----------|
| **Seleção** | Torneio (Tournament Selection) |
| **Crossover** | Order Crossover (OX) |
| **Mutação** | Inversão de segmentos e swap aleatório |
| **Fitness** | Distância total da rota (menor é melhor) |

### Fluxo do Algoritmo

```
1. Inicializar população aleatória
2. PARA cada geração:
   a. Avaliar fitness de cada indivíduo
   b. Seleção dos melhores indivíduos
   c. Aplicar crossover aos selecionados
   d. Aplicar mutação com taxa configurável
   e. Substituir população
3. Retornar melhor solução encontrada
```

## 🛠️ Requisitos

### Sistema
- Windows/Linux/MacOS
- GCC ou Clang (C++17 ou superior)
- Python 3.7+ (para visualização dos resultados)

### Dependências C++
- Nenhuma dependência externa obrigatória
- Utiliza apenas a biblioteca padrão do C++

### Dependências Python
```
matplotlib
pandas
numpy
```

## 🚀 Quickstart

### Compilação

```bash
# Windows (usando MinGW/g++)
g++ -std=c++17 -O2 src/main.cpp src/City.cpp src/GeneticAlgorithm.cpp src/Individual.cpp -o tsp.exe

# Linux/MacOS
g++ -std=c++17 -O2 src/main.cpp src/City.cpp src/GeneticAlgorithm.cpp src/Individual.cpp -o tsp
```

### Execução

```bash
# Windows
./tsp.exe

# Linux/MacOS
./tsp
```

O programa gerará automaticamente:
- Pasta `resultados/execucao_X/` com os dados da execução
- Arquivo `evolucao.csv` com dados de evolução por geração
- Arquivo `rota_final.csv` com a melhor rota encontrada

### Visualização dos Resultados

```bash
python plot_results.py
```

## 📁 Estrutura do Projeto

```
tsp-genetic-algorithm/
├── src/
│   ├── main.cpp                    # Função principal e configurações
│   ├── City.hpp / City.cpp         # Classe para representar cidades
│   ├── Individual.hpp / Individual.cpp    # Classe para indivíduos (rotas)
│   ├── GeneticAlgorithm.hpp / GeneticAlgorithm.cpp  # Algoritmo genético
│   ├── Visualization.hpp           # Funções de visualização
│   └── teste.cpp                   # Testes e validação
├── resultados/                     # Resultados das execuções
│   ├── execucao_1/
│   ├── execucao_2/
│   └── execucao_3/
├── plot_results.py                 # Script de visualização dos resultados
├── README.md                       # Este arquivo
└── anotacoes.txt                   # Notas de implementação
```

## ⚙️ Configuração

Edite os parâmetros em `src/main.cpp` para ajustar o comportamento do algoritmo:

```cpp
const int TOTAL_CIDADES = 65;           // Número de cidades
const int POPULATION_SIZE = 1000;       // Tamanho da população
const int GENERATIONS = 1500;           // Número de gerações
const double MUTATION_RATE = 0.3;       // Taxa de mutação (0.0 - 1.0)
const int TOURNAMENT_SIZE = 2;          // Tamanho do torneio de seleção
const int EXECUTION_ID = 3;             // ID da execução para identificar resultados
```

### Parametrização Recomendada

| Parâmetro | Pequeno | Médio | Grande |
|-----------|---------|-------|--------|
| Cidades | 20-30 | 30-100 | 100+ |
| População | 100-300 | 500-1500 | 1000-5000 |
| Gerações | 500-1000 | 1000-3000 | 3000+ |
| Taxa Mutação | 0.1-0.2 | 0.2-0.4 | 0.3-0.5 |

## 📊 Estrutura de Dados

### City
Representa uma cidade com coordenadas (x, y) e identificador único.

### Individual
Representa uma solução (rota) com:
- Sequência de cidades visitadas
- Distância total da rota
- Fitness (avaliação da qualidade)

### GeneticAlgorithm
Gerencia:
- População de indivíduos
- Matriz de distâncias pré-calculadas
- Operadores genéticos
- Evolução das gerações

## 📈 Interpretação dos Resultados

### evolucao.csv
Contém dados sobre a evolução do algoritmo por geração:
- **Geração**: Número da geração
- **Melhor Fitness**: Melhor distância encontrada até agora
- **Fitness Médio**: Média de fitness da população
- **Pior Fitness**: Pior fitness da geração

### rota_final.csv
Contém a melhor rota encontrada:
- Sequência ordenada de cidades visitadas
- Coordenadas (x, y) de cada cidade
- Distância total da rota

## 🎨 Visualização

O script `plot_results.py` gera:
1. **Gráfico de Convergência**: Evolução do melhor fitness ao longo das gerações
2. **Representação da Rota**: Visualização espacial da melhor rota encontrada
3. **Distribuição de Fitness**: Histograma do fitness da população final

## 📊 Resultados Esperados

A performance depende dos parâmetros configurados:
- **Cidades: 65** | **População: 1000** | **Gerações: 1500**
- Convergência típica: ~80-90% do ótimo em casos de benchmark conhecidos
- Tempo de execução: Segundos a minutos (máquina dependente)

## 🔬 Experimentos e Análise

Para executar múltiplas execuções e comparar resultados:

1. Altere `EXECUTION_ID` em `main.cpp`
2. Recompile e execute
3. Analise os arquivos CSV em `resultados/`
4. Use `plot_results.py` para visualizar convergência

## 🧬 Fundamento Teórico

### Seleção por Torneio
Seleciona os melhores indivíduos através de competições aleatórias de tamanho configurável.

### Order Crossover (OX)
Preserva a ordem relativa de cidades de ambos os pais, mantendo a integridade da rota.

### Mutação
Aplica perturbações pequenas nas rotas para explorar o espaço de soluções.

## 📝 Autor

Desenvolvido como projeto acadêmico de **Inteligência Artificial**

## 📚 Referências

- Back, T., Fogel, D. B., & Michalewicz, Z. (1997). *Handbook of Evolutionary Computation*
- Holland, J. H. (1992). *Adaptation in Natural and Artificial Systems*
- Goldberg, D. E. (1989). *Genetic Algorithms in Search, Optimization, and Machine Learning*

## 📄 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo LICENSE para detalhes.

---

**Última atualização**: Setembro de 2026
