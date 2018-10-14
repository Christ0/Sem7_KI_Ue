#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoDodecahedronWerk: Klasse für eine Dodekaeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoDodecahedronWerk :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	CHVector GetPointInner(int iMain, int i2, int i3, int i4, int i5, float fr);
	void MakeFaceFive(int iA, int iB, int iC, int iD, int iE, int iAs, int iBs, int iCs, int iDs, int iEs, float fr, int & iIndex);	
	void MakeFaceTri(int iA, int iB, int iC, float fr, int & iIndex);
	void MakeFaceBack(int iA, int iB, int iC, int iD, float fr, int & iIndex);


public:
	///<summary> Konstruktor.</summary>
	CGeoDodecahedronWerk(void);

	///<summary> Destruktor.</summary>
	~CGeoDodecahedronWerk(void);

	///<summary> Erzeugt einen Dodekaeder. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Dodecahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Dodecahedron erzeugt</param>
	void Init(float fRadius, float fr, CMaterial * pmaterial); 

	///<summary> Erzeugt einen verzerrten Dodekaeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Dodecahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Dodecahedron erzeugt</param>
	void Init(CHVector vSize, float fr, CMaterial * pmaterial);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 20 Eckpunkte des Dodekaeders + seine 60 Innenpunkte.</summary>
	CHVector m_avPoint[80];

	///<summary> Die 600 Vertices des Dodekaeder-Gewerkes (Jeder der 12 Seiten hat 10 Facetten a 3 Vertices + 30 Kanten a 2 Facetten a 3 Vertices + 20 Ecken a 1 Facettte entsprechend 3 Vertices).</summary>
	CVertex m_avertex[600];

	///<summary> Das v-Offset der UV-Koordiaten im Innenbereich.</summary>
	float m_fvOffset;

};

}