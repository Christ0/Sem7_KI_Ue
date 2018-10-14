#pragma once
#include "HVector.h"
#include "Ray.h"

//------------------------------------
// CPlane
// Klasse für Ebenenmathematik
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Copyright: Vektoria UG (haftungsbeschränkt)
//------------------------------------

namespace Vektoria
{

class CPlane
{
public:
	// ---------
	// Methoden:
	// ---------

	///<summary>  Konstruktor ohne initialisierung.</summary> 
	CPlane(); 

	///<summary>  Initialisiert eine Ebene durch die Angabe dreier Punkte, die in der Ebene liegen.</summary> 
	///<param name="pvA">Punktvektor 1</param> 
	///<param name="pvB">Punktvektor 2</param>
	///<param name="pvC">Punktvektor 3</param>
	CPlane(CHVector * pvA, CHVector * pvB, CHVector * pvC); 

	///<summary>  Initialisiert eine Ebene durch die Angabe eines Punktes plus Normalenvektor.</summary> 
	///<param name="vPoint">Punktvektor</param>
	///<param name="vNormal">Normalenvektor</param>
	CPlane(CHVector & vPoint, CHVector & vNormal); 

	///<summary> Destruktor.</summary> 
	~CPlane();

	///<summary> Kopieroperator.</summary> 
	///<param name="plane">Zu kopierende Ebene</param>
	CPlane operator=(CPlane & plane); 

	///<summary> Kopierfunktion.</summary> 
	///<param name="plane">Zu kopierende Ebene</param>
	void Copy(CPlane & plane); 

	///<summary>  (Re-)initialisiert eine Ebene durch die Angabe dreier Punkte.</summary> 
	///<param name="pvA">Punktvektor 1</param>
	///<param name="pvB">Punktvektor 2</param>
	///<param name="pvC">Punktvektor 3</param>
	void Init(CHVector * pvA, CHVector * pvB, CHVector * pvC); 	
	
	///<summary>  (Re-)initialisiert eine Ebene durch die Angabe eines Punktes plus Normalenvektor.</summary> 
	///<param name="vPoint">Punktvektor</param>
	///<param name="vNormal">Normalenvektor</param>
	void Init(CHVector & vPoint, CHVector & vNormal); 

	///<summary>  Deinitialisiert die Ebene
	void Fini();

	///<summary>  Berechnet den Schnittwinkel zwischen zwei Ebenen.</summary> 
	///<param name="plane">Schnittebene</param>
	float Angle(CPlane & plane); 

	///<summary>  Berechnet den Schnittpunkt dreier Ebenen.</summary> 
	///<param name="plane2">Schnittebene 1</param>
	///<param name="plane3">Schnittebene 2</param>
	CHVector Intersect(CPlane & plane2, CPlane & plane3); 

	///<summary>  Berechnet Schnittpunkt eines Strahls mit der Ebene.</summary> 
	///<param name="ray">Schnittstrahl</param>
	CHVector Intersect(CRay & ray); 

	///<summary>  Transliert entlang der Normalen.</summary> 
	///<param name="f">Verschiebungsabstand</param>
	void Move(float f); 

	///<summary>  Gibt true aus, wenn Punkt v vor der Ebene liegt (also in Richtung der Normalen von der Ebene aus).</summary> 
	///<param name="v">Punktvektor</param>
 	bool IsFront(CHVector & v); 

	///<summary>  Gibt true aus, wenn Punkt v in der Ebene liegt.</summary> 
	///<param name="v">Punktvektor</param>
	bool IsIn(CHVector & v); 

	///<summary>  Gibt true aus, wenn Punkt v hinter der Ebene liegt  (also entgegengesetzt zur Richtung der Normalen von der Ebene aus).</summary> 
	///<param name="v">Punktvektor</param>
	bool IsBack(CHVector & v); 

	///<summary>  Gibt den D-Parameter der Ebene aus.</summary> 
	float GetD(); 

	///<summary>  Rechnet die Normale der Ebene aus.</summary> 
	CHVector GetNormal(); 

	///<summary>  Gibt die Entfernung des angegebenen Punktes zur Ebene aus, liegt Punkt hinter der Ebene, wird der Wert negativ.</summary> 
	///<param name="v">Punktvektor</param>
	float Distance(CHVector & v); 

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary>  X-Wert der Ebene.</summary> 
	float m_fx;

	///<summary>  Y-Wert der Ebene.</summary> 
	float m_fy;

	///<summary>  Z-Wert der Ebene.</summary> 
	float m_fz;

	///<summary>  D-Wert der Ebene.</summary> 
	float m_fd;
};

}