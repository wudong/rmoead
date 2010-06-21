/*
 * common.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#include "common.h"

void minsort(double* x, int* idx, size_t size) {
	size_t * temp = new size_t[size];
	gsl_sort_index(temp, x, 1, size);
	for (unsigned int i = 0; i < size; i++)
		idx[i] = temp[i];
	delete[] temp;
}

double dist_vector(std::vector<double> vec1, std::vector<double> vec2, int dim) {
	double temp_buffer_1[BUFFER_SIZE];
	double temp_buffer_2[BUFFER_SIZE];
	std::copy(vec1.begin(), vec1.end(), temp_buffer_1);
	std::copy(vec2.begin(), vec2.end(), temp_buffer_2);
	return dist_vector(temp_buffer_1, temp_buffer_2, dim);
}

double dist_vector(double* vec1, double* vec2, int dim) {
	double sum = 0;
	for (int n = 0; n < dim; n++)
		sum += (vec1[n] - vec2[n]) * (vec1[n] - vec2[n]);
	return sqrt(sum);
}

bool dominate_vector(std::vector<double> u, std::vector<double> v, int dim) {
	double temp_buffer_1[BUFFER_SIZE];
	double temp_buffer_2[BUFFER_SIZE];
	std::copy(u.begin(), u.end(), temp_buffer_1);
	std::copy(v.begin(), v.end(), temp_buffer_2);
	return dominate_vector(temp_buffer_1, temp_buffer_2, dim);
}

bool dominate_vector(double* u, double* v, int dim) {
	bool a_is_worse = false;
	bool equals = true;
	for (int i = 0; i < dim && !a_is_worse; i++) {
		double fitnessValueA = u[i];
		double fitnessValueB = v[i];
		a_is_worse = (fitnessValueA > fitnessValueB);
		equals = (fitnessValueA == fitnessValueB) && equals;
	}
	return (!equals && !a_is_worse);
}

double fitnessfunction(std::vector<double>& y_obj, std::vector<double>& nambda) {
	double temp_buffer_1[BUFFER_SIZE];
	double temp_buffer_2[BUFFER_SIZE];
	std::copy(y_obj.begin(), y_obj.end(), temp_buffer_1);
	std::copy(nambda.begin(), nambda.end(), temp_buffer_2);
	double result = fitnessfunction(temp_buffer_1, temp_buffer_2);
	return result;
}

double fitnessfunction(double* y_obj, double* namda) {

	char* i = getScalarizationMethod();
	if (strcmp("te", i) == 0) {// Chebycheff Scalarizing Function
		double max_fun = -1.0e+30;

		for (int n = 0; n < nobj; n++) {
			double diff = fabs(y_obj[n] - idealpoint[n]);
			double feval;
			if (namda[n] == 0)
				feval = 0.0001 * diff;
			else
				feval = diff * namda[n];
			if (feval > max_fun)
				max_fun = feval;

		}
		return max_fun;
	} else if (strcmp("ws", i) == 0) {//weighted sum.
		double sum = 0;
		for (int n = 0; n < nobj; n++) {
			sum += namda[n] * y_obj[n];
		}
		return sum;
	} else if (strcmp("ate", i) == 0) {//argumented Te.
		double max_fun = -1.0e+30;

		for (int n = 0; n < nobj; n++) {
			double diff = fabs(y_obj[n] - idealpoint[n]);
			double feval;
			if (namda[n] == 0)
				feval = 0.0001 * diff;
			else
				feval = diff * namda[n];
			if (feval > max_fun)
				max_fun = feval;
		}

		double sum = 0;
		for (int n = 0; n < nobj; n++) {
			sum += namda[n] * y_obj[n];
		}
		return max_fun + 0.0001 * sum;
	} else {
		assert(false);
	}
}

void load_data(char filename[1024], vector<vector<double> > &data, int dim) {
	std::ifstream readf(filename);
	vector<double> vect = vector<double> (dim, 0);
	while (!readf.eof()) {
		for (int i = 0; i < dim; i++) {
			readf >> vect[i];
			//printf(" %f ", vect[i]);
		}
		data.push_back(vect);
		//vect.clear();    // bug here.
	}

	readf.close();
}

