#pragma once
#include "geoellipsoid.h"

//------------------------------------
// CGeoSphere
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//------------------------------------

namespace Vektoria
{

class CGeoSphere : 
    public CGeoEllipsoid
{
public:
	///<summary> Konstruktor.</summary>
	CGeoSphere(void);

	///<summary> Destruktor.</summary>
	~CGeoSphere(void);

	///<summary> Gibt "CGeoSphere" aus.</summary>
	virtual const char* ClassName(void) { return "CGeoSphere"; }

	///<summary> Erzeugt eine Kugel, deren Vernetzung Polarkoordinaten folgt.<para></para> 
	/// Der Geometrietyp ist CGeoTriangleStrip. </summary>
	///<param name = "fRadius"> Radius der Kugel in Units</param>
	///<param name = "pmaterial"> Pointer auf das Material der Kugel, bei Angabe von NULL wird mit dem Defaultmaterial eine weiße Kugel erzeugt</param>
	///<param name = "iLongitude"> Anzahl der Vertices um den Äquator herum</param>
	///<param name = "iLattitude"> Anzahl der Vertices von Pol zu Pol</param>
	///<param name = "eMapping"> Art des Mappings (z.B. Cylindrical, Bicylindrical, etc.)</param>
	///<param name = "iRepeatUV"> Anzahl der Wiederholungen des UV-Texturmappings (Default = 1)</param>
	void Init(float fRadius, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Erzeugt Kugel

};

}