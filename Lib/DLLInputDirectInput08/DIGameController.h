#pragma once
#include "DIDevice.h"
#include "DIFoundController.h"

namespace Vektoria
{

class CDIGameController // : public CDIDevice
{
public:
	CDIGameController(void);
	~CDIGameController(void);


	bool Init(); // Initialisiert den Game Controller
	void Tick(void); // Muss jeden Tick aufgerufen werden um den device state zu aktualisieren
	void Fini();

	void SetSensitivity(float fSensitivity); // Setzt die Empfindlichkeit
    float GetSensitivity(void); // Gibt die Empfindlichkeit aus

    void SetInvertedYAxisOn(void); // Y-Achse invertieren
    void SetInvertedYAxisOff(void); // Y-Achse nicht invertieren

	float GetRelativeX(void);
	float GetRelativeY(void);
	float GetRelativeZ(void);

	float GetRelativeRX(void);
	float GetRelativeRY(void);
	float GetRelativeRZ(void);


	float GetSliderMain(void); // Gibt die Stellung des Hauptsliders an
	float GetSliderVice(void); // Gibt die Stellung des Nebensliders an

	bool POV1Pressed();
	bool POV2Pressed();
	bool POV3Pressed();
	bool POV4Pressed();

	float GetAnglePOV1(); // Gibt die Stellung der Point of View-Taste 1 im Bogenmaﬂ an
	float GetAnglePOV2(); // Gibt die Stellung der Point of View-Taste 2 im Bogenmaﬂ an
	float GetAnglePOV3(); // Gibt die Stellung der Point of View-Taste 3 im Bogenmaﬂ an
	float GetAnglePOV4(); // Gibt die Stellung der Point of View-Taste 4 im Bogenmaﬂ an

	void SetJoyRange(int iJoyRange);

	bool ButtonPressed(unsigned int uButton); // true, falls Taste uButton (Tastennummer gem‰ﬂ DirectX) gedr¸ckt ist, ansonsten false
	bool ButtonDown(unsigned int uButton); // einmal true, falls Taste uButton (Tastennummer gem‰ﬂ DirectX) heruntergedr¸ckt wurde, ansonsten false
	bool ButtonUp(unsigned int uButton); // einmal true, falls Taste uButton (Tastennummer gem‰ﬂ DirectX) heruntergedr¸ckt wurde, ansonsten false

	DIJOYSTATE2* GetState(void); 

	CDIFoundController * m_pdifoundcontroller; 
	float m_fSensitivity; // Gamecontrollerempfindlichkeit
	bool m_bInvertedY; // Invertierte Y-Achse

	bool m_abButtonPressed[128];
private:





	/*
	//////////////////////////////////////////////////////////////////////
	// Used for Force Feed Back, Not Yet Implemented
	//////////////////////////////////////////////////////////////////////
	LPDIRECTINPUTEFFECT  m_lpTriggerEffect; // For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpStickyEffect; // For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpResistEffect; // For Force Feedback Effects
	bool m_TriggerOK;
	BOOL bHasForceFeedback;	// Is device Force Feedback Compatible?
	GUID m_TriggerGuid;	// GUID For Force Feed Back Device?

	GUID m_guidEffext;               // GUID for the selected effect


	*/
};

}