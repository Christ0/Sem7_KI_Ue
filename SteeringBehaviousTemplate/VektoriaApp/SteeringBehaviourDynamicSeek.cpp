#include "SteeringBehaviourDynamicSeek.h"


SteeringBehaviourDynamicSeek::SteeringBehaviourDynamicSeek(Spielfeld * aspielfeld) {
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourDynamicSeek::~SteeringBehaviourDynamicSeek()
{
}

Steuerung SteeringBehaviourDynamicSeek::update(Boid * aboid, std::vector<Boid*>* atarget) {
	Steuerung ergSteuerung;
	ergSteuerung.linear = CHVector(0.f, 0.f, 0.f);
	ergSteuerung.angular = 0.f;
	ergSteuerung.linear = m_kinematikZiel->position - m_kinematikBoid->position;
	ergSteuerung.linear = ergSteuerung.linear.Normal() * m_boid->getMaxSteuerungsKraft();
	return ergSteuerung;
}
