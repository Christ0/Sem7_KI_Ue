#pragma once

#include "Geo.h"
#include "Light.h"

namespace Vektoria
{

class CGeoLineList : public CGeo
{
	friend class CPlacement;
	friend class CGeoLineLists;
	friend class CGeoWalls;
	friend class CGeoWall;
	friend class CGeoWing;
	friend class CNode;
	friend class CNode3D;
	friend class CGeos;
	friend class CGeo;
protected:
	///<summary> Zeichnet die Geometrie und alle Untergeometrien (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "fDistanceToCameraSquare"> Quadrat des Abstandes zur Kamera </param>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "pcamera"> Pointer auf die Kamera, für die gerade gerendert wird </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	void Draw(float & fDistanceToCameraSquare, CHMat & mGlobal, CCamera * pcamera, int & iTick);

public:
	// --------------
	// Hauptmethoden:
	// --------------

	///<summary> Konstruktor.</summary>
	CGeoLineList();

	///<summary> Destruktor.</summary>
	~CGeoLineList();

	///<summary> Initialisiert die LineList.<parfa></para>
	/// Sollte genau einmal aufgerufen werden, nachdem man alle Linien durch eine gerade Anzahl von AddVertex()-Aufrufen gesetzt hat.</summary>
	void Init();

	///<summary> Deinitialisiert die Linienliste.</summary>
	void Fini();

	///<summary> Kopiert die Vertices der übergebenen linelist in die aktuelle hinein, erzeugt aber keine neuen Kopien der Vertices, sondern kopiert nur die Pointer.</summary>
	///<param name = "linelist">In die vorliegende Linienliste zu kopierende Linienliste</param>
	void CopyVertices(CGeoLineList & linelist); 

	///<summary> Kopiert die Parameter und Vertices und erzeugt dabei auch neue Kopien der Vertices.</summary>
	///<param name = "linelist">In die vorliegende Linienliste zu kopierende Linienliste</param>
	void CopyHierarchy(CGeoLineList & linelist);

	///<summary> Sendet die Veränderungen der Linelist an die Grafikkarte.<para></para>
	/// Achtung, nur in Notfällen verwenden, da langsam!</summary>
	void Update();

	///<summary> Sendet die Geometriedaten aufbereitet an das Rendermodul und erzeugt dadurch die Geometrie auf der Grafikkarte bzw. den Grafikkarten. <para></para> 
	/// Wird automatisch aufgerufen.</summary>
	void Create();

	///<summary> Berechnet irgendeinen zufälligen interpolierten Vertex auf dem Linienzug.</summary>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	void CalcRandomVertex(CVertex & vertexInterpolated);





};

}