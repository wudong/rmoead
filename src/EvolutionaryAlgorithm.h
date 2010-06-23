/*
 * EvolutionaryAlgorithm.h
 *
 *  Created on: 14 Jun 2010
 *      Author: wudong
 */

#ifndef EVOLUTIONARYALGORITHM_H_
#define EVOLUTIONARYALGORITHM_H_

#include "Chromosome.h"
#include "Function.h"
#include "RandomGenerator.h"

template<typename T>
class EvolutionaryAlgorithm {

protected:
	int runid;
	int fesCounter;
	FunctionPtr function;
	RandomGeneratorPtr randGenerator;
	std::vector<T> population;

public:
	EvolutionaryAlgorithm() :fesCounter(0){
	}

	virtual ~EvolutionaryAlgorithm() {
	}

	virtual void evaluate(ChromosomePtr chrom);

	virtual void setFunction(FunctionPtr func) {
		this->function = func;
	}

	virtual void setRandomGenerator(RandomGeneratorPtr r) {
		this->randGenerator = r;
	}

	virtual void initPop(int popsize)=0;
	virtual void evolve()=0;

	T randomInd(){
		int ran= this->randGenerator->nextRandomInt(getPopsize());
		return population[ran];
	}

	void setRunId(int id) {
		this->runid = id;
	}

	int getPopsize() {
		return population.size();
	}

	//The genetic operations.
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


};

template<typename T>
void EvolutionaryAlgorithm<T>::evaluate(ChromosomePtr chrom) {
	(*this->function)(chrom);
	this->fesCounter++;
}

/* Routine for real polynomial mutation of an T */
template<typename T>
void EvolutionaryAlgorithm<T>::
realmutation(ChromosomePtr ind, double rate) {
	double rnd, delta1, delta2, mut_pow, deltaq;
	double y, yl, yu, val, xy;
	double eta_m = etam;

	int id_rnd = randGenerator->nextRandomInt(nvar);

	for (int j = 0; j < nvar; j++) {
		if (randGenerator->nextRandomDouble() <= rate) {
			y = ind->x_var[j];
			yl = lowBound;
			yu = uppBound;
			delta1 = (y - yl) / (yu - yl);
			delta2 = (yu - y) / (yu - yl);
			rnd = randGenerator->nextRandomDouble();
			mut_pow = 1.0 / (eta_m + 1.0);
			if (rnd <= 0.5) {
				xy = 1.0 - delta1;
				val = 2.0 * rnd + (1.0 - 2.0 * rnd) * (pow(xy, (eta_m + 1.0)));
				deltaq = pow(val, mut_pow) - 1.0;
			} else {
				xy = 1.0 - delta2;
				val = 2.0 * (1.0 - rnd) + 2.0 * (rnd - 0.5) * (pow(xy, (eta_m
						+ 1.0)));
				deltaq = 1.0 - (pow(val, mut_pow));
			}
			y = y + deltaq * (yu - yl);
			if (y < yl)
				y = yl;
			if (y > yu)
				y = yu;
			ind->x_var[j] = y;
		}
	}
	return;
}

