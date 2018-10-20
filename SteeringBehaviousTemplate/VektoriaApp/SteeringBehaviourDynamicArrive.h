#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourDynamicArrive :
	public SteeringBehaviour {
	float m_radius;
	float m_timeToArrive;
public:
	SteeringBehaviourDynamicArrive(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourDynamicArrive();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

