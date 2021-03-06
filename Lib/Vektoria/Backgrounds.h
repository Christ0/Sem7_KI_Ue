#pragma once

#include "Background.h"

//------------------------------------
// CBackgrounds, Pluralklasse von CBackground
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CBackgrounds
{
	friend class CViewport;
protected:
	void SetRoot(CRoot * proot);

public:
	CBackgrounds();
	~CBackgrounds();
	CBackgrounds operator=(CBackgrounds backgrounds);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CBackground * pbackground);
	bool Sub(CBackground * pbackground);

	CBackground * Make(CImage * pimage, CFloatRect & floatrect);
	bool Kill(CBackground * pbackground);

	void SetViewport(CViewport * pviewport);

	CBackground * PickBackground(float frxViewport, float fryViewport, float &fLayerDistance);
	void PickBackgrounds(float frxViewport, float fryViewport, CBackgrounds * pzbs);


	CBackground ** m_apbackground;
	int m_iBackgroundAllocs;
	int m_iAllocBlock;
	int m_iBackgrounds;
	CViewport * m_pviewport;


};

}