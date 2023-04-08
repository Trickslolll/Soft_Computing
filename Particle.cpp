#include "Particle.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#define PI 3.14159265359
using namespace std;
Particle::Particle()
{
    fitness = 0;
    position.resize(2);
    velocity.resize(2);
    best_position.resize(2);
    for (int i = 0; i < 2; i++)
    {
        position.at(i) = random_number(-5.0, 5.0);
        fitness += evaluate(position.at(i));
        velocity.at(i) = random_number(-5.0, 5.0);
        best_position[i] = position[i];
    }
    pbest = fitness;
}

double Particle::random_number(double a, double b)
{
    double x = (b - a) * rand() / (RAND_MAX + 1.0) + a;
    return x;
}

double Particle::evaluate(double x) {
    double fitness = pow(x, 2) - 10 * cos(2 * PI * x) + 10;
    return fitness;
}