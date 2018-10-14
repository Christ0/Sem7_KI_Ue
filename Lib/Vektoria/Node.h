#pragma once
#include <limits.h>
#include "Nodes.h"
#include "FileVektoria.h"

namespace Vektoria
{

class CGeoCube;
class CRoot;
class CPlacement;

#define TEXT_BUFFER 256

#define S_KINDDIMENSION_UNDEFINED 0
#define S_KINDDIMENSION_ROOT 1
#define S_KINDDIMENSION_2D 2
#define S_KINDDIMENSION_3D 3
#define S_KINDDIMENSION_HARDWARE 4


#define S_KINDSUB_UNDEFINED 0
#define S_KINDSUB_GEOWALL 1
#define S_KINDSUB_GEOWINDOW 2
#define S_KINDSUB_GEOWING 3
#define S_KINDSUB_GEOCYLINDER 4
#define S_KINDSUB_GEOSPHERE 5
#define S_KINDSUB_GEODOME 6
#define S_KINDSUB_GEOTUBE 7
#define S_KINDSUB_GEOSLICE 8
#define S_KINDSUB_GEOCONE 12
#define S_KINDSUB_GEOELLIPSOID 13
#define S_KINDSUB_GEOTRIANGLE 14
#define S_KINDSUB_GEOSKYBOX 30
#define S_KINDSUB_GEOELLIPSOIDTILED 53
#define S_KINDSUB_GEOSPHERETILED 55
#define S_KINDSUB_GEODOMETILED 56
#define S_KINDSUB_GEOARROW 60
#define S_KINDSUB_GEOINFOVERTEX 61
#define S_KINDSUB_GEOINFOGEO 62
#define S_KINDSUB_GEOFRUSTUM 63
#define S_KINDSUB_GEOCUBE 70
#define S_KINDSUB_GEOTETRAHEDRON 70
#define S_KINDSUB_GEOICOSAHEDRON 71
#define S_KINDSUB_GEOOCTAHEDRON 72
#define S_KINDSUB_GEODODECAHEDRON 73





#define S_KIND_UNDEFINED 0
#define S_KIND_AUDIO 10
#define S_KIND_BACKGROUND 20
#define S_KIND_CAMERA 30
#define S_KIND_DEVICEKEYBOARD 40
#define S_KIND_DEVICEMOUSE 41
#define S_KIND_DEVICECURSOR 42
#define S_KIND_DEVICEGAMECONTROLLER 43
#define S_KIND_EMITTER 50
#define S_KIND_FRAME 60
#define S_KIND_GEO_BEGIN 70 // Achdung, bidde ned die Reihenfolge vertausche, da an annerer Stelle e Bereichabfrache is
#define S_KIND_GEO_TRIANGLELIST 71 
#define S_KIND_GEO_TRIANGLESTRIP 72
#define S_KIND_GEO_TRIANGLETABLE 73
#define S_KIND_GEO_POINTLIST 74
#define S_KIND_GEO_LINELIST 75
#define S_KIND_GEO_END 76 
#define S_KIND_HARDWARE 80
#define S_KIND_IMAGE 90
#define S_KIND_J 100
#define S_KIND_KEYFRAME 110
#define S_KIND_LIGHT 120
#define S_KIND_LIGHT_PARALLEL 121
#define S_KIND_LIGHT_RADIAL 122
#define S_KIND_LIGHT_SPOT 123
#define S_KIND_MATERIAL 130
#define S_KIND_N 140
#define S_KIND_OVERLAY 150
#define S_KIND_PLACEMENT 160
#define S_KIND_PHYSICAL 161
#define S_KIND_Q 170
#define S_KIND_ROOT 180
#define S_KIND_SCENE 190
#define S_KIND_TEXTURE 200
#define S_KIND_U 210
#define S_KIND_VIEWPORT 220
#define S_KIND_WRITING 230
#define S_KIND_WRITINGCHAR 231
#define S_KIND_WRIBEL 232
#define S_KIND_X 240
#define S_KIND_Y 250
#define S_KIND_Z 260


// Fortlaufende Zählung der Knotenobjekte, mir fällt leider keine bessere Möglichkeit ein, als eine globale Variable // Id 0 ist für Sonderobjete vorgesehen.
static unsigned int g_id = 1; 

///<summary> Die aktuelle Version von Vektoria (notwendig für die Aufwärtskombablilität).</summary> 
static float g_fVektoriaVersion = 16.00f;


class CNode 
{
	friend class CNodes;
	friend class CCamera;
	friend class CEmitter;
	friend class CPlacements;
	friend class CPlacement;
	friend class CGeoWall;
	friend class CGeoWindow;
	friend class CGeoWindows;
	friend class CGeoWing;
	friend class CGeos;
	friend class CGeo;
	friend class CGeoTriangleList;
	friend class CGeoTriangleStrip;
	friend class CNode3D;
	friend class CSprites;
	friend class CSprite;
	friend class CScenes;
	friend class CScene;
	friend class CAudios;
	friend class CAudio;
	friend class CHardwares;
	friend class CHardware;
	friend class CMaterial;
	friend class CRoot;
	friend class CFrame;
	friend class CDeviceKeyboard;
	friend class CDeviceMouse;
	friend class CDeviceGameController;

protected:
	///<summary> Setzt den Pointer zum Wurzelknoten (wird automatisch von der darüber liegenden Hierarchie aufgerufen).</summary>
	///<param name = "proot"> Pointer auf die Wurzel</param>
	void SetRoot(CRoot* proot);

