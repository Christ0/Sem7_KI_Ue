#pragma once
#include "Node.h"
#include "ApiCyberglasses.h"

//--------------------------------------------------------------------------------------------
// CDeviceVRController: Klasse für die Controllerbehandlung von HMDs (HTC Vove, Oculus Rift, etc.) 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

	class CFrame;

class CDeviceVRController : public CNode
{
	/*
protected:
	///<summary> Initialisiert VRDevice, gibt true aus, wenn`s geklappt hat.</summary>
	bool Init();

	///<summary> Wird jeden Tick aufgerufen.</summary>
	void Tick();

	///<summary> Finalisiert VRDevice.</summary>
	void Fini();
	*/
public:
	// --------------
	// Basismethoden:
	// --------------

	///<summary> Konstruktor.</summary>
	CDeviceVRController(); 

	///<summary> Destruktor.</summary>
	~CDeviceVRController(); 

	///<summary> Gibt die homogene Matrix des Controllers aus. Damit kann die Position und die Orientierung des Controllers ermittelt werden .</summary>
	CHMat GetMatController();

	///<summary> Gibt true aus, wenn Button eButton gerade berührt wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonTouched(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn Button eButton gerade gedrückt wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonPressed(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn Button eButton gerade zum ersten Mal (Tick) heruntergedrückt wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonDown(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn Button eButton gerade zum ersten Mal (Tick) losgelöst wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonUp(EHmdButtonKind eButton);

	///<summary> Lässt Controller vibirieren.</summary>
	///<param name= "frStrength"> Stärke der Vibration (0 = gar nix ... 1 = Volle Pulle).</param>
	///<param name= "iAxis"> Virabtionsachse (0 bis 3, normalerweise ist bei Controillern nur Achse 0 implementiert).</param>
	void Vibrate(float frStrength, int iAxis = 0);

	///<summary> Steuerung.  Falls Space Taste gedrückt wurde, wird true ausgegeben.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="placementController">Placement des Controllers</param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
	bool Move(CPlacement & placementCamera, CPlacement & placementController, float & fTimeDelta, bool bEarth = false);

	///<summary> WASD Steuerung mit Kollisionserkennung.  Falls die Kamera kolliderte, hält sie an, und die Methode gibt true aus.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="placementController">Placement des Controllers</param>
	///<param name="zgsCollisionItems">Liste von Geometrien, mit denen die Kamera kollidieren kann</param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
	virtual bool MoveWithCollisionDetection(CPlacement & placementCamera, CPlacement & placementController, CGeos & zgsCollisionItems, float & fTimeDelta, bool bEarth = false);


	///<summary> WASD Steuerung mit Kollisionserkennung.  Falls die Kamera kolliderte, hält sie an, und die Methode gibt true aus.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="placementOffset">Offset-Placement (z.B. wenn an dem Kameraplacement noch ein HMD-Positionsplacement hängt) </param>
	///<param name="placementController">Placement des Controllers</param>
	///<param name="zgsCollisionItems">Liste von Geometrien, mit denen die Kamera kollidieren kann</param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
	virtual bool MoveWithCollisionDetection(CPlacement & placementCamera, CPlacement & placementOffset, CPlacement & placementController, CGeos & zgsCollisionItems, float & fTimeDelta, bool bEarth = false);


	///<summary> Steuerung.  Falls Space Taste gedrückt wurde, wird true ausgegeben.</summary>
	///<param name="placementCamera">Placement der Kamera</param>
	///<param name="placementController">Placement des Controllers</param>
	///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
	///<param name="fDistance"> Entfernung in Units bis zu nächsten Haltepunkt </param>
	bool MoveInSteps(CPlacement & placementCamera, CPlacement & placementController, float & fTimeDelta, bool bEarth = false, float fDistance = 5.0f);

	///<summary> Hilfsroutine für eigene WASD-Steuerungen.</summary>
	///<param name="rfAD">Wird -1 bei Druck auf Taste A und 1 bei Druck auf Taste D, ansonsten 0</param>
	///<param name="rfSW">Wird -1 bei Druck auf Taste S und 1 bei Druck auf Taste W, ansonsten 0</param>
	///<param name="rfFR">Wird -1 bei Druck auf Taste F und 1 bei Druck auf Taste R, ansonsten 0</param>
	///<param name="rbSpace">Wird true, wenn Leertaste gedrückt, ansonsten false</param>
	void GetMove(float &rfAD, float &rfSW, float &rfFR, bool &rbSpace);



	/*
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

	///<summary> Gibt true aus, wenn der System-Button gerade berührt wird.</summary>
	bool ButtonSystemTouched();

	///<summary> Gibt true aus, wenn der System-Button gerade gedrückt wird.</summary>
	bool ButtonSystemPressed();

	///<summary> Gibt true aus, wenn der System-Button gerade zum ersten Mal (Tick) heruntergedrückt wird.</summary>
	bool ButtonSystemDown(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn der System-Button gerade zum ersten Mal (Tick) losgelöst wird.</summary>
	bool ButtonSystemUp(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn der Application Menu-Button gerade berührt wird.</summary>
	bool ButtonMenuTouched();

	///<summary> Gibt true aus, wenn der Application Menu-Button gerade gedrückt wird.</summary>
	bool ButtonMenuPressed();

	///<summary> Gibt true aus, wenn der Application Menu-Button gerade zum ersten Mal (Tick) heruntergedrückt wird.</summary>
	bool ButtonMenuDown(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn der Application Menu-Button gerade zum ersten Mal (Tick) losgelöst wird.</summary>
	bool ButtonMenuUp(EHmdButtonKind eButton);


	///<summary> Gibt true aus, wenn Button eButton gerade berührt wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonTouched(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn Button eButton gerade gedrückt wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonPressed(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn Button eButton gerade zum ersten Mal (Tick) heruntergedrückt wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonDown(EHmdButtonKind eButton);

	///<summary> Gibt true aus, wenn Button eButton gerade zum ersten Mal (Tick) losgelöst wird.</summary>
	///<param name= "eButton"> Wert des Buttons.</param>
	bool ButtonUp(EHmdButtonKind eButton);

	*/



	///<summary> Gibt die X-Koordinate einer Achse eines Buttons aus.</summary>
	///<param name= "iAxis"> Nummer der Achse.</param>
	float GetX(int iAxis = 0);

	///<summary> Gibt die Y-Koordinate einer Achse eines Buttons aus.</summary>
	///<param name= "iAxis"> Nummer der Achse.</param>
	float GetY(int iAxis = 0);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Pointer auf den übergeordneten Frame.</summary>
	CFrame * m_pframe;

	///<summary> Nummer des Controllers.</summary>
	unsigned int m_uController;

};

}