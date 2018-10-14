#include "Steuerung.h"


Steuerung::Steuerung()
{
}


Steuerung::~Steuerung()
{
}

Steuerung Steuerung::operator+=(Steuerung& rhs){
	linear += rhs.linear;
	angular += rhs.angular;
	return *this;
}

Steuerung operator*(Steuerung& lhs, float rhs){
	Steuerung result;
	result.linear = lhs.linear * rhs;
	result.angular = lhs.angular * rhs;
	return result;
}
Steuerung operator+(Steuerung& lhs, Steuerung& rhs){
	Steuerung result;
	result.linear = lhs.linear + rhs.linear;
	result.angular = lhs.angular + rhs.angular;
	return result;
}

