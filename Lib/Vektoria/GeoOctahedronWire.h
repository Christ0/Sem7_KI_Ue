#pragma once
#include "GeoLineList.h"

//------------------------------------------------------------------
// GeoOctahedronWire: Klasse für eine Octahedron-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoOctahedronWire :
	public CGeoLineList
{
protected:
	CHVector GetPoint(int i);
	void MakeLine(int iA, int iB, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoOctahedronWire(void);

	///<summary> Destruktor.</summary>
	~CGeoOctahedronWire(void);

	///<summary> Erzeugt einen Octahedron. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Octahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Octahedron erzeugt</param>
	void Init(float fRadius, CMaterial * pmaterial); 

	///<summary> Erzeugt einen verzerrten Octahedron.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Octahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Octahedron erzeugt</param>
	void Init(CHVector vSize, CMaterial * pmaterial);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 6 Eckpunkte des Octahedrons.</summary>
	CHVector m_avPoint[6];

	///<summary> Die 24 Vertices des Octahedrons (Jeder der 12 Kanten hat 2 angrenzende Linien).</summary>
	CVertex m_avertex[24];
};

}