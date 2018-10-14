#pragma once

#include "Geo.h"
#include "Light.h"
#include "HitPoint.h"
#include "Faces.h"

namespace Vektoria
{

class CGeoTriangleList : public CGeo
{
	friend class CPlacement;
	friend class CGeoTriangleLists;
	friend class CGeoWalls;
	friend class CGeoWall;
	friend class CGeoWing;
	friend class CNode;
	friend class CNode3D;
	friend class CGeos;
	friend class CGeo;
protected:
	///<summary> Zeichnet die Geometrie und alle Untergeometrien (wird automatisch von �berhierarchie aufgerufen).</summary>
	/// <param name= "fDistanceToCameraSquare"> Quadrat des Abstandes zur Kamera </param>
	/// <param name= "mGlobal"> Die globale Matrix des �bergeordneten Knotens </param>
	/// <param name= "pcamera"> Pointer auf die Kamera, f�r die gerade gerendert wird </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	void Draw(float & fDistanceToCameraSquare, CHMat & mGlobal, CCamera * pcamera, int & iTick);

public:
	// --------------
	// Hauptmethoden:
	// --------------

	///<summary> Konstruktor.</summary>
	CGeoTriangleList();

	///<summary> Destruktor.</summary>
	~CGeoTriangleList();

	///<summary> Initialisiert die Dreiecksliste.<para></para>
	/// Sollte genau einmal aufgerufen werden, nachdem man alle Punkte durch AddVertex()-Aufrufe gesetzt hat.</summary>
	void Init();

	///<summary> Deinitialisiert die Dreiecksliste.</summary>
	void Fini();

	///<summary> // Kopiert Vertices und Indices der �bergebenen trianglelist in die aktuelle hinein (nur Pointerliste).</summary>
	///<param name = "trianglelist">In die vorliegende Dreiecksliste zu kopierende Dreiecksliste</param>
	void CopyVertices(CGeoTriangleList & trianglelist);

	///<summary> Kopiert die Parameter und Vertices und erzeugt dabei auch neue Kopien der Vertices.</summary>
	///<param name = "trianglelist">In die vorliegende Dreiecksliste zu kopierende Dreiecksliste</param>
	void CopyHierarchy(CGeoTriangleList & trianglelist); 

	///<summary> Vertauscht die Vertexreihenfolge und dreht Normalen- und Tangentenvektor um 180 Grad.</summary>
	void Flip();

	///<summary> Vertauscht die Vertexreihenfolge, l�sst aber anders als Flip den Normalen- und Tangentenvektor unbeeinflusst.<para></para>
	/// Dies ist wichtig f�r die korrekte Anzeige nach Spiegelungen.</summary>
	void FlipSpin();	

	///<summary> Macht jedes Polygon flach, indem die Normalenvektoren senkrecht zur Fl�che ausgerichtet werden.</summary>
	void FlattenFaces(); 

	///<summary> Wandelt das Mesh in ein Subdivision-Mesh mit mehr Polygonen um.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	void Subdivide(float fLengthMax);  

	///<summary> Wandelt das Mesh in ein Subdivision-Mesh mit mehr Polygonen um. Es wird nur die X-Richtung ber�cksichtigt.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	void SubdivideX(float fLengthMax); 

	///<summary> Wandelt das Mesh in ein Subdivision-Mesh mit mehr Polygonen um. Es wird nur die Y-Richtung ber�cksichtigt.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	void SubdivideY(float fLengthMax); 

	///<summary> Wandelt das Mesh in ein Subdivision-Mesh mit mehr Polygonen um. Es wird nur die Z-Richtung ber�cksichtigt.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	void SubdivideZ(float fLengthMax); 

	///<summary> Extrahiert ein Subdivision-Mesh mit mehr Polygonen aus dem vorliegenden Mesh.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	CGeoTriangleList * ExtractSubdivition(float fLengthMax); 

	///<summary> Extrahiert ein Subdivision-Mesh mit mehr Polygonen aus dem vorliegenden Mesh. Es wird nur die X-Richtung ber�cksichtigt.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	CGeoTriangleList * ExtractSubdivitionX(float fLengthMax);
	
	///<summary> Extrahiert ein Subdivision-Mesh mit mehr Polygonen aus dem vorliegenden Mesh. Es wird nur die Y-Richtung ber�cksichtigt.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	CGeoTriangleList * ExtractSubdivitionY(float fLengthMax);
	
	///<summary> Extrahiert ein Subdivision-Mesh mit mehr Polygonen aus dem vorliegenden Mesh. Es wird nur die Z-Richtung ber�cksichtigt.</summary>
	///<param name = "trianglelist">Maximale Kantenl�nge in Units, liegt der Abstand zweier benachbarter Vertices �ber diesem Grenzwert, wird ein neuer Vertex in der Mitte hinzugef�gt.</param>
	CGeoTriangleList * ExtractSubdivitionZ(float fLengthMax);
	
	///<summary> Versucht, die Tangenten und die Bitangenten f�r das Bumpmapping aus den gegebenen UV-Koordianten zu erraten.<para></para>
	/// Algorithmus von Tobias Breiner. <para></para>
	/// Vorzugsweise bei Objekten zu verwenden, bei denen die Texturen gespiegelt sind.</summary>
	void EstimateTangentsAndBitangents();

	///<summary> Versucht, die Tangenten und die Bitangenten f�r das Bumpmapping aus den gegebenen UV-Koordianten zu erraten.<para></para>
	/// Algorithmus von �mit �r�mcek. <para></para>
	/// Vorzugsweise bei importierten Objekten zu verwenden.</summary>
	void EstimateTangentsAndBitangents2();


