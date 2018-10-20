#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourKinematicSeek :
	public SteeringBehaviour
{
public:
	SteeringBehaviourKinematicSeek(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourKinematicSeek();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

