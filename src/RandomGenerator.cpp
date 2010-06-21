/*
 * RandomGenerator.cpp
 *
 *  Created on: 16 Jun 2010
 *      Author: wudong
 */

#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(long seed) {
	rand_T = gsl_rng_default;
	rand_generator = gsl_rng_alloc(rand_T);

	//	if (seed!=0)
	reSeed(seed);

	//setRandomSeed(random_seed);
	//gsl_rng_env_setup();
}

void RandomGenerator::reSeed(long seed) {
	random_seed = seed;
	gsl_rng_set(rand_generator, random_seed);
}

RandomGenerator::~RandomGenerator() {
	gsl_rng_free(rand_generator);
}

double RandomGenerator::nextRandomDouble() {
	return gsl_rng_uniform(rand_generator);
}

double RandomGenerator::nextRandomDouble(double low, double high) {
	assert(high >= low);
	if (high == low)
		return high;
	else {
		double value = low + gsl_rng_uniform(rand_generator) * (high - low);
		return value;
	}
}

unsigned int RandomGenerator::nextRandomInt(unsigned int high) {
	return gsl_rng_uniform_int(rand_generator, high);
}

void RandomGenerator::randomShuffle(int* perm, unsigned int size) {
	gsl_ran_shuffle(rand_generator, perm, size, sizeof(int));
}
