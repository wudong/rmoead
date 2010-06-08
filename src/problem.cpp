/*
 * problem.cpp
 *
 *  Created on: 13 Aug 2009
 *      Author: wudong
 */
#include "problem.h"


// *********************** CEC 2009 ************************************
void CEC09_F1(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -1.0 + 2.0*X[i];
	CEC09::UF1(XX, F, nvar);
	delete[] XX;
}

void CEC09_F2(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -1.0 + 2.0*X[i];
	CEC09::UF2(XX, F, nvar);
	delete[] XX;
}

void CEC09_F3(double* F, double* X){
	CEC09::UF3(X, F, nvar);
}

void CEC09_F4(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -2.0 + 4.0*X[i];
	CEC09::UF4(XX, F, nvar);
	delete[] XX;
}

void CEC09_F5(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -1.0 + 2.0*X[i];
	CEC09::UF5(XX, F, nvar);
	delete[] XX;
}

void CEC09_F5_1(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -1.0 + 2.0*X[i];
	CEC09::UF5_1(XX, F, nvar);
	delete[] XX;
}

void CEC09_F6(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -1.0 + 2.0*X[i];
	CEC09::UF6(XX, F, nvar);
	delete[] XX;
}

void CEC09_F7(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];
	for(unsigned int i=1; i<nvar; i++)
		XX[i] = -1.0 + 2.0*X[i];
	CEC09::UF7(XX, F, nvar);
	delete[] XX;
}

void CEC09_F8(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];XX[1]=X[1];
	for(unsigned int i=2; i<nvar; i++)
		XX[i] = -2.0 + 4.0*X[i];
	CEC09::UF8(XX, F, nvar);
	delete[] XX;
}

void CEC09_F9(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];XX[1]=X[1];
	for(unsigned int i=2; i<nvar; i++)
		XX[i] = -2.0 + 4.0*X[i];
	CEC09::UF9(XX, F, nvar);
	delete[] XX;
}

void CEC09_F10(double* F, double* X){
	double* XX = new double[nvar];
	XX[0]=X[0];XX[1]=X[1];
	for(unsigned int i=2; i<nvar; i++)
		XX[i] = -2.0 + 4.0*X[i];
	CEC09::UF10(XX, F, nvar);
	delete[] XX;
}

