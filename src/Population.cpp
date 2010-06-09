/*
 * Population.cpp
 *
 *  Created on: 6 Jun 2010
 *      Author: wudong
 */

#include "Population.h"

Population::Population(int popsize) {
	this->individuals.resize(popsize);
	for (int i=0;i<popsize;i++){
		ChromosomePtr ptr(new Chromosome());
		this->individuals.push_back(ptr);
	}
}

