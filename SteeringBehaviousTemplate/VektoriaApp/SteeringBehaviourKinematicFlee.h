#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourKinematicFlee :
	public SteeringBehaviour
{
public:
	SteeringBehaviourKinematicFlee(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourKinematicFlee();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

