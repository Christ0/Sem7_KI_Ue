#include "StdAfx.h"

#include "Boid.h"
#include "SteeringBehaviour.h"

Boid::Boid()
{
	m_gBody.Init(1.0F, NULL, 50, 50);
	m_gHead.Init(0.5f, NULL, 50, 50);
	m_pNeck.TranslateZ(0.8f);
	m_m.MakeTextureDiffuse("textures\\blue_image.jpg");
	m_mTarget.MakeTextureDiffuse("textures\\red_image.jpg");
	
	m_p.AddGeo(&m_gBody); 
	m_p.AddPlacement(&m_pNeck);
	m_pNeck.AddGeo(&m_gHead);

	reset(CHVector());
	m_typ = "BOID";
	
	resetEnergie();
	maxGeschwindigkeit = 8.f;
	maxSteuerungskrafts = rand() % 2 + 8.f;

	m_SteeringBehaviour = NULL;
}

Boid::~Boid()
{
}

float Boid::getEnergie(){
	return m_energie;
}

void Boid::setSteeringBehaviour(SteeringBehaviour *aSteeringBehaviour){
	m_SteeringBehaviour = aSteeringBehaviour;
}

SteeringBehaviour*  Boid::getSteeringBehaviour(){
	return m_SteeringBehaviour;
}

void Boid::resetEnergie(float energie){
	m_kinematik.orientierung = DEGREES_TO_RADIANS(rand() % 360);
	m_energie = /*(rand() % 5) + */30; // Boid hat zwischen 5 und 10 Sekunden Energie
}

CPlacement * Boid::getPlacement(){
	return &m_p;
}

Kinematik* Boid::getKinematik(){
	return &m_kinematik;
}

Steuerung* Boid::getSteuerung(){
	return &m_steuerung; 
}

void Boid::Tick(float fTime, float fTimeDelta){
	//Energie

	if (m_energie > -5)
		m_energie -= fTimeDelta;

	if (m_SteeringBehaviour){
		m_SteeringBehaviour->Tick(fTime, fTimeDelta, this);
	}

	m_p.Translate(m_kinematik.position);
	m_pNeck.TranslateZ(0.8f);
	m_pNeck.RotateYDelta(m_kinematik.orientierung);
}

void Boid::reset(CHVector aposition){
	m_kinematik.orientierung = DEGREES_TO_RADIANS(rand() % 360)/*0.0f*/;
	m_kinematik.position = aposition;
	//Bewegung
	m_kinematik.rotation = 0.f;
	m_kinematik.geschwindigkeit = CHVector(0.f, 0.f, 0.f);
	//Steuerung
	m_steuerung.linear = CHVector(0.f, 0.f, 0.f);
	m_steuerung.angular = 0.f;

	return;
}

float Boid::getMaxSteuerungsKraft(){
	return maxSteuerungskrafts;
}
float Boid::getMaxGeschwindigkeit(){
	return maxGeschwindigkeit;
}

void Boid::uiSteuerung(CDeviceKeyboard *zdKeyboard){
	m_zdKeyboard = zdKeyboard;


	if (m_zdKeyboard->KeyUp(DIK_LEFT)){
		this->getSteuerung()->linear += CHVector(-0.1, 0.0, 0.0);
	}
	else if (m_zdKeyboard->KeyUp(DIK_RIGHT)){
		this->getSteuerung()->linear += CHVector(0.1, 0.0, 0.0);
	}
	else if (m_zdKeyboard->KeyUp(DIK_UP)){
		this->getSteuerung()->linear += CHVector(0.0, 0.0, 0.1);
	}
	else if (m_zdKeyboard->KeyUp(DIK_DOWN)){
		this->getSteuerung()->linear += CHVector(0.0, 0.0, -0.1);
	}
}

void Boid::setMaterial(){
	m_gBody.SetMaterial(&m_m);
	m_gHead.SetMaterial(&m_m);
}

void Boid::setMaterialTarget() {
	m_gBody.SetMaterial(&m_mTarget);
	m_gHead.SetMaterial(&m_mTarget);
}