/* Routine for real variable SBX crossover */
template<typename T>
void EvolutionaryAlgorithm<T>::
real_sbx_xoverA(ChromosomePtr parent1, ChromosomePtr parent2,
		ChromosomePtr child1, ChromosomePtr child2) {
	double rand;
	double y1, y2, yl, yu;
	double c1, c2;
	double alpha, beta, betaq;
	double eta_c = etax;
	if (randGenerator->nextRandomDouble() <= 1.0) {
		for (int i = 0; i < nvar; i++) {
			if (randGenerator->nextRandomDouble() <= 0.5) {
				if (fabs(parent1->x_var[i] - parent2->x_var[i]) > EPS) {
					if (parent1->x_var[i] < parent2->x_var[i]) {
						y1 = parent1->x_var[i];
						y2 = parent2->x_var[i];
					} else {
						y1 = parent2->x_var[i];
						y2 = parent1->x_var[i];
					}
					yl = lowBound;
					yu = uppBound;
					rand = randGenerator->nextRandomDouble();
					beta = 1.0 + (2.0 * (y1 - yl) / (y2 - y1));
					alpha = 2.0 - pow(beta, -(eta_c + 1.0));
					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand * alpha), (1.0 / (eta_c + 1.0)));
					} else {
						betaq = pow((1.0 / (2.0 - rand * alpha)), (1.0 / (eta_c
								+ 1.0)));
					}
					c1 = 0.5 * ((y1 + y2) - betaq * (y2 - y1));
					beta = 1.0 + (2.0 * (yu - y2) / (y2 - y1));
					alpha = 2.0 - pow(beta, -(eta_c + 1.0));
					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand * alpha), (1.0 / (eta_c + 1.0)));
					} else {
						betaq = pow((1.0 / (2.0 - rand * alpha)), (1.0 / (eta_c
								+ 1.0)));
					}
					c2 = 0.5 * ((y1 + y2) + betaq * (y2 - y1));
					if (c1 < yl)
						c1 = yl;
					if (c2 < yl)
						c2 = yl;
					if (c1 > yu)
						c1 = yu;
					if (c2 > yu)
						c2 = yu;
					if (randGenerator->nextRandomDouble() <= 0.5) {
						child1->x_var[i] = c2;
						child2->x_var[i] = c1;
					} else {
						child1->x_var[i] = c1;
						child2->x_var[i] = c2;
					}
				} else {
					child1->x_var[i] = parent1->x_var[i];
					child2->x_var[i] = parent2->x_var[i];
				}
			} else {
				child1->x_var[i] = parent1->x_var[i];
				child2->x_var[i] = parent2->x_var[i];
			}
		}
	} else {
		for (int i = 0; i < nvar; i++) {
			child1->x_var[i] = parent1->x_var[i];
			child2->x_var[i] = parent2->x_var[i];
		}
	}
	return;
}

template<typename T>
void EvolutionaryAlgorithm<T>::
real_sbx_xoverB(ChromosomePtr parent1, ChromosomePtr parent2,
		ChromosomePtr child) {
	double rand;
	double y1, y2, yl, yu;
	double c1, c2;
	double alpha, beta, betaq;
	double eta_c = etax;
	if (randGenerator->nextRandomDouble() <= 1.0) {
		for (int i = 0; i < nvar; i++) {
			if (randGenerator->nextRandomDouble() <= 0.5) {
				if (fabs(parent1->x_var[i] - parent2->x_var[i]) > EPS) {
					if (parent1->x_var[i] < parent2->x_var[i]) {
						y1 = parent1->x_var[i];
						y2 = parent2->x_var[i];
					} else {
						y1 = parent2->x_var[i];
						y2 = parent1->x_var[i];
					}
					yl = lowBound;
					yu = uppBound;
					rand = randGenerator->nextRandomDouble();
					beta = 1.0 + (2.0 * (y1 - yl) / (y2 - y1));
					alpha = 2.0 - pow(beta, -(eta_c + 1.0));
					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand * alpha), (1.0 / (eta_c + 1.0)));
					} else {
						betaq = pow((1.0 / (2.0 - rand * alpha)), (1.0 / (eta_c
								+ 1.0)));
					}
					c1 = 0.5 * ((y1 + y2) - betaq * (y2 - y1));
					beta = 1.0 + (2.0 * (yu - y2) / (y2 - y1));
					alpha = 2.0 - pow(beta, -(eta_c + 1.0));
					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand * alpha), (1.0 / (eta_c + 1.0)));
					} else {
						betaq = pow((1.0 / (2.0 - rand * alpha)), (1.0 / (eta_c
								+ 1.0)));
					}
					c2 = 0.5 * ((y1 + y2) + betaq * (y2 - y1));
					if (c1 < yl)
						c1 = yl;
					if (c2 < yl)
						c2 = yl;
					if (c1 > yu)
						c1 = yu;
					if (c2 > yu)
						c2 = yu;
					if (randGenerator->nextRandomDouble() <= 0.5) {
						child->x_var[i] = c2;
					} else {
						child->x_var[i] = c1;
					}
				} else {
					child->x_var[i] = parent1->x_var[i];
				}
			} else {
				child->x_var[i] = parent1->x_var[i];
			}
		}
	} else {
		for (int i = 0; i < nvar; i++) {
			child->x_var[i] = parent1->x_var[i];
		}
	}
	return;
}

