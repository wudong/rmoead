/*
 * Function.h
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#ifndef FUNCTION_CPP_
#define FUNCTION_CPP_

#include "Function.h"


Function::~Function() {
}

void Function::operator()(ChromosomePtr chrom){
	std::copy(chrom->x_var.begin(), chrom->x_var.end(), TEMP_X);
	std::copy(chrom->y_obj.begin(), chrom->y_obj.end(), TEMP_Y);
	evaluate(TEMP_X, TEMP_Y);

	unsigned int size = chrom->y_obj.size();
	std::copy(TEMP_Y, TEMP_Y+size, chrom->y_obj.begin());
}

void Function::operator()(double* var, double* obj){
	evaluate(var, obj);
}
#endif /* FUNCTION_H_ */
