/*
 * Cec09Function.cpp
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#include "Cec09Function.h"

Cec09Function::Cec09Function(std::string funcname) {
	this->funcname = funcname;
	for (unsigned int i = 0; i < this->funcname.length(); i++) {
		this->funcname[i] = toupper(this->funcname[i]);
	}
	this->scale = 20;
}

void Cec09Function::evaluate(double* var, double* obj) {
	if (this->funcname.compare("UF1")) {
		CEC09_F1(var, obj);
	} else if (this->funcname.compare("UF1X")) {
		CEC09_F1(var, obj);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF2")) {
		CEC09_F2(var, obj);
	} else if (this->funcname.compare("UF2X")) {
		CEC09_F2(var, obj);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF3")) {
		CEC09_F3(var, obj);
	} else if (this->funcname.compare("UF3X")) {
		CEC09_F3(var, obj);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF4")) {
		CEC09_F4(var, obj);
	} else if (this->funcname.compare("UF5")) {
		CEC09_F5(var, obj);
	} else if (this->funcname.compare("UF5_1")) {
		CEC09_F5_1(var, obj);
	} else if (this->funcname.compare("UF6")) {
		CEC09_F6(var, obj);
	} else if (this->funcname.compare("UF7")) {
		CEC09_F7(var, obj);
	} else if (this->funcname.compare("UF7X")) {
		CEC09_F7(var, obj);
		obj[0] = scale * obj[0];
	} else if (this->funcname.compare("UF8")) {
		CEC09_F8(var, obj);
	} else if (this->funcname.compare("UF9")) {
		CEC09_F9(var, obj);
	} else if (this->funcname.compare("UF10")) {
		CEC09_F10(var, obj);
	} else
		assert(false);
}
