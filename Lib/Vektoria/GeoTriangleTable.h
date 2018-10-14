#pragma once

#include "Geo.h"
#include "Light.h"
#include "Faces.h"

#define INDEX_INCREASE 1024

namespace Vektoria
{

	

class CGeoTriangleTable : public CGeo
{
	friend class CPlacement;
	friend class CGeoBezierTables;
	friend class CGeoTriangleTables;
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
	CGeoTriangleTable();

	///<summary> Destruktor.</summary>
	~CGeoTriangleTable();

	///<summary> // Kopiert Vertices und Indices der übergebenen triangletable in die aktuelle hinein (nur Pointerliste).</summary>
	void CopyVertices(CGeoTriangleTable & triangletable); 

	///<summary> Kopiert die Triangletable mitsamt ihrer Unterhierarchie (erzeugt neue Instanzen).</summary>
	///<param name= "triangletable"> Zu kopierende Triangletable</param>
	void CopyHierarchy(CGeoTriangleTable & triangletable);

	///<summary> Initialisiert die Dreieckstabelle.<para></para>
	/// Sollte genau einmal aufgerufen werden, nachdem man alle Punkte durch AddVertex()-Aufrufe gesetzt und mit AddIndex indiziert hat.</summary>
	void Init();

	///<summary> Deinitialisiert die Dreieckstabelle.</summary>
	void Fini();

	///<summary> Sendet die Veränderungen der Dreieckstabelle an die Grafikkarte.<para></para>
	/// Achtung, nur in Notfällen verwenden, da langsam!</summary>
	void Update();

	///<summary> Setzt den nächsten Vertexindex.<para></para>
	/// Achtung! Sollte nach den AddVertex-Aufrufen und vor dem Init-Aufruf verwendet werden.</summary>
	///<param name = "iIndex">Nächster Vertexindex (Indizes beginnen bei Null)</param>
	void AddIndex(int iIndex);

	///<summary> Sendet die Geometriedaten aufbereitet an das Rendermodul und erzeugt dadurch die Geometrie auf der Grafikkarte bzw. den Grafikkarten. Wird automatisch aufggerufen.</summary>
	void Create();

	///<summary> Vertauscht die Vertexreihenfolge und dreht Normalen- und Tangentenvektor um 180 Grad.</summary>
	void Flip(); 

	///<summary> Vertauscht die Vertexreihenfolge, lässt aber anders als Flip den Normalen- und Tangentenvektor unbeeinflusst (wichtig für die korrekte Anzeige nach Spiegelungen).</summary>
	void FlipSpin(); 

	///<summary> Gibt eine dem TriangleTable äquivalente TriangleList aus.</summary>
	CGeoTriangleList * CopyToTriangleList(); 

	///<summary> Versucht, die Tangenten und die Bitangenten für das Bumpmapping aus den gegebenen UV-Koordianten zu erraten.<para></para>
	/// Algorithmus von Tobias Breiner. <para></para>
	/// Vorzugsweise bei Objekten zu verwenden, bei denen die Texturen gespiegelt sind.</summary>
	void EstimateTangentsAndBitangents(); 

	///<summary> Versucht, die Tangenten und die Bitangenten für das Bumpmapping aus den gegebenen UV-Koordianten zu erraten.<para></para>
	/// Algorithmus von Ümit Örümcek. <para></para>
	/// Vorzugsweise bei importierten Objekten zu verwenden.</summary>
	void EstimateTangentsAndBitangents2();

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

	///<summary> Reduziert Redundanzen in der Geometriebeschreibung. <para></para>
	/// Gleiche Vertices werden dabei zusammengefügt. <para></para>
	/// Achtung! Dauert bei großen Geometrien extrem lange (quadratische Laufzeit bezüglich der Anzahl der Vertices)!</summary>
	///<param name = "bCheckNormals">Soll die Normaleninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengefügt.</param>
  	///<param name = "fPosThresholdRadius">Wie nah müssen zwei Vertices in Units sein, damit sie zusammengefügt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz dürfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenmaß maximal haben, damit sie zusammengefügt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah müssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengefügt werden?</param>
	void ReduceRedundancy(bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);

	///<summary> Macht jedes Polygon flach, indem die Normalenvektoren senkrecht zur Fläche ausgerichtet werden.</summary>
	void FlattenFaces();

	///<summary> Berechnet das arithmetische Mittel von allen adjazenten Flächennormalen, das Objekt wirkt dadurch gerundet.</summary>
	void SmoothFaces(); 

	///<summary> Gibt die Fläche mit der Listenposition iFace aus, falls diese nicht vorhanden ist, wird false ausgegeben.</summary>
	///<param name = "iFace">Nummer der Fläche in der Flächenliste</param>
	///<param name = "face">Fläche, die zurückgegeben wird</param>
	bool GetFace(int iFace, CFace & face);

	///<summary> Berechnet irgendeinen zufälligen interpolierten Vertex auf der Oberfläche .</summary>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	void CalcRandomVertex(CVertex & vertexInterpolated);

	// ----------------------------
	// TODO: Noch zu Programmieren:
	// ----------------------------

	void Subdivide(float fLengthMax);  // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenlänge fLengthMax
	void SubdivideX(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenbreite fLengthMax in X-Richtung
	void SubdivideY(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantenhöhe fLengthMax in Y-Richtung
	void SubdivideZ(float fLengthMax); // Wandelt Mesh in ein Subdivision-Mesh mit mehr Polygonen um, abhängig von der maximalen Kantentiefe fLengthMax in Z-Richtung

	CGeoTriangleTable * ExtractSubdivition(float fLengthMax); // Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh, abhängig von der maximalen Kantenlänge fLengthMax
	CGeoTriangleTable * ExtractSubdivitionX(float fLengthMax);// Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh, abhängig von der maximalen Kantenbreite fLengthMax in X-Richtung
	CGeoTriangleTable * ExtractSubdivitionY(float fLengthMax);// Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh, abhängig von der maximalen Kantenhöhe fLengthMax in Y-Richtung
	CGeoTriangleTable * ExtractSubdivitionZ(float fLengthMax);// Extrahiert Subdivision-Mesh mit mehr Polygonen aus dem aktuellen Mesh,  abhängig von der maximalen Kantentiefe fLengthMax in Z-Richtung

protected:
	///<summary> Redundanter Konstruktor, notwendig, da man den normalen Konstruktor nicht aus CGeo aufrufen kann.</summary>
	void Construct(); 

	void TriSub(CGeoTriangleTable * ptrianglelist, CVertex * pvertex0, CVertex * pvertex1, CVertex * pvertex2, float fLengthMax, int eKind, int iRecursionDepth = 0);
	void TriSubDisplace(CGeoTriangleTable * ptrianglelist, CVertex * pvertex0, CVertex * pvertex1, CVertex * pvertex2, float fLengthMax, float fStrength, int iRecursionDepth = 0);
	float DistanceExt(CHVector vDist, int eKind);

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

	///<summary> Liste der Facetten.<para></para>
	CFaces m_faces;

	///<summary> Hilfsvariable: Pointer auf die letzte geladene Facette.<para></para>
	CFace * m_pfaceLast;

};

}