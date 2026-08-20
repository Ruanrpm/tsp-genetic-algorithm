#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>

class Individual {
private:
    std::vector<int> route;
    double fitness = 0.0;

public:
    Individual(const std::vector<int>& cityId);

    double fitnessCalc(const std::vector<std::vector<double>>& distanceMatrix);

    const std::vector<int>& getRoute() const;
};

#endif