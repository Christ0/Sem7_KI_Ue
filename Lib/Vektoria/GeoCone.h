#pragma once
#include "GeoSweep.h"

//------------------------------------------------------------------
// CGeoCone: Klasse für eine Kegel-Geometrie
//
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt) 
//-------------------------------------------------------------------


namespace Vektoria
{

class CGeoCone :
	public CGeoSweep
{
public:
	///<summary> Konstruktor.</summary>
	CGeoCone(void);

	///<summary> Destruktor.</summary>
	~CGeoCone(void);

	///<summary> Initialisiert einen Kegel. Der Geoemtrietyp ist CGeoTriangleStrip. </summary>
	///<param name = "fRadius"> Radius des Basis </param> 
	///<param name = "fHeight"> Höhe des Kegels </param> 
	///<param name = "pmaterial"> Pointer auf das Material des Kegels</param>
	///<param name = "iLongitude"> Anzahl der radialen Vertices </param> 
	///<param name = "bHasBottom"> = Flag, ob der Boden miterzeugt werden soll </param>
	void Init(float fRadius, float fHeight, CMaterial * pmaterial, int iLongitude = 24, bool bHasBottom = true); 
};

}