#pragma once
#include "GeoLineList.h"

//------------------------------------------------------------------
// CGeoDodecahedronWire: Klasse für eine Dodekaeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoDodecahedronWire :
	public CGeoLineList
{
protected:
	CHVector GetPoint(int i);
	void MakeLine(int iA, int iB, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoDodecahedronWire(void);

	///<summary> Destruktor.</summary>
	~CGeoDodecahedronWire(void);

	///<summary> Erzeugt einen Dodekaeder. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Dodecahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Dodecahedron erzeugt</param>
	void Init(float fRadius, CMaterial * pmaterial); 

	///<summary> Erzeugt einen verzerrten Dodekaeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Dodecahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Dodecahedron erzeugt</param>
	void Init(CHVector vSize, CMaterial * pmaterial);  

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 20 Eckpunkte des Dodekaeders.</summary>
	CHVector m_avPoint[20];

	///<summary> Die 108 Vertices des Dodekaeders.</summary>
	CVertex m_avertex[108];
};

}