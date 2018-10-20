#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourDynamicSeek :
	public SteeringBehaviour
{
public:
	SteeringBehaviourDynamicSeek(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourDynamicSeek();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

