/*
 * Subproblem.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#include "Subproblem.h"

Subproblem::Subproblem() {
	//queue_size = 0;
	this->selection_times = 0;
	this->isEdge = false;
	this->searchSelected = false;
	this->utility = 1;
	this->de_f = 0.5;
	this->de_cr = 1;
	this->update_temp = 0;

	namda = new double[nobj];
    refpoint = new double[nobj];

    this->indiv = new Chromosome();

	this->indiv->rnd_init();
	this->indiv->obj_eval();
	this->saved = this->indiv;
}

Subproblem::~Subproblem() {
	delete[] namda;
	delete[] refpoint;
}

void Subproblem::show_weight() {
	for (unsigned int n = 0; n < nobj; n++) {
		std::cout << namda[n] << " ";
	}
	std::cout << std::endl;
}

double Subproblem::scalarObjective() {
	return fitnessfunction(this->indiv.y_obj, this->namda);
}

void Subproblem::operator=(const Subproblem &sub2) {
	this->indiv = sub2.indiv; // best solution
	this->saved = sub2.saved; // last solution
	for (unsigned int i = 0; i < nobj; i++)
		this->namda[i] = sub2.namda[i];
	this->neighbour = sub2.neighbour; // neighbourhood table
	this->searchSelected = sub2.searchSelected;
}

bool Subproblem::update(Chromosome &newind, bool updatecurrent) {
	update_temp++;

	double f1, f2, f0;
	f0 = fitnessfunction(this->lbest.y_obj, this->namda);
	f1 = fitnessfunction(this->indiv.y_obj, this->namda);
	f2 = fitnessfunction(newind.y_obj, this->namda);

	//update the best always.
	if (f2 < f0)
		this->lbest = newind;

	bool result;
	if (updatecurrent) {
		bool updated = f2 < f1;
		if (updated) {
			this->indiv = newind;
		}
		result = updated;
	} else
		result = false;

	//change from update in the post_itr.
	//should provide more accurate estimation.
	//typical value used is 500.
	int gen = getUtilityComputationGen();
	if (update_temp % gen == 0) {
		compute_util();
	}

	return result;
}

void Subproblem::compute_util() {
	double f0, f1, f2, uti, delta;

	f0 = fitnessfunction(this->lbest.y_obj, this->namda);
	f1 = fitnessfunction(this->indiv.y_obj, this->namda);
	f2 = fitnessfunction(this->saved.y_obj, this->namda);

	//	delta = f2 - f1;
	//  TODO test
	delta = f2 - f0;
	delta = delta / f2;//percentage.

	float deltalimit = getDecayDelta();

	if (delta > deltalimit)
		this->utility = 1.0;
	else if (delta >= 0) {
		double drate = getDecayRate();
		uti = (drate + 10 * delta) * this->utility;
		this->utility = uti < 1.0 ? uti : 1.0;
	} else { //delta < 0; can happen sometime.
		//don't change the utility.
		this->indiv = this->saved;
	}

	this->saved = this->indiv;
}

void Subproblem::postItr(int gen) {
	//	int geninterval = getUtilityComputationGen();
	//	if (gen % geninterval == 0) {
	//		this->compute_util();
	//	}
	//what else can we do?
}

void Subproblem::getAvgAdjacentDistance(double& avgdist) {
	SubproblemItr itr;
	double totalDistance = 0;
	for (itr = this->adjacent.begin(); itr != this->adjacent.end(); ++itr) {
		double d = dist_vector((*itr)->indiv.y_obj, this->indiv.y_obj, nobj);
		totalDistance += d;
	}
	avgdist = totalDistance / adjacent.size();
}

void Subproblem::getMinAdjacentDistance(SubproblemPtr& minProb, double& min) {
	SubproblemItr itr;
	min = 10e10;
	for (itr = this->adjacent.begin(); itr != this->adjacent.end(); ++itr) {
		if ((*itr)->isLater(*this)) {
			double d =
					dist_vector((*itr)->indiv.y_obj, this->indiv.y_obj, nobj);
			if (d < min) {
				min = d;
				minProb = (*itr);
			}
		}
	}
}

void Subproblem::getMaxAdjacentDistance(SubproblemPtr& maxProb, double& max) {
	SubproblemItr itr;
	max = -10e10;
	for (itr = this->adjacent.begin(); itr != this->adjacent.end(); ++itr) {
		if ((*itr)->isLater(*this)) {
			double d =
					dist_vector((*itr)->indiv.y_obj, this->indiv.y_obj, nobj);
			if (d > max) {
				max = d;
				maxProb = (*itr);
			}
		}
	}
}

bool Subproblem::dominate(Subproblem& sub) {
	return dominate_vector(this->indiv.y_obj, sub.indiv.y_obj, nobj);
}

bool Subproblem::isLater(Subproblem& sub) {
	return (this->namda[0] > sub.namda[0]);
}

//NEED TESTING.
void Subproblem::nondom_select(vector<SubproblemPtr>& nondominate, vector<
		SubproblemPtr>& dom, vector<SubproblemPtr>& collection) {
	if (collection.size() == 0)
		return;

	SubproblemItr popsItr = collection.begin();
	nondominate.push_back(*popsItr);

	popsItr++;

	while (popsItr != collection.end()) {
		SubproblemPtr chromosome2 = *popsItr;
		popsItr++;
		vector<SubproblemPtr> remove;

		bool dominated = false;
		for (SubproblemItr itr = nondominate.begin(); itr != nondominate.end(); itr++) {
			SubproblemPtr chromosome1 = *itr;
			if (chromosome2->dominate((*chromosome1))) {
				remove.push_back(chromosome1);
			} else if (chromosome1->dominate((*chromosome2))) {
				dominated = true;
				break;
			}
		}

		if (!dominated) {//non-dominated with the current set.
			//remove from the result.
			for (SubproblemItr itr = remove.begin(); itr != remove.end(); itr++) {
				SubproblemItr itrNond = std::find(nondominate.begin(),
						nondominate.end(), *itr);
				if (itrNond != nondominate.end()) {
					dom.push_back(*itrNond);
					nondominate.erase(itrNond);
				}
			}
			nondominate.push_back(chromosome2);
		} else {
			dom.push_back(chromosome2);
		}
	}

	assert(collection.size()==nondominate.size()+dom.size());
}

//just search on its own, using a DE method. or any other method.
void Subproblem::searchOnItOwn(int fes){

}

