#pragma once
#include "geoellipsoidtiled.h"

namespace Vektoria
{

class CGeoDomeTiled :
	public CGeoEllipsoidTiled
{
public:
	///<summary> Konstruktor.</summary>
	CGeoDomeTiled(void);

	///<summary> Destruktor.</summary>
	~CGeoDomeTiled(void);

	/// <summary> Erzeugt eine Kuppel, dessen Vernetzung Polarkoordinaten folgt, der Geometrietyp ist CGeoTriangleList. </summary>
	/// <param name = "fRadius"> Radius in der horizontalen Ebene in Units</param>
	/// <param name = "fHeight"> Höhe der Kuppel in Units</param>
	/// <param name = "pmaterial"> Pointer auf das Material der Kuppel, bei Angabe von NULL wird mit dem Defaultmaterial eine weiße Kuppel erzeugt</param>
	/// <param name = "bSkyDome"> Wenn true, wird eine spezielle Kuppel für Sky-Domes erzeugt (Die Kuppel reicht dann etwas in den Boden hinein und die Normalen zeigen nach innen)</param>
	/// <param name = "iLongitude"> Anzahl der Vertices  um den Horizont herum</param>
	/// <param name = "iLattitude"> Anzahl der Vertices von der Basis bis zur Spitze</param>
	/// <param name = "eMapping"> Art des Mappings (z.B. eMapping_Cylindrical, eMapping_Bicylindrical, etc.)</param>
	void Init(float fRadius, float fHeight, CMaterial * pmaterial, bool bSkyDome = false, int iLongitude = 24, int iLattitude = 12,  EMapping eMapping = eMapping_Cylindrical);  // Erzeugt Kuppel

};

}