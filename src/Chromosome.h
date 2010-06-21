/*
 * Chromosome.h
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

#include "global.h"
#include "common.h"
#include "RandomGenerator.h"
#include <boost/smart_ptr.hpp>

class Chromosome;
typedef boost::shared_ptr<Chromosome> ChromosomePtr;

class Chromosome{
public:
	Chromosome();
	virtual ~Chromosome();

	std::vector<double> x_var;
	std::vector<double> y_obj;
	int    rank;

	bool evaluated;

	ChromosomePtr clone();

	void   rnd_init(RandomGeneratorPtr r);

	void show_objective();
	void show_variable();

    bool   operator<(const Chromosome &ind2);
	bool   operator<<(const Chromosome &ind2);
    bool   operator==(const Chromosome &ind2);
    void   operator=(const Chromosome &ind2);
};


#endif /* CHROMOSOME_H_ */
