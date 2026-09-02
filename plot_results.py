import csv
from pathlib import Path

import matplotlib.pyplot as plt


# ============================================================
# LOCALIZAR A EXECUÇÃO MAIS RECENTE
# ============================================================

RESULTADOS = Path("resultados")

execucoes = [
    pasta
    for pasta in RESULTADOS.glob("execucao_*")
    if pasta.is_dir()
]


if not execucoes:
    raise FileNotFoundError(
        "Nenhuma pasta de execução foi encontrada em 'resultados'."
    )


def numero_execucao(pasta):
    return int(pasta.name.split("_")[1])


execucoes.sort(key=numero_execucao)

EXECUCAO = execucoes[-1]


print(f"Gerando gráficos para: {EXECUCAO}")


# ============================================================
# EVOLUÇÃO DO FITNESS
# ============================================================

arquivo = EXECUCAO / "evolucao.csv"

geracoes = []
fitness = []

with open(
    arquivo,
    newline="",
    encoding="utf-8"
) as file:

    reader = csv.DictReader(file)

    for row in reader:

        geracoes.append(
            int(row["generation"])
        )

        fitness.append(
            float(row["fitness"])
        )


# Melhor resultado
melhor_fitness = max(fitness)

geracao_melhor = geracoes[
    fitness.index(melhor_fitness)
]


plt.figure(figsize=(10, 6))

plt.plot(
    geracoes,
    fitness,
    linewidth=1.8,
    label="Melhor fitness"
)


# Destaca o melhor ponto
plt.scatter(
    geracao_melhor,
    melhor_fitness,
    s=60,
    zorder=3
)


plt.annotate(
    f"Melhor: {melhor_fitness:.6f}\n"
    f"Geração: {geracao_melhor}",
    (geracao_melhor, melhor_fitness),
    xytext=(10, -35),
    textcoords="offset points"
)


# Configurações
plt.title(
    "Evolução do Fitness no Algoritmo Genético",
    fontsize=14
)

plt.xlabel(
    "Geração",
    fontsize=11
)

plt.ylabel(
    "Melhor Fitness",
    fontsize=11
)

plt.grid(
    True,
    alpha=0.3
)

plt.legend()

plt.tight_layout()


# Salvar
plt.savefig(
    EXECUCAO / "evolucao_fitness.png",
    dpi=300,
    bbox_inches="tight"
)


# ============================================================
# ROTA FINAL
# ============================================================

route_file = EXECUCAO / "rota_final.csv"

cities = []

with open(
    route_file,
    newline="",
    encoding="utf-8"
) as file:

    reader = csv.DictReader(file)

    for row in reader:

        cities.append({
            "id": int(row["city_id"]),
            "x": float(row["x"]),
            "y": float(row["y"]),
            "position": int(row["route_position"])
        })


# Ordena pela ordem da rota
cities.sort(
    key=lambda city: city["position"]
)


x = [city["x"] for city in cities]
y = [city["y"] for city in cities]
ids = [city["id"] for city in cities]


plt.figure(figsize=(10, 8))


# ============================================================
# DESENHAR A ROTA
# ============================================================

for i in range(len(cities) - 1):

    plt.plot(
        [x[i], x[i + 1]],
        [y[i], y[i + 1]]
    )


# Fecha o ciclo
plt.plot(
    [x[-1], x[0]],
    [y[-1], y[0]]
)


# ============================================================
# DESENHAR AS CIDADES
# ============================================================

plt.scatter(
    x,
    y,
    s=70
)


# ============================================================
# IDS
# ============================================================

for i in range(len(cities)):

    plt.annotate(
        str(ids[i]),
        (x[i], y[i]),
        xytext=(5, 5),
        textcoords="offset points"
    )


# ============================================================
# CONFIGURAÇÕES
# ============================================================

plt.title(
    "Melhor Rota Encontrada - TSP",
    fontsize=14
)

plt.xlabel(
    "X",
    fontsize=11
)

plt.ylabel(
    "Y",
    fontsize=11
)

plt.grid(
    True,
    alpha=0.3
)

plt.axis("equal")

plt.tight_layout()


# Salvar
plt.savefig(
    EXECUCAO / "rota_final.png",
    dpi=300,
    bbox_inches="tight"
)


# ============================================================
# MOSTRAR GRÁFICOS
# ============================================================

plt.show()