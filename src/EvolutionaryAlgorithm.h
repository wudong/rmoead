/*
 * EvolutionaryAlgorithm.h
 *
 *  Created on: 14 Jun 2010
 *      Author: wudong
 */

#ifndef EVOLUTIONARYALGORITHM_H_
#define EVOLUTIONARYALGORITHM_H_

#include "Chromosome.h"
#include "Function.h"

template <typename T>
class EvolutionaryAlgorithm {
public:
	EvolutionaryAlgorithm(){};
	virtual ~EvolutionaryAlgorithm(){};
	virtual void evaluate(ChromosomePtr chrom);
	virtual void setFunction(FunctionPtr func){this->function = func;};
	virtual void initPop()=0;
	virtual void evolve()=0;
	void setRunId(int id){this->runid=id;};
	int getPopsize(){return population.size();};

protected:
	int runid;
	int fesCounter;
	FunctionPtr function;
	std::vector<T> population;
};

template <typename T>
void EvolutionaryAlgorithm<T>::evaluate(ChromosomePtr chrom) {
	(*this->function)(chrom);
	this->fesCounter++;
}

#endif /* EVOLUTIONARYALGORITHM_H_ */
