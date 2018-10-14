#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoTetrahedronWerk: Klasse für eine Tetraeder-Geometrie
// 
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoTetrahedronWerk :
	public CGeoTriangleList
{
protected:
	CHVector GetPoint(int i);
	CHVector GetPointInner(int iMain, int i2, int i3, float fr);
	void MakeFaceTri(int iA, int iB, int iC, float fr, int & iIndex);
	void MakeFaceBack(int iA, int iB, int iC, int iD, float fr, int & iIndex);
	void MakeFaceWerk(int iA, int iB, int iC, int iAs, int iBs, int iCs, float fr, int & iIndex);
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor.</summary>
	CGeoTetrahedronWerk(void);

	///<summary> Destruktor.</summary>
	~CGeoTetrahedronWerk(void);

	///<summary> Erzeugt einen Tetraeder. <para></para>
	/// Die Spitze zeigt in Richtung der Y-Achse.<para></para>
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Entfernung der Eckpunkte des Tetraeders in Units im lokalen Koordinatensystem</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Tetraeder erzeugt</param>
	void Init(float fRadius, float fr, CMaterial * pmaterial);

	///<summary> Erzeugt einen verzerrten Tetraeder.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "vSize"> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Tetraeders in Units im lokalen Koordinatensystem definiert</param>
	///<param name = "fr"> Relative Breite der Eckmaßbögen. (0.0=hauchdünn ... 1.0 = Gewerk füllt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Tetraeder erzeugt</param>
	void Init(CHVector vSize, float fr, CMaterial * pmaterial);


	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die drei Radien eines Ellipsoides, welches die Entfernung der Eckpunkte des (verzerrten) Tetraeders in Units im lokalen Koordinatensystem definiert.</summary>
	float m_fSize;

	///<summary> Die 4 Eckpunkte des Tetraeders + die 12 Innenpunkte.</summary>
	CHVector m_avPoint[16];

	///<summary> Die 120 Vertices pro Dreieck * ((6 Dreiecke pro Seite *4 Seiten)+(6 Kanten * 2 Dreiecke)+(1 Inneneckendreieck*4Ecken))) =             (6*3+6+3)* 4 = 52= Vertices des Tetraeders.</summary>
	CVertex m_avertex[120];

	///<summary> Das v-Offset der UV-Koordiaten im Innenbereich.</summary>
	float m_fvOffset;

};

}