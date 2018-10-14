#pragma once

#include "Geo.h"

//------------------------------------
// CGeos, Pluralklasse von CGeo
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CGeos
{
	friend class CPlacement;
	friend class CGeoTriangleLists;
	friend class CGeoTriangleList;
	friend class CGeoWings;
	friend class CGeoWing;
	friend class CGeo;
private:
	void Tick(CHMat & m, int & iTick, float & fTimeDelta);

public:
	///<summary> Konstruktor.</summary>
	CGeos();

	///<summary> Destruktor.</summary>
	~CGeos();

	///<summary> Kopiert Container. <para></para>
	/// Achtung! Kopiert nur die Pointer, nicht die enthaltenen Geometrien. </summary>
	void Copy(CGeos & geos);

	///<summary> Kopieroperator. <para></para>
	/// Achtung! Lieber Methode "Copy" verwenden, schneller und sicherer. </summary>
	CGeos operator=(CGeos geos);

	///<summary> Initialisiert Container. <para></para>
	/// Achtung! Nicht notwendig, falls Konstruktor schon aufgerufen wurde (Regelfall). </summary>
	void Init();

	///<summary> Finalisiert Container. <para></para>
	/// Achtung! Nicht notwendig, falls Destruktor noch aufgerufen wird (Regelfall). </summary>
	void Fini();

	///<summary> Fügt eine Geometrie zu Liste hinzu.</summary>
	///<param name= "pgeo"> Pointer auf die hinzuzufügende Geometrie</param>
	void Add(CGeo * pgeo);

	///<summary> Hängt eine Geometrie von der Liste ab.</summary>
	///<param name= "pgeo"> Pointer auf die abzuhängende Geometrie</param>
	bool Sub(CGeo * pgeo);

	///<summary> Fügt pgeo nur hinzu, wenn es noch nicht in der Liste vorhanden ist.</summary>
	///<param name= "pgeo"> Pointer auf die hinzuzufügende Geometrie</param>
	bool AddOnce(CGeo * pgeo);

	///<summary> True, falls irgendein Unter-Geo transparent ist.</summary>
	bool HasTransparent();

	///<summary> Schaut, ob pgeo in der Liste vorhanden ist, gibt true aus, falls ja.</summary>
	///<param name= "pgeo"> Pointer auf die zu überprüfende Geometrie</param>
	bool Has(CGeo * pgeo);

	///<summary> Erzeugt eine Geometrie und hängt sie an.</summary>
	CGeo * Make();

	///<summary> Hängt eine mit Make erzeugte Geometrie ab und vernichtet sie.</summary>
	///<param name= "pgeo"> Pointer auf die zu vernichtende Geometrie</param>
	bool Kill(CGeo * pgeo);

	///<summary> Fügt alle Geometrien zur Liste hinzu, die in der Hierarchie unter einem Placement liegen.<para></para>
	/// Sollte die Geometrie mehrfach referenziert sein, wird sie nur einmal hinzugefügt.</summary>
	///<param name= "pplacement"> Pointer auf das Placement</param>
	void AddPlacementGeos(CPlacement * pplacement);

	///<summary> Berechnet, ob Strahl r ein Dreieck irgendeiner Geometrie (alle Instanzen) trifft, gibt trúe aus, wenn ja.</summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "vIntersection"> Schnittpunkt des Strahl mit der Geometrie (falls getroffen, ansonsten unsinnige Werte) </param>
	///<param name= "fDistanceSquare"> Quadrierter Abstand des Strahlursprungs mit der dem Schnittpunkt (falls getroffen, ansonsten unsinnige Werte) </param>
	bool Intersects(CRay & r, CHVector & vIntersection, float & fDistanceSquare);

	///<summary> Berechnet, ob der Strahl r ein Dreieck der Geometrie trifft, gibt trúe aus, wenn ja, hitpoint ist dann der Schnittpunkt.</summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "hitpoint"> Schnittpunkt mit Zusatzinformationen</param>
	///<param name= "iMaxVertices"> Maximalanzahl der Vertices, die die Geometrie haben darf (da eine Schnittpunktberechnung mit großen Geometrien sehr lange dauert)</param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgeführt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in großen Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	bool Intersects(CRay & r, CHitPoint & hitpoint, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Berechnet, ob der Strahl r ein Dreieck der Geometrie trifft, gibt trúe aus, wenn ja, hitpoint ist dann der Schnittpunkt.</summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "iMaxVertices"> Maximalanzahl der Vertices, die die Geometrie haben darf (da eine Schnittpunktberechnung mit großen Geometrien sehr lange dauert)</param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgeführt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in großen Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	bool Intersects(CRay & r, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Verschiebt die Vertexpositionen, so dass die Geometrien nicht mehr so mathematisch-korrekt ausssehen, sondern eher gammlig.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) in Einheiten </param>
	///<param name= "vMid"> Mittelpunkt der Verzerrung.</param>
	///<param name= "pgraphnoise"> Zufallsgraph.</param>
	void Gammel(float fAmplitudeMax, CHVector vMid, CGraphNoise * pgraphnoise);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Dynamisches Array, welches Pointer auf die Geometrien der Liste beinhaltet.</summary>
	CGeo ** m_apgeo;

	///<summary> Anzahl der allokierten Geometrien.</summary>
	int m_iGeoAllocs;

	///<summary> Anzahl der Geometrien.</summary>
	int m_iGeos;

	///<summary> Nächster Allokierungsschritt.</summary>
	int m_iAllocBlock;

};

}