///////////////////////////////////////////////////////////////////
// Autor: Prof. Dr. Tobias Breiner
// DIFoundController.h: Interface für diverse Game Controller via Direct input 
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "DIDevice.h"

namespace Vektoria
{

class CDIFoundController : public CDIDevice
{
public:
	CDIFoundController(void);
	~CDIFoundController(void);

	bool Init(HINSTANCE hinst, HWND hwnd, LPDIRECTINPUT8 lpDI); // Initialisiert den Game Controller
   	void Tick(void); // Muss jeden Tick aufgerufen werden um den device state zu aktualisieren

	void SetJoyRange(int iRange);


	DIJOYSTATE2* GetJoystickStateInfo(void) {return &m_DIJoyState;};
	DIJOYSTATE2 m_DIJoyState; // Game Controller Statusinformation

	/*
	void EnumEffects();
	static bool CALLBACK DIEnumEffectsCallback(LPCDIEFFECTINFO pdei, LPVOID pvRef);
	void AddEffectInfo(); 
	*/
	int m_iJoyRange;
	float m_fJoyRangeInv;
private:

	//////////////////////////////////////////////////////////////////////
	// Used for Force Feed Back, Not Yet Implemented
	//////////////////////////////////////////////////////////////////////
	LPDIRECTINPUTEFFECT  m_lpTriggerEffect; // For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpStickyEffect; // For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpResistEffect; // For Force Feedback Effects
	bool m_TriggerOK;
	BOOL m_FFAvailable;	// Is device Force Feedback Compatible?
	GUID m_TriggerGuid;	// GUID For Force Feed Back Device?

};

}