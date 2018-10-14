#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoIcosahedronWerk: Klasse für eine Ikosaeder-Gewerk-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CGeoIcosahedronWerk :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	CHVector GetPointInner(int iMain, int i2, int i3, float fr);
	void MakeFaceFive(int iA, int iB, int iC, int iD, int iE, int & iIndex);
	void MakeFaceBack(int iA, int iB, int iC, int iD, float fr, int & iIndex);
	void MakeFaceWerk(int iA, int iB, int iC, int iAs, int iBs, int iCs, float fr, int & iIndex);
public:
	///<summary> Konstruktor.</summary>
	CGeoIcosahedronWerk(void);

	///<summary> Destruktor.</summary>
	~CGeoIcosahedronWerk(void);

	///<summary> Erzeugt einen Ikosaeder. <para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Icosahedrons in Units im lokalen Koordinatensystem</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Icosahedron erzeugt</param>
	void Init(float fRadius, float fr, CMaterial * pmaterial); 

	///<summary> Erzeugt einen verzerrten Ikosaeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Icosahedrons in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Icosahedron erzeugt</param>
	void Init(CHVector vSize, float fr, CMaterial * pmaterial);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 12 Eckpunkte + 60 Innenpunkte des Gewerks-Ikosaeders.</summary>
	CHVector m_avPoint[72];

	///<summary> Die 60 Eck-Vertices des Gewerks-Ikoseeders (Jeder der 12 Eckpunkte hat 5 angrenzende Flächen).</summary>
	CVertex m_avertex[1260]; // TODO anpassen!

	///<summary> Das v-Offset der UV-Koordiaten im Innenbereich.</summary>
	float m_fvOffset;

};

}