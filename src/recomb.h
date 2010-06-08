#ifndef _RECOMBINATION_H_
#define _RECOMBINATION_H_

#include "global.h"
#include "Chromosome.h"

/* Routine for real polynomial mutation of an T */
void realmutation(Chromosome &ind, double rate);

/* Routine for real variable SBX crossover */
void real_sbx_xoverA(Chromosome &parent1, Chromosome &parent2, Chromosome &child1, Chromosome &child2);

void real_sbx_xoverB (Chromosome &parent1, Chromosome &parent2, Chromosome &child);


/**
 * The first one is used as base. can be either random or best.
 * the second and third is the mutation varaibles.
 *
 * the result is stored in child without modify others.
 */
void diff_evo_xover_1(Chromosome &base, Chromosome &ind1, Chromosome &ind2, Chromosome &child, double de_f, double de_cr);

void diff_evo_xover_current2best(Chromosome &base, Chromosome &best,  Chromosome &ind1, Chromosome &ind2, Chromosome &child, double de_f, double de_cr);

void diff_evo_xover_2(Chromosome &base, Chromosome &ind1, Chromosome &ind2,
		Chromosome &ind3, Chromosome &ind4, Chromosome &child, double de_f, double de_cr);

void partical_swarm_evol(Chromosome &current, Chromosome &best, Chromosome& local, double* direction);

#endif
