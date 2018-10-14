#pragma once

#include "DIGameController.h"

//------------------------------------
// CDIGameControllers, Pluralklasse von CDIGameController
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CDIGameControllers
{
public:
	CDIGameControllers();
	~CDIGameControllers();
	CDIGameControllers operator=(CDIGameControllers digamecontrollers);

	void Init(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI);
	void Tick();
	void Fini();

	void Add(CDIGameController * pdigamecontroller);
	bool Sub(CDIGameController * pdigamecontroller);

	CDIGameController * Make();
	bool Kill(CDIGameController * pdigamecontroller);

	CDIGameController ** m_apdigamecontroller;
	int m_iDIGameControllerAllocs;
	int m_iAllocBlock;
	int m_iDIGameControllers;
};
}
