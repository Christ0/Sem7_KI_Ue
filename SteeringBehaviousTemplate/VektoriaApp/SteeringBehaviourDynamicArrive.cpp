#include "SteeringBehaviourDynamicArrive.h"



SteeringBehaviourDynamicArrive::SteeringBehaviourDynamicArrive(Spielfeld * aspielfeld) {
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;
	m_radius = 2.f;
	m_timeToArrive = 0.1f;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourDynamicArrive::~SteeringBehaviourDynamicArrive()
{
}

Steuerung SteeringBehaviourDynamicArrive::update(Boid * aboid, std::vector<Boid*>* atarget) {
	Steuerung ergSteuerung;
	float zielgeschwindigkeit = 0.f;
	CHVector richtung = m_kinematikZiel->position - m_kinematikBoid->position;
	if (richtung.Length() > m_radius) {
		zielgeschwindigkeit = aboid->getMaxGeschwindigkeit();
	}
	else {
		zielgeschwindigkeit = aboid->getMaxGeschwindigkeit() * richtung.Length() / m_radius;
	}
	richtung = richtung.Normal()*zielgeschwindigkeit;

	ergSteuerung.linear = richtung - m_kinematikBoid->geschwindigkeit;
	ergSteuerung.linear /= m_timeToArrive;
	ergSteuerung.angular = 0;
	return ergSteuerung;

}
