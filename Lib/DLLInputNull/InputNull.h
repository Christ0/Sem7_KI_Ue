#pragma once
#include "..\Vektoria\ApiInput.h"

namespace Vektoria
{
	class CInputNull : public CApiInput
	{
	public:

		//-----------------------
		// Schnittstellenroutinen
		//-----------------------

		// Geburt, Leben und Sterben:
		void Init(HWND hwnd, int iWidthWindow, int iHeightWindow);
		void Tick();
		void Fini();

		void ReSize(int iWidthWindow, int iHeightWindow);

		// Log-File & Debug:
		void SetLogFileData(FILE * pfile, unsigned int uStartTime, char * acFile);

		// Create & Delete Devices:
		bool CreateDeviceKeyboard(unsigned int & idDevice);
		bool CreateDeviceMouse(unsigned int & idDevice);
		bool CreateDeviceGameController(unsigned int & idDevice);
		void DeleteDevice(unsigned int & idDevice);

		// Abfrage:
		bool IsPressed(unsigned int & idDevice, int iButton);
		bool IsDown(unsigned int & idDevice, int iButton);
		bool IsUp(unsigned int & idDevice, int iButton);

		bool GetCoordinatesAbsolute(unsigned int & idDevice, float & fx, float & fy, float & fz);
		bool GetCoordinatesRelative(unsigned int & idDevice, float & fx, float & fy, float & fz);

		void SetSensitivity(unsigned int & idDevice, float fSensitivity); // Setzt die Empfindlichkeit
		float GetSensitivity(unsigned int & idDevice); // Gibt die Empfindlichkeit aus

		void SetInvertedYAxisOn(unsigned int & idDevice); // Y-Achse invertieren
		void SetInvertedYAxisOff(unsigned int & idDevice); // Y-Achse nicht invertieren

		float GetAbsoluteX(unsigned int & idDevice);
		float GetAbsoluteY(unsigned int & idDevice);

		float GetRelativeX(unsigned int & idDevice);
		float GetRelativeY(unsigned int & idDevice);
		float GetRelativeZ(unsigned int & idDevice);

		float GetRelativeRX(unsigned int & idDevice);
		float GetRelativeRY(unsigned int & idDevice);
		float GetRelativeRZ(unsigned int & idDevice);

		float GetSliderMain(unsigned int & idDevice); // Gibt die Stellung des Hauptsliders an
		float GetSliderVice(unsigned int & idDevice); // Gibt die Stellung des Nebensliders an

		bool POV1Pressed(unsigned int & idDevice);
		bool POV2Pressed(unsigned int & idDevice);
		bool POV3Pressed(unsigned int & idDevice);
		bool POV4Pressed(unsigned int & idDevice);

		float GetAnglePOV1(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 1 im Bogenmaﬂ an
		float GetAnglePOV2(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 2 im Bogenmaﬂ an
		float GetAnglePOV3(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 3 im Bogenmaﬂ an
		float GetAnglePOV4(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 4 im Bogenmaﬂ an

		void SetJoyRange(unsigned int & idDevice, int iJoyRange);

	};

}
