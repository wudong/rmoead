#ifndef _RECOMBINATION_H_
#define _RECOMBINATION_H_

#include "global.h"
#include "Chromosome.h"

/* Routine for real polynomial mutation of an T */
void realmutation(ChromosomePtr ind, double rate);

/* Routine for real variable SBX crossover */
void real_sbx_xoverA(ChromosomePtr parent1, ChromosomePtr parent2,
		ChromosomePtr child1, ChromosomePtr child2);

void real_sbx_xoverB(ChromosomePtr parent1, ChromosomePtr parent2,
		ChromosomePtr child);

/**
 * The first one is used as base. can be either random or best.
 * the second and third is the mutation varaibles.
 *
 * the result is stored in child without modify others.
 */
void diff_evo_xover_1(ChromosomePtr base, ChromosomePtr ind1,
		ChromosomePtr ind2, ChromosomePtr child, double de_f, double de_cr);

void diff_evo_xover_current2best(ChromosomePtr base, ChromosomePtr best,
		ChromosomePtr ind1, ChromosomePtr ind2, ChromosomePtr child,
		double de_f, double de_cr);

void diff_evo_xover_2(ChromosomePtr base, ChromosomePtr ind1,
		ChromosomePtr ind2, ChromosomePtr ind3, ChromosomePtr ind4,
		ChromosomePtr child, double de_f, double de_cr);

void partical_swarm_evol(ChromosomePtr current, ChromosomePtr best,
		ChromosomePtr local, double* direction);

#endif
