#pragma once

#include "Viewport.h"

//------------------------------------
// CViewports, Pluralklasse von CViewport
// 
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CViewports
{
public:
	CViewports();
	~CViewports();
	CViewports operator=(CViewports viewports);

	void Init();
	void Tick(float & fTimeDelta, int & iTick);
	void Fini();

	void Add(CViewport * pviewport);
	bool Sub(CViewport * pviewport);

	void Add(CViewports * pviewports);
	bool Has(CViewport * pviewport);

	CViewport * Make(CCamera * pcamera, float frx, float fry, float frWidth, float frHeight);
	bool Kill(CViewport * pviewport);


	CViewport * Get(unsigned int id); // Gibt einen Pointer auf denjenigen Viewport mit der entsprechenden ID zurück, falls nicht in der Liste vorhanden, wird ein Nullptr ausgegeben.	

	bool AddOnce(CViewport * pviewport);
	bool AddOnce(CViewports * pviewports);


	void ReSize();

	CViewport ** m_apviewport;
	int m_iViewportAllocs;
	int m_iAllocBlock;
	int m_iViewports;
	CFrame * m_pframe;
	void SetRoot(CRoot * proot);
	void SetFrame(CFrame * pframe);
	CRoot * m_proot;

};

}