	///<summary> Informiert den Knoten, dass er pnodeParent als Elternknoten hat, pnodeParent wird in die Elternliste m_nodesParents eingefügt.</summary>
	///<param name = "pnodeParent"> Pointer auf einen Vater, an den der vorliegende Knoten angehängt werden soll</param>
	void AddParent(CNode* pnodeParent);

	///<summary> Hängt pnode pnodeParent, falls vorhanden, als Elternknoten ab, pnodeParent wird danach nicht mehr in der Elternliste auftauchen, gibt true aus, falls es funktioniert hat.</summary>
	///<param name = "pnodeParent"> Pointer auf den Vater, von dem der vorliegende Knoten abgehängt werden soll</param>
	bool SubParent(CNode* pnodeParent);

	///<summary>Schaut, ob als Elternknoten pnodeParent vorhanden ist, gibt true aus, falls ja.</summary>
	///<param name = "pnodeParent"> Pointer auf den potentiellen Vater</param>
	bool HasParent(CNode* pnodeParent);

	///<summary> Informiert den Knoten, dass er pnodeChild als Kindknoten hat, pnodeChild wird in die Kinderliste m_nodesParents eingefügt.</summary>
	///<param name = "pnodeChild"> Pointer auf ein Kind, das an den der vorliegenden Knoten angehängt werden soll</param>
	void AddChild(CNode* pnodeChild);

	///<summary> Hängt pnode pnodeChild, falls vorhanden, als Kindknoten ab, pnodeChild wird danach nicht mehr in der Kinderliste auftauchen, gibt true aus, falls es funktioniert hat.</summary>
	///<param name = "pnodeChild"> Pointer auf ein Kind, das vom vorliegenden Knoten abgehängt werden soll</param>
	bool SubChild(CNode* pnodeChild);

	///<summary>Schaut, ob als Kindknoten pnodeParent vorhanden ist, gibt true aus, falls ja.</summary>
	///<param name = "pnodeParent"> Pointer auf den potentielle Kindknoten</param>
	bool HasChild(CNode* pnodeParent);

	///<summary> Informiert den Knoten, dass er pnodeChild als Kindknoten hat, pnodeChild wird in die Kinderliste m_nodesParents eingefügt.<para></para>
	/// Anders als bei AddChild kann nur maximal ein Kinderknoten hinzugefügt werden.</summary>
	///<param name = "pnodeChild"> Pointer auf ein Kind, das an den der vorliegenden Knoten angehängt werden soll</param>
	void SetChild(CNode* pnodeChild);

	///<summary> Initialisierungsmethode (wird automatisch von der darüber liegenden Hierarchie aufgerufen).</summary>
	void Init();

	///<summary> Deinitialisierungsmethode (wird automatisch von der darüber liegenden Hierarchie aufgerufen).</summary>
	void Fini();

	///<summary>Lädt eine Knotenbeschreibung aus einem Vektoria-Materialfile, vererbbare Hilfmethode.</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	void Load(CFileVektoria & filevektoria);

	///<summary>Speichert eine Knotenbeschreibung in ein Vektoria-Materialfile, vererbbare Hilfsmethode.</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	void Save(CFileVektoria & filevektoria);

	///<summary>Liefert die Knoten-"Ahnenliste" in nodes (von unten nach oben).</summary>
	///<param name = "nodes"> Node-Container für die Ahnenliste.</param>
	void GetAnchestors(CNodes & nodes);

	///<summary>Liefert die Knoten-"Nachkommenliste" in nodes (von oben nach unten).</summary>
	///<param name = "nodes"> Node-Container für die Nachkommenliste.</param>
	void GetDescendants(CNodes & nodes);



public:
	///<summary> Konstruktor.</summary>
	CNode();

	///<summary> Destruktor.</summary>
	~CNode();

	///<summary> Kopiert Knoteninformationen. </summary>
	///<param name = "pnode"> Zu kopierender Knoten</param>
	void Copy(CNode & node);

	///<summary> Gibt die eindeutige ID des Knotens zurück.</summary>
    unsigned int GetID(); 
    
	///<summary> Setzt einen benutzerdefinierten Namen für diesen Knoten (z.B. "PMoon" für ein Placement, an dem der Mond angehängt ist).</summary>
	///<param name = "acName"> ASCII-String</param>
	void SetName(const char* acName);

	///<summary> Gibt den benutzerdefinierten Namen des Knotens zurück.</summary>
    const char* GetName(); 

