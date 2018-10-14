#pragma once

#include "Vektoria\Root.h"
using namespace Vektoria;

struct Steuerung
{
public:
	Steuerung();
	~Steuerung();
	
	CHVector linear;
	float angular;

	friend Steuerung operator+(Steuerung& lhs, Steuerung& rhs);
	friend Steuerung operator*(Steuerung& lhs, float rhs);
	Steuerung operator+=(Steuerung& rhs);
private:

};

Steuerung operator+(Steuerung& lhs, Steuerung& rhs);
Steuerung operator*(Steuerung& lhs, float rhs);