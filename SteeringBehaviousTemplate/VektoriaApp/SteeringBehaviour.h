#pragma once

#include "Boid.h"
#include "Spielfeld.h"
#include "Kinematik.h"
#include "Steuerung.h"

class SteeringBehaviourDynamicALIGN;

class SteeringBehaviour
{
public:
	SteeringBehaviour(Spielfeld *aspielfeld = NULL/**/);
	~SteeringBehaviour();

	enum  FaceingMode
	{
		FACETARGET,
		MOVEDIRECTION,
		DEFAULT
	};

	virtual void Tick(float fTime, float fTimeDelta, Boid *aboid);

	virtual Steuerung update(Boid *aboid, std::vector<Boid*> *atarget);
	void setfacing(FaceingMode facemode);
	void settarget(std::vector<Boid*> *atarget);

protected:
	Kinematik *m_kinematikBoid;
	Kinematik *m_kinematikZiel;
	Steuerung *m_steuerungZiel;

	Boid *m_boid;
	std::vector<Boid*> *m_targetgroup;
	Spielfeld *m_spielfeld;

	FaceingMode m_facemode;

	CHVector truncate(CHVector avector, float maxlenght);
	CHVector angletovector(float angle);
	float orientationToMoveDirection(float currentorientation, CHVector geschwindigkeit);
	bool imsichtbereich(CHVector &blickrichtung, CHVector &zielrichtung, float FOV);

private:
	void billiardkinematik();
};

