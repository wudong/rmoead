/*
 * Population.cpp
 *
 *  Created on: 6 Jun 2010
 *      Author: wudong
 */

#include "SingleObjEA.h"

SingleObjEA::SingleObjEA(int popsize) {
	this->individuals.resize(popsize);
	for (int i = 0; i < popsize; i++) {
		ChromosomePtr ptr(new Chromosome());
		this->individuals.push_back(ptr);
	}
}

void SingleObjEA::seed(ChromosomePtr seed) {
	unsigned int size = this->individuals.size();
	int random = nextRandomInt(size);
	*this->individuals[random] = *seed;
}

void SingleObjEA::setFitnessFunction(Function& func) {
	this->fitnessFunc.reset(&func);
}

void SingleObjEA::evolve(int fes) {
}

ChromosomePtr SingleObjEA::findBest() {

}

double SingleObjEA::fitness(std::vector<double>& var) {
	std::copy(var.begin(), var.end(), TEMP_BUFFER);
	return fitness(TEMP_BUFFER);
}

double SingleObjEA::fitness(double *var) {
	double result;
	(*this->fitnessFunc)(var, &result);
	return result;
}

