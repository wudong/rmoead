/*
 * Population.h
 *
 *  Created on: 6 Jun 2010
 *      Author: wudong
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Chromosome.h"

class Population {
public:
	Population();

	virtual ~Population();

	std::vector<ChromosomePtr> individuals;
};

#endif /* POPULATION_H_ */
