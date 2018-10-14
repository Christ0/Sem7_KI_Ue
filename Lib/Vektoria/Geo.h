 #pragma once
#include "Face.h"
#include "Vertexs.h"
#include "Material.h"
#include "Node3D.h"
#include "ApiRender.h"
#include "../VektoriaMath/HVector.h"

#define COMPAREV_DIST 0
#define COMPAREV_X 1
#define COMPAREV_Y 2
#define COMPAREV_Z 3
#define COMPAREV_DISPLACE 4
#define COMPAREV_TIMES 5



//--------------------------------------------
// CGeo: Klasse für Geometrien
//
// Autor: Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------
namespace Vektoria
{

class CLight;
class CGeoCube;
class CGeos;
class CScenes;


enum EMagnet
{
	eMagnet_Center,
	eMagnet_SurfaceNormal,
	eMagnet_X,
	eMagnet_Y,
	eMagnet_Z
};

enum EMapping
{
	eMapping_Cylindrical = 0,
	eMapping_Quadrocylindrical,
	eMapping_Bicylindrical,
	eMapping_Quadrobicylindrical,
	eMapping_Orthographic,
	eMapping_Biorthographic,
	eMapping_Cylindrical_Tiled
};



class CHitPoint;

class CGeo : public CNode3D
{
	friend class CGeos;
	friend class CGeoPointList;
	friend class CGeoLineList;
	friend class CGeoTriangleTable;
	friend class CGeoTriangleList;
	friend class CGeoTriangleStrip;
	friend class CDeviceCursor;
	friend class CGeoWing;
	friend class CGeoWings;
	friend class CPlacement;

protected:

	///<summary> Trägt die Szene in die Ahnen-Szenenliste ein.</summary>
	/// <param name= "pscene"> Pointer auf eine Szene, die ein Vorgänger ist. </param>
	void SetScene(CScene * pscene);

	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat &mGlobal, int & iTick, float & fTimeDelta);

	///<summary> Zeichnet die Geometrie und alle Untergeometrien (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "fDistanceToCameraSquare"> Quadrat des Abstandes zur Kamera </param>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "pcamera"> Pointer auf die Kamera, für die gerade gerendert wird </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	virtual void Draw(float & fDistanceToCameraSquare, CHMat & mGlobal, CCamera * pcamera, int & iTick);

	///<summary> Hilfsroutine für das Picking (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "r"> Kollisionsstrahl </param>
	/// <param name= "vIntersection"> Kollisionspunkt (hier stehen natürlich nur sinnvolle Werte drin, wenn Geometrie getroffen wurde </param>
	/// <param name= "fDistanceSquare"> Quadrat der Entfernung vom Strahlurssprung zum Kollisionspunkt dieseer Geometrie(hier stehen natürlich nur sinnvolle Werte drin, wenn Geometrie getroffen wurde </param>
	/// <param name= "fDistanceSquareMin"> Quadrat der Entfernung vom Strahlurssprung zum ersten Kollisionspunkt aller untergordneten Geometrien  (hier stehen natürlich nur sinnvolle Werte drin, wenn Geometrie getroffen wurde </param>
	/// <param name= "pzg"> Pointer auf die gefundene Geometrie, falls keine Geometrie getroffen wurde, ist pzg gleich NULL  </param>
	void PickGeo(CRay r, CHVector & vIntersection, float & fDistanceSquare, float & fDistanceSquareMin, CGeo * pzg);

	///<summary>  Echtes kubisches UV-Mapping mit gleichem Bild pro Seite, Hilfsroutine für die MapCubic-Methoden.</summary>
	void MapCubicHelp(int eKind, int iRepeat = 0, bool bDirection = false); 
public:
	///<summary> Konstruktor.</summary>
	CGeo();

	///<summary> Destruktor.</summary>
	~CGeo();

