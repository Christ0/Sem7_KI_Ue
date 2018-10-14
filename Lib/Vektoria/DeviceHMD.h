#pragma once
#include "Node.h"
#include "ApiCyberglasses.h"

//--------------------------------------------------------------------------------------------
// CDeviceHMD: Klasse für HMDs (HTC Vive, Oculus Rift, etc.) 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

	class CFrame;

class CDeviceHMD : public CNode
{

public:
	// --------------
	// Basismethoden:
	// --------------

	///<summary> Konstruktor.</summary>
	CDeviceHMD(); 

	///<summary> Destruktor.</summary>
	~CDeviceHMD(); 

	///<summary> Gibt die homogene Matrix des Kopfes aus. Damit kann die Position und die Orientierung des HMDs ermittelt werden.</summary>
	CHMat GetMatHead();

	///<summary> Gibt die homogene Matrix des linken Auges aus. Damit kann die Position und die Orientierung bezüglich des HMDs ermittelt werden.</summary>
	CHMat GetMatEyeLeft();

	///<summary> Gibt die homogene Matrix des rechten Auges aus. Damit kann die Position und die Orientierung bezüglich des HMDs ermittelt werden.</summary>
	CHMat GetMatEyeRight();
	
	///<summary> Gibt die homogene Projektionsmatrix des linken Auges aus. </summary>
	/// <param name= "fNearClipping"> Abstand der vorderen Clippingebene des Kamera-Frustums in Units (ab welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
	/// <param name= "fFarClipping"> Abstand der hinteren Clippingebene des Kamera-Frustums in Units (bis zu welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
	CHMat GetMatProjLeft(float fNearClipping, float fFarClipping);

	///<summary> Gibt die homogene Projektionsmatrix des rechten Auges aus. </summary>
	/// <param name= "fNearClipping"> Abstand der vorderen Clippingebene des Kamera-Frustums in Units (ab welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
	/// <param name= "fFarClipping"> Abstand der hinteren Clippingebene des Kamera-Frustums in Units (bis zu welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
	CHMat GetMatProjRight(float fNearClipping, float fFarClipping);

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