#pragma once
#include "HVector.h"
#include "Util.h"

//------------------------------------
// CRay
//
// Autor    : Prof. Dr. Tobias Breiner (Anlehnung und Erweiterung von CRay von Patrick Fleischmann zur besseren Aufwärtskompabilität)
// Ort      : Pfungstadt
// Copyright: Vektoria UG (haftungsbeschränkt)
//------------------------------------

namespace Vektoria
{

class CRay
{
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor ohne Initialisierung.</summary>
	CRay(); 

	///<summary> Kostruktor, alle relevanten Parameter des Strahls werden initialisiert.</summary>
	///<param name="vOrigin">Startpunkt des Strahls</param>
	///<param name="vDirection">Richtung des Strahls, wird automatisch normiert.</param>
	///<param name="fMin">Startwirkabstand (vom Startpunkt aus gemessen)</param>
	///<param name="fMax">Endwirkabstand (vom Startpunkt aus gemessen)</param>
	CRay(CHVector vOrigin, CHVector vDirection, float fMin = QUASI_ZERO, float fMax = F_MAX); 

	///<summary> Destruktor ohne Initialisierung.</summary>
	~CRay();

	///<summary> Gibt denjenigen Punkt auf dem Strahl aus, dem im Abstand fT von vOrigin liegt.</summary>
	///<param name="fT">Abstand</param>
	CHVector operator()(float fT);

	///<summary> Gibt für jeden Richtungstupel X, Y und Z eine Eins aus, falls der Betrag negativ ist.</summary>
	///<param name="aiSigns">Array für die drei kartesischen Richtungen</param>
	void GetDirectionSign(int aiSigns[3]);

	///<summary> Kopieroperator.</summary>
	///<param name="ray">Zu kopierender Strahl</param>
	CRay operator=(CRay ray); 

	///<summary> Kopiermethode.</summary>
	///<param name="ray">Zu kopierender Strahl</param>
	void Copy(CRay & ray);  
	
	///<summary> (Re-)Initialiert den Strahl.</summary>
	///<param name="vOrigin">Startpunkt des Strahls</param>
	///<param name="vDirection">Richtung des Strahls</param>
	void Init(CHVector & vOrigin, CHVector & vDirection); 	
	
	///<summary> (Re-)Initialieret Strahl ray mittels Start- und Endvektor.</summary>
	///<param name="vOrigin">Startpunkt des Strahls</param>
	///<param name="vTo">Richtung des Strahls</param>
	void InitFromTo(CHVector & vOrigin, CHVector & vTo); 

	///<summary> Setzt die Strahlminimaldistanz ausgehend von vOrigin.</summary>
	///<param name="fMin">Startwirkabstand</param>
	void SetMin(float fMin); 

	///<summary> Setzt die Strahlmaximaldistanz ausgehend von vOrigin.</summary>
	///<param name="fMax">Endwirkabstand</param>
	void SetMax(float fMax); 

	///<summary> Gibt die Strahlminimaldistanz ausgehend von vOrigin aus.</summary>
	float GetMin();  

	///<summary> Gibt die Strahlmaximaldistanz ausgehend von vOrigin aus
	float GetMax(); 

	///<summary> Berechnet den minimalen Abstand zweier Strahlgeraden.</summary>
	///<param name="ray">Strahl</param>
	float Distance(CRay & ray); 

	///<summary> Berechnet den kleinsten Abstand der aktuellen Strahlgeraden vom Punkt v.</summary>
	///<param name="v">Punktvektor</param>
	float Distance(CHVector & v); 

	///<summary> Berechnet den Winkel zwischen Strahl und der Richtung von vOrigin zu Punkt v.</summary>
	///<param name="v">Punktvektor</param>
	float Angle(CHVector & v);  

	///<summary> Schaut, ob Strahl mit Dreieick v1-v2-v3 kollidiert, wenn ja, wird true ausgegeben.</summary> 
	///<param name="v1">Punkt 1 des Dreiecks</param>
	///<param name="v2">Punkt 2 des Dreiecks</param>
	///<param name="v3">Punkt 3 des Dreiecks</param>
	///<param name="vIntersection">Schnittpunkt</param>
	///<param name="fDistanceSquare">Quadrat des Abstands vom Strahlursprung (vOrigin) zum Schnittpunkt</param>
	bool IntersectsTriangle(CHVector & v1, CHVector & v2, CHVector & v3, CHVector & vIntersection, float &fDistanceSquare); 

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Startpunkt des Strahls.</summary>
	CHVector m_vOrigin;

	///<summary> Richtung des Strahls.</summary>
	CHVector m_vDirection;

	///<summary> Minimaldistanz vom Startpunkt aus.</summary>
	float m_fMin;

	///<summary> Maximaldistanz vom Startpunkt aus.</summary>
	float m_fMax;

};

}