/*
 * Cec09Function.h
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#ifndef CEC09FUNCTION_H_
#define CEC09FUNCTION_H_

#include "Function.h"
#include "cec09.h"
#include <string>

class Cec09Function: public Function {
public:
	Cec09Function(boost::shared_ptr<std::string> funcname, int vd, int od);
	virtual ~Cec09Function(){};
	void evaluate(double* var, double* obj);
	inline int getObjDim(){return objdim;};
	inline int getVarDim(){return vardim;};

private:
	double scale;
	int objdim;
	int vardim;
};

#endif /* CEC09FUNCTION_H_ */
