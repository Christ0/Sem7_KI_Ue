#pragma once
#include "GeoTriangleStrip.h"
#include "Face.h"

//--------------------------------------------------------------------------------------------
// CGeoEllipsoid 
// Beschreibung: Klasse f�r ein Ellipsoid 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

class CApiRender;


class CGeoEllipsoid :
	public CGeoTriangleStrip
{
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor.</summary>
	CGeoEllipsoid(void);

	///<summary> Destruktor.</summary>
	~CGeoEllipsoid(void);

	///<summary> Gibt "CGeoEllipsoid" aus.</summary>
	virtual const char* ClassName(void) { return "CGeoEllipsoid"; }

	///<summary> Gibt den Vertex-Index des CGeoTriangleStrips f�r eine Longitude und eine Lattitude zur�ck (Hilfsroutine zur Vernetzung).</summary>
	///<param name ="iLo"> Vertexnummer um die Achse herum</param>
	///<param name ="iLa"> Vertexnummer entlang der Achse</param>
	int GetVertexIndex(int iLo, int iLa);

	///<summary> Erzeugt ein Ellipsoid, dessen Vernetzung Polarkoordinaten folgt, der Geometrietyp ist CGeoTriangleStrip. </summary>
	///<param name = "vSize"> Radius-Ausma�e des Ellipsoids in Units in X-, Y- und Z-Richtung, der W-Faktor wird ignoriert.</param>
	///<param name = "pmaterial"> Pointer auf das Material des Ellipsoids, bei Angabe von NULL wird mit dem Defaultmaterial ein wei�es Ellipsoid erzeugt</param>
	///<param name = "iLongitude"> Anzahl der Vertices um den �quator herum</param>
	///<param name = "iLattitude"> Anzahl der Vertices von Pol zu Pol</param>
	///<param name = "iLattitudeMin"> Ab welcher Lattitudenvertexh�he wird vernetzt? </param>
	///<param name = "iLattitudeMax"> Bis zu welcher Lattitudenvertexh�he wird vernetzt? </param>
	///<param name = "eMapping"> Art des Mappings (z.B. eMapping_Cylindrical, eMapping_Bicylindrical, etc.)</param>
	///<param name = "iRepeatUV"> Anzahl der Wiederholungen des UV-Texturmappings (Default = 1)</param>
	void Init(CHVector vSize, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, int iLattitudeMin = 0, int iLattitudeMax = INT_MAX, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1);  

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Radius-Ausma�e des Ellipsoids in Units in X-, Y- und Z-Richtung, der W-Faktor wird ignoriert.</summary>
	CHVector m_vSize;

	///<summary> Liste der Vertices.</summary>
	CVertex * m_avertex;

	///<summary> Anzahl der Vertices von Pol zu Pol.</summary>
	int m_iLongitude;

	///<summary> Anzahl der Vertices um den �quator herum.</summary>
	int m_iLattitude;
};

}