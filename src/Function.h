/*
 * Function.h
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "Chromosome.h"

class Function {
public:
	Function();
	virtual ~Function();

	void operator() (double *var, double *obj);
	void operator() (ChromosomePtr chrom);

	virtual void evaluate(double* var, double* obj){};
	virtual std::string & getName() =0;
	virtual int getObjDim() = 0;
	virtual int getVarDim() = 0;

private:
	double TEMP_X[100];
	double TEMP_Y[100];
};

typedef boost::shared_ptr<Function> FunctionPtr;

#endif /* FUNCTION_H_ */
