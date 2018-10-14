#pragma once
#include "GeoTriangleList.h"

namespace Vektoria
{

class CApiRender;

class CGeoEllipsoidTiled :
	public CGeoTriangleList
{
public:
	// --------------
	// Hauptmethoden:
	// --------------

	///<summary> Konstruktor.</summary>
	CGeoEllipsoidTiled(void);

	///<summary> Destruktor.</summary>
	~CGeoEllipsoidTiled(void);

	/// <summary> Gibt "CGeoEllipsoidTiled" aus. </summary>
	virtual const char* ClassName(void) { return "CGeoEllipsoidTiled"; }

	/// <summary> Erzeugt ein Ellipsoid, dessen Vernetzung Polarkoordinaten folgt, der Geometrietyp ist CGeoTriangleList. </summary>
	/// <param name = "vSize"> Radius-Ausmaße des Ellipsoids in Units in X-, Y- und Z-Richtung, der W-Faktor wird ignoriert.</param>
	/// <param name = "pmaterial"> Pointer auf das Material des Ellipsoids, bei Angabe von NULL wird mit dem Defaultmaterial ein weißes Ellipsoid erzeugt</param>
	/// <param name = "iLongitude"> Anzahl der Vertices um den Äquator herum</param>
	/// <param name = "iLattitude"> Anzahl der Vertices von Pol zu Pol</param>
	/// <param name = "iLattitudeMin"> Ab welcher Lattitudenvertexhöhe wird vernetzt? </param>
	/// <param name = "iLattitudeMax"> Bis zu welcher Lattitudenvertexhöhe wird vernetzt? </param>
	/// <param name = "eMapping"> Art des Mappings (z.B. eMapping_Cylindrical, eMapping_Bicylindrical, etc.)</param>
	/// <param name = "iRepeatUV"> Anzahl der Wiederholungen des UV-Texturmappings (Default = 1)</param>
	void Init(CHVector vSize, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, int iLattitudeMin = 0, int iLattitudeMax = INT_MAX, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Initialisiert eine ellisoide Geometrie 

protected:
	// ----------------
	// Hilfsmethoden:
	// ----------------

	int GetVertexIndex(int iLo, int iLa, int iCounterclock);
	void CalcMapping(float & frU, float & frV, int iLo, int iLa, int iLongitude, int iLattitude, CHVector & vTangent, CHVector & vBitangent, CHVector v, CHVector vSize, EMapping eMapping, int iRepeatUV);

public:
	// ----------------
	// Membervariablen:
	// ----------------


	/// <summary> Radius-Ausmaße des Ellipsoids in Units in X-, Y- und Z-Richtung, der W-Faktor wird ignoriert. </summary>
	CHVector m_vSize;

	/// <summary> Vertex-Hilfsliste. </summary>
	CVertex * m_avertex;

	/// <summary> Anzahl der Vertices um den Äquator herum. </summary>
	int m_iLongitude;

	/// <summary> Anzahl der Vertices von Pol zu Pol. </summary>
	int m_iLattitude;


};

}