/*
 * Function.h
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

class Function {
public:
	Function();
	virtual ~Function(){};

	virtual void operator() (double *var, double *obj);
};

#endif /* FUNCTION_H_ */
