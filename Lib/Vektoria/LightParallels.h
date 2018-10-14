#pragma once

#include "LightParallel.h"

//------------------------------------
// CLightParallels, Pluralklasse von CLightParallel
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CLightParallels
{
	friend class CScene;
protected:
	void Tick(CHMat & m, int & iTick);

public:
	CLightParallels();
	~CLightParallels();
	CLightParallels operator=(CLightParallels & parallellights);

	void Init();
	void Fini();

	void Add(CLightParallel * plightparallel);
	bool Sub(CLightParallel * plightparallel);

	CLightParallel * Make(CHVector vDirection, CColor color);
	bool Kill(CLightParallel * plightparallel);

	CLightParallel ** m_aplightparallel;
	int m_iLightParallelAllocs;
	int m_iAllocBlock;
	int m_iLightParallels;
	void Draw();

};

}