#include "SteeringBehaviourKinematicFlee.h"



SteeringBehaviourKinematicFlee::SteeringBehaviourKinematicFlee(Spielfeld * aspielfeld) {
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourKinematicFlee::~SteeringBehaviourKinematicFlee()
{
}

Steuerung SteeringBehaviourKinematicFlee::update(Boid * aboid, std::vector<Boid*>* atarget) {
	Steuerung ergSteuerung;
	ergSteuerung.linear = CHVector(0.f, 0.f, 0.f);
	ergSteuerung.angular = 0.f;
	Kinematik * kine = aboid->getKinematik();
	kine->geschwindigkeit = kine->position - m_kinematikZiel->position;
	kine->geschwindigkeit = kine->geschwindigkeit.Normal() * aboid->getMaxGeschwindigkeit();
	return ergSteuerung;
}