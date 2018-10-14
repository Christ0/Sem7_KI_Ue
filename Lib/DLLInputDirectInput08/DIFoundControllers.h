#pragma once

#include "DIFoundController.h"

//------------------------------------
// CDIFoundControllers, Pluralklasse von CDIFoundController
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CDIFoundControllers
{
public:
	CDIFoundControllers();
	~CDIFoundControllers();
	CDIFoundControllers operator=(CDIFoundControllers difoundcontrollers);

	void Init();
	void Tick();
	void Fini();

	void Add(CDIFoundController * pdifoundcontroller);
	bool Sub(CDIFoundController * pdifoundcontroller);

	CDIFoundController * Make(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI);
	bool Kill(CDIFoundController * pdifoundcontroller);

	CDIFoundController ** m_apdifoundcontroller;
	int m_iDIFoundControllerAllocs;
	int m_iAllocBlock;
	int m_iDIFoundControllers;
};
}
