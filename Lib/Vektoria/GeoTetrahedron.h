#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoTetrahedron: Klasse für eine Tetraeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoTetrahedron :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	void MakeFace(int iA, int iB, int iC, int & iIndex);
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor.</summary>
	CGeoTetrahedron(void);

	///<summary> Destruktor.</summary>
	~CGeoTetrahedron(void);

	///<summary> Erzeugt einen Tetraeder. <para></para>
	/// Die Spitze zeigt in Richtung der Y-Achse.<para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Tetraeders in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Tetraeder erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(float fRadius, CMaterial * pmaterial, bool bFlip = false);  

	///<summary> Erzeugt einen verzerrten Tetraeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Tetraeders in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Tetraeder erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(CHVector vSize, CMaterial * pmaterial, bool bFlip = false); 


	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Tetraeders in Units im lokalen Koordinatensystem definiert.</summary>
	float m_fSize;

	///<summary> Die 4 Eckpunkte des Tetraeders.</summary>
	CHVector m_avPoint[4];

	///<summary> Die 12 Vertices des Tetraeders.</summary>
	CVertex m_avertex[12];
};

}