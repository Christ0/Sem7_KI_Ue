#include "StdAfx.h"
#include "Spielfeld.h"

Spielfeld::Spielfeld()
{
	m_m.MakeTextureDiffuse("textures\\green_image.jpg");

	m_dimension.x = 40.f;
	m_dimension.z = 25.f;
	m_pose.x = 0.f;
	m_pose.y = -1.f;
	//m_p.Translate(m_pose.x, m_pose.y, 0.f);

	m_g.Init(m_dimension.x, m_dimension.z, &m_m);
	m_spielbrett.AddGeo(&m_g);

	m_spielbrett.RotateX(DEGREES_TO_RADIANS(-90));
	m_spielbrett.TranslateDelta(m_pose.x, m_pose.y, 0.f);
	m_p.AddPlacement(&m_spielbrett);
	m_tierpfleger.reset(CHVector());
}


Spielfeld::~Spielfeld()
{
	

}

void Spielfeld::Tick(float fTime, float fTimeDelta){
	
}
Boid* Spielfeld::getFutterPlatz(){
	return &m_tierpfleger;
}

CPlacement * Spielfeld::getPlacement(){
	return &m_p;
}

CHVector * Spielfeld::getDimension(){
	return &m_dimension;
}

CHVector * Spielfeld::getPose(){
	return &m_pose;
}
