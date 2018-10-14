#pragma once
#include <Windows.h> // Für "HWND"
#include <stdio.h> // Für "FILE"

//---------------------------------------------------
// CApiInput - Schnittstelle für alle Input-Module
//
// Autoren  : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt) 
//---------------------------------------------------

namespace Vektoria
{

	// Input-API:
	enum EApiInput
	{
		eApiInput_Null,				// Nullinput.
		eApiInput_DirectInput,		// DirectInput8.
		eApiInput_SDL,				// SDL, Noch nicht implementiert 
		eApiInput_Own				// Falls man eine eigene DLL schreiben will 
	};

	class CApiInput
	{
	public:

		//-----------------------
		// Schnittstellenroutinen
		//-----------------------

		// Geburt, Leben und Sterben:
		virtual void Init(HWND hwnd, int iWidthWindow, int iHeightWindow) = 0;
		virtual void Tick() = 0;
		virtual void Fini() = 0;

		virtual void ReSize(int iWidthWindow, int iHeightWindow) = 0;

		// Log-File & Debug:
		virtual void SetLogFileData(FILE * pfile, unsigned int uStartTime, char * acFile) = 0;

		// Create & Delete Devices:
		virtual bool CreateDeviceKeyboard(unsigned int & idDevice) = 0;
		virtual bool CreateDeviceMouse(unsigned int & idDevice) = 0;
		virtual bool CreateDeviceGameController(unsigned int & idDevice) = 0;
		virtual void DeleteDevice(unsigned int & idDevice) = 0;

		// Abfrage:
		virtual bool IsPressed(unsigned int & idDevice, int iButton) = 0;
		virtual bool IsDown(unsigned int & idDevice, int iButton) = 0;
		virtual bool IsUp(unsigned int & idDevice, int iButton) = 0;

		virtual bool GetCoordinatesAbsolute(unsigned int & idDevice, float & fx, float & fy, float & fz) = 0;
		virtual bool GetCoordinatesRelative(unsigned int & idDevice, float & fx, float & fy, float & fz) = 0;

		virtual void SetSensitivity(unsigned int & idDevice, float fSensitivity) = 0; // Setzt die Empfindlichkeit
		virtual float GetSensitivity(unsigned int & idDevice) = 0; // Gibt die Empfindlichkeit aus

		virtual void SetInvertedYAxisOn(unsigned int & idDevice) = 0; // Y-Achse invertieren
		virtual void SetInvertedYAxisOff(unsigned int & idDevice) = 0; // Y-Achse nicht invertieren

		virtual float GetAbsoluteX(unsigned int & idDevice) = 0;
		virtual float GetAbsoluteY(unsigned int & idDevice) = 0;

		virtual float GetRelativeX(unsigned int & idDevice) = 0;
		virtual float GetRelativeY(unsigned int & idDevice) = 0;
		virtual float GetRelativeZ(unsigned int & idDevice) = 0;

		virtual float GetRelativeRX(unsigned int & idDevice) = 0;
		virtual float GetRelativeRY(unsigned int & idDevice) = 0;
		virtual float GetRelativeRZ(unsigned int & idDevice) = 0;

		virtual float GetSliderMain(unsigned int & idDevice) = 0; // Gibt die Stellung des Hauptsliders an
		virtual float GetSliderVice(unsigned int & idDevice) = 0; // Gibt die Stellung des Nebensliders an

		virtual bool POV1Pressed(unsigned int & idDevice) = 0;
		virtual bool POV2Pressed(unsigned int & idDevice) = 0;
		virtual bool POV3Pressed(unsigned int & idDevice) = 0;
		virtual bool POV4Pressed(unsigned int & idDevice) = 0;

		virtual float GetAnglePOV1(unsigned int & idDevice) = 0; // Gibt die Stellung der Point of View-Taste 1 im Bogenmaß an
		virtual float GetAnglePOV2(unsigned int & idDevice) = 0; // Gibt die Stellung der Point of View-Taste 2 im Bogenmaß an
		virtual float GetAnglePOV3(unsigned int & idDevice) = 0; // Gibt die Stellung der Point of View-Taste 3 im Bogenmaß an
		virtual float GetAnglePOV4(unsigned int & idDevice) = 0; // Gibt die Stellung der Point of View-Taste 4 im Bogenmaß an

		virtual void SetJoyRange(unsigned int & idDevice, int iJoyRange) = 0;

	};

}