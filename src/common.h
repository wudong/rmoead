#ifndef __COMMON_H_
#define __COMMON_H_

#include "global.h"
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_sort.h>

void minsort(double* x, int* pindex, size_t size);

double dist_vector(std::vector<double> vec1, std::vector<double> vec2, int dim);
double dist_vector(double* vec1, double* vec2, int size);

bool dominate_vector(std::vector<double> u, std::vector<double> v, int dim);
bool dominate_vector(double* u, double* v, int dim);

double fitnessfunction(std::vector<double>& y_obj, std::vector<double>& nambda);
double fitnessfunction(double* y_obj, double* namda);

void load_data(char filename[1024], vector<vector<double> > &data, int dim);

#endif
