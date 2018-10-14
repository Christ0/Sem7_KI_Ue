#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoIcosahedron: Klasse für eine Ikosaeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoIcosahedron :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	void MakeFace(int iA, int iB, int iC, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoIcosahedron(void);

	///<summary> Destruktor.</summary>
	~CGeoIcosahedron(void);

	///<summary> Erzeugt einen Ikosaeder. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Icosahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Icosahedron erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(float fRadius, CMaterial * pmaterial, bool bFlip = false); 

	///<summary> Erzeugt einen verzerrten Ikosaeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Icosahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Icosahedron erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(CHVector vSize, CMaterial * pmaterial, bool bFlip = false);  

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 12 Eckpunkte des Ikosaeders.</summary>
	CHVector m_avPoint[12];

	///<summary> Die 60 Vertices des Ikoseeders (Jeder der 12 Eckpunkte hat 5 angrenzende Flächen).</summary>
	CVertex m_avertex[60];
};

}