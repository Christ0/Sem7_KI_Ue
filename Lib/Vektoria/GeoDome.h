#pragma once
#include "geoellipsoid.h"

namespace Vektoria
{

class CGeoDome :
	public CGeoEllipsoid
{
public:
	///<summary> Konstruktor.</summary>
	CGeoDome(void);

	///<summary> Destruktor.</summary>
	~CGeoDome(void);

	///<summary> Erzeugt eine Kuppel, deren Vernetzung Polarkoordinaten folgt, der Geometrietyp ist CGeoTriangleStrip. </summary>
	///<param name = "fRadius"> Radius in der horizontalen Ebene in Units</param>
	///<param name = "fHeight"> Höhe der Kuppel in Units</param>
	///<param name = "pmaterial"> Pointer auf das Material der Kuppel, bei Angabe von NULL wird mit dem Defaultmaterial eine weiße Kuppel erzeugt</param>
	///<param name = "bSkyDome"> Wenn true, wird eine spezielle Kuppel für Sky-Domes erzeugt (Die Kuppel reicht dann etwas in den Boden hinein und die Normalen zeigen nach innen)</param>
	///<param name = "iLongitude"> Anzahl der Vertices um den Horizont herum</param>
	///<param name = "iLattitude"> Anzahl der Vertices von der Basis bis zur Spitze</param>
	///<param name = "eMapping"> Art des Mappings (z.B. eMapping_Cylindrical, eMapping_Bicylindrical, etc.)</param>
	void Init(float fRadius, float fHeight, CMaterial * pmaterial, bool bSkyDome = false, int iLongitude = 24, int iLattitude = 12, EMapping eMapping = eMapping_Cylindrical);

};

}