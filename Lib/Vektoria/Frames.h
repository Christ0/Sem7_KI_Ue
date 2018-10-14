#pragma once

#include "Frame.h"

//------------------------------------
// CFrames, Pluralklasse von CFrame
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CFrames
{
	friend class CRoot;
	friend class CHardware;
protected:
	void Tick(int & iTick);
public:
	CFrames();
	~CFrames();
	CFrames operator=(CFrames & frames);

	void Init(bool bLocal = true);
	void Fini();

	void Add(CFrame * pframe);
	bool Sub(CFrame * pframe);
	bool AddOnce(CFrame * pframe);

	bool Has(CFrame * pframe);

	CFrame * Make(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), EApiRender eApiRender, EApiInput eApiInput);
	bool Kill(CFrame * pframe);

	CFrame ** m_apframe;
	int m_iFrameAllocs;
	int m_iAllocBlock;
	int m_iFrames;

	void SetRoot(CRoot * proot);

	CRoot * m_proot;
	bool m_bHasOneRemote;

};

}