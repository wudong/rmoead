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

	virtual void initPop(int popsize);
	virtual void seed(ChromosomePtr seed);
	void evolve(int fes);

	virtual ChromosomePtr findBest(bool best);

private:

};

#endif /* POPULATION_H_ */