	///<summary> Kopiert die Geometrie mitsamt ihrer Unterhierarchie (erzeugt neue Instanzen).</summary>
	///<param name= "geo"> Zu kopierende Geometrie</param>
	void CopyHierarchy(CGeo & geo);

	///<summary> Initialisiert die Geometrie nachdem die Vertices gesetzt sind.</summary>
	void Init(); 

	///<summary> Finalisiert eine Geometrie.</summary>
	void Fini(); 

	///<summary> Fügt der Geometrie einen Vertex hinzu.</summary>
	///<param name= "vertex"> Hinzuzufügender Vertex</param>
	void AddVertex(CVertex *vertex);

	///<summary> Hängt ein Vertex ab, gibt true aus, wenn es funktioniert hat.</summary>
	///<param name= "vertex"> Abzuhängender Vertex</param>
	bool SubVertex(CVertex *vertex);

	///<summary> Berechnet irgendeinen zufälligen interpolierten Vertex auf der Oberfläche .</summary>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	virtual void CalcRandomVertex(CVertex & vertexInterpolated);

	///<summary> Berechnet die Axis Alligned Bounding Boxen neu.</summary>
	virtual void UpdateAABB();

	///<summary> Zentriert die Geometrie, sodass der lokale Ursprung in der Mitte zwischen vMin und vMax liegt.</summary>
	void Center(); 

	//----------------------------
	// Lade- und Speichermethoden:
	//----------------------------

	///<summary> Lädt vorgefertige Geometrie mit dem Dateinamen "acName.vg" aus den Ordner "Geos/acName" der Lib.<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name= "acName"> Objektnamen</param>
	bool LoadPreset(char * acName);

	///<summary> Speichert vorgefertige Geometrie mit dem Dateinamen "acName.vg" in den Ordner "Geos/acName" der Lib.<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name= "acName">Objektnamen</param>
	bool SavePreset(char * acName);

	///<summary> Lädt die Parameterdaten mitsamt untergeordneter Hieracrhie aus einer Vektoria-Geometrie-Datei (.vg).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Geometriedatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyGeo.vg" oder ".\\geos\\MyGeo.vg" </param>
	bool Load(char * acPath);

	///<summary> Speichert die Parameterdaten mitsamt untergeordneter Hieracrhie in eine Vektoria-Geometrie-Datei (.vg).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Geometriedatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyGeo.vg" oder ".\\geos\\MyGeo.vg" </param>
	bool Save(char * acPath);

protected: 

	///<summary> Lädt eine Geometrie aus einer Vektoria-Geometrie-Datei (.vg).</summary>
	///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
	///<param name="id">Eindeutige Identifikationsnummer der zu ladenden Geometrie innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id = -1, float fVersion = 14.11f);

	///<summary> Speichert eine Geometrie in eine Vektoria-Geometrie-Datei (.vg).</summary>
	///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
	///<param name= "bWithID"> Flag, ob die eigene Knoten-ID mit abgespeichert werden soll</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

public:

	//-----------------
	// Mappingmethoden:
	//-----------------

	///<summary> Planares UV-Mapping entlang der X-Achse.</summary>
	void MapPlanarX(); 

	///<summary> Planares UV-Mapping entlang der Y-Achse.</summary>
	void MapPlanarY();  

	///<summary> Planares UV-Mapping entlang der Z-Achse.</summary>
	void MapPlanarZ(); 

	///<summary>  Echtes kubisches UV-Mapping mit gleichem Bild pro Seite.</summary>
	///<param name= "iUVRepeat"> Gibt an, wie oft die Textur wiederholt werden soll (Default = 1 Mal)</param>
	void MapCubic(int iUVRepeat = 1);

	///<summary>  Echtes kubisches UV-Mapping mit gleichem Bild pro Seite, hier wird der Normalenvektor als Grundlage genommen.
	///<param name= "iUVRepeat"> Gibt an, wie oft die Textur wiederholt werden soll (Default = 1 Mal)</param>
	void MapCubicByDirection(int iUVRepeat = 1);

