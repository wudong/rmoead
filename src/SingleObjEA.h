/*
 * Population.h
 *
 *  Created on: 6 Jun 2010
 *      Author: wudong
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Chromosome.h"
#include "Function.h"

class SingleObjEA;
typedef boost::shared_ptr<SingleObjEA> PopulationPtr;

class SingleObjEA {
public:
	SingleObjEA(int popsize);

	virtual ~SingleObjEA() {
	}
	;

	std::vector<ChromosomePtr> individuals;

	void seed(ChromosomePtr seed);
	void evolve(int fes);
	void setFitnessFunction(Function& func);

	ChromosomePtr findBest();

private:
	boost::shared_ptr<Function> fitnessFunc;
	double fitness(double*);
	double fitness(std::vector<double>&);

	double TEMP_BUFFER[100];
};

#endif /* POPULATION_H_ */
