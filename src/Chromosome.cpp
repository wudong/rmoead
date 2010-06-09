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

void Chromosome::rnd_init() {
	for (unsigned int n = 0; n < nvar; n++)
		x_var[n] = nextRandomDouble(lowBound, uppBound);

	this->evaluated = false;
}

void Chromosome::obj_eval() {

	std::copy(y_obj.begin(), y_obj.end(), temp_buffer_1);
	std::copy(x_var.begin(), x_var.end(), temp_buffer_2);

	double scale = 20;

	if (!strcmp("UF1", strTestInstance)) {
		CEC09_F1(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF1X", strTestInstance)) {
		CEC09_F1(temp_buffer_1, temp_buffer_2);
		temp_buffer_1[0] = scale * temp_buffer_1[0];
	} else if (!strcmp("UF2", strTestInstance)) {
		CEC09_F2(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF2X", strTestInstance)) {
		CEC09_F2(temp_buffer_1, temp_buffer_2);
		temp_buffer_1[0] = scale * temp_buffer_1[0];
	} else if (!strcmp("UF3", strTestInstance)) {
		CEC09_F3(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF3X", strTestInstance)) {
		CEC09_F3(temp_buffer_1, temp_buffer_2);
		temp_buffer_1[0] = scale * temp_buffer_1[0];
	} else if (!strcmp("UF4", strTestInstance)) {
		CEC09_F4(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF5", strTestInstance)) {
		CEC09_F5(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF5_1", strTestInstance)) {
		CEC09_F5_1(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF6", strTestInstance)) {
		CEC09_F6(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF7", strTestInstance)) {
		CEC09_F7(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF7X", strTestInstance)) {
		CEC09_F7(temp_buffer_1, temp_buffer_2);
		temp_buffer_1[0] = scale * temp_buffer_1[0];
	} else if (!strcmp("UF8", strTestInstance)) {
		CEC09_F8(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF9", strTestInstance)) {
		CEC09_F9(temp_buffer_1, temp_buffer_2);
	} else if (!strcmp("UF10", strTestInstance)) {
		CEC09_F10(temp_buffer_1, temp_buffer_2);
	} else
		assert(false);

	std::copy(temp_buffer_1, temp_buffer_1 + nobj, y_obj.begin());

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

