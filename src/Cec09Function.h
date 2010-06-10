/*
 * Cec09Function.h
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#ifndef CEC09FUNCTION_H_
#define CEC09FUNCTION_H_

#include "Function.h"
#include <string>

class Cec09Function: public Function {
public:
	Cec09Function(std::string name);
	virtual ~Cec09Function(){};
	void evaluate(double* var, double* obj);

private:
	std::string funcname;
	double scale;
};

#endif /* CEC09FUNCTION_H_ */
