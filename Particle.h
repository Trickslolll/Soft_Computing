#pragma once
#include <vector>
using namespace std;
class Particle
{
public:
    vector<double> position;
    vector<double> velocity;
    vector<double> best_position;
    double fitness,pbest;
    Particle();
private:
    double random_number(double a, double b);
    double evaluate(double x);
};

