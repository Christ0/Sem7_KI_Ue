#pragma once
#include "GeoTriangleStrip.h"
#include "GeoSweep.h"
#include "Face.h"

//------------------------------------------------------------------
// CCamera: Klasse f�r R�hren
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//-------------------------------------------------------------------


namespace Vektoria
{

class CGeoTube :
	public CGeoSweep
{
public:
	///<summary> Konstruktor.</summary>
	CGeoTube(void);

	///<summary> Destruktor.</summary>
	~CGeoTube(void);

	///<summary> Initialisiert eine gerade R�hre. <para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name ="fRadiusInner">Innenradius in Units</param>
	///<param name ="fRadiusOuter">Au�enradius in Units</param>
	///<param name ="fLength">L�nge in Units</param>
	///<param name ="pmaterial">Pointer auf das Material</param>
	///<param name ="iLongitude"> Anzahl der Vertices um die Achse, je h�her dieser Wert, desto mehr Polygone</param>
	///<param name ="bInner"> Flag, ob die Innen und Endseiten der R�hre erzeugt werden sollen (default = true)</param>
	void InitStraight(float fRadiusInner, float fRadiusOuter, float fLength, CMaterial * pmaterial, int iLongitude = 24, bool bInner = true); // Initialisiert eine R�hren-Geometrie, fRadiusInner = innerer R�hrenradius, fRadiusOuter = �u�erer R�hrenradius, fLength = L�nge der R�hre, pmaterial = Materialpointer, iLongitude = Anzahl der radialen Vertices, bInner = true, wenn Innenleben des Rohres erzeugt werden soll

	///<summary> Initialisiert eine gebogene R�hre. <para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name ="fRadiusInner">Innenradius in Units</param>
	///<param name ="fRadiusOuter">Au�enradius in Units</param>
	///<param name ="fRadiusArc">Radius der Biegung in Units</param>
	///<param name ="faArc">Winkel des Biegungsbogens im Bogenma� (z.B. PI erzeugt einen u-f�rmigen Bogen)</param>
	///<param name ="fLength">L�nge in Units</param>
	///<param name ="pmaterial">Pointer auf das Material</param>
	///<param name ="iLongitude"> Anzahl der Vertices um die Achse, je h�her dieser Wert, desto mehr Polygone</param>
	///<param name ="iLattitude"> Anzahl der Vertices entlang der R�hrenbiegung, je h�her dieser Wert, desto mehr Polygone</param>
	///<param name ="bInner"> Flag, ob die Innen und Endseiten der R�hre erzeugt werden sollen (default = true)</param>
	void InitArc(float fRadiusInner, float fRadiusOuter, float fRadiusArc, float faArc, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 24, bool bInner = true); // Initialisiert eine Rohrbogen-Geometrie, fRadiusInner = innerer R�hrenradius, fRadiusOuter = �u�erer R�hrenradius, fRadiusArc = Gesamtradius des Rohrbogens, faArc = zu zeichnender �ffnungswinkel des Rohrbogens im Bogenm�, iLongitude = Anzahl der radialen Vertexunterteilungen, pmaterial = Materialpointer, iLattitude = Anzahl der Vertexunterteilungen entlang des Rohres, bInner = true, wenn Innenleben des Rohres erzeugt werden soll   
};

}