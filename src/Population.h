/*
 * Population.h
 *
 *  Created on: 6 Jun 2010
 *      Author: wudong
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Chromosome.h"

class Population;
typedef boost::shared_ptr<Population> PopulationPtr;

class Population {
public:
	Population(int popsize);

	virtual ~Population() {
	}
	;

	std::vector<ChromosomePtr> individuals;

	void seed(ChromosomePtr seed);
	void evolve(int fes);
	ChromosomePtr findBest();
};

#endif /* POPULATION_H_ */
