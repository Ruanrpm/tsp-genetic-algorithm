#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>

class Individual {
private:
    std::vector<int> route;
    double distance = 0.0;
    double fitness = 0;

public:
    Individual(const std::vector<int>& cityId);
    Individual(const std::vector<int>& cityId, bool shuffleRoute);
    Individual();

    double distenceCalc(const std::vector<std::vector<double>>& distanceMatrix);

    double fitnessCalc();

    double getFitness() const;

    const std::vector<int>& getRoute() const;
};

#endif