#pragma once

#include "DeviceVRController.h"

//------------------------------------
// CDeviceVRControllers, Pluralklasse von CDeviceVRController
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.201
// Copyright: Moyzelle Vektoria
//------------------------------------


namespace Vektoria
{
	class CDeviceVRControllers
	{
	public:
		CDeviceVRControllers();
		~CDeviceVRControllers();
		CDeviceVRControllers operator=(CDeviceVRControllers & devicevrcontrollers);

		/*
		void Init();
		void Tick(float & fTimeDelta);
		void Fini();
		*/
		void Add(CDeviceVRController * pdevicevrcontroller);
		bool Sub(CDeviceVRController * pdevicevrcontroller);

		CDeviceVRController * Make();
		bool Kill(CDeviceVRController * pdevicevrcontroller);

		CDeviceVRController ** m_apdevicevrcontroller;
		int m_iDeviceVRControllerAllocs;
		int m_iAllocBlock;
		int m_iDeviceVRControllers;
	};
}