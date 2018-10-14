#pragma once
#include "Node.h"
#include "ApiInput.h"

//--------------------------------------------------------------------------------------------
// CDeviceMouse: Klasse für die Mausbehandlung in 3D-Applikationen 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{
	class CFrame;

class CDeviceMouse : public CNode
{
public:
	// --------------
	// Basismethoden:
	// --------------

	///<summary> Konstruktor</summary>
	CDeviceMouse();

	///<summary> Destruktor.</summary>
	~CDeviceMouse();

	///<summary> Setzt die Empfindlichkeit für die relativen Abfragemethoden.</summary>
    void SetSensitivity(float fSensitivity=0.0005f); 

	///<summary> Gibt die Empfindlichkeit der relativen Abfragemethoden aus.</summary>
    float GetSensitivity(); 

	///<summary> Invertiert die Y-Achse.</summary>
    void SetInvertedYAxisOn(); 

	///<summary> Die Y-Achse soll nicht invertiert werden (default).</summary>
	void SetInvertedYAxisOff(); 

	///<summary> Gibt relative Mausbewegung in X-Richtung aus.</summary>
	float GetRelativeX(); 

	///<summary> Gibt relative Mausbewegung in Y-Richtung aus.</summary>
	float GetRelativeY(); 

	///<summary> Gibt relative Mausradbewegung (Z-Richtung) aus.</summary>
	float GetRelativeZ(); 

	///<summary> Gibt absolute Mausbewegung in X-Richtung aus (in Mickeys).</summary>
    float GetAbsoluteX(); 

	///<summary> Gibt absolute Mausbewegung in X-Richtung aus (in Mickeys).</summary>
    float GetAbsoluteY(); 

	///<summary> true, falls Taste iButton (Tastennummer gemäß DirectX) gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonPressed(int iButton);

	///<summary> true, falls linke Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonPressedLeft(); 

	///<summary> true, falls mittlere Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonPressedMid(); 

	///<summary> true, falls rechte Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonPressedRight(); 

	///<summary> einmal true, falls Taste iButton (Tastennummer gemäß DirectX) gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonDown(int iButton);

	///<summary> einmal true, falls linke Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonDownLeft(); 

	///<summary> einmal true, falls mittlere Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonDownMid(); 

	///<summary> einmal true, falls rechte Maustaste gedrückt wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonDownRight(); 

	///<summary> einmal true, falls Taste iButton (Tastennummer gemäß DirectX) losgelassen wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonUp(int iButton);

	///<summary> einmal true, falls linke Maustaste losgelassen wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonUpLeft(); 

	///<summary> einmal true, falls mittlere Maustaste losgelassen wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonUpMid(); 

	///<summary> einmal true, falls rechte Maustaste losgelassen wurde, ansonsten false (synchrone Mausklickabfragemethode).</summary>
	bool ButtonUpRight(); 

	///<summary> Wird vom übergeordneten Frame automatisch aufgerufen wenn sich die Größe des Bildschirms verändert hat.</summary>
	void ReSize(int iWidthWindow, int iHeightWindow); 

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Schnittstellennummer der Mouse.</summary>
	unsigned int m_idForInterface;

	//	///<summary> Pointer auf die Input-API.</summary>
	//	CApiInput * m_papiinput;

	///<summary> Pointer auf den übergeordneten Frame.</summary>
	CFrame * m_pframe;

	///<summary> Art der Input-API</summary>
	int m_eApiInput;

	///<summary> Flag, ob GameController erzeugt werden konnte.</summary>
	bool m_bCreated;

};

}