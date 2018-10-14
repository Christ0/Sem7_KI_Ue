#pragma once

#include "Device.h"

//------------------------------------
// CDevices, Pluralklasse von CDevice
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

class CDevices
{
public:
	CDevices();
	~CDevices();
	CDevices operator=(CDevices devices);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CDevice * pdevice);
	bool Sub(CDevice * pdevice);

	CDevice * Make();
	bool Kill(CDevice * pdevice);

	CDevice ** m_apdevice;
	int m_iDeviceAllocs;
	int m_iAllocBlock;
	int m_iDevices;
};
