#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <memory.h>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iomanip>

#include <gsl/gsl_rng.h>
#include <confuse.h>
#include "configurator.h"

#define EPS 1.0E-10

#ifndef QUEUE_SIZE
#define QUEUE_SIZE 100
#endif

using namespace std;
//------------- Parameters in test instance ------------------

extern unsigned int nvar, nobj; //  the number of variables and objectives

extern double lowBound, uppBound; //  lower and upper bounds of variables

extern char* strTestInstance;

extern std::string output_dir;
extern std::string input_dir;

//------------- Parameters in MOEA/D -------------------------

extern double idealpoint[100];
extern double scale[100];

extern int etax, etam; // distribution indexes of crossover and mutation

extern double realx, realm, realb; // crossover, mutation, selection probabilities

extern cfg_t *configurator;

//------------------Random Seed---------------------------------------

extern long random_seed;

extern const gsl_rng_type * rand_T;

extern gsl_rng * rand_generator;

//------------------number of function evaluation.
extern int nfes;

#endif
