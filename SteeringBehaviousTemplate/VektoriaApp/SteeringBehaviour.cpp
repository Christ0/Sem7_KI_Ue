#include "StdAfx.h"
#include "SteeringBehaviour.h"


SteeringBehaviour::SteeringBehaviour(Spielfeld *aspielfeld)
{
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;

	m_facemode = MOVEDIRECTION;
}


SteeringBehaviour::~SteeringBehaviour()
{
}

Steuerung SteeringBehaviour::update(Boid *aboid, std::vector<Boid*> *atarget) {
	Steuerung ergSteuerung;

	ergSteuerung.linear = CHVector(0.f, 0.f, 0.f);
	ergSteuerung.angular = 0.f;
	return ergSteuerung;
}

void SteeringBehaviour::setfacing(FaceingMode facemode) {
	m_facemode = facemode;
}
void SteeringBehaviour::settarget(std::vector<Boid*> *atarget) {
	m_targetgroup = atarget;
}

void SteeringBehaviour::Tick(float fTime, float fTimeDelta, Boid *aboid) {

	m_boid = aboid;

	if (m_boid) {
		m_kinematikBoid = m_boid->getKinematik();
	}
	else
	{
		return;
	}

	Steuerung ergSteuerung;
	ergSteuerung.linear = CHVector(0.f, 0.f, 0.f);
	ergSteuerung.angular = 0.f;

	//update wird für jedes spezielles SB neu implementiert
	ergSteuerung = update(aboid, m_targetgroup);
	////Update Position
	ergSteuerung.linear = truncate(ergSteuerung.linear, m_boid->getMaxSteuerungsKraft());
	m_kinematikBoid->geschwindigkeit = truncate(m_kinematikBoid->geschwindigkeit, m_boid->getMaxGeschwindigkeit());

	//Update Geschwindigkeit und Rotation
	m_kinematikBoid->geschwindigkeit += ergSteuerung.linear *fTimeDelta;
	m_kinematikBoid->rotation += ergSteuerung.angular *fTimeDelta;

	//update position und orientierung
	m_kinematikBoid->position += m_kinematikBoid->geschwindigkeit * fTimeDelta;
	m_kinematikBoid->orientierung += m_kinematikBoid->rotation*fTimeDelta;

	if (m_facemode == MOVEDIRECTION) {
	}

	if (m_targetgroup && m_facemode == FACETARGET) {
	}

	//checke on Spielfeldrand erreicht wurde
	billiardkinematik();
}

bool SteeringBehaviour::imsichtbereich(CHVector &blickrichtung, CHVector &zielrichtung, float FOV) {
	//
	return true;
}

void SteeringBehaviour::billiardkinematik() {
	//BILLIARD
	CHVector *dim = m_spielfeld->getDimension();
	CHVector *pose = m_spielfeld->getPose();

	if (m_kinematikBoid->position.x > pose->x + dim->x) {
		m_kinematikBoid->position.x = pose->x + dim->x;
		m_kinematikBoid->geschwindigkeit.x = -m_kinematikBoid->geschwindigkeit.x;
	}

	if (m_kinematikBoid->position.x < pose->x - dim->x) {
		m_kinematikBoid->position.x = pose->x - dim->x;
		m_kinematikBoid->geschwindigkeit.x = -m_kinematikBoid->geschwindigkeit.x;
	}

	if (m_kinematikBoid->position.z > pose->z + dim->z) {
		m_kinematikBoid->position.z = pose->z + dim->z;
		m_kinematikBoid->geschwindigkeit.z = -m_kinematikBoid->geschwindigkeit.z;
	}

	if (m_kinematikBoid->position.z < pose->z - dim->z) {
		m_kinematikBoid->position.z = pose->z - dim->z;
		m_kinematikBoid->geschwindigkeit.z = -m_kinematikBoid->geschwindigkeit.z;
	}
}

CHVector SteeringBehaviour::truncate(CHVector avector, float maxlenght) {
	CHVector result;
	//

	return result;
}


CHVector SteeringBehaviour::angletovector(float angle) {
	CHVector result = CHVector(0.f, 0.f, 0.f);
	///

	return result.Normal();

}

float SteeringBehaviour::orientationToMoveDirection(float currentorientation, CHVector geschwindigkeit) {
	float result = currentorientation;
	//
	return result;
}