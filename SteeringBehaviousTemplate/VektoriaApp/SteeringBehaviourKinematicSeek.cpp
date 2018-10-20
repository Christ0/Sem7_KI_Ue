#include "SteeringBehaviourKinematicSeek.h"


SteeringBehaviourKinematicSeek::SteeringBehaviourKinematicSeek(Spielfeld * aspielfeld){
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourKinematicSeek::~SteeringBehaviourKinematicSeek()
{
}

Steuerung SteeringBehaviourKinematicSeek::update(Boid * aboid, std::vector<Boid*>* atarget){
	Steuerung ergSteuerung;
	ergSteuerung.linear = CHVector(0.f, 0.f, 0.f);
	ergSteuerung.angular = 0.f;
	m_kinematikBoid->geschwindigkeit = m_kinematikZiel->position - m_kinematikBoid->position;
	m_kinematikBoid->geschwindigkeit = m_kinematikBoid->geschwindigkeit.Normal() * aboid->getMaxGeschwindigkeit();
	return ergSteuerung;
}