	///<summary> Vereinfachtes kubisches UV-Mapping.</summary>
	void MapCubicPlanar(); 

	///<summary> Echtes kubisches UV-Mapping mit verschiedenen Bildern pro Seite.</summary>
	void MapCubicVektorian(); 

	///<summary> Echtes kubisches UV-Mapping mit verschiedenen Bildern pro Seite, hier wird der Normalenvektor als Grundlage genommen.</summary>
	void MapCubicVektorianByDirection(); 

	///<summary> Zylindrisches UV-Mapping um die Y-Achse.</summary>
	void MapCylindricalY(); 

	///<summary> Bizylindrisches UV-Mapping um die Y-Achse.</summary>
	void MapBicylindricalY(); 

	// --------------------------------------
	// Breiner- & Barr-Modellierungsmethoden:
	// --------------------------------------

	///<summary> Twisting um die X-Achse.</summary>
	///<param name= "faStrength"> Drehwinkel im Bogenmaß auf eine Unit bezogen (Beispiel: bei PI wird ein 3 Einheiten langes Objekt anderthalbmal um die X-Achse gewunden)</param>
	void TwistX(float faStrength);

	///<summary> Twisting um die Y-Achse.</summary>
	///<param name= "faStrength"> Drehwinkel im Bogenmaß auf eine Unit bezogen (Beispiel: bei PI wird ein 3 Einheiten hohes Objekt anderthalbmal um die Y-Achse gewunden)</param>
	void TwistY(float faStrength);

	///<summary> Twisting um die Z-Achse.</summary>
	///<param name= "faStrength"> Drehwinkel im Bogenmaß auf eine Unit bezogen (Beispiel: bei PI wird ein 3 Einheiten tiefes Objekt anderthalbmal um die Z-Achse gewunden)</param>
	void TwistZ(float faStrength);

	///<summary> Bending um die X-Achse.</summary>
	///<param name= "fRadius"> Biegeradius </param>
	///<param name= "faSection"> Abschnitt in Einheiten, auf die sich eine Komplettbiegung (TWOPI) bezieht. <para></para> 
	///Beispiel: Bei PI würde ein eine Unit langer Körper zu einem U-förmigen Objekt verbogen</param>
	void BendX(float fRadius, float faSection);

	///<summary> Bending um die Y-Achse.</summary>
	///<param name= "fRadius"> Biegeradius </param>
	///<param name= "faSection"> Abschnitt in Einheiten, auf die sich eine Komplettbiegung (TWOPI) bezieht. <para></para> 
	///Beispiel: Bei PI würde ein eine Unit hoher Körper zu einem U-förmigen Objekt verbogen</param>
	void BendY(float fRadius, float faSection);

	///<summary> Bending um die Z-Achse.</summary>
	///<param name= "fRadius"> Biegeradius </param>
	///<param name= "faSection"> Abschnitt in Einheiten, auf die sich eine Komplettbiegung (TWOPI) bezieht. <para></para> 
	///Beispiel: Bei PI würde ein eine Unit tiefer Körper zu einem U-förmigen Objekt verbogen</param>
	void BendZ(float fRadius, float faSection);

	///<summary> Tapering in Richtung der X-Achse.</summary>
	///<param name= "fStrength"> Stärke des Taperings pro Einheit <para></para>
	///Beispiel: Bei fStrength=0.3 würde ein zwei Einheiten langer Körper an der Spitze um 60% verbreitert.</param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void TaperX(float fStrength, bool bInfluenceX=false, bool bInfluenceY=true, bool bInfluenceZ = true);

	///<summary> Tapering in Richtung der Y-Achse.</summary>
	///<param name= "fStrength"> Stärke des Taperings pro Einheit <para></para>
	///Beispiel: Bei fStrength=0.3 würde ein zwei Einheiten hoher Körper an der Spitze um 60% verbreitert.</param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void TaperY(float fStrength, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true);

