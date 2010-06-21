#ifndef __GLOBAL_H_
#define __GLOBAL_H_

using namespace std;

#include <string>
#include <vector>
#include <confuse.h>

//------------- Parameters in test instance ------------------

unsigned int     nvar,  nobj;     //  the number of variables and objectives

double  lowBound = 0,   uppBound = 1;   //  lower and upper bounds of variables

//char*    strTestInstance;

std::string    output_dir;
std::string    input_dir;

//------------- Parameters in MOEA/D -------------------------

double         idealpoint[100];
double         scale[100];

int		etax    = 20, 	etam    = 20;   // distribution indexes of crossover and mutation

double  realx,  realm,  realb = 0.9;    // crossover, mutation, selection probabilities

cfg_t *configurator;

int nfes=0;

#endif
