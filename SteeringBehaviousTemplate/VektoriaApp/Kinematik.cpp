#include "Kinematik.h"


Kinematik::Kinematik()
{
}


Kinematik::~Kinematik()
{
}

Kinematik operator+(Kinematik& lhs, Kinematik& rhs){
	Kinematik result;
	result.geschwindigkeit = lhs.geschwindigkeit + rhs.geschwindigkeit;
	result.orientierung = lhs.orientierung + rhs.orientierung;
	result.position = lhs.position + rhs.position;
	result.rotation = lhs.rotation + rhs.rotation;
	return result;
}

Kinematik Kinematik::operator+=(Kinematik& rhs){
	geschwindigkeit += rhs.geschwindigkeit;
	rotation += rhs.rotation;
	return *this;
}

Kinematik operator*(Kinematik& lhs, float rhs){
	Kinematik result;
	result.geschwindigkeit = lhs.geschwindigkeit * rhs;
	result.rotation = lhs.rotation * rhs;
	return result;
}