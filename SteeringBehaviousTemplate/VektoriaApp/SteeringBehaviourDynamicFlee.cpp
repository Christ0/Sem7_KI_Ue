#include "SteeringBehaviourDynamicFlee.h"



SteeringBehaviourDynamicFlee::SteeringBehaviourDynamicFlee(Spielfeld * aspielfeld) {
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourDynamicFlee::~SteeringBehaviourDynamicFlee()
{
}

Steuerung SteeringBehaviourDynamicFlee::update(Boid * aboid, std::vector<Boid*>* atarget) {
	Steuerung ergSteuerung;
	//ergSteuerung.linear = CHVector(1.f, 0.f, 1.f);
	ergSteuerung.angular = 0.f;
	ergSteuerung.linear = m_kinematikBoid->position - m_kinematikZiel->position;
	ergSteuerung.linear = ergSteuerung.linear.Normal() * m_boid->getMaxSteuerungsKraft();
	return ergSteuerung;
}