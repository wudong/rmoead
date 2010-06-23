/*
 * Cec09Function.cpp
 *
 *  Created on: 10 Jun 2010
 *      Author: wudong
 */

#include "Cec09Function.h"

Cec09Function::Cec09Function(boost::shared_ptr<std::string> funcname, int vd, int od):
 objdim(od), vardim(vd) {
	this->name = funcname;
	for (unsigned int i = 0; i < this->name->length(); i++) {
		(*this->name)[i] = toupper((*this->name)[i]);
	}
	this->scale = 20;
}

void Cec09Function::evaluate(double* var, double* obj) {
	if (this->name->compare("UF1")) {
		CEC09::UF1(var, obj, vardim);
	} else if (this->name->compare("UF1X")) {
		CEC09::UF1(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->name->compare("UF2")) {
		CEC09::UF2(var, obj, vardim);
	} else if (this->name->compare("UF2X")) {
		CEC09::UF2(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->name->compare("UF3")) {
		CEC09::UF3(var, obj, vardim);
	} else if (this->name->compare("UF3X")) {
		CEC09::UF3(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->name->compare("UF4")) {
		CEC09::UF4(var, obj, vardim);
	} else if (this->name->compare("UF5")) {
		CEC09::UF5(var, obj, vardim);
	} else if (this->name->compare("UF5_1")) {
		CEC09::UF5_1(var, obj, vardim);
	} else if (this->name->compare("UF6")) {
		CEC09::UF6(var, obj, vardim);
	} else if (this->name->compare("UF7")) {
		CEC09::UF7(var, obj, vardim);
	} else if (this->name->compare("UF7X")) {
		CEC09::UF7(var, obj, vardim);
		obj[0] = scale * obj[0];
	} else if (this->name->compare("UF8")) {
		CEC09::UF8(var, obj, vardim);
	} else if (this->name->compare("UF9")) {
		CEC09::UF9(var, obj, vardim);
	} else if (this->name->compare("UF10")) {
		CEC09::UF10(var, obj, vardim);
	} else
		assert(false);
}
