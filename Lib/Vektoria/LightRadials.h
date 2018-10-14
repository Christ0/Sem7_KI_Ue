#pragma once

#include "LightRadial.h"

//------------------------------------
// CLightRadials, Pluralklasse von CLightRadial
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CLightRadials
{
	friend class CPlacement;
protected:
	void Tick(CHMat & m, int & iTick);
public:
	CLightRadials();
	~CLightRadials();

	void Copy(CLightRadials & lightradials);
	CLightRadials operator=(CLightRadials & lightradials);

	void Init();
	void Fini();

	void Add(CLightRadial * plightradial);
	bool Sub(CLightRadial * plightradial);

	CLightRadial * Make(CColor color);
	bool Kill(CLightRadial * plightradial);

	CLightRadial ** m_aplightradial;
	int m_iLightRadialAllocs;
	int m_iAllocBlock;
	int m_iLightRadials;
protected:
	void Draw(CHMat & mGlobal);
};

}