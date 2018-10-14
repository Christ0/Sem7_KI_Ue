#pragma once
#include <stdio.h> // Für "FILE"
#include "..//VektoriaMath//HMat.h"

//---------------------------------------------------
// CApiCyberglasses - Schnittstelle für alle Cyberglasses-Module
//
// Autoren  : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt) 
//---------------------------------------------------

namespace Vektoria
{

	// Cyberglasses-API:
	enum EApiCyberglasses
	{
		eApiCyberglasses_None,				// Keine Videobrille soll angehängt werden (default)
		eApiCyberglasses_Null,				// NullCyberglasses
		eApiCyberglasses_OpenVR,			// OpenVR von Valve 
		eApiCyberglasses_Own				// Falls man eine eigene DLL schreiben will 
	};

	enum EHmdButtonKind
	{
		eHmdButtonKind_System = 0,
		eHmdButtonKind_ApplicationMenu = 1,
		eHmdButtonKind_DashboardBack = 2,
		eHmdButtonKind_Grip = 2,
		eHmdButtonKind_DPadLeft = 3,
		eHmdButtonKind_DPadUp = 4,
		eHmdButtonKind_DPadRight = 5,
		eHmdButtonKind_DPadDown = 6,
		eHmdButtonKind_A = 7,
		eHmdButtonKind_ProximitySensor = 31,
		eHmdButtonKind_Axis0 = 32,
		eHmdButtonKind_Axis1 = 33,
		eHmdButtonKind_Axis2 = 34,
		eHmdButtonKind_Axis3 = 35,
		eHmdButtonKind_Axis4 = 36,
		eHmdButtonKind_SteamVRTouchpad = 32,
		eHmdButtonKind_SteamVRTrigger = 33
	};



	class CApiCyberglasses
	{
	public:

		//-----------------------
		// Schnittstellenroutinen
		//-----------------------

		// Geburt, Leben und Sterben:
		virtual bool Init() = 0;
		virtual void Tick() = 0;
		virtual void Fini() = 0;

		// Log-File & Debug:
		virtual void SetLogFileData(FILE * pfile, unsigned int uStartTime, char * acFile) = 0;

		// Systentatusabfragen:
		virtual int GetEyePixelsX() = 0;
		virtual int GetEyePixelsY() = 0;
		virtual int GetNumControllers() = 0;

		// Matrixabfragen:
		virtual bool GetMatHMD(CHMat & m) = 0;
		virtual bool GetMatEyeLeft(CHMat & m) = 0;
		virtual bool GetMatEyeRight(CHMat & m) = 0;
		virtual bool GetMatProjLeft(CHMat & m, float & fNear, float & fFar) = 0;
		virtual bool GetMatProjRight(CHMat & m, float & fNear, float & fFar) = 0;
		virtual bool GetMatController(unsigned int & iController, CHMat & m) = 0;

		// Abfrage:
		virtual bool IsTouched(unsigned int & iController, EHmdButtonKind eButton) = 0;
		virtual bool IsPressed(unsigned int & iController, EHmdButtonKind eButton) = 0;
		virtual bool IsDown(unsigned int & iController, EHmdButtonKind eButton) = 0;
		virtual bool IsUp(unsigned int & iController, EHmdButtonKind eButton) = 0;

		// Koordinatenabfage:
		virtual float GetAbsoluteX(unsigned int & iController, int & iAxis) = 0;
		virtual float GetAbsoluteY(unsigned int & iController, int & iAxis) = 0;

		// Haptik:
		virtual void Haptic(unsigned int & iController, int & iAxis, float & fr) = 0;

		// Rendering:
		virtual void SetTextureEyeLeft(void * pRenderTexture) = 0;
		virtual void SetTextureEyeRight(void * pRenderTexture) = 0;

	};
}