	///<summary> Berechnet, ob der Strahl r irgendein Dreieck der Geometrie trifft, gibt true aus, wenn ja..</summary>
	///<param name = "r">Strahl</param>
	///<param name = "vIntersection">Schnittpunkt(nicht unbedingt der N�chste und nicht unbedingt derjenige der zum Betrachter zeigt!)</param>
	///<param name = "fDistanceSquare">Quadrierte der Distanz zwischen Strahlanfang (r.vOrigin) und Schnittpunkt.</param>
	///<param name = "iMatGlobal">Nummer der Instanz der Geometrie (bei zusammenlaufenden Hierarchien, kann eine Geometrie mehrfach referenziert werden)</param>
	bool Intersects(CRay & r, CHVector & vIntersection, float & fDistanceSquare, int & iMatGlobal); 

	///<summary> Berechnet, ob der Strahl r ein Dreieck der Geometrie trifft, gibt true aus, wenn ja, Der hitpoint ist dann der Schnittpunkt.<summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "hitpoint"> Schnittpunkt </param>
	///<param name= "iMaxVertices"> Begrenzung der Vertices (da bei gro�en Geometrien die Schnittpunktberechnung sehr lange dauern kann) </param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgef�hrt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in gro�en Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	bool Intersects(CRay & r, CHitPoint & hitpoint, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Berechnet, ob der Strahl r irgendein Dreieck der Geometrie trifft, gibt true aus, wenn ja.</summary>
	///<param name = "r">Strahl</param>
	///<param name = "iMaxVertices">Eventuelle Maximalzahl an Vertices. Liegt die Geometrie dar�ber, wird die �berpr�fung �bersprungen  (hilfreich, da eine Geometrie�berpr�fung sehr langsam sein kann) </param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgef�hrt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in gro�en Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	bool Intersects(CRay & r, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Sendet die Ver�nderungen der Dreieckstabelle an die Grafikkarte.
	/// Achtung, nur in Notf�llen verwenden, da langsam!</summary>
	void Update();

	///<summary> Sendet die Geometriedaten aufbereitet an das Rendermodul und erzeugt dadurch die Geometrie auf der Grafikkarte bzw. den Grafikkarten. <para></para>
	/// Wird automatisch aufggerufen.</summary>
	void Create();

	///<summary> Gibt die Fl�che mit der Position iFace aus, falls diese nicht vorhanden ist, wird false ausgegeben.</summary>
	///<param name = "iFace">Nummer der Fl�che in der Fl�chenliste</param>
	///<param name = "face">Fl�che, die zur�ckgegeben wird</param>
	bool GetFace(int iFace, CFace & face);

	///<summary> Berechnet irgendeinen zuf�lligen interpolierten Vertex auf der Oberfl�che .</summary>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	void CalcRandomVertex(CVertex & vertexInterpolated);
	
	///<summary> F�gt der Geometrie einen Vertex hinzu.<para></para>
	/// �berladene Funktion.</summary>
	///<param name= "pvertex"> Hinzuzuf�gender Vertex</param>
	void AddVertex(CVertex * pvertex);

	///<summary> H�ngt ein Vertex von der Geometrie ab, gibt true aus, wenn es funktioniert hat.<para></para>
	/// �berladene Funktion.</summary>
	///<param name= "pvertex"> Abzuh�ngender Vertex</param>
	bool SubVertex(CVertex *pvertex);

	///<summary> Reduziert Redundanzen in der Geometriebeschreibung. <para></para>
	/// Gleiche Vertices werden dabei zusammengef�gt. <para></para>
	/// Achtung! Dauert bei gro�en Geometrien extrem lange (quadratische Laufzeit bez�glich der Anzahl der Vertices)!</summary>
	///<param name = "bCheckNormals">Soll die Normaleninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "fPosThresholdRadius">Wie nah m�ssen zwei Vertices in Units sein, damit sie zusammengef�gt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz d�rfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenma� maximal haben, damit sie zusammengef�gt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah m�ssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengef�gt werden?</param>
	void ReduceRedundancy(bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);

	///<summary> F�llt in einem Polygonnetz eventuelle L�cken mit Polygonen.</summary>
	void FillCracks();

	///<summary> F�llt in einem Polygonnetz eventuelle L�cken mit Polygonen.</summary>
	void Stopf();


	///<summary> Berechnet das arithmetische Mittel von allen adjazenten Fl�chennormalen, das Objekt wirkt dadurch gerundet.</summary>
	void SmoothFaces();

	///<summary> Erneuert die optionalen Topologiedaten (Zusatzinformationen zu adjazenten Facetten und �hnlichen Vertices).</summary>
	void UpdateTopology();

protected:
	// --------------
	// Hilfsmethoden:
	// --------------

	void TriSub(CGeoTriangleList * ptrianglelist, CVertex * pvertex0, CVertex * pvertex1, CVertex * pvertex2, float fLengthMax, int eKind, int iRecursionDepth = 0);
	void TriSubDisplace(CGeoTriangleList * ptrianglelist, CVertex * pvertex0, CVertex * pvertex1, CVertex * pvertex2, float fLengthMax, float fStrength, int iRecursionDepth = 0);
	float DistanceExt(CHVector vDist,  int eKind);

public:

	///<summary> Liste der Facetten.<para></para>
	CFaces m_faces;

	///<summary> Hilfsvariable: Pointer auf die letzte geladene Facette.<para></para>
	CFace * m_pfaceLast;
};

}