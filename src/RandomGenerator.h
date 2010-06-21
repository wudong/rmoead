/*
 * RandomGenerator.h
 *
 *  Created on: 16 Jun 2010
 *      Author: wudong
 */

#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

#include <boost/smart_ptr.hpp>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class RandomGenerator {
public:
	RandomGenerator(long seed);
	virtual ~RandomGenerator();
	void reSeed(long seed);
	double nextRandomDouble();
	double nextRandomDouble(double low, double high);
	unsigned int nextRandomInt(unsigned int high);
	void randomShuffle(int* perm, unsigned int size);

private:
	//------------------Random Seed---------------------------------------

	long random_seed;
	const gsl_rng_type * rand_T;
	gsl_rng * rand_generator;
};

typedef boost::shared_ptr<RandomGenerator> RandomGeneratorPtr;

#endif /* RANDOMGENERATOR_H_ */
