#pragma once
#include "GeoSweep.h"

namespace Vektoria
{

class CGeoCylinder :
	public CGeoSweep
{
public:
	///<summary> Konstruktor.</summary>
	CGeoCylinder(void);
	
	///<summary> Destruktor.</summary>
	~CGeoCylinder(void);

	///<summary> Erzeugt einen Zylinder.</summary>
	///<param name = "fRadiusBottom"> Radius des Bodens in Units</param>
	///<param name = "fRadiusTop"> Radius des Spitze in Units</param>
	///<param name = "fHeight"> Höhe des Zylinders in Units (In der Mitte liegt der lokale Ursprung)</param>
	/// <param name = "pmaterial"> Pointer auf das Material des Zylinders, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Zylinder erzeugt</param>
	/// <param name = "iLongitude"> Anzahl der Vertices von Pol zu Pol</param>
	/// <param name = "bHasBottom"> Flag, ob Polygone für den Boden erzeugt werden sollen</param>
	/// <param name = "bHasTop"> Flag, ob Polygone für die Spitze erzeugt werden sollen</param>
	void Init(float fRadiusBottom, float fRadiusTop, float fHeight, CMaterial * pmaterial, int iLongitude = 24, bool bHasBottom = true, bool bHasTop = true);
};

}