	///<summary> Tapering in Richtung der Z-Achse.</summary>
	///<param name= "fStrength"> Stärke des Taperings pro Einheit <para></para>
	///Beispiel: Bei fStrength=0.3 würde ein zwei Einheiten tiefer Körper am Ende um 60% verbreitert.</param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = false)</param>
	void TaperZ(float fStrength, bool bInfluenceX=true, bool bInfluenceY=true, bool bInfluenceZ = false);

	///<summary> Wellenform in Richtung der X-Achse.</summary>
	///<param name= "fAmplitude"> Amplitude der Welle (Wellenhöhe) in Einheiten </param>
	///<param name= "fWavelength"> Wellenlänge der Welle (Abstand zwischen zwei Wellenbergen) in Einheiten </param>
	///<param name= "faPhase"> Phase der Welle (Welleananfang) in Einheiten (Default = 0.0) </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void WaveX(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true);

	///<summary> Wellenform in Richtung der Y-Achse.</summary>
	///<param name= "fAmplitude"> Amplitude der Welle (Wellenhöhe) in Einheiten </param>
	///<param name= "fWavelength"> Wellenlänge der Welle (Abstand zwischen zwei Wellenbergen) in Einheiten </param>
	///<param name= "faPhase"> Phase der Welle (Welleananfang) in Einheiten (Default = 0.0) </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void WaveY(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true);

	///<summary> Wellenform in Richtung der Z-Achse.</summary>
	///<param name= "fAmplitude"> Amplitude der Welle (Wellenhöhe) in Einheiten </param>
	///<param name= "fWavelength"> Wellenlänge der Welle (Abstand zwischen zwei Wellenbergen) in Einheiten </param>
	///<param name= "faPhase"> Phase der Welle (Welleananfang) in Einheiten (Default = 0.0) </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = false)</param>
	void WaveZ(float fAmplitude, float fWavelength, float faPhase = 0.0F, bool bInfluenceX = true, bool bInfluenceY = false, bool bInfluenceZ = true);

	///<summary> Zufälliges Shuffeln um die Y-Achse.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) des Shuffle in Einheiten </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void ShuffleX(float fAmplitudeMax, bool bInfluenceX = false, bool bInfluenceY = true, bool bInfluenceZ = true);

	///<summary> Zufälliges Shuffeln um die Y-Achse.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) des Shuffle in Einheiten </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void ShuffleY(float fAmplitudeMax, bool bInfluenceX = true, bool bInfluenceY = false, bool bInfluenceZ = true);

	///<summary> Zufälliges Shuffeln um die Y-Achse.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) des Shuffle in Einheiten </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = false)</param>
	void ShuffleZ(float fAmplitudeMax, bool bInfluenceX = true, bool bInfluenceY = true, bool bInfluenceZ = false);

	///<summary> Zufälliges Shuffeln um die Y-Achse.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) des Shuffle in Einheiten </param>
	///<param name= "pgraphnoise"> Zufallsgraph.</param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void ShuffleX(float fAmplitudeMax, CGraphNoise * pgraphnoise, bool bInfluenceX = false, bool bInfluenceY = true, bool bInfluenceZ = true);

	///<summary> Zufälliges Shuffeln um die Y-Achse.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) des Shuffle in Einheiten </param>
	///<param name= "pgraphnoise"> Zufallsgraph.</param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void ShuffleY(float fAmplitudeMax, CGraphNoise * pgraphnoise, bool bInfluenceX = true, bool bInfluenceY = false, bool bInfluenceZ = true);

	///<summary> Zufälliges Shuffeln um die Y-Achse.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) des Shuffle in Einheiten </param>
	///<param name= "pgraphnoise"> Zufallsgraph.</param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = false)</param>
	void ShuffleZ(float fAmplitudeMax, CGraphNoise * pgraphnoise, bool bInfluenceX = true, bool bInfluenceY = true, bool bInfluenceZ = false);

