#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourDynamicFlee :
	public SteeringBehaviour
{
public:
	SteeringBehaviourDynamicFlee(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourDynamicFlee();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

