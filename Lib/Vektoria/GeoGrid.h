#pragma once
#include "GeoTriangleTable.h"

//------------------------------------------------------------------
// CGeoGrid: Klasse zum Erzeugen eines ebenen n*n-Dreiecksnetzes
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt) 
//-------------------------------------------------------------------


namespace Vektoria
{

class CGeoGrid : public CGeoTriangleTable
{
public:
	///<summary> Konstruktor.</summary>
	CGeoGrid(void);

	///<summary> Destruktor.</summary>
	~CGeoGrid(void);

	///<summary> Setzt die kartesische Erstellungsachse des Quads. <para></para>
	/// Muss vor dem Init-Methodenaufruf aufgerufen werden, damit die Methode einen Effekt hat. </summary>
	///<param name="eAxis"> Kann drei verschiedene Werte annehmen: eAxisX, eAxisY oder eAxisZ (default) </param>
	void SetAxis(EAxis eAxis);

	///<summary> Initialisiert und erzeugt eine Dreiecksgitter-Geometrie (=Grid).<para></para>
	/// Die Erstellungsebene kann durch vorheriges Aufrufen von eAxis definiert werden, ansonsten wird das Grid automatisch in der XZ-Ebene erzeugt.<para></para>
	/// Der Geometrietyp ist CGeoTriangleTable.</summary>
	///<param name="fxSize"> Halbe horizontale Größe des Grids (Grid erstreckt sich horizontal von -fxSize bis +fxSize)</param>
	///<param name="fySize"> Halbe vertikale Größe des Grids (Grid erstreckt sich horizontal von -fySize bis +fySize)</param>
	///<param name="pmaterial"> Pointer auf das aufzubringende Material</param>
	///<param name="ixVertices"> Anzahl der Vertices in X-Richtung</param>
	///<param name="iyVertices"> Anzahl der Vertices in Y-Richtung</param>
	///<param name="fuStart"> U-Koordinatenwert des UV-Mappings der linken Seite</param>
	///<param name="fvStart"> V-Koordinatenwert des UV-Mappings der rechten Seite</param>
	///<param name="fuEnd"> U-Koordinatenwert des UV-Mappings der oberen Seite</param>
	///<param name="fvEnd"> V-Koordinatenwert des UV-Mappings der unteren Seite</param>
	void Init(float fxSize, float fySize, CMaterial * pmaterial, int ixVertices, int iyVertices, float fuStart = 0, float fvStart = 0, float fUEnd = 1, float fVEnd = 1); // Initialisiert eine Rechteckige planare Geometrie 
	

	///<summary> Die Vertices des Quads. </summary>
	CVertex **m_aavertex;

	///<summary> Die kartesische Erstellungsachse des Quads. </summary>
	EAxis m_eAxis;
};

}