/*
 * Population.cpp
 *
 *  Created on: 6 Jun 2010
 *      Author: wudong
 */

#include "SingleObjEA.h"

void SingleObjEA::evolve(int fes) {
	while (this->fesCounter < fes) {
		ChromosomePtr best = findBest(true);
		ChromosomePtr rand1, rand2;
		while ((rand1 = randomInd()) == best)
			;
		while ((rand2 = randomInd()) == best || (rand2 == rand1))
			;


	}
}

void SingleObjEA::seed(ChromosomePtr seed) {
	*(this->randomInd()) = *seed;
}

void SingleObjEA::initPop(int popsize) {
	this->population.resize(popsize);
	for (unsigned int i = 0; i < popsize; i++) {
		ChromosomePtr chrom(new Chromosome());
		chrom->rnd_init(randGenerator);
		this->evaluate(chrom);
		population.push_back(chrom);
	}
}

ChromosomePtr SingleObjEA::findBest(bool best) {
	std::vector<ChromosomePtr>::iterator current = population.begin();
	std::vector<ChromosomePtr>::iterator end = population.end();

	ChromosomePtr bestInd = *current;
	double bestValue = bestInd->y_obj[0];

	current++;
	while (current != end) {
		if (best ? (*current)->y_obj[0] < bestValue :
		(*current)->y_obj[0] > bestValue) {
			bestInd = *current;
			bestValue = bestInd->y_obj[0];
		}
		current++;
	}
	return bestInd;
}

