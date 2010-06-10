/*
 * individual.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#include "Chromosome.h"

Chromosome::Chromosome() {
	x_var.resize(nvar);
	y_obj.resize(nvar);
	rnd_init();
	rank = 0;
}

Chromosome::~Chromosome() {
}

ChromosomePtr Chromosome::clone(){
	ChromosomePtr chrom(new Chromosome());
	*chrom = *this;
}

void Chromosome::rnd_init() {
	for (unsigned int n = 0; n < nvar; n++)
		x_var[n] = nextRandomDouble(lowBound, uppBound);

	this->evaluated = false;
}

void Chromosome::show_objective() {
	for (unsigned int n = 0; n < nobj; n++)
		printf("%f ", y_obj[n]);
	printf("\n");
}

void Chromosome::show_variable() {
	for (int n = 0; n < nvar; n++)
		printf("%f ", x_var[n]);
	printf("\n");
}

void Chromosome::operator=(const Chromosome &ind2) {
	x_var = ind2.x_var;
	y_obj = ind2.y_obj;
	rank = ind2.rank;
	evaluated = ind2.evaluated;
}

bool Chromosome::operator<(const Chromosome &ind2) {
	bool dominated = true;
	for (int n = 0; n < nobj; n++) {
		if (ind2.y_obj[n] < y_obj[n])
			return false;
	}
	if (ind2.y_obj == y_obj)
		return false;
	return dominated;
}

bool Chromosome::operator<<(const Chromosome &ind2) {
	bool dominated = true;
	for (int n = 0; n < nobj; n++) {
		if (ind2.y_obj[n] < y_obj[n] - 0.0001)
			return false;
	}
	if (ind2.y_obj == y_obj)
		return false;
	return dominated;
}

bool Chromosome::operator==(const Chromosome &ind2) {
	return (dist_vector(this->x_var, ind2.x_var, nvar) < 1.0E-10);
}



