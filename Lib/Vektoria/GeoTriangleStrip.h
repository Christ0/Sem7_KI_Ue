#pragma once

#include "Geo.h"
#include "Light.h"
#include "GeoTriangleList.h"

#define INDEX_INCREASE 1024

namespace Vektoria
{



class CGeoTriangleStrip : public CGeo
{
	friend class CPlacement;
	friend class CGeoTriangleStrips;
	friend class CNode3D;
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
	CGeoTriangleStrip();

	///<summary> Destruktor.</summary>
	~CGeoTriangleStrip();

	///<summary> Kopiert den Trianglestrip mitsamt seiner Unterhierarchie (erzeugt neue Instanzen).</summary>
	///<param name= "trianglestrip"> Zu kopierender Trianglestrip</param>
	void CopyHierarchy(CGeoTriangleStrip & trianglestrip);

	///<summary> Initialisiert den Dreiecksstreifen.<para></para>
	/// Sollte genau einmal aufgerufen werden, nachdem man alle Punkte durch AddVertex()-Aufrufe gesetzt und mit AddIndex indiziert hat.</summary>
	void Init();

	///<summary> Deinitialisiert den Dreiecksstreifen.</summary>
	void Fini();

	///<summary> Sendet die Veränderungen der Punkteliste an die Grafikkarte.<para></para>
	/// Achtung, nur in Notfällen verwenden, da langsam!</summary>
	void Update();

	///<summary> Setzt den nächsten Vertexindex.<para></para>
	/// Sollte vor Init aufgerufen werden.</summary>
	///<param name = "iIndex">Nächster Vertexindex (Indizes beginnen bei Null)</param>
	void AddIndex(int iIndex);

	///<summary> Sendet die Geometriedaten aufbereitet an das Rendermodul und erzeugt dadurch die Geometrie auf der Grafikkarte bzw. den Grafikkarten. Wird automatisch aufggerufen.</summary>
	void Create();

	///<summary> Vertauscht die Vertexreihenfolge und dreht Normalen- und Tangentenvektor um 180 Grad.</summary>
	void Flip(); 

	///<summary> Vertauscht die Vertexreihenfolge, lässt aber anders als Flip den Normalen- und Tangentenvektor unbeeinflusst (wichtig für die korrekte Anzeige nach Spiegelungen).</summary>
	void FlipSpin(); 

	///<summary> Gibt eine dem TriangleStrip äquivalente TriangleList aus.</summary>
	CGeoTriangleList * CopyToTriangleList(); 

	///<summary> Versucht, die Tangenten und die Bitangenten für das Bumpmapping aus den gegebenen UV-Koordianten zu erraten.</summary>
	void EstimateTangentsAndBitangents();

	///<summary> Berechnet, ob der Strahl r irgendein Dreieck der Geometrie trifft, gibt true aus, wenn ja..</summary>
	///<param name = "r">Strahl</param>
	///<param name = "vIntersection">Schnittpunkt(nicht unbedingt der Nächste und nicht unbedingt derjenige der zum Betrachter zeigt!)</param>
	///<param name = "fDistanceSquare">Quadrierte der Distanz zwischen Strahlanfang (r.vOrigin) und Schnittpunkt.</param>
	///<param name = "iMatGlobal">Nummer der Instanz der Geometrie (bei zusammenlaufenden Hierarchien, kann eine Geometrie mehrfach referenziert werden)</param>
	bool Intersects(CRay & r, CHVector & vIntersection, float & fDistanceSquare, int & iMatGlobal);

	///<summary> Berechnet, ob der Strahl r ein Dreieck der Geometrie trifft, gibt true aus, wenn ja, Der hitpoint ist dann der Schnittpunkt.<summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "hitpoint"> Schnittpunkt </param>
	///<param name= "iMaxVertices"> Begrenzung der Vertices (da bei großen Geometrien die Schnittpunktberechnung sehr lange dauern kann) </param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgeführt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in großen Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	bool Intersects(CRay & r, CHitPoint & hitpoint, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Berechnet, ob der Strahl r irgendein Dreieck der Geometrie trifft, gibt true aus, wenn ja.</summary>
	///<param name = "r">Strahl</param>
	///<param name = "iMaxVertices">Eventuelle Maximalzahl an Vertices. Liegt die Geometrie darüber, wird die Überprüfung übersprungen  (hilfreich, da eine Geometrieüberprüfung sehr langsam sein kann) </param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgeführt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in großen Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	bool Intersects(CRay & r, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Gibt die Fläche mit der Position iFace aus, falls diese nicht vorhanden ist, wird false ausgegeben.</summary>
	///<param name = "iFace">Nummer der Fläche in der Flächenliste</param>
	///<param name = "face">Fläche, die zurückgegeben wird</param>
	bool GetFace(int iFace, CFace & face);

	///<summary> Berechnet irgendeinen zufälligen interpolierten Vertex auf der Oberfläche .</summary>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	void CalcRandomVertex(CVertex & vertexInterpolated);

protected:
	///<summary> Setzt den ersten Vertexindex.<para></para>
	/// Sollte vor Init aufgerufen werden.</summary>
	void AddIndexFirst(int iIndex);

	///<summary> Redundanter Konstruktor, notwendig, da man den normalen Konstruktor nicht aus CGeo aufrufen kann.</summary>
	void Construct(); 

public:
	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Array von Indices.</summary>
	int * m_aiIndex;

	///<summary> Anzahl der Indices.</summary>
	int m_iIndices;

	///<summary> Anzahl der aktuell allokierten Indices.</summary>
	int m_iIndicesAllocated;
};

}