	///<summary> Verschiebt die Vertexpositionen, so dass die Geometrie nicht mehr so mathematisch-korrekt ausssieht, sondern eher gammlig.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) in Einheiten </param>
	void Gammel(float fAmplitudeMax);

	///<summary> Verschiebt die Vertexpositionen, so dass die Geometrie nicht mehr so mathematisch-korrekt ausssieht, sondern eher gammlig.</summary>
	///<param name= "fAmplitudeMax"> Maximale Amplitude (Auslenkung) in Einheiten </param>
	///<param name= "vMid"> Mittelpunkt der Verzerrung.</param>
	///<param name= "pgraphnoise"> Zufallsgraph.</param>
	void Gammel(float fAmplitudeMax, CHVector vMid, CGraphNoise * pgraphnoise);

	///<summary> Wellenriffeln um die Y-Achse.</summary>
	///<param name= "fAmplitude"> Amplitude der Welle (Wellenhöhe) in Einheiten </param>
	///<param name= "iHarmonics"> Anzahl der Wellen um die Y-Achse </param>
	///<param name= "faPhase"> Phase der Welle (Welleananfang) in Einheiten (Default = 0.0) </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void RippleY(float fAmplitude, int iHarmonics, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true);

	///<summary> Hartes Wellenriffeln um die Y-Achse.</summary>
	///<param name= "fAmplitude"> Amplitude der Welle (Wellenhöhe) in Einheiten </param>
	///<param name= "iHarmonics"> Anzahl der Wellen um die Y-Achse </param>
	///<param name= "faPhase"> Phase der Welle (Welleananfang) in Einheiten (Default = 0.0) </param>
	///<param name= "bInfluenceX"> Sollen die Vertices in X-Richtung verschoben werden? (Default = true)</param>
	///<param name= "bInfluenceY"> Sollen die Vertices in Y-Richtung verschoben werden? (Default = false)</param>
	///<param name= "bInfluenceZ"> Sollen die Vertices in Z-Richtung verschoben werden? (Default = true)</param>
	void RippleYHard(float fAmplitude, int iHarmonics, float faPhase = 0.0F, bool bInfluenceX=true, bool bInfluenceY=false, bool bInfluenceZ = true);

	///<summary> Transformiert alle Punkte der Geometrie mit der Transformationsmatrix m.</summary>
	///<param name= "m"> Transformationsmatrix </param>
	void Transform(CHMat & m);

	///<summary> Vereinigt die Vorliegende Geometrie und die Geometrie pzg zu einer Einzigen.</summary>
	///<param name= "pzg"> Zeiger auf die andere Geometrie </param>
	///<param name= "m"> Transformationsmatrix (die zweite Geometrie qwird damit vor der Vereinigung transformiert)</param>
	///<param name= "bKill"> , Flag, ob pzg danach gelöscht werden soll, ansonsten kann man mit pzg ganz normal weiterarbeiten (default=false)</param>
	void Unite(CGeo * pzg, CHMat & m, bool bKill = false);

	///<summary> Gibt true aus, wenn es sich bei der vorliegenden Geometrie um ein TriangleList handelt, ansonsten false.</summary>
	bool IsTriangleList(); 

	///<summary> Gibt true aus , wenn es sich  bei der vorliegenden Geometrie um ein TriangleStrip handelt, ansonsten false.</summary>
	bool IsTriangleStrip(); 

