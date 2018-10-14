#pragma once

#include "Vektoria\Root.h"
#include "Kinematik.h"
#include "Steuerung.h"


class SteeringBehaviour;

using namespace Vektoria;

class Boid
{
public:
	Boid();
	~Boid();
	
	void Tick(float fTime, float fTimeDelta);

	Kinematik *getKinematik();
	Steuerung *getSteuerung();

	CPlacement * getPlacement();
	
	void reset(CHVector aposition);
	
	float getMaxSteuerungsKraft();
	float getMaxGeschwindigkeit();

	float getEnergie();
	void resetEnergie(float energie = 0);

	void setSteeringBehaviour(SteeringBehaviour *aSteeringBehaviour);
	SteeringBehaviour* getSteeringBehaviour();

	void uiSteuerung(CDeviceKeyboard *zdKeyboard);

	void setMaterial();
	void setMaterialTarget();
protected:
	CGeoSphere m_gBody;
	CGeoSphere m_gHead;
	CPlacement m_pNeck;
	CMaterial m_m;
	CMaterial m_mTarget;

	CPlacement m_p;

	Kinematik m_kinematik;
	Steuerung m_steuerung;

	std::string m_typ;

	float maxSteuerungskrafts;
	float maxGeschwindigkeit;

	float m_energie;

	SteeringBehaviour *m_SteeringBehaviour;

	CDeviceKeyboard *m_zdKeyboard;
};

