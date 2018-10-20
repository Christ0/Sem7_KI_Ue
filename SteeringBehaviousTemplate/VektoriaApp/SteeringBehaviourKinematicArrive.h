#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourKinematicArrive :
	public SteeringBehaviour{
	float m_radius;
	float m_timeToArrive;
public:
	SteeringBehaviourKinematicArrive(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourKinematicArrive();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