	///<summary> Neuartige Modellierungsmethode (Magnet, der die Vertices im Radius fRadius anzieht bzw. abstößt).</summary>
	///<param name= "v"> Position des virtuellen Magneten </param>
	///<param name= "frStrength"> Radius, innerhalb dessen der Magnet wirkt </param>
	///<param name= "bAttract"> Flag, ob der Magnet anzieht (true) oder abstößt (false) </param>
	///<param name= "eKind"> Art des Magneten:<para></para>
	///eMagnet_Center: Punktförmiger Magnet<para></para>
	///eMagnet_SurfaceNormal: Magnet, der sich in Richtung der Oberflächennormale auswirkt <para></para>
	///eMagnet_X: Flächenmagnet der sich nur in X-Richtung auswirkt<para></para>
	///eMagnet_Y: Flächenmagnet der sich nur in Y-Richtung auswirkt<para></para>
	///eMagnet_Z: Flächenmagnet der sich nur in Z-Richtung auswirkt</param>
	void Magnet(CHVector v, float fRadius, float frStrength, bool bAttract, EMagnet eKind = eMagnet_Center);

	///<summary> Reduziert redundante Vertices (Achtung!!! Braucht sehr lange, nur in Notfällen während der Laufzeit benutzen).</summary>
	///<param name= "bSmooth"> Flag, ob Normalenvektoren neu berechnet werden sollen (default = true)</param>
	///<param name= "fMaxDistanceToUnite"> Maximale Entfernung zwischen zwei benachbarten Kantenvektoren<para></para> 
	///(Nur wenn die tatsächliche Entferung darunter liegt, kollabiert die Kante </param>
	///<param name= "fBevel"> Die Tiefe, in die zusammengeführte Vetrices in Richtung der negatigen gemittelten Normalen verschoben werden, um runden Rand zu erzeugen.  </param>
	void ReduceRedundancy(bool bSmooth = true, float fMaxDistanceToUnite = 0.0001f, float fBevel = 0.0f);

	///<summary> Setzt Material auf Geometiemesh, kann auch während der Laufzeit geschehen.</summary>
	///<param name= "pmaterial"> Pointer auf das Material</param>
	void SetMaterial(CMaterial * pmaterial);

	///<summary> Dreht die Tangenten um 180 Grad.</summary>
	void FlipTangents(); 

	///<summary> Dreht die Bitangenten um 180 Grad.</summary>
	void FlipBitangents(); 

	///<summary> Gibt true aus, wenn irgenein transparentes Objekt an die Geometrie angehängt wurde.</summary>
	bool HasTransparent(); 

	///<summary> Informiert übergeordnete Knoten, ob die Geometrie ein transparenmtes Material enthält (wichtig für z-Buffer-Sortierung, wird automatisch aufgerufen)</summary>
	void UpdateTransparency(); 

	///<summary> Hängt eine Geometrie an eine andere Geometrie an.</summary>
	///<param name= "pgeo"> Pointer auf die anzuhängende Geometrie</param>
	void AddGeo(CGeo * pgeo);

	///<summary> Hängt die Geometrie wieder von der aktuellen Geometrie ab, gibt true aus, wenn es geklappt hat.</summary>
	///<param name= "pgeo"> Pointer auf die abzuhängende Geometrie</param>
	bool SubGeo(CGeo * pgeo);
	
	///<summary> Hängt einen Emitter an das vorliegende Geo an.</summary>
	///<param name="pemitter">Zeiger auf den anzuhängenden Emitter</param>
	void AddEmitter(CEmitter * pemitter);

	///<summary> Hängt den Emitter wieder von dem vorliegenden Geo ab, gibt true aus, wenn es funktioniert hat.</summary>
	///<param name="pemitter">Zeiger auf den abzuhängenden Emitter</param>
	bool SubEmitter(CEmitter * pemitter);

	///<summary> Erzeugt Material auf der Grafikkarte (Achtung! Sollte nur ein eiziges Mal aufgerufen werden!).</summary>
	void Create();

	///<summary> Sammelt Materialien des aktuellen Geos und der Untergeohierarchie (rekursiv) und meldet alle Materialien bei der Root an (wird automatisch beim ersten Tick aufgerufen).</summary>
	void CollectMaterials();

	//-------------------------------------------------------------------------------
	// Schnittpunktberechnungsmethoden 
	// (werden in CGeoTriangleStrip, CGeoTriangleList und CGeoTriangleTable überladen)
	//-------------------------------------------------------------------------------