	///<summary> Gibt den Namen der Klasse (Achtung, nicht Knotennamen!) zurück.</summary>
	virtual const char* ClassName() { return "CNode"; } 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um ein Placement handelt, ansonsten false.</summary>
    bool IsPlacement(); 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um eine TriangleList handelt, ansonsten false.</summary>
    bool IsTriangleList(); 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um ein TriangleStrip handelt, ansonsten false.</summary>
    bool IsTriangleStrip(); 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um eine Geo handelt, ansonsten false.</summary>
    bool IsGeo(); 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um ein LightSpot handelt, ansonsten false.</summary>
	bool IsLightSpot(); 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um ein 2D-Knoten (Sprite) handelt, ansonsten false.</summary>
	bool IsNode2D(); 

	///<summary> Gibt true zurück, wenn es sich bei diesem Knoten um ein 3D-Knoten handelt, ansonsten false.</summary>
	bool IsNode3D(); 

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie zum Zeichnen ein.</summary>
	void SetDrawingOn();

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie zum Zeichnen aus.</summary>
	void SetDrawingOff();

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie zum Speichern wieder ein. (Default)</summary>
	void SetSavingOn();

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie zum Speichern aus.</summary>
	void SetSavingOff();

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie ein.</summary>
	void SwitchOn(); 

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie aus.</summary>
	void SwitchOff(); 

	///<summary> Gibt true zurück, wenn Knoten angeschaltet ist.</summary>
	bool IsOn(); 

	///<summary> Sucht in der angehängten Hierarchie abwärts rekursiv nach Node mit dem angegebenen Namen und gibt einen Pointer darauf aus.</summary>
	///<param name = "acName"> Name des Knotens (muss natürlich vorher mit SetName() eindeutig benannt worden sein) </param>
	CNode * SearchName(char * acName);

	///<summary> Sucht in der angehängten Hierarchie abwärts rekursiv nach Node mit der angegebenen ID  und gibt einen Pointer darauf aus.</summary>
	///<param name = "id"> Identifikationsnummer des Knotens</param>
	CNode * SearchID(int id);

	///<summary> Sucht in der angehängten Hierarchie abwärts rekursiv nach Node mit der angegebenen ID Loaded  und gibt einen Pointer darauf aus.</summary>
	///<param name = "id"> Identifikationsnummer des Knotens, die abgespreichert wurde (muss nicht mit der aktuellen übereinstimmen</param>
	CNode * SearchIDLoaded(int id);

	///<summary> Gibt die Anzahl an Kinderknoten zurück.</summary>
	int GetNrOfChildren(); 

	///<summary>Gibt die Anzahl an Elternknoten zurück.</summary>
	int GetNrOfParents();

	///<summary>Gibt true zurück, wenn es sich bei diesem Knoten um einen Knoten vom Typ iKind (defines KIND_...) handelt, ansonsten false.</summary>
	///<param name = "id"> Define-Nummer des Typs</param>
	bool TypeOf(int iKind);

	///<summary>Setzt alle Marker (m_bMarked) in dieser Entität und der darunter liegenden Hierarchie auf false.</summary>
	void Demark();


	//------------------
	// Membervariablen:
	//------------------

	///<summary>Containerklasse der Elternknoten.</summary>
	CNodes m_nodesParents; 

	///<summary>Containerklasse der Kindknoten.</summary>
	CNodes m_nodesChildren; 

	///<summary>Handelt es sich um einen 2D-Knoten (2), einen 3D-Knoten (3) oder sonst eine Art (0)?</summary>
	int m_eKindDimension; 

	///<summary>Art des Knotens.</summary>
	int m_eKind; 

	///<summary>Unterart des Knotens.</summary>
	int m_eKindSub; 

	///<summary>Boolsches Flag, um Zweig des Graphen aus (false) bezüglich der Transformationsrechnungen bzw. an (true) zu schalten.</summary>
	bool m_bSwitchTick;  

	///<summary>Boolsches Flag, um Zweig des Graphen aus (false) bezüglich des Renderings bzw. an (true) zu schalten.</summary>
	bool m_bSwitchDraw;

	///<summary>Boolsches Flag, um Zweig des Graphen aus (false) bezüglich des Speicherns bzw. an (true) zu schalten.</summary>
	bool m_bSwitchSave;

	///<summary>Optionaler Name des Knotens.</summary>
	char* m_acName; 

	///<summary>Eindeutige ID des Knotens.</summary>
	unsigned int m_id; 

	///<summary>Falls mit Load geladen, ID des geladenen Knotens (wichtig zur Vernetzung nach dem Laden).</summary>
	unsigned int m_idLoaded; 

	///<summary>Marker zur vielfältigen Verwendung in verschiedenen Algorithen, muss nach Verwendung immer wieder auf false gesetzt werden.</summary>
	bool m_bMarked;

	///<summary>Pointer zum Wurzelknoten (wird automatisch gesetzt, sobald das Objekt in die Hierarchie eingefügt wird).</summary>
	CRoot*  m_proot;

};

}