#pragma once
#include "SteeringBehaviour.h"
class SteeringBehaviourDynamicWander :
	public SteeringBehaviour {
	float m_radius;
	float m_offset;
	float m_maxRichtungsaenderung;
	float m_winkelAenderung;
	CHVector m_positionAufKreis;
public:
	SteeringBehaviourDynamicWander(Spielfeld *aspielfeld = NULL);
	~SteeringBehaviourDynamicWander();
	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
};