	///<summary> Berechnet, ob der Strahl r ein Dreieck der Geometrie mit der Instanz iMatGlobal trifft, gibt true aus, wenn ja.</summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "vIntersection"> Schnittpunkt des Strahl mit der Geometrie (falls getroffen, ansonsten unsinnige Werte) </param>
	///<param name= "fDistanceSquare"> Quadrierter Abstand des Strahlursprungs mit der dem Schnittpunkt (falls getroffen, ansonsten unsinnige Werte) </param>
	///<param name= "iMatGlobal"> Nummer der Instanz </param>
	virtual bool Intersects(CRay & r, CHVector & vIntersection, float & fDistanceSquare, int & iMatGlobal);

	///<summary> Berechnet, ob der Strahl r ein Dreieck der Geometrie trifft, gibt true aus, wenn ja, Der hitpoint ist dann der Schnittpunkt.<summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "hitpoint"> Schnittpunkt </param>
	///<param name= "iMaxVertices"> Maximalanzahl der Vertices, die die Geometrie haben darf (da eine Schnittpunktberechnung mit großen Geometrien sehr lange dauert)</param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgeführt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in großen Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	virtual bool Intersects(CRay & r, CHitPoint & hitpoint, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	///<summary> Berechnet, ob Strahl r irgendein Dreieck der Geometrie trifft, gibt true aus, wenn ja.</summary>
	///<param name= "r"> Kollisionsstrahl</param>
	///<param name= "iMaxVertices"> Maximalanzahl der Vertices, die die Geometrie haben darf (da eine Schnittpunktberechnung mit großen Geometrien sehr lange dauert)</param>
	///<param name= "bSpeedUpByAABBs"> Flag, ob erst eine Schnittpunktberechnung mit der Axis Aligned Bounding Box durchgeführt werden soll. <para></para>
	/// Dies beschleunigt die Schnittpunktberechnung in großen Szenen aber funktioniert nur bei eingeschalteten AABBs. </param>
	virtual bool Intersects(CRay & r, int iMaxVertices = INT_MAX, bool bSpeedUpByAABBs = true);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Vertex-Listencontainer der Geometrie.</summary>
	CVertexs m_vertices;

	///<summary> Pointer auf die Liste der angehängten Geos.</summary>
	CGeos * m_pgeos;

	///<summary> Pointer auf die Liste der Unter-Emitter.</summary>
	CEmitters * m_pemitters;

	///<summary> Zeiger auf das Material des Geos.</summary>
	CMaterial * m_pmaterial; 

	///<summary> Eindeutige ID des Materials (Achtung nicht mit Knoten-ID-verwechseln!).</summary>
	int m_idMaterial;

	///<summary> Axis Alligned Bounding Box.</summary>
	CAABB m_aabb;

	///<summary> Renderart.  </summary>
	int m_iRenderKind;

	///<summary> true, wenn Material der Geometrie irgendwo durchsichtige Anteile enthält.</summary>
	bool m_bTransparent; 

	///<summary> true, wenn die Geo erzeugt wurde.</summary>
	bool m_bCreated; 

	///<summary> true, wenn der Transparenzwert geändert wurde.</summary>
	bool m_bTransparencyChanged;

	///<summary> true vor demn ersten Rendering.</summary>
	bool m_bFirstDraw;

	///<summary> Liste der vier Lichter, welche am meisten Einfluss auf die Optik des Geos haben.</summary>
	unsigned int m_aidLightAffect[LIGHTS_MAX];

	///<summary> Anzahl der Lichter, welche das Aussehen des Geos beeinflussen (aus shadertechnischen Gründen max. 4).</summary>
	unsigned int m_iLightsAffectCount;

	///<summary> Szenenliste, mit denen das Geo verbunden ist.</summary>
	CScenes *  m_pscenesAnchestor;

};

}