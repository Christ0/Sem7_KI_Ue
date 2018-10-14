#pragma once
#include "Node.h"
#include "Placement.h"
#include "ApiInput.h"

//--------------------------------------------------------------------------------------------
// CDeviceMouse: Klasse für die Tastaturbehandlung in 3D-Applikationen 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{
	class CFrame;

class CDeviceKeyboard : public CNode
{
public:
	///<summary> Konstruktor.</summary>
	CDeviceKeyboard(void);

	///<summary> Destruktor.</summary>
	~CDeviceKeyboard(void);

	///<summary> Gibt true aus, falls Taste iKey (Tastaturnummer gemäß DirectX) gedrückt wurde, ansonsten false.</summary>
	bool KeyPressed(int iKey); 

	///<summary> Gibt einmal true aus, falls Taste iKey (Tastaturnummer gemäß DirectX) gerade im letzten Tick nach unten gedrückt wurde, ansonsten false.</summary>
	bool KeyDown(int iKey); 

	///<summary> Gibt einmal true aus, falls Taste iKey (Tastaturnummer gemäß DirectX) gerade im letzten Tick losgelassen wurde, ansonsten false.</summary>
	bool KeyUp(int iKey); 

	/*
	///<summary> Gibt die gedrückte Tastaturnummer (gemäß DirectX) zurück.<para></para> 
	///Achtung, fuktioniert naturgemäß nur, wenn nur eine einzige Taste gedrückt wurde!!!</summary>
	int GetKey(void); 

	///<summary> Gibt die gedrückte Tastaturnummer (gemäß DirectX) für Tasten, die einen char darstellen, zurück. (Ohne Strg, Return, etc.).<para></para>
	///Achtung 1: Fuktioniert naturgemäß nur, wenn nur eine einzige Taste gedrückt wurde!<para></para>
	///Achtung 2: Fuktioniert nur bei einer deutschen Tastatur, für ausländische Tastaturen muss man seine eigene Funktion schreiben!</summary>
	///<param name="iKey">Tastennummer Beispiel bei iKey = DIK_BACKSLASH wird '#' zurückgegeben.</param>
	char GetChar(int iKey);
	*/

	///<summary> WASD Steuerung.  Falls Space Taste gedrückt wurde, wird true ausgegeben.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
	virtual bool PlaceWASD(CPlacement & placementCamera, float & fTimeDelta, bool bEarth = false);

	///<summary> WASD Steuerung mit Kollisionserkennung.  Falls die Kamera kolliderte, hält sie an, und die Methode gibt true aus.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="zgsCollisionItems">Liste von Geometrien, mit denen die Kamera kollidieren kann</param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
	virtual bool PlaceWASDWithCollisionDetection(CPlacement & placementCamera, CGeos & zgsCollisionItems, float & fTimeDelta, bool bEarth = false);

	///<summary> WASD Steuerung um ein Zentrum. Falls Leertaste gedrückt wurde, wird true ausgegeben.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="placementCenter">Zentrales Placement, um das sich die Kamera bewegen soll. </param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bRot">Flag, wenn true kann man mit den Pfeiltasten vom Zentraum wegschwenken </param>
	virtual bool PlaceWASDPan(CPlacement & placementCamera, CPlacement & placementCenter, float & fTimeDelta, bool bRot = false);

	///<summary> Hilfsroutine für eigene WASD-Steuerungen.</summary>
	///<param name="rfAD">Wird -1 bei Druck auf Taste A und 1 bei Druck auf Taste D, ansonsten 0</param>
	///<param name="rfSW">Wird -1 bei Druck auf Taste S und 1 bei Druck auf Taste W, ansonsten 0</param>
	///<param name="rfFR">Wird -1 bei Druck auf Taste F und 1 bei Druck auf Taste R, ansonsten 0</param>
	///<param name="rfLeftRight">Wird -1 bei Druck auf Linkspfeil-Taste und 1 bei Druck auf Rechtspfeil-Taste, ansonsten 0</param>
	///<param name="rfUpDown">Wird -1 bei Druck auf Hochpfeil-Taste und 1 bei Druck auf Runterpfeil-Taste, ansonsten 0</param>
	///<param name="rfPageUpDown">Wird -1 bei Druck auf Seite-Hoch-Taste und 1 bei Druck auf Seite-Runter-Taste, ansonsten 0</param>
	///<param name="rbSpace">Wird true, wenn Leertaste gedrückt, ansonsten false</param>
	virtual void GetMove(float &rfAD, float &rfSW, float &rfFR, float &rfLeftRight, float &rfUpDown, float &rfPageUpDown, bool &rbSpace);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Schnittstellen-ID des Keyboards.</summary>
	unsigned int m_idForInterface;

	///<summary> Pointer auf den übergeordneten Frame.</summary>
	CFrame * m_pframe;

	///<summary> Art der Keyboard-API.</summary>
	int m_eApiInput;
	
	///<summary> Flag, ob GameController erzeugt werden konnte.</summary>
	bool m_bCreated;

};

}