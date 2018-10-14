#pragma once
#include "GeoSweep.h"

//--------------------------------------------
// CGeoArrow: Klasse zur Erzeugung von 3D-Pfeilen
//
// Autor: Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------

namespace Vektoria
{

	class CGeoArrow :
		public CGeoSweep
	{
	public:
		///<summary> Konstruktor.</summary>
		CGeoArrow();

		///<summary> Destruktor.</summary>
		~CGeoArrow();

		///<summary> Erzeugt einen 3D-Pfeil (z.B. zur Visualisierung von Vektoren). Der Geometrietyp ist CGeoTriangleStrip.</summary>
		///<param name = "v">Richtungsvektor, der die Größe und Richtung des 3D-Pfeils bestimmt. Der Sockel liegt im Ursprung.</param>
		///<param name = "fRadiusBottom">Radius des Sockels und des Stängels</param>
		///<param name = "fRadiusHead">Radius der Pfeilspitze</param>
		///<param name = "pmaterial">Pointer auf das Material</param>
		///<param name = "iLongitude">Anzahl der Vertices um den Stängel herum</param>
		///<param name = "bLengthHeadIsRelative">Flag, ob die Pfeilspitze mit der Länge des Vektors mitwachsen soll</param>
		///<param name = "bHasBottom">Flag, ob der Pfeil unten an der Basis geschlossen sein soll</param>
		void Init(CHVector & v, float fRadiusBottom, float fRadiusHead, float fLengthHead, CMaterial * pmaterial, int iLongitude = 7, bool bLengthHeadIsRelative = true, bool bHasBottom = true);   
	};

}