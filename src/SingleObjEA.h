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
#include "EvolutionaryAlgorithm.h"

class SingleObjEA : public EvolutionaryAlgorithm<ChromosomePtr>{
public:
	SingleObjEA(int popsize);

	virtual ~SingleObjEA() {
	}
	;

	void seed(ChromosomePtr seed);
	void evolve(int fes);
	void setFitnessFunction(Function& func);

	ChromosomePtr findBest();

private:

};

#endif /* POPULATION_H_ */
