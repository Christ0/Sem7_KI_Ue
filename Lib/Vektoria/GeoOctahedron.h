#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoOctahedron: Klasse für eine Octahedron-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoOctahedron :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	void MakeFace(int iA, int iB, int iC, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoOctahedron(void);

	///<summary> Destruktor.</summary>
	~CGeoOctahedron(void);

	///<summary> Erzeugt einen Octahedron. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Octahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Octahedron erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(float fRadius, CMaterial * pmaterial, bool bFlip = false); 

	///<summary> Erzeugt einen verzerrten Octahedron.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Octahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Octahedron erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(CHVector vSize, CMaterial * pmaterial, bool bFlip = false);  

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 6 Eckpunkte des Octahedrons.</summary>
	CHVector m_avPoint[6];

	///<summary> Die 24 Vertices des Octahedrons (Jeder der 6 Eckpunkte hat 4 angrenzende Flächen).</summary>
	CVertex m_avertex[24];
};

}