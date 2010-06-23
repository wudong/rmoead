/*
 * SingleObjEATest.h
 *
 *  Created on: 23 Jun 2010
 *      Author: wudong
 */

#ifndef SINGLEOBJEATEST_H_
#define SINGLEOBJEATEST_H_

#include "../src/Function.h"
#include "../src/SingleObjEA.h"
#include <gtest/gtest.h>

class SingleObjEATest: public ::testing::Test {
public:
	SingleObjEATest() {
	}
	;
	virtual ~SingleObjEATest() {
	}
	;
};

class SimpleFunction: public Function {
public:
	SimpleFunction() {
		this->name.reset(new std::string("SimpleTestFunction"));
	}
	;

	virtual void evaluate(double* var, double* obj);
	virtual int getObjDim() {
		return 1;
	}
	;
	virtual int getVarDim() {
		return 2;
	}
	;
};

void SimpleFunction::evaluate(double* var, double* obj) {
	obj[0] = var[0] * var[0] + var[1] * var[1];
}
;

TEST_F(SingleObjEATest, initPop)
{

	FunctionPtr func(new SimpleFunction());
	RandomGeneratorPtr rg(new RandomGenerator(0));
	boost::shared_ptr<SingleObjEA> ea(new SingleObjEA());

	ea->setFunction(func);
	ea->setRandomGenerator(rg);

	ea->initPop(10);
	ASSERT_EQ(10, ea->getPopsize());

	for (unsigned int i=0;i<100;i++) {
		ChromosomePtr chrom = ea->randomInd();
		ASSERT_TRUE(chrom);
		ASSERT_TRUE(chrom->evaluated);
	}
}

TEST_F(SingleObjEATest, simpleFunction)
{

	FunctionPtr func(new SimpleFunction());
	RandomGeneratorPtr rg(new RandomGenerator(0));

	boost::shared_ptr<SingleObjEA> ea(new SingleObjEA());

	ea->setFunction(func);
	ea->setRandomGenerator(rg);
	ea->setRunId(0);
	ea->initPop(10);
	ea->evolve();

	ChromosomePtr chrom = ea->findBest(true);
	std::cout << "Opt Result:" << chrom->y_obj[0];
}

#endif /* SINGLEOBJEATEST_H_ */
