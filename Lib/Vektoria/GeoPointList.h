#pragma once

#include "Geo.h"
#include "Light.h"

namespace Vektoria
{

class CGeoPointList : public CGeo
{
	friend class CPlacement;
	friend class CGeoPointLists;
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
	CGeoPointList();

	///<summary> Destruktor.</summary>
	~CGeoPointList();

	///<summary> Initialisiert die Punktliste.
	/// Sollte genau einmal aufgerufen werden, nachdem man alle Punkte durch AddVertex()-Aufrufe gesetzt hat.</summary>
	void Init();

	///<summary> Deinitialisiert die Punktliste.</summary>
	void Fini();

	///<summary> Kopiert die Vertices der übergebenen pointlist in die aktuelle hinein, erzeugt aber keine neuen Kopien der Vertices, sondern kopiert nur die Pointer.</summary>
	///<param name = "pointlist">In die vorliegende Punkteliste zu kopierende Punkteliste</param>
	void CopyVertices(CGeoPointList & pointlist);

	///<summary> Kopiert die Parameter und Vertices und erzeugt dabei auch neue Kopien der Vertices.</summary>
	///<param name = "pointlist">In die vorliegende Punkteliste zu kopierende Punkteliste</param>
	void CopyHierarchy(CGeoPointList & pointlist);

	///<summary> Sendet die Veränderungen der Punkteliste an die Grafikkarte.
	/// Achtung, nur in Notfällen verwenden, da langsam!</summary>
	void Update();

	///<summary> Sendet die Geometriedaten aufbereitet an das Rendermodul und erzeugt dadurch die Geometrie auf der Grafikkarte bzw. den Grafikkarten. Wird automatisch aufggerufen.</summary>
	void Create();

	///<summary> Wählt irgendeinen zufälligen Vertex der Punktliste aus.</summary>
	///<param name="vertexRandom"> Zufällig ausgesuchter Vertex</param>
	void CalcRandomVertex(CVertex & vertexRandom);

};

}