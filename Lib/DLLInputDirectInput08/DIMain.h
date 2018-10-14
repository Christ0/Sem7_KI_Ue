#pragma once
#define DIRECTINPUT_VERSION 0x0800
//----------------------------------
// Autor: Prof.- Dr. Tobias Breiner
// 
// Vektoria UG (haftungsbeschränkt)
//----------------------------------
#include "dinput.h"
#include "DIFoundControllers.h"
#include "DIGameControllers.h"
#include "DIMouse.h"
#include "DIKeyboard.h"
#include "..\Vektoria\ApiInput.h"

namespace Vektoria
{
	enum EDeviceKind
	{
		eDeviceKind_No,
		eDeviceKind_Keyboard,
		eDeviceKind_Mouse,
		eDeviceKind_GameController
	};


struct SDeviceInfo
{
	int id;
	EDeviceKind eDeviceKind;
	void * pvDevice;
};

class CDIMain: public CApiInput // TODO Klasse müsste eigentlich CDevices heißen und in Core hinein, Members CDI... müssten in CDIMain... umgewandelt werden.
{
public:
	CDIMain(void);
	~CDIMain(void);

	// --------------------------
	// BEGIN Schnittstellenroutinen
	// --------------------------

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

	float GetAnglePOV1(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 1 im Bogenmaß an
	float GetAnglePOV2(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 2 im Bogenmaß an
	float GetAnglePOV3(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 3 im Bogenmaß an
	float GetAnglePOV4(unsigned int & idDevice); // Gibt die Stellung der Point of View-Taste 4 im Bogenmaß an

	void SetJoyRange(unsigned int & idDevice, int iJoyRange);

	// --------------------------
	// END Schnittstellenroutinen
	// --------------------------












//	void ReSize(int & iWidthWindow, int & iHeightWindow);
	
	bool AddKeyboard(CDIKeyboard * pdikeyboard);
 	bool AddMouse(CDIMouse * pdimouse);
	bool AddGameController(CDIGameController * pdigamecontroller);

    bool m_bDIInit; // Wurde Direct Input ergolgreich initialsiert?
    bool m_bDIKeyboardInit; // Wurde die Tastatur erfolgreich initialsiert?
	bool m_bDIMouseInit; // Wurde die Maus erfolgreich Initialisiert?
 	bool m_bEnumerated; // Wurde schon nach Game Controller Geräten gesucht?

    bool StartEnumeration(void); // Startet das Aufzählen der vorhandenen Geräte
    CDIKeyboard* GetKeyboard(void); // Gibt einen Pointer auf die System-Tastatur zurück
    CDIMouse* GetMouse(void); // Gibt einen Pointer auf die System-Maus zurück


	SDeviceInfo * m_adeviceinfo; 
	int m_iDevices;


private:
    HINSTANCE m_hInstance;
    HWND m_hwnd;

    DWORD m_dwScreenWidth; // Screenbreite
    DWORD m_dwScreenHeight; // Screenhöhe

	CDIMouse* m_pdimouse; // System-Maus
	CDIKeyboard* m_pdikeyboard; // System-Tastatur
	CDIFoundControllers m_difoundcontrollers; // Angeschlossene Game Controller
	CDIGameControllers m_digamecontrollers;   // Geaddete Game Gontroller

	// TODO: Diese Sachen müssten eigentlich in CDIDevice rein:
	LPDIRECTINPUT8 m_lpDI; // Direct Input Interface
    bool InitDirectInput(void);
    static BOOL CALLBACK EnumDevsCallback(LPDIDEVICEINSTANCE lpddi, LPVOID pvRef); // Callback Funktion um die Geräte aufzuzählen
	void AddDeviceInfo(LPCDIDEVICEINSTANCE lpddi); // Fügt die Device Info dem Gerät hinzu
};

}