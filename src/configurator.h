/*
 * configurator.h
 *
 *  Created on: 21 Aug 2009
 *      Author: wudong
 */

#ifndef CONFIGURATOR_H_
#define CONFIGURATOR_H_

#include <confuse.h>
#include <string>

struct Problem { // Declare PERSON struct type
	char name[20];
	int nvar;
	int nobj;
};

int getPopulationSize();
int getNeighbourSize();

int load_parameters(std::string configfile);

int getRandomSeed();

int getNumberofTestInstance();

int getTotalNumberofRun();

void getTestInstance(Problem& p, int i);

int getNumberofProblemToTest();

char* getProblemToTest(int i);

int getTournamentSize();

void printAllParameters(FILE* file);

char* getSelectionMethod();
float getSortProb();

int getSelectionSize();

float getDecayRate();

int getUtilityComputationGen();

char* getScalarizationMethod();//0 for weighedtsum, 1 for techbycheff.

char* getEvolveMethod();

bool ifUseReactive();
bool ifUseWeightAdjust();

int getWeightAdjustSize();

float getDEWeight();

float getMutationRate();

float getDecayDelta();

float getReactiveProb();

float getDEf();
float getDEcr();

float getUpdateLimit();
float getUpdateNeighbourProb();

void setRandomSeed(int seed);

#endif /* CONFIGURATOR_H_ */
