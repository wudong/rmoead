/*
 * individual.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#include "Chromosome.h"

Chromosome::Chromosome() {
	x_var = new double[nvar];
	y_obj = new double[nvar];
	rank = 0;
}

Chromosome::~Chromosome() {
	delete[] x_var;
	delete[] y_obj;
}

void Chromosome::rnd_init() {
	for (unsigned int n = 0; n < nvar; n++)
		x_var[n] = nextRandomDouble(lowBound, uppBound);
}

void Chromosome::obj_eval() {

	double scale = 20;
	if (!strcmp("UF1", strTestInstance)) {
		CEC09_F1(y_obj, x_var);
	} else if (!strcmp("UF1X", strTestInstance)) {
		CEC09_F1(y_obj, x_var);
		y_obj[0] = scale * y_obj[0];
	} else if (!strcmp("UF2", strTestInstance)) {
		CEC09_F2(y_obj, x_var);
	} else if (!strcmp("UF2X", strTestInstance)) {
		CEC09_F2(y_obj, x_var);
		y_obj[0] = scale * y_obj[0];
	} else if (!strcmp("UF3", strTestInstance)) {
		CEC09_F3(y_obj, x_var);
	} else if (!strcmp("UF3X", strTestInstance)) {
		CEC09_F3(y_obj, x_var);
		y_obj[0] = scale * y_obj[0];
	} else if (!strcmp("UF4", strTestInstance)) {
		CEC09_F4(y_obj, x_var);
	} else if (!strcmp("UF5", strTestInstance)) {
		CEC09_F5(y_obj, x_var);
	} else if (!strcmp("UF5_1", strTestInstance)) {
		CEC09_F5_1(y_obj, x_var);
	} else if (!strcmp("UF6", strTestInstance)) {
		CEC09_F6(y_obj, x_var);
	} else if (!strcmp("UF7", strTestInstance)) {
		CEC09_F7(y_obj, x_var);
	} else if (!strcmp("UF7X", strTestInstance)) {
		CEC09_F7(y_obj, x_var);
		y_obj[0] = scale * y_obj[0];
	} else if (!strcmp("UF8", strTestInstance)) {
		CEC09_F8(y_obj, x_var);
	} else if (!strcmp("UF9", strTestInstance)) {
		CEC09_F9(y_obj, x_var);
	} else if (!strcmp("UF10", strTestInstance)) {
		CEC09_F10(y_obj, x_var);
	} else
		assert(false);

	nfes++;

	//update reference.
	for (unsigned int n = 0; n < nobj; n++) {
		if (y_obj[n] < idealpoint[n]) {
			idealpoint[n] = y_obj[n];
		}
	}
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
	for (int i = 0; i < nvar; i++) {
		x_var[i] = ind2.x_var[i];
	}
	for (int i = 0; i < nobj; i++) {
		y_obj[i] = ind2.y_obj[i];
	}
	rank = ind2.rank;
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

