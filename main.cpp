#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include "Particle.h"

using namespace std;
#define PI 3.14159265359
#define iteration 100
#define w 0.729
#define c1 1.49445
#define c2 1.49445
double evaluate(double x1, double x2);
double random_number(double a, double b);
int main() {
	Particle particle[40];
	vector<double> gbest_position = { 0,0 };
	double gbest = 1000;
	ofstream File,particle_position;
	int record = 0;
	File.open("gbest.txt");
	particle_position.open("particle_position.txt");
	if (!File.is_open()||!particle_position.is_open()) {
		cout << "Failed to open file" << endl;
		return -1;
	}
	for (int i = 0; i < 40; i++) {
		Particle* temp = new Particle();
		particle[i] = *temp;
	}
	
	for (int i = 0; i < 40; i++) {
		if (particle[i].fitness < gbest) {
			gbest = particle[i].fitness;
			gbest_position = particle[i].best_position;
		}
	}

	for (int i = 0; i < iteration; i++) {
		if (i% 10 == 0 || i == 99) {
			particle_position << "Iteration: "<< i << "\n";
		}
		for (int j = 0; j < 40; j++) {
			//update velocity
			for (int k = 0; k < 2; k++) {
				particle[j].velocity[k] = w * particle[j].velocity[k] + 
					c1 * random_number(0.0, 1.0) * (particle[j].best_position[k] - particle[j].position[k]) + 
					c2 * random_number(0.0, 1.0) * (gbest_position[k] - particle[j].position[k]);
				// if velocity out of range
				if (particle[j].velocity[k] < -5.0) {
					particle[j].velocity[k] = -5.0;
				}
				else if (particle[j].velocity[k] > 5.0) {
					particle[j].velocity[k] = 5.0;
				}
			}

			// update position
			for (int k = 0; k < 2; k++) {
				particle[j].position[k] += particle[j].velocity[k];
			}
			// calculate fitness
			particle[j].fitness = evaluate(particle[j].position[0], particle[j].position[1]);
			// print particle information
			if (i % 10 == 0 || i == 99) {
				particle_position << particle[j].position[0] << " " << particle[j].position[1]<<" "<< particle[j].fitness<<"\n";
			}
			// Determine if it's pbest
			if (particle[j].fitness < particle[j].pbest) {
				particle[j].pbest = particle[j].fitness;
				particle[j].best_position = particle[j].position;
			}
			
			// Determine if it's gbest
			if (particle[j].fitness < gbest) {
				gbest = particle[j].fitness;
				gbest_position = particle[j].position;
				record = 0;
			}
			else {
				record++;
				if (record >= 40*20) { // if the result is not progess, terminate it.
					cout << "Terminated because it's reach the terminate condition." << endl;
					return 0;
				}
			}
		}
		File << gbest << "\n";
		cout << i << ":" << gbest << endl;
	}
	File.close();
	return 0;
}

double evaluate(double x1, double x2)
{
	double fitness = 0;
	fitness += pow(x1, 2) - 10 * cos(2 * PI * x1) + 10;
	fitness += pow(x2, 2) - 10 * cos(2 * PI * x2) + 10;
	return fitness;
}

double random_number(double a, double b)
{
	double x = (b - a) * rand() / (RAND_MAX + 1.0) + a;
	return x;
}