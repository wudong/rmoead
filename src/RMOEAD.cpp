/*
 * RMOEAD.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#include "RMOEAD.h"


void RMOEAD::initPop(int popsize) {
	firstime_adjust = true;
	char filename[1024];
	// Read weight vectors from a data file
	int pops = getPopulationSize();
	sprintf(filename, "%s/ParameterSetting/Weight/W%dD_%d.dat",
			input_dir.c_str(), nobj, pops);
	std::cout << "loading weight from file: ";
	std::cout << filename << std::endl;

	std::ifstream readf(filename);

	//int pops = population.size();

	for (int i = 0; i < pops; i++) {
		ChromosomePtr ch(new Chromosome());
		ch->rnd_init(randGenerator);
		evaluate(ch);

		SubproblemPtr sub(new Subproblem(ch));

		// Load weight vectors
		for (unsigned int j = 0; j < nobj; j++) {
			readf >> sub->namda[j];
			if (sub->namda[j] == 0)
				sub->isEdge = true;
		}

		population.push_back(sub);
	}
	readf.close();

	build_neighbourhood(this->population);
	build_adjacent(this->population);
}

void RMOEAD::build_neighbourhood(vector<SubproblemPtr>& pop) {
	int popsize = pop.size();
	double* dist = new double[popsize];
	int* indx = new int[popsize];

	for (int i = 0; i < popsize; i++) {
		// calculate the distances based on weight vectors
		SubproblemPtr si = pop[i];
		si->neighbour.clear();

		for (int j = 0; j < popsize; j++) {
			SubproblemPtr sj = pop[j];
			dist[j] = dist_vector(si->namda, sj->namda, nobj);
			//indx[j] = j;
		}

		// find 'niche' nearest neighboring subproblems
		minsort(dist, indx, popsize);

		// save the indexes of the nearest 'niche' neighboring weight vectors
		int niche = getNeighbourSize();
		for (int k = 0; k < niche; k++) {
			pop[i]->neighbour.push_back(pop[indx[k]]);
		}
	}
	delete[] dist;
	delete[] indx;
}

void RMOEAD::build_adjacent(vector<SubproblemPtr>& pop) {
	int popsize = pop.size();
	for (int current = 0; current < popsize; current++) {
		pop[current]->adjacent.clear();

		if (nobj == 2) {
			int upindex = -1, downindex = -1;
			for (int compare = 0; compare < popsize; compare++) {
				if (current == compare)
					continue;

				if (upindex == -1 && (pop[current]->namda[0]
						< pop[compare]->namda[0]))
					upindex = compare;
				else if (downindex == -1 && (pop[current]->namda[0]
						> pop[compare]->namda[0]))
					downindex = compare;
				else if (upindex != -1 && pop[current]->namda[0]
						< pop[compare]->namda[0] && pop[upindex]->namda[0]
						> pop[compare]->namda[0])
					upindex = compare;
				else if (downindex != -1 && pop[current]->namda[0]
						> pop[compare]->namda[0] && pop[downindex]->namda[0]
						< pop[compare]->namda[0])
					downindex = compare;
			}

			if (upindex != -1)
				pop[current]->adjacent.push_back(pop[upindex]);
			if (downindex != -1)
				pop[current]->adjacent.push_back(pop[downindex]);
		} else {
			//TODO
		}
	}
}

void RMOEAD::weight_adjust(int & counter) {
	int total_evaluations = cfg_getint(configurator, "total_evaluations");

	double averateUtil = 0;
	for (SubproblemItr itr = population.begin(); itr != population.end(); itr++) {
		averateUtil += (*itr)->utility;
	}
	averateUtil /= population.size();

	if (nfes >= 100000 && nfes - counter > 50000 && total_evaluations - nfes
			> 50000) {
		counter = nfes;
		if (!firstime_adjust) {
			weight_adjust_remove(population);
		}
		weight_adjust_add(population);
		firstime_adjust = false;
	}
}

void RMOEAD::weight_adjust_remove(vector<SubproblemPtr> & subproblems) {
	int popsize = subproblems.size(); // the size of non-domination.

	// also using the adjacentSubs to find the average distance.
	double* adjacentDistance = new double[popsize];
	int* sortIdx = new int[popsize];

	double averageAdjacentDistance = 0;
	for (int i = 0; i < popsize; i++) {
		SubproblemPtr subproblem = subproblems[i];
		SubproblemPtr subproblem2;
		subproblem->getMinAdjacentDistance(subproblem2, adjacentDistance[i]);
		double v;
		subproblem->getAvgAdjacentDistance(v);
		averageAdjacentDistance += v;
	}
	averageAdjacentDistance /= popsize;
	std::cout << "Average distance: " << averageAdjacentDistance << std::endl;

	minsort(adjacentDistance, sortIdx, popsize);

	vector<SubproblemPtr> remove;
	vector<SubproblemPtr> remain;

	unsigned int adjustsize = getWeightAdjustSize();
	for (int i = 0; i < popsize; i++) {
		if (remove.size() >= adjustsize)
			break;

		SubproblemPtr subproblem = subproblems[sortIdx[i]];
		SubproblemPtr another;
		double smallest;

		subproblem->getMinAdjacentDistance(another, smallest);

		//		int columnwidth = 15;
		//		std::cout << "Check:" << setw(columnwidth) << subproblem->utility
		//				<< setw(columnwidth) << another->utility << setw(columnwidth)
		//				<< smallest;

		if (smallest > 0.3 * averageAdjacentDistance)
			break;

		// if it is the edge subproblem, remain it.
		if (subproblem->isEdge || subproblem->utility < 0.99) {
			remain.push_back(subproblem);
			continue;
		}

		SubproblemItr findInRemain = std::find(remain.begin(), remain.end(),
				subproblem);
		SubproblemItr findInRemove = std::find(remove.begin(), remove.end(),
				subproblem);

		if (findInRemain != remain.end() || findInRemove != remove.end())
			continue;

		bool hasAdjacentRemoved = false;

		for (SubproblemItr subadj = subproblem->adjacent.begin(); subadj
				!= subproblem->adjacent.end(); subadj++) {
			SubproblemItr findInRemove2 = std::find(remove.begin(),
					remove.end(), *subadj);
			if (findInRemove2 != remove.end()) {
				hasAdjacentRemoved = true;
				break;
			}
		}

		// it has an adjacent subproblem already in the remove
		// then don't remove it.remain it.
		if (!hasAdjacentRemoved) {
			remove.push_back(subproblem);
			std::cout << "removed: " << subproblem->namda[0] << std::endl;
		} else if (hasAdjacentRemoved) {
			remain.push_back(subproblem);
			std::cout << "passed" << std::endl;
		}
	}

	for (unsigned int i = 0; i < remove.size(); i++) {
		SubproblemItr itr = std::find(subproblems.begin(), subproblems.end(),
				remove[i]);
		if (itr != subproblems.end()) {
			SubproblemPtr ptr = (*itr);
			subproblems.erase(itr);
		}
	}

	delete[] adjacentDistance;
	delete[] sortIdx;

	build_neighbourhood(subproblems);
	build_adjacent(subproblems);
	std::cout << "weight adjust remove: " << remove.size() << std::endl;
}

void RMOEAD::weight_adjust_add(vector<SubproblemPtr> & subproblems) {
	int popsize = subproblems.size();
	// also using the adjacentSubs to find the average distance.
	double* adjacentDistance = new double[popsize];
	int* sorting = new int[popsize];

	double averageAdjacentDistance = 0;
	for (int i = 0; i < popsize; i++) {
		SubproblemPtr subproblem = subproblems[i];
		SubproblemPtr subproblem2;
		subproblem->getMaxAdjacentDistance(subproblem2, adjacentDistance[i]);
		adjacentDistance[i] *= -1;
		double v;
		subproblem->getAvgAdjacentDistance(v);
		averageAdjacentDistance += v;
	}

	averageAdjacentDistance /= popsize;
	std::cout << "Average distance: " << averageAdjacentDistance << std::endl;

	vector<SubproblemPtr> toadd;
	minsort(adjacentDistance, sorting, popsize);

	unsigned int adjustsize = getWeightAdjustSize();
	for (int i = 0; i < popsize; i++) { // not adjust on the first and
		if (toadd.size() >= adjustsize)
			break;

		SubproblemPtr subproblem = subproblems[sorting[i]];
		SubproblemPtr another;
		double largest;

		int columnwidth = 15;
		subproblem->getMaxAdjacentDistance(another, largest);

		if (largest < 3 * averageAdjacentDistance)
			break;

		std::cout << "Check:" << setw(columnwidth) << subproblem->utility
				<< setw(columnwidth) << another->utility << setw(columnwidth)
				<< largest << std::endl;

		//		if (subproblem->utility == 1 || another->utility == 1) {
		//			std::cout << " :pass." << std::endl;
		//			continue;
		//		}

		double lowerWeight = fmin(subproblem->namda[0], another->namda[0]);
		double higherWeight = fmax(subproblem->namda[0], another->namda[0]);
		double weightspan = higherWeight - lowerWeight;

		assert(weightspan > 0);
		int insertnumber = (int) floor(largest / (3 * averageAdjacentDistance));

		//if (insertnumber > 0) {
		if (nobj == 2) {
			insertnumber = fmin(10, insertnumber); //cap it.
			for (int idx = 1; idx < insertnumber; idx++) {
				ChromosomePtr ptr(new Chromosome());
				ptr->rnd_init(randGenerator);
				evaluate(ptr);
				SubproblemPtr sub(new Subproblem(ptr));

				sub->namda[0] = lowerWeight + (idx) * weightspan / insertnumber;
				sub->namda[1] = 1 - sub->namda[0];
				toadd.push_back(sub);
				std::cout << " inserted: " << setw(columnwidth) << lowerWeight
						<< " [" << sub->namda[0] << "] " << higherWeight
						<< std::endl;
			}
		} else if (nobj == 3)
			;
		//		} else
		//			break;
	}

	for (SubproblemItr itr = toadd.begin(); itr != toadd.end(); itr++) {
		subproblems.push_back(*itr);
	}

	build_neighbourhood(subproblems);
	build_adjacent(subproblems);
	std::cout << "weight adjust add: " << toadd.size() << std::endl;
}

void RMOEAD::tour_selection(vector<SubproblemPtr> &selected) {
	// selection based on utility
	vector<int> candidate;
	//	for (int k = 0; k < nobj; k++)
	//		selected.push_back(population[k]); // select first m weights
	int pops = this->population.size();
	for (int n = nobj; n < pops; n++)
		candidate.push_back(n); // set of unselected weights

	int depth = getTournamentSize();

	while (selected.size() < getSelectionSize()) {
		int best_idd = randGenerator->nextRandomInt(candidate.size()), i2;
		int best_sub = candidate[best_idd], s2;
		for (int i = 1; i < depth; i++) {
			i2 = randGenerator->nextRandomInt(candidate.size());
			s2 = candidate[i2];
			if (population[s2]->utility > population[best_sub]->utility) //using the cec selection utility.
			{
				best_idd = i2;
				best_sub = s2;
			}
		}
		selected.push_back(population[best_sub]);
		candidate.erase(candidate.begin() + best_idd);
	}
}

void RMOEAD::order_selection(vector<SubproblemPtr> &selected) {
	unsigned int required_size = getSelectionSize();

	unsigned int us = population.size();
	double* utility_da = new double[us];
	for (unsigned int i = 0; i < us; i++) {
		//over the neighbours.
		utility_da[i] = 0;
		for (unsigned int j = 0; j < population[i]->neighbour.size() / 4; j++)
			utility_da[i] += -1 * population[i]->neighbour[j]->utility;
	}

	int* idx = new int[us];
	minsort(utility_da, idx, us);

	for (unsigned int i = 0; i < required_size; i++) {
		selected.push_back(population[idx[i]]);
	}

	delete[] idx;
	delete[] utility_da;
}

void RMOEAD::sort_selection(vector<SubproblemPtr> &selected) {
	// selection based on utility
	unsigned int required_size = getSelectionSize();

	unsigned int us = population.size();
	double* utility_da = new double[us];
	for (unsigned int i = 0; i < us; i++) {
		//over the neighbours.
		utility_da[i] = 0;
		for (unsigned int j = 0; j < population[i]->neighbour.size() / 4; j++)
			utility_da[i] += -1 * population[i]->neighbour[j]->utility;
		//					utility_da[i] = -1 * utility[i];
	}

	int* idx = new int[us];
	minsort(utility_da, idx, us);

	double rate = getSortProb();
	while (selected.size() < required_size) {
		for (unsigned int i = 0; i < us; i++) {
			if (idx[i] >= 0) {
				double p = pow(rate, i);
				double rn = randGenerator->nextRandomDouble();
				if (rn < p) {
					selected.push_back(population[idx[i]]);
					idx[i] = -idx[i];
					if (selected.size() == required_size)
						goto out;
				}
			}
		}
	}

	out: assert(selected.size()==required_size);
	delete[] utility_da;
	delete[] idx;
}

void RMOEAD::update_problem_de(ChromosomePtr indiv, SubproblemPtr id, bool type) {
	// indiv: child solution
	// id:   the id of current subproblem
	// type: update solutions in - neighborhood (1) or whole population (otherwise)
	int size, time = 0;

	if (type)
		size = id->neighbour.size(); // from neighborhood
	else
		size = population.size(); // from whole population

	int * perm = new int[size];
	for (int k = 0; k < size; k++)
		perm[k] = k;

	randGenerator->randomShuffle(perm, size);

	int limit = getUpdateLimit();

	// update the whole population more.
	if (!type)
		limit = 2 * limit;

	bool upcurrent = true;
	for (int i = 0; i < size; i++) {
		// Pick a subproblem to update
		SubproblemPtr k;
		if (type)
			k = id->neighbour[perm[i]];
		else
			k = population[perm[i]];

		// calculate the values of objective function regarding the current subproblem
		bool up = k->update(indiv, upcurrent);
		if (up) {
			time++;
			if (time >= limit) {
				upcurrent = false;
			}
		}
	}
	delete[] perm;
}

//type 1 - neighborhood; otherwise - whole population
void RMOEAD::find_best(SubproblemPtr cid, SubproblemPtr& best, bool type) {
	best = cid;
	double fbest = cid->scalarObjective(), ftest;

	if (type) {//neighbour.
		for (unsigned int i = 0; i < cid->neighbour.size(); i++) {
			SubproblemPtr test = cid->neighbour[i];
			ftest = fitnessfunction(test->indiv->y_obj, cid->namda);
			if (ftest < fbest) {
				best = test;
				fbest = ftest;
			}
		}
	} else {//whole population.
		for (unsigned int i = 0; i < population.size(); i++) {
			SubproblemPtr test = population[i];
			ftest = fitnessfunction(test->indiv->y_obj, cid->namda);
			if (ftest < fbest) {
				best = test;
				fbest = ftest;
			}
		}
	}
}

// list : the set of the indexes of selected mating parents
// cid  : the id of current subproblem
// size : the number of selected mating parents
// type : true - neighborhood; false - whole population
void RMOEAD::mate_selection(vector<SubproblemPtr> &list, SubproblemPtr cid,
		unsigned int size, bool type) {
	unsigned int ss = cid->neighbour.size(), id;
	SubproblemPtr parent;
	while (list.size() < size) {
		if (type) {
			id = randGenerator->nextRandomInt(ss);
			parent = cid->neighbour[id];
		} else
			parent = population[randGenerator->nextRandomInt(population.size())];

		// avoid the repeated selection
		bool flag = true;
		for (unsigned int i = 0; i < list.size(); i++) {
			if (list[i] == parent) // parent is in the list
			{
				flag = false;
				break;
			}
		}

		if (flag)
			list.push_back(parent);
	}
}

void RMOEAD::evolve_de(SubproblemPtr c_sub) {

	double rnd = randGenerator->nextRandomDouble();
	double prob = getUpdateNeighbourProb();
	bool type_neighbour = (rnd < prob);

	ChromosomePtr child(new Chromosome()), child2(new Chromosome());
	double de_f = 0.5;
	double de_cr = 1;
	vector<SubproblemPtr> plist;

	SubproblemPtr bestIndLocal;

	find_best(c_sub, bestIndLocal, true);

	mate_selection(plist, c_sub, 2, true);

	diff_evo_xover_current2best((c_sub->indiv), (bestIndLocal->indiv),
			(plist[0]->indiv), (plist[1]->indiv), child, de_f, de_cr);

	plist.clear();

	mate_selection(plist, c_sub, 2, type_neighbour);
	diff_evo_xover_1((c_sub->indiv), (plist[0]->indiv), (plist[1]->indiv),
			child2, de_f, de_cr);

	double w = getDEWeight();
	if (w < 1) {
		w = randGenerator->nextRandomDouble(w, 1);
	}

	for (unsigned int idx = 0; idx < nvar; idx++) {
		child->x_var[idx] = (1 - w) * child->x_var[idx] + w
				* child2->x_var[idx];
	}

	float f = getMutationRate();
	realmutation(child, f / nvar);

	//child->obj_eval();
	evaluate(child);

	//population[c_sub]->update_pop(child, type_neighbour, population);
	update_problem_de(child, c_sub, type_neighbour);
}

void RMOEAD::evol_population() {

	vector<SubproblemPtr> selection;

	bool reactive = ifUseReactive();

	if (reactive) {
		double rnd = randGenerator->nextRandomDouble();
		double prob = getReactiveProb();

		if (rnd < prob) {
			char* s = getSelectionMethod();
			if (strcmp("sort", s) == 0) {
				this->sort_selection(selection);
			} else if (strcmp("order", s) == 0) {
				this->order_selection(selection);
			} else if (strcmp("tour", s) == 0) {
				this->tour_selection(selection);
			} else
				assert(false);
		} else {
			selection = population;
		}
	} else {
		selection = population;
	}

	unsigned int selectionsize = selection.size();
	int * perm = new int[selectionsize];
	for (unsigned int k = 0; k < selectionsize; k++)
		perm[k] = k;

	randGenerator->randomShuffle(perm, selectionsize);

	for (unsigned int sub = 0; sub < selectionsize; sub++) {
		SubproblemPtr c_sub = selection[perm[sub]];
		c_sub->searchSelected = true;
		c_sub->selection_times++;

		evolve_de(c_sub);
	}

	delete[] perm;
}

void RMOEAD::evolve() {
	nfes = 0;
	int gen = 1;
	initPop(0);

	int total_evaluations = cfg_getint(configurator, "total_evaluations");

	int save_front_counter = 1;
	int save_selection_counter = 1;
	int weight_adjust_counter = 1;

	//the main evolutionary process.
	while (nfes < total_evaluations) {
		evol_population();
		gen++;
		for (unsigned int idx = 0; idx < population.size(); idx++)
			population[idx]->postItr(gen);
		save_state(runid, save_front_counter, save_selection_counter);

		//weight adjust.
		if (ifUseReactive() && ifUseWeightAdjust()) {//doing the weight adjust.
			weight_adjust(weight_adjust_counter);
		}
	}

	// save the final population - X space
	{
		std::string funcname = this->function->getName();
		char file[100];
		sprintf(file, "%s/POF_MOEAD_%s_RUN%d.txt", output_dir.c_str(),
				funcname.c_str(), runid);
		std::string filename(file);
		save_front(filename);

		//save the weight distribution
		sprintf(file, "%s/MOEAD_%s_RUN%d-Selection.txt", output_dir.c_str(),
				funcname.c_str(), runid);
		std::string filename2(file);
		save_selection(filename2);

		printRunningState();
	}

	printf("\n");

	//	population.clear();
	//	idealpoint.clear();
}

void RMOEAD::save_state(int run, int& save_front_counter,
		int& save_selection_counter) {

	if (nfes > save_front_counter * 5000) {
		std::string funcname = this->function->getName();
		char file[100];
		sprintf(file, "%s/POF_MOEAD_%s_EVA_%d-%d.txt", output_dir.c_str(),
				funcname.c_str(), run, save_front_counter);
		std::string filename(file);
		save_front(filename);
		save_front_counter++;
		printRunningState();
	}

	if (nfes > save_selection_counter * 30000) {
		std::string funcname = this->function->getName();
		char file[100];
		sprintf(file, "%s/POF_MOEAD_%s_SELEC_%d-%d.txt", output_dir.c_str(),
				funcname.c_str(), run, save_selection_counter);
		std::string filename(file);
		save_selection(filename);
		save_selection_counter++;
	}
}

void RMOEAD::save_front(std::string& saveFilename) {
	std::fstream fout;
	fout.open(saveFilename.c_str(), std::ios::out);
	char* me = getEvolveMethod();
	int pops = this->population.size();
	for (int n = 0; n < pops; n++) {
		for (unsigned int k = 0; k < nobj; k++) {
			if (strcmp("de", me) == 0) {
				fout << population[n]->indiv->y_obj[k] << "  ";
			} else
				assert(false);
		}
		fout << "\n";
	}
	fout.close();
}

void RMOEAD::save_selection(std::string & filename) {
	std::fstream fout;
	fout.open(filename.c_str(), std::ios::out);
	int pops = this->population.size();
	for (int n = 0; n < pops; n++) {
		for (unsigned int k = 0; k < nobj; k++) {
			fout << population[n]->namda[k] << "  ";
		}
		fout << population[n]-> selection_times;
		fout << "\n";
	}
	fout.close();
}

void RMOEAD::save_pos(std::string& saveFilename) {
	std::fstream fout;
	fout.open(saveFilename.c_str(), std::ios::out);
	int pops = this->population.size();
	for (int n = 0; n < pops; n++) {
		for (unsigned int k = 0; k < nvar; k++)
			fout << population[n]->indiv->x_var[k] << "  ";
		fout << "\n";
	}
	fout.close();
}

void RMOEAD::printRunningState() {
	double averateUtil = 0;
	double averateDistance = 0;
	int populationsize = population.size();

	for (SubproblemItr itr = population.begin(); itr != population.end(); itr++) {
		averateUtil += (*itr)->utility;
		double v;
		(*itr)->getAvgAdjacentDistance(v);
		averateDistance += v;
	}
	averateUtil /= populationsize;
	averateDistance /= populationsize;

	int columnwidth = 15;
	int precision = 5;
	setfill(' ');
	std::cout << setw(columnwidth) << nfes;
	std::cout << setw(columnwidth) << setprecision(precision) << populationsize;
	std::cout << setw(columnwidth) << setprecision(precision) << averateUtil;
	std::cout << setw(columnwidth) << setprecision(precision)
			<< averateDistance << std::endl;
}

