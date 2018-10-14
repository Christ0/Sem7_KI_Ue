#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoDodecahedron: Klasse für eine Dodekaeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoDodecahedron :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	void MakeFaceFive(int iA, int iB, int iC, int iD, int iE, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoDodecahedron(void);

	///<summary> Destruktor.</summary>
	~CGeoDodecahedron(void);

	///<summary> Erzeugt einen Dodekaeder. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Dodecahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Dodecahedron erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(float fRadius, CMaterial * pmaterial, bool bFlip = false); 

	///<summary> Erzeugt einen verzerrten Dodekaeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Dodecahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Dodecahedron erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(CHVector vSize, CMaterial * pmaterial, bool bFlip = false);  

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 20 Eckpunkte des Dodekaeders.</summary>
	CHVector m_avPoint[20];

	///<summary> Die 108 Vertices des Dodekaeders (Jeder der 12 Seiten hat 3 Facetten a drei Vertices = ).</summary>
	CVertex m_avertex[108];
};

}