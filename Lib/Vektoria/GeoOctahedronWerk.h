#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoOctahedronWerk: Klasse für eine Octahedron-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoOctahedronWerk :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	CHVector GetPointInner(int iMain, int i2, int i3, float fr);
	void MakeFaceQuad(int iA, int iB, int iC, int iD, int & iIndex);
	void MakeFaceBack(int iA, int iB, int iC, int iD, float fr, int & iIndex);
	void MakeFaceWerk(int iA, int iB, int iC, int iAs, int iBs, int iCs, float fr, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoOctahedronWerk(void);

	///<summary> Destruktor.</summary>
	~CGeoOctahedronWerk(void);

	///<summary> Erzeugt einen Octahedron. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Octahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Octahedron erzeugt</param>
	void Init(float fRadius, float fr, CMaterial * pmaterial);

	///<summary> Erzeugt einen verzerrten Octahedron.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Octahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Octahedron erzeugt</param>
	void Init(CHVector vSize, float fr, CMaterial * pmaterial);  

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 6 Eckpunkte des Octahedrons + die 24 Innenpunkte des Gewerks</summary>
	CHVector m_avPoint[30];

	///<summary> Die 24 Vertices des Octahedrons (Jeder der 6 Eckpunkte hat 4 angrenzende Flächen).</summary>
	CVertex m_avertex[1024]; // TODO 

	///<summary> Das v-Offset der UV-Koordiaten im Innenbereich.</summary>
	float m_fvOffset;

};

}