#pragma once

//------------------------------------
// CDevice
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.08.2013
// Copyright: Moyzelle Vektoria
//------------------------------------


class CDevice
{
public:
	CDevice();
	~CDevice();
	CDevice operator=(CDevice device);
	void Copy(CDevice device);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

};
