/*
 * Subproblem.h
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#ifndef SUBPROBLEM_H_
#define SUBPROBLEM_H_

#include <boost/smart_ptr.hpp>
#include "Chromosome.h"

class Subproblem;
typedef boost::shared_ptr<Subproblem> SubproblemPtr;
typedef vector<SubproblemPtr>::iterator SubproblemItr;

class Subproblem {
public:
	Subproblem(ChromosomePtr init);
	virtual ~Subproblem(){};

	ChromosomePtr indiv; // current solution
	ChromosomePtr saved; // last solution
	ChromosomePtr lbest; //local best solution

	std::vector<double> namda; // weight vector
	std::vector<double> refpoint;// reference point

	vector<SubproblemPtr> neighbour; // neighbourhood table
	vector<SubproblemPtr> adjacent; // neighbourhood table
	double utility;

	bool searchSelected; // whether the subproblem is selected for search in the iteration.
	int selection_times; // how many times the subproblem has been selected.
	bool isEdge; //whether the subproblem is an edge problem
	int update_temp; //how many updated are attempted since last update.

	double de_f;
	double de_cr;

	void getMaxAdjacentDistance(SubproblemPtr& maxProb, double& max);
	void getMinAdjacentDistance(SubproblemPtr& minProb, double& min);
	void getAvgAdjacentDistance(double& avg);

	void show_weight();

	void operator=(const Subproblem &ind2);

	double scalarObjective();
	void postItr(int gen);
	bool update(ChromosomePtr indiv, bool updatebest);
	bool dominate(Subproblem& sub);

	bool isLater(Subproblem& sub);

	static void nondom_select(vector<SubproblemPtr>& selected, vector<
			SubproblemPtr>& dominated, vector<SubproblemPtr>& pops);

	void searchOnItOwn(int fes); //search the subproblem on its own with the given number of function evaluations.

private:
	void compute_util();
};

#endif /* SUBPROBLEM_H_ */