template<typename T>
void EvolutionaryAlgorithm<T>::
diff_evo_xover_current2best(ChromosomePtr base, ChromosomePtr best,
		ChromosomePtr ind2, ChromosomePtr ind1, ChromosomePtr child, double de_f,
		double de_cr) {
	int idx_rnd = randGenerator->nextRandomInt(nvar);

	for (int n = 0; n < nvar; n++) {
		//*
		// strategy two
		double rnd1 = randGenerator->nextRandomDouble();
		if (rnd1 < de_cr || n == idx_rnd)
			child->x_var[n] = base->x_var[n] + de_f * (best->x_var[n]
					- base->x_var[n]) + de_f * (ind2->x_var[n] - ind1->x_var[n]);
		else
			child->x_var[n] = base->x_var[n];
		//*/

		// handle the boundary voilation
		if (child->x_var[n] < lowBound) {
			double rnd = randGenerator->nextRandomDouble();
			child->x_var[n] = lowBound + rnd * (base->x_var[n] - lowBound);
		}
		if (child->x_var[n] > uppBound) {
			double rnd = randGenerator->nextRandomDouble();
			child->x_var[n] = uppBound - rnd * (uppBound - base->x_var[n]);
		}
	}
}

template<typename T>
void EvolutionaryAlgorithm<T>::
diff_evo_xover_1(ChromosomePtr base, ChromosomePtr ind1, ChromosomePtr ind2,
		ChromosomePtr child, double de_f, double de_cr) {

	int idx_rnd = randGenerator->nextRandomInt(nvar);

	for (int n = 0; n < nvar; n++) {
		//*
		// strategy two
		double rnd1 = randGenerator->nextRandomDouble();
		if (rnd1 < de_cr || n == idx_rnd)
			child->x_var[n] = base->x_var[n] + de_f * (ind2->x_var[n]
					- ind1->x_var[n]);
		else
			child->x_var[n] = base->x_var[n];
		//*/

		// handle the boundary voilation
		if (child->x_var[n] < lowBound) {
			double rnd = randGenerator->nextRandomDouble();
			child->x_var[n] = lowBound + rnd * (base->x_var[n] - lowBound);
		}
		if (child->x_var[n] > uppBound) {
			double rnd = randGenerator->nextRandomDouble();
			child->x_var[n] = uppBound - rnd * (uppBound - base->x_var[n]);
		}

	}
}

template<typename T>
void EvolutionaryAlgorithm<T>::
diff_evo_xover_2(ChromosomePtr base, ChromosomePtr ind1, ChromosomePtr ind2,
		ChromosomePtr ind3, ChromosomePtr ind4, ChromosomePtr child, double de_f,
		double de_cr) {
	int idx_rnd = randGenerator->nextRandomInt(nvar);

	for (int n = 0; n < nvar; n++) {
		//*
		// strategy two
		double rnd1 = randGenerator->nextRandomDouble();
		if (rnd1 < de_cr || n == idx_rnd)
			child->x_var[n] = base->x_var[n] + de_f * (ind2->x_var[n]
					- ind1->x_var[n]) + de_f * (ind4->x_var[n] - ind3->x_var[n]);
		else
			child->x_var[n] = base->x_var[n];
		//*/

		// handle the boundary voilation
		if (child->x_var[n] < lowBound) {
			double rnd = randGenerator->nextRandomDouble();
			child->x_var[n] = lowBound + rnd * (base->x_var[n] - lowBound);
		}
		if (child->x_var[n] > uppBound) {
			double rnd = randGenerator->nextRandomDouble();
			child->x_var[n] = uppBound - rnd * (uppBound - base->x_var[n]);
		}
	}
}

template<typename T>
void EvolutionaryAlgorithm<T>::
partical_swarm_evol(ChromosomePtr current, ChromosomePtr best, ChromosomePtr local, double* direction){
	double c=2;
	double rand= c* randGenerator->nextRandomDouble();

	for (int i=0;i<nvar;i++){
		double backup = current->x_var[i];

		direction[i]=direction[i]+rand*(best->x_var[i]-current->x_var[i])
				+rand*(local->x_var[i]-current->x_var[i]);

		current->x_var[i]=current->x_var[i]+direction[i];

		if (current->x_var[i] < lowBound) {
			double rnd = randGenerator->nextRandomDouble();
			current->x_var[i] = lowBound + rnd * (backup - lowBound);
		}
		if (current->x_var[i] > uppBound) {
			double rnd = randGenerator->nextRandomDouble();
			current->x_var[i] = uppBound - rnd * (uppBound - backup);
		}
	}
}


#endif /* EVOLUTIONARYALGORITHM_H_ */
