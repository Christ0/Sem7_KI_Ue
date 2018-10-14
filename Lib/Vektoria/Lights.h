#pragma once

#include "Light.h"
#include "../VektoriaMath/HMat.h"

//------------------------------------
// CLights, Pluralklasse von CLight
// Copyright: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CLights
{
	friend class CScene;
	friend class CVektoriaClient;

protected: 
	void Tick(CHMat &m, int & iTick);

public:
	CLights();
	~CLights();
	CLights operator=(CLights lights);

	void Init();
	void Fini();

	void Add(CLight * plight);
	bool Sub(CLight * plight);

	CLight * Make(CColor pcolor);
	bool Kill(CLight * plight);

	CLight ** m_aplight;
	int m_iLightAllocs;
	int m_iAllocBlock;
	int m_iLights;

	CLight * Get(unsigned int id); // Gibt einen Pointer auf dasjenige licht mit der entsprechenden ID zurück, falls nicht in der Liste vorhanden, wird ein Nullptr ausgegeben.	
	CLight * GetByIdLight(unsigned int & idLight); // Gibt einen Pointer auf dasjenige licht mit der entsprechenden ID zurück, falls nicht in der Liste vorhanden, wird ein Nullptr ausgegeben.	

};

}