/*
 * recomb.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */
#include "recomb.h"

/* Routine for real polynomial mutation of an T */
void realmutation(Chromosome &ind, double rate) {
	double rnd, delta1, delta2, mut_pow, deltaq;
	double y, yl, yu, val, xy;
	double eta_m = etam;

	int id_rnd = nextRandomInt(nvar);

	for (int j = 0; j < nvar; j++) {
		if (nextRandomDouble() <= rate) {
			y = ind.x_var[j];
			yl = lowBound;
			yu = uppBound;
			delta1 = (y - yl) / (yu - yl);
			delta2 = (yu - y) / (yu - yl);
			rnd = nextRandomDouble();
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
			ind.x_var[j] = y;
		}
	}
	return;
}

/* Routine for real variable SBX crossover */
template<class T>
void real_sbx_xoverA(Chromosome &parent1, Chromosome &parent2,
		Chromosome &child1, Chromosome &child2) {
	double rand;
	double y1, y2, yl, yu;
	double c1, c2;
	double alpha, beta, betaq;
	double eta_c = etax;
	if (nextRandomDouble() <= 1.0) {
		for (int i = 0; i < nvar; i++) {
			if (nextRandomDouble() <= 0.5) {
				if (fabs(parent1.x_var[i] - parent2.x_var[i]) > EPS) {
					if (parent1.x_var[i] < parent2.x_var[i]) {
						y1 = parent1.x_var[i];
						y2 = parent2.x_var[i];
					} else {
						y1 = parent2.x_var[i];
						y2 = parent1.x_var[i];
					}
					yl = lowBound;
					yu = uppBound;
					rand = nextRandomDouble();
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
					if (nextRandomDouble() <= 0.5) {
						child1.x_var[i] = c2;
						child2.x_var[i] = c1;
					} else {
						child1.x_var[i] = c1;
						child2.x_var[i] = c2;
					}
				} else {
					child1.x_var[i] = parent1.x_var[i];
					child2.x_var[i] = parent2.x_var[i];
				}
			} else {
				child1.x_var[i] = parent1.x_var[i];
				child2.x_var[i] = parent2.x_var[i];
			}
		}
	} else {
		for (int i = 0; i < nvar; i++) {
			child1.x_var[i] = parent1.x_var[i];
			child2.x_var[i] = parent2.x_var[i];
		}
	}
	return;
}

void real_sbx_xoverB(Chromosome &parent1, Chromosome &parent2,
		Chromosome &child) {
	double rand;
	double y1, y2, yl, yu;
	double c1, c2;
	double alpha, beta, betaq;
	double eta_c = etax;
	if (nextRandomDouble() <= 1.0) {
		for (int i = 0; i < nvar; i++) {
			if (nextRandomDouble() <= 0.5) {
				if (fabs(parent1.x_var[i] - parent2.x_var[i]) > EPS) {
					if (parent1.x_var[i] < parent2.x_var[i]) {
						y1 = parent1.x_var[i];
						y2 = parent2.x_var[i];
					} else {
						y1 = parent2.x_var[i];
						y2 = parent1.x_var[i];
					}
					yl = lowBound;
					yu = uppBound;
					rand = nextRandomDouble();
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
					if (nextRandomDouble() <= 0.5) {
						child.x_var[i] = c2;
					} else {
						child.x_var[i] = c1;
					}
				} else {
					child.x_var[i] = parent1.x_var[i];
				}
			} else {
				child.x_var[i] = parent1.x_var[i];
			}
		}
	} else {
		for (int i = 0; i < nvar; i++) {
			child.x_var[i] = parent1.x_var[i];
		}
	}
	return;
}

void diff_evo_xover_current2best(Chromosome &base, Chromosome &best,
		Chromosome &ind2, Chromosome &ind1, Chromosome &child, double de_f,
		double de_cr) {
	int idx_rnd = nextRandomInt(nvar);

	for (int n = 0; n < nvar; n++) {
		//*
		// strategy two
		double rnd1 = nextRandomDouble();
		if (rnd1 < de_cr || n == idx_rnd)
			child.x_var[n] = base.x_var[n] + de_f * (best.x_var[n]
					- base.x_var[n]) + de_f * (ind2.x_var[n] - ind1.x_var[n]);
		else
			child.x_var[n] = base.x_var[n];
		//*/

		// handle the boundary voilation
		if (child.x_var[n] < lowBound) {
			double rnd = nextRandomDouble();
			child.x_var[n] = lowBound + rnd * (base.x_var[n] - lowBound);
		}
		if (child.x_var[n] > uppBound) {
			double rnd = nextRandomDouble();
			child.x_var[n] = uppBound - rnd * (uppBound - base.x_var[n]);
		}
	}
}

void diff_evo_xover_1(Chromosome &base, Chromosome &ind1, Chromosome &ind2,
		Chromosome &child, double de_f, double de_cr) {

	int idx_rnd = nextRandomInt(nvar);

	for (int n = 0; n < nvar; n++) {
		//*
		// strategy two
		double rnd1 = nextRandomDouble();
		if (rnd1 < de_cr || n == idx_rnd)
			child.x_var[n] = base.x_var[n] + de_f * (ind2.x_var[n]
					- ind1.x_var[n]);
		else
			child.x_var[n] = base.x_var[n];
		//*/

		// handle the boundary voilation
		if (child.x_var[n] < lowBound) {
			double rnd = nextRandomDouble();
			child.x_var[n] = lowBound + rnd * (base.x_var[n] - lowBound);
		}
		if (child.x_var[n] > uppBound) {
			double rnd = nextRandomDouble();
			child.x_var[n] = uppBound - rnd * (uppBound - base.x_var[n]);
		}

	}
}

void diff_evo_xover_2(Chromosome &base, Chromosome &ind1, Chromosome &ind2,
		Chromosome &ind3, Chromosome &ind4, Chromosome &child, double de_f,
		double de_cr) {
	int idx_rnd = nextRandomInt(nvar);

	for (int n = 0; n < nvar; n++) {
		//*
		// strategy two
		double rnd1 = nextRandomDouble();
		if (rnd1 < de_cr || n == idx_rnd)
			child.x_var[n] = base.x_var[n] + de_f * (ind2.x_var[n]
					- ind1.x_var[n]) + de_f * (ind4.x_var[n] - ind3.x_var[n]);
		else
			child.x_var[n] = base.x_var[n];
		//*/

		// handle the boundary voilation
		if (child.x_var[n] < lowBound) {
			double rnd = nextRandomDouble();
			child.x_var[n] = lowBound + rnd * (base.x_var[n] - lowBound);
		}
		if (child.x_var[n] > uppBound) {
			double rnd = nextRandomDouble();
			child.x_var[n] = uppBound - rnd * (uppBound - base.x_var[n]);
		}
	}
}

void partical_swarm_evol(Chromosome &current, Chromosome &best, Chromosome& local, double* direction){
	double c=2;
	double rand= c*nextRandomDouble();

	for (int i=0;i<nvar;i++){
		double backup = current.x_var[i];

		direction[i]=direction[i]+rand*(best.x_var[i]-current.x_var[i])
				+rand*(local.x_var[i]-current.x_var[i]);

		current.x_var[i]=current.x_var[i]+direction[i];

		if (current.x_var[i] < lowBound) {
			double rnd = nextRandomDouble();
			current.x_var[i] = lowBound + rnd * (backup - lowBound);
		}
		if (current.x_var[i] > uppBound) {
			double rnd = nextRandomDouble();
			current.x_var[i] = uppBound - rnd * (uppBound - backup);
		}
	}
}
