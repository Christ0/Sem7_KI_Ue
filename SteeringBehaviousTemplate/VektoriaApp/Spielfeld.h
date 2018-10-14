#pragma once
#include "Vektoria\Root.h"
#include "Boid.h"

using namespace Vektoria;


class Spielfeld
{
public:
	Spielfeld();
	
	~Spielfeld();
	CPlacement * getPlacement();
	CHVector * getDimension();
	CHVector * getPose();

	void Init(int xdim, int zdim);
	void Tick(float fTime, float fTimeDelta);
	//Objekte
	Boid* getFutterPlatz();

	private:

	CGeoQuad m_g;
	CMaterial m_m;

	CPlacement m_p;
	CPlacement m_spielbrett;
	CHVector m_dimension;
	CHVector m_pose;
	
	//Objekte
	Boid m_tierpfleger;
};

