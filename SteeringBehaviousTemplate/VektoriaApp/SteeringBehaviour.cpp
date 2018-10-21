#include "StdAfx.h"
#include "SteeringBehaviour.h"


SteeringBehaviour::SteeringBehaviour(Spielfeld *aspielfeld)
{
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;

	m_facemode = FACETARGET;
	m_movingMode = DYNAMIC;
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
	if (m_targetgroup) {
		m_kinematikZiel = m_targetgroup->at(0)->getKinematik();
	}
	else return;
}

void SteeringBehaviour::setMoving(MovingMode movingMode){
	m_movingMode = movingMode;
}

void SteeringBehaviour::Tick(float fTime, float fTimeDelta, Boid *aboid) {

	m_boid = aboid;

	if (m_boid) {
		m_kinematikBoid = m_boid->getKinematik();
	}
	else return;

	//Reset Steuerung
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
		m_kinematikBoid->orientierung = orientationToMoveDirection(m_kinematikBoid->orientierung, m_kinematikBoid->geschwindigkeit);
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
	if (avector.Length() > maxlenght) {
		float x = avector.Length();
		avector /= avector.Length();
		avector *= maxlenght;
	}
	return avector;
}


CHVector SteeringBehaviour::angletovector(float angle) {
	//angle = DEGREES_TO_RADIANS(angle);
	CHVector result = CHVector(cos(angle), 0.f, sin(angle));
	return result.Normal();
}

float SteeringBehaviour::vectorToAngle(CHVector v){
	//Ergebnis in Radian
	return atan(v.z / v.x);
}

float SteeringBehaviour::orientationToMoveDirection(float currentorientation, CHVector geschwindigkeit) {
	float result = currentorientation;
	if (geschwindigkeit.Length() > 0) {
		result = -atan2(-geschwindigkeit.x, geschwindigkeit.z);
	}
	return result;
}