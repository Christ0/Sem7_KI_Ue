#pragma once
#include "Node.h"
#include "ApiInput.h"

//--------------------------------------------------------------------------------------------
// CDeviceMouse: Klasse f�r die Mausbehandlung in 3D-Applikationen 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

	class CFrame;

class CDeviceGameController : public CNode
{
public:
	// --------------
	// Basismethoden:
	// --------------

	///<summary> Konstruktor.</summary>
	CDeviceGameController(); 

	///<summary> Destruktor.</summary>
	~CDeviceGameController(); 

	///<summary> Setzt die Empfindlichkeit des Game Controllers.</summary>
	///<param name= "fSensitivity"> Empfindlichkeit, je h�her desto Empfindlicher.</param>
	void SetSensitivity(float fSensitivity); 

	///<summary> Gibt die Empfindlichkeit aus.</summary>
    float GetSensitivity(); 

	///<summary> Y-Achse invertieren.</summary>
    void SetInvertedYAxisOn(); 

	///<summary> Y-Achse nicht invertieren (default).</summary>
	void SetInvertedYAxisOff(); 

	// ----------------
	// Auslesemethoden:
	// ----------------

	///<summary> Gibt die X-Richtung des Hauptkn�ppels aus (-1.0 ist links ... 0.0 ist Mitte ... 1.0 ist rechts).</summary>
	float GetRelativeX(); 

	///<summary> Gibt die Y-Richtung des Hauptkn�ppels aus(-1.0 bis +1.0, Ruhestelluzng = 0.0f).</summary>
	float GetRelativeY();  

	///<summary> Gibt die Z-Richtung des Hauptkn�ppels aus (-1.0 bis +1.0, Ruhestelluzng = 0.0f).</summary>
	float GetRelativeZ(); 

	///<summary> Gibt die X-Richtung des R-Kn�ppels aus (-1.0 bis +1.0, Ruhestelluzng = 0.0f).</summary>
	float GetRelativeRX(); 

	///<summary> Gibt die Y-Richtung des R-Kn�ppels aus (-1.0 bis +1.0, Ruhestelluzng = 0.0f).</summary>
	float GetRelativeRY(); 	
	
	///<summary> Gibt die Z-Richtung des R-Kn�ppels aus (-1.0 bis +1.0, Ruhestelluzng = 0.0f).</summary> 
	float GetRelativeRZ(); 

	///<summary> Gibt die Stellung des Hauptsliders als Wert zwischen 0.0f und 1.0f an. (Die meisten Joysticks/Gamepads haben nur diesen einen Slider).</summary>
	float GetSliderMain(); 

	///<summary> Gibt die Stellung des Nebensliders als Wert zwischen 0.0f und 1.0f an. (Dieser Slider ist nur bei sehr exotischen Joysticks/Gamepads/Flightsticks vorhanden, trotzdem der Vollst�ndigkeit halber implementiert).</summary>
	float GetSliderVice(); 

	///<summary> Ist die Point of View-Taste 1 aus der Ruhestellung gedr�ckt? (Die meisten Joysticks/Gamepads haben nur diese eine POV-Taste).</summary>
	bool POV1Pressed(); 

	///<summary> Ist die Point of View-Taste 2 aus der Ruhestellung gedr�ckt?</summary>
	bool POV2Pressed();  

	///<summary> Ist die Point of View-Taste 3 aus der Ruhestellung gedr�ckt?</summary>
	bool POV3Pressed(); 

	///<summary> Ist die Point of View-Taste 4 aus der Ruhestellung gedr�ckt?</summary>
	bool POV4Pressed();  

	///<summary> Gibt die Orientierung der Point of View-Taste 1 im Bogenma� an. (Die meisten Joysticks/Gamepads haben nur diese eine POV-Taste)</summary>
	float GetAnglePOV1(); 

	///<summary> Gibt die Orientierung der Point of View-Taste 2 im Bogenma� an.</summary>
	float GetAnglePOV2(); 

	///<summary> Gibt die Orientierung der Point of View-Taste 3 im Bogenma� an.</summary>
	float GetAnglePOV3(); 

	///<summary> Gibt die Orientierung der Point of View-Taste 4 im Bogenma� an.</summary>
	float GetAnglePOV4(); 

	///<summary> Setzt den Wertebereich der Steuerung bzw. des Steuerkn�ppels.</summary>
	///<param name= "iJoyRange"> Wertebereich des Steuerkn�ppels.</param>
	void SetJoyRange(int iJoyRange);

	///<summary> Gibt true aus, falls Taste uButton gedr�ckt wurde, ansonsten false.</summary>
	///<param name= "uButton"> Tastennummer gem�� DirectX.</param>
	bool ButtonPressed(unsigned int uButton);

	///<summary> Gibt einmal true aus, falls Taste uButton gedr�ckt wurde, ansonsten false.</summary>
	///<param name= "uButton"> Tastennummer gem�� DirectX.</param>
	bool ButtonDown(unsigned int uButton);

	///<summary> Gibt einmal true aus, falls Taste uButton losgelassen wurde, ansonsten false.</summary>
	///<param name= "uButton"> Tastennummer gem�� DirectX.</param>
	bool ButtonUp(unsigned int uButton);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Schnittstellennummer der Mouse.</summary>
	unsigned int m_idForInterface;

	///<summary> Pointer auf den �bergeordneten Frame.</summary>
	CFrame * m_pframe;

	///<summary> Art der Input-Api, 0 = NullApi, 1=DirectInput, ...</summary>
	int m_eApiInput; 

	///<summary> Flag, ob GameController erzeugt werden konnte.</summary>
	bool m_bCreated;


};

}