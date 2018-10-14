#pragma once
#include "GeoLineList.h"

//------------------------------------------------------------------
// CGeoTetrahedronWire: Klasse für eine Tetraeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoTetrahedronWire :
	public CGeoLineList
{
protected:
	CHVector GetPoint(int i);
	void MakeLine(int iA, int iB, int & iIndex);
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor.</summary>
	CGeoTetrahedronWire(void);

	///<summary> Destruktor.</summary>
	~CGeoTetrahedronWire(void);

	///<summary> Erzeugt einen Tetraeder. <para></para>
	/// Die Spitze zeigt in Richtung der Y-Achse.<para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Tetraeders in Units im lokalen Koordinatensystem</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Tetraeder erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(float fRadius, CMaterial * pmaterial); // Initialisiert eine Geometrie mit Tetraeder 

	///<summary> Erzeugt einen verzerrten Tetraeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Tetraeders in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Tetraeder erzeugt</param>
	///<param name = "bFlip"> Flag, ob die Flächen nach Innen zeigen sollen</param>
	void Init(CHVector vSize, CMaterial * pmaterial); // Initialisiert eine Geometrie mit Tetraeder 


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