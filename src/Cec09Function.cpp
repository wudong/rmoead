/*
 * Cec09Function.cpp
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#include "Cec09Function.h"

Cec09Function::Cec09Function(std::string funcname, int vd, int od):
 objdim(od), vardim(vd) {
	this->funcname = funcname;
	for (unsigned int i = 0; i < this->funcname.length(); i++) {
		this->funcname[i] = toupper(this->funcname[i]);
	}
	this->scale = 20;
}

std::string & Cec09Function::getName(){
	return this->funcname;
}

void Cec09Function::evaluate(double* var, double* obj) {
	if (this->funcname.compare("UF1")) {
		CEC09::UF1(var, obj, vardim);
	} else if (this->funcname.compare("UF1X")) {
		CEC09::UF1(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF2")) {
		CEC09::UF2(var, obj, vardim);
	} else if (this->funcname.compare("UF2X")) {
		CEC09::UF2(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF3")) {
		CEC09::UF3(var, obj, vardim);
	} else if (this->funcname.compare("UF3X")) {
		CEC09::UF3(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF4")) {
		CEC09::UF4(var, obj, vardim);
	} else if (this->funcname.compare("UF5")) {
		CEC09::UF5(var, obj, vardim);
	} else if (this->funcname.compare("UF5_1")) {
		CEC09::UF5_1(var, obj, vardim);
	} else if (this->funcname.compare("UF6")) {
		CEC09::UF6(var, obj, vardim);
	} else if (this->funcname.compare("UF7")) {
		CEC09::UF7(var, obj, vardim);
	} else if (this->funcname.compare("UF7X")) {
		CEC09::UF7(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF8")) {
		CEC09::UF8(var, obj, vardim);
	} else if (this->funcname.compare("UF9")) {
		CEC09::UF9(var, obj, vardim);
	} else if (this->funcname.compare("UF10")) {
		CEC09::UF10(var, obj, vardim);
	} else
		assert(false);
}
