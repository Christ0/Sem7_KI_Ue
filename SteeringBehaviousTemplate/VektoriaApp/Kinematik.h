#pragma once

#include "Vektoria\Root.h"
using namespace Vektoria;

struct Kinematik
{
public:
	Kinematik();
	~Kinematik();
	friend Kinematik operator+(Kinematik& lhs, Kinematik& rhs);
	friend Kinematik operator*(Kinematik& lhs, float rhs);
	Kinematik operator+=(Kinematik& rhs);

	CHVector position;
	float orientierung;
	CHVector geschwindigkeit;
	float rotation;

private:
};

Kinematik operator+(Kinematik& lhs, Kinematik& rhs);

