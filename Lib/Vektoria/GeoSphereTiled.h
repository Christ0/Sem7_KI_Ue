#pragma once
#include "geoellipsoidtiled.h"

//------------------------------------
// CGeoSphereTiled
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//------------------------------------


namespace Vektoria
{

class CGeoSphereTiled : 
    public CGeoEllipsoidTiled
{
public:
	///<summary> Konstruktor.</summary>
	CGeoSphereTiled(void);

	///<summary> Destruktor.</summary>
	~CGeoSphereTiled(void);

	///<summary> Gibt "CGeoSphereTiled" aus.</summary>
    virtual const char* ClassName(void) { return "CGeoSphereTiled"; }

	///<summary> Erzeugt eine Kugel, deren Vernetzung Polarkoordinaten folgt, der Geometrietyp ist CGeoTriangleList. </summary>
	///<param name = "fRadius"> Radius der Kugel in Units</param>
	///<param name = "pmaterial"> Pointer auf das Material der Kugel, bei angabe von NULL wird mit dem Defaultmaterial eine weiße Kugel erzeugt</param>
	///<param name = "iLongitude"> Anzahl der Vertices um den Äquator herum</param>
	///<param name = "iLattitude"> Anzahl der Vertices von Pol zu Pol</param>
	///<param name = "eMapping"> Art des Mappings (z.B. Cylindrical, Bicylindrical, etc.)</param>
	///<param name = "iRepeatUV"> Anzahl der Wiederholungen des UV-Texturmappings (Default = 1)</param>
	void Init(float fRadius, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Erzeugt getilte Kugel

};

}