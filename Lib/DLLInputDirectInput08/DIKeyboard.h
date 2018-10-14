// DIKeyboard.h: interface for the CDIKeyboard class
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "DIDevice.h"
#include "..\Vektoria\Placement.h"

#define KEYBOARD_BUFFERSIZE 256

namespace Vektoria
{

class CDIKeyboard : public CDIDevice
{
public:
    CDIKeyboard(void);
    ~CDIKeyboard(void);

    bool Init(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI); // Initialisiert die Tastatur
	void Tick(void); // Muss jeden Tick aufgerufen werden um den device state zu aktualisieren

    bool KeyPressed(int iKey); // true, falls Taste iKey (Tastaturnummer gemäß DirectX) gedrückt wurde, ansonsten false
	bool KeyDown(int iKey); // einmal true, falls Taste iKey (Tastaturnummer gemäß DirectX) im letzten Tick heruntergedrückt wurde, ansonsten false
	bool KeyUp(int iKey); // einmal true, falls Taste iKey (Tastaturnummer gemäß DirectX) im letzten Tick losgelassen wurde, ansonsten false

	// TODO: Raus, da sinnlos:
	/*
	int GetKey(void); 
    char GetChar(int iKey);
	void GetMove(int &riAD, int &riSW, int &riFR, int &riLeftRight, int &riUpDown, int &riPageUpDown, bool &rbSpace); // Hilfmethode für WASD-Steuerungen
	*/
	float GetRelativeX(); // Hilfmethode für WASD-Steuerungen
	float GetRelativeY(); // Hilfmethode für WASD-Steuerungen
	float GetRelativeZ(); // Hilfmethode für WASD-Steuerungen
	float GetRelativeRX(); // Hilfmethode für WASD-Steuerungen
	float GetRelativeRY(); // Hilfmethode für WASD-Steuerungen
	float GetRelativeRZ(); // Hilfmethode für WASD-Steuerungen


private:
    BYTE m_abyte[KEYBOARD_BUFFERSIZE];
	BYTE m_abyteLast[KEYBOARD_BUFFERSIZE];
};

}