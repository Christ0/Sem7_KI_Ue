#pragma once
#include "GeoTriangleStrip.h"
#include "GeoSweep.h"
#include "Face.h"

//------------------------------------------------------------------
// CCamera: Klasse für Röhren
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
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

	///<summary> Initialisiert eine gerade Röhre. <para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name ="fRadiusInner">Innenradius in Units</param>
	///<param name ="fRadiusOuter">Außenradius in Units</param>
	///<param name ="fLength">Länge in Units</param>
	///<param name ="pmaterial">Pointer auf das Material</param>
	///<param name ="iLongitude"> Anzahl der Vertices um die Achse, je höher dieser Wert, desto mehr Polygone</param>
	///<param name ="bInner"> Flag, ob die Innen und Endseiten der Röhre erzeugt werden sollen (default = true)</param>
	void InitStraight(float fRadiusInner, float fRadiusOuter, float fLength, CMaterial * pmaterial, int iLongitude = 24, bool bInner = true); // Initialisiert eine Röhren-Geometrie, fRadiusInner = innerer Röhrenradius, fRadiusOuter = äußerer Röhrenradius, fLength = Länge der Röhre, pmaterial = Materialpointer, iLongitude = Anzahl der radialen Vertices, bInner = true, wenn Innenleben des Rohres erzeugt werden soll

	///<summary> Initialisiert eine gebogene Röhre. <para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name ="fRadiusInner">Innenradius in Units</param>
	///<param name ="fRadiusOuter">Außenradius in Units</param>
	///<param name ="fRadiusArc">Radius der Biegung in Units</param>
	///<param name ="faArc">Winkel des Biegungsbogens im Bogenmaß (z.B. PI erzeugt einen u-förmigen Bogen)</param>
	///<param name ="fLength">Länge in Units</param>
	///<param name ="pmaterial">Pointer auf das Material</param>
	///<param name ="iLongitude"> Anzahl der Vertices um die Achse, je höher dieser Wert, desto mehr Polygone</param>
	///<param name ="iLattitude"> Anzahl der Vertices entlang der Röhrenbiegung, je höher dieser Wert, desto mehr Polygone</param>
	///<param name ="bInner"> Flag, ob die Innen und Endseiten der Röhre erzeugt werden sollen (default = true)</param>
	void InitArc(float fRadiusInner, float fRadiusOuter, float fRadiusArc, float faArc, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 24, bool bInner = true); // Initialisiert eine Rohrbogen-Geometrie, fRadiusInner = innerer Röhrenradius, fRadiusOuter = äußerer Röhrenradius, fRadiusArc = Gesamtradius des Rohrbogens, faArc = zu zeichnender Öffnungswinkel des Rohrbogens im Bogenmß, iLongitude = Anzahl der radialen Vertexunterteilungen, pmaterial = Materialpointer, iLattitude = Anzahl der Vertexunterteilungen entlang des Rohres, bInner = true, wenn Innenleben des Rohres erzeugt werden soll   
};

}