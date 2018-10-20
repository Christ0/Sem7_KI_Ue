#include "SteeringBehaviourKinematicArrive.h"



SteeringBehaviourKinematicArrive::SteeringBehaviourKinematicArrive(Spielfeld * aspielfeld) {
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;
	m_radius = 0.001f;
	m_timeToArrive = 2.f;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourKinematicArrive::~SteeringBehaviourKinematicArrive()
{
}

Steuerung SteeringBehaviourKinematicArrive::update(Boid * aboid, std::vector<Boid*>* atarget) {
	Steuerung ergSteuerung;
	CHVector richtung = m_kinematikZiel->position - m_kinematikBoid->position;
	if (m_kinematikBoid->geschwindigkeit.Length() < m_radius) {
		m_kinematikBoid->geschwindigkeit = CHVector(0.f, 0.f, 0.f);
	}
	else {
		m_kinematikBoid->geschwindigkeit = richtung;
		m_kinematikBoid->geschwindigkeit *= m_timeToArrive;
		m_kinematikBoid->rotation = 0.f;
	}

	ergSteuerung.angular = 0.f;
	ergSteuerung.linear = CHVector(0.f, 0.f, 0.f);
	return ergSteuerung;

}
