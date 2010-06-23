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
	Function(){};
	virtual ~Function();

	void operator() (double *var, double *obj);
	void operator() (ChromosomePtr chrom);

	virtual boost::shared_ptr<std::string> getName() {return name;};

	virtual void evaluate(double* var, double* obj){};
	virtual int getObjDim() = 0;
	virtual int getVarDim() = 0;

protected:
	boost::shared_ptr<std::string> name;

private:
	double TEMP_X[100];
	double TEMP_Y[100];
};

typedef boost::shared_ptr<Function> FunctionPtr;

#endif /* FUNCTION_H_ */
