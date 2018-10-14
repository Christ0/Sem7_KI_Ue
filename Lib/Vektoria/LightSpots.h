#pragma once

#include "LightSpot.h"

//------------------------------------
// CLightSpots, Pluralklasse von CLightSpot
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CLightSpots
{
	friend class CPlacement;
public:
	CLightSpots();
	~CLightSpots();
	void Copy(CLightSpots & lightspots);

	CLightSpots operator=(CLightSpots & lightspots);

	void Init();
	void Tick(CHMat & m, int & iTick);
	void Fini();

	void Add(CLightSpot * plightspot);
	bool Sub(CLightSpot * plightspot);

	CLightSpot * Make(CColor color, float fInnerAngle, float fOuterAngle, float fIntensity);
	bool Kill(CLightSpot * plightspot);

	void Draw(CHMat & mGlobal);






	CLightSpot ** m_aplightspot;
	int m_iLightSpotAllocs;
	int m_iAllocBlock;
	int m_iLightSpots;
};

}