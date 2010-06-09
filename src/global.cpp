#ifndef __GLOBAL_H_
#define __GLOBAL_H_

using namespace std;

#include <string>
#include <vector>
#include <gsl/gsl_rng.h>
#include <confuse.h>

//------------- Parameters in test instance ------------------

unsigned int     nvar,  nobj;     //  the number of variables and objectives

double  lowBound = 0,   uppBound = 1;   //  lower and upper bounds of variables

char*    strTestInstance;

std::string    output_dir;
std::string    input_dir;

//------------- Parameters in random number ------------------
long random_seed;

const gsl_rng_type * rand_T;

gsl_rng * rand_generator;

//------------ some temporary buffer.
double temp_buffer_1[100];
double temp_buffer_2[100];
double temp_buffer_3[100];
double temp_buffer_4[100];

//------------- Parameters in MOEA/D -------------------------

double         idealpoint[100];
double         scale[100];

int		etax    = 20, 	etam    = 20;   // distribution indexes of crossover and mutation

double  realx,  realm,  realb = 0.9;    // crossover, mutation, selection probabilities

cfg_t *configurator;

int nfes=0;

#endif
