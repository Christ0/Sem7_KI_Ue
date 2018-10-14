#pragma once
#include "Hardware.h"

//------------------------------------
// CHardwares, Pluralklasse von CHardware
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CHardwares
{
protected: 
	void Tick(int & iTick);
public:
	CHardwares();
	~CHardwares();
	CHardwares operator=(CHardwares & hardwares);


	void Init();
	void Fini();

	void Add(CHardware * phardware);
	bool Sub(CHardware * phardware);

	CHardware * Make(char * acAddress);
	bool Kill(CHardware * phardware);

	CHardware ** m_aphardware;
	int m_iHardwareAllocs;
	int m_iAllocBlock;
	int m_iHardwares;

	void SetRoot(CRoot * proot);
	CRoot * m_proot;
};

}