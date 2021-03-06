/*
 * RMOEAD.h
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#ifndef RMOEAD_H_
#define RMOEAD_H_

#include "global.h"
#include "EvolutionaryAlgorithm.h"
#include "common.h"
#include "Chromosome.h"
#include "Subproblem.h"
#include "Function.h"
#include <stdlib.h>

class RMOEAD: public EvolutionaryAlgorithm<SubproblemPtr> {

public:
	RMOEAD(){};
	virtual ~RMOEAD(){};

	void evolve();

	void save_front(std::string & savefilename);
	void save_pos(std::string & savefilename);
	void initPop(int popsize);

private:
	void order_selection(vector<SubproblemPtr> & selected);
	void sort_selection(vector<SubproblemPtr> & selected);
	void tour_selection(vector<SubproblemPtr> & selected);

	void evol_population();

	void build_neighbourhood(vector<SubproblemPtr> & pop);
	void build_adjacent(vector<SubproblemPtr> & pop);

	void weight_adjust_remove(vector<SubproblemPtr> & pop);
	void weight_adjust_add(vector<SubproblemPtr> & pop);
	void mate_selection(vector<SubproblemPtr> & list, SubproblemPtr cid,
			unsigned int size, bool type);
	void evolve_de(SubproblemPtr c_sub);
	void update_problem_de(ChromosomePtr ind, SubproblemPtr id, bool type);
	void save_selection(std::string & filename);
	void find_best(SubproblemPtr cid, SubproblemPtr& best, bool type);

	void save_state(int run, int& save_front_counter,
			int& save_selection_counter);
	void printRunningState();
	void weight_adjust(int& counter);

	bool firstime_adjust;
};
#endif /* RMOEAD_H_ */
