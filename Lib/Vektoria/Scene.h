#pragma once
#include "ApiRender.h"
#include "LightParallels.h"
#include "Cameras.h"
#include "Node3D.h"
#include "Audios.h"
#include "ScenePhysics.h"
#include "SceneWeather.h"

//---------------------------------------------------
// CScene: Klasse f�r ein Szenenobjekt 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//---------------------------------------------------

namespace Vektoria
{

	class CPlacements; 

	class CScene : public CNode3D
	{
		friend class CRoot;
		friend class CScenes;
	protected:

		// --------------
		// Basismethoden:
		// --------------

		///<summary> Wird automatisch jedes Frame von Root aus aufgerufen.</summary>
		///<param name="iTick">Nummer des Ticks</param>
		///<param name="fTimeDelta">Zeit in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		void Tick(int & iTick, float & fTimeDelta);

		///<summary> Sucht alle Cameras (wird pro Tick automatisch aufgerufen).</summary>
		void SearchForCameras();

		///<summary> Kopiert alle Eigenschaften des Placements rekursiv in der Hierarchie hinunter, bel�sst die Eigenschaften, wo ein Entry-Flag gesetzt wurde.</summary>
		void CopyDownwards();

	public:
		///<summary> Konstruktor.</summary>
		CScene();

		///<summary> Destruktor.</summary>
		~CScene();

		///<summary> Kopieroperator.</summary>
		///<param name="scene">Zu kopierende Szene</param>
		CScene operator=(CScene & scene);

		///<summary> Kopiermethode (Kopiert Informationen aus scene in die vorliegende Szene).</summary>
		///<param name="scene">Zu kopierende Szene</param>
		void Copy(CScene & scene);

		///<summary> Initialisiert ein Szenenobjekt (Aufruf nicht unbedingt notwendig, da Werte schon im Konstruktor vern�nftig gesetzt werden).</summary>
		void Init(); 

		///<summary> Finaliisiert ein Szenenobjekt.</summary>
		void Fini();  

		// ---------------------
		// Verkn�pfungsmethoden:
		// ---------------------

		///<summary> H�ngt ein Placement an eine Szene an.</summary>
		///<param name="scene">Pointer auf das anzuh�ngende Placement</param>
		void AddPlacement(CPlacement * pplacement);

		///<summary> H�ngt ein direktionales Licht an die Szene an.</summary>
		///<param name="scene">Pointer auf das anzuh�ngende Parallellicht</param>
		void AddLightParallel(CLightParallel * plightparallel);

		///<summary> H�ngt ein Audio an eine Szene an.</summary>
		///<param name="scene">Pointer auf das anzuh�ngende Audio</param>
		void AddAudio(CAudio * paudio);

		///<summary> H�ngt ein Placement von einer Szene ab, gibt true aus, wenn es geklappt hat.</summary>
		///<param name="scene">Pointer auf das abzuh�ngende Placement</param>
		bool SubPlacement(CPlacement * pplacement);

		///<summary> H�ngt ein direktionales Licht von der Szene ab, gibt true aus, wenn es geklappt hat.</summary>
		///<param name="scene">Pointer auf das abzuh�ngende Parallellicht</param>
		bool SubLightParallel(CLightParallel * pparallelLight);

		///<summary> H�ngt ein Audio von der Szene ab, gibt true aus, wenn es geklappt hat. </summary>
		///<param name="scene">Pointer auf das abzuh�ngende Audio</param>
		bool SubAudio(CAudio * paudio);

		// ----------------
		// Anzeigemethoden:
		// ----------------

		///<summary> Setzt die St�rke des ambienten Lichtes (Hintergrundslicht, welches die Schatten der Objekte ausleuchtet).<para></para>
		/// Die Farbe des Lichtes ist automatisch wei�, wenn dies nicht gewollt ist, als Parameter CColor nehmen.</summary>
		///<param name="frStrength">Lichtst�rke, 0.0 = aus, 1.0 = volle Pulle, vern�nftige Werte liegen zwischen 0.02 und 0.1</param>
		void SetLightAmbient(float frStrength); 

		///<summary> Setzt die Farbe des ambienten Lichtes (default = schwarz).</summary> 
		///<param name="frStrength">Lichtst�rke getrennt nach RGB-Werten, 0.0 = aus, 1.0 = volle Pulle, vern�nftige Werte liegen jeweils zwischen 0.02 und 0.1</param>
		void SetLightAmbient(CColor color);

		///<summary> L�dt eine Szene mitsamt untergeordneter Hierarchie aus einer Vektoria-Szenendatei (.vs).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Szenendatei (mit Suffix), absolute und relative Pfade sind m�glich, z.B. "C:\\MyScene.vs" oder ".\\Scenes\\MyScene.vs" </param>
		bool Load(char * acPath);

		///<summary> Speichert die Szene mitsamt untergeordneter Hierarchie in eine Vektoria-Szenendatei (.vs).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Szenendatei (mit Suffix), absolute und relative Pfade sind m�glich, z.B. "C:\\MyScene.vs" oder ".\\Scenes\\MyScene.vs" </param>
		bool Save(char * acPath);

		// ---------------
		// Wettermethoden:
		// ---------------

		///<summary> Erzeugt einen Himmel mit Wetter und erm�glcht damit auch Wettereffekte.<para></para>
		/// Greift dabei auf Materialien der Vektoria-Library zur�ck, um einen Sky-Dome und die Wettereffdekte zu erzeugen.</summary>
		///<param name="pcamera">Point auf das Kameraplacment</param>
		void SetHeavenOn(CPlacement * pcamera);

		///<summary> Setzt die Positionskoordinaten auf der Erde. <para></para>
		/// Sonne, Mond und Sterne werden dann demensprechend berechnet.</summary>
		///<param name="faLongitude">Longitudinaler Winkel auf der Erde im Bogenma�. (Greenwich = 0.0f) </param>
		///<param name="faLongitude">H�henwinkel auf der Erde im Bogenma�. (�quator = 0.0f, Nordpopl = HALFPI) </param>
		void SetPosOnEarth(float faLongitude, float faLattitude);

		///<summary> Setzt die Tageszeit auf der Erde. </summary>
		///<param name="frTimeOfDay">Fraktionale Tageszeit (00:00 Uhr = 0.0f ... 12:00 Uhr = 0.5f ... 24:00 Uhr = 1.0f) </param>
		void SetTimeOfDay(float frTimeOfDay);

		///<summary> Setzt die Jahreszeit auf der Erde. </summary>
		///<param name="frTimeOfYear">Fraktionale Jahreszeit (Wintersonnenwende = 0.0f .. Fr�hjahrstagundnachtgleiche = 0.25f ... Sommersonnenwende = 0.5f ... Herbsttagundnachtgleiche = 0.75f) </param>
		void SetTimeOfYear(float frTimeOfYear);

		///<summary> Setzt die Dunstst�rke aller konnektierten Viewports.<para></para>
		/// Erkl�rung: Dunst ist im Gegensatz zur Nebel gleichm��ig, unbewegt und rein schaderbasiert. </summary>
		///<param name="fMistStrength">Dunstst�rke (Undurchdringlichkeit pro Einheit, z.B. kann man bei 0.2 f�nf Einheiten weit sehen), Default = 0.01</param>
		void SetMistStrength(float fMistStrength);

		///<summary> Setzt die Dunstfarbe aller konnektierten Viewports.<para></para>
		/// Erkl�rung: Dunst ist im Gegensatz zur Nebel gleichm��ig, unbewegt und rein schaderbasiert. </summary>
		///<param name="color">Dunstfarbe (RGB-Werte zwischen 0 und 1, A-Wert wird ignoriert)</param>
		void SetMistColor(CColor color);

		///<summary> Setzt die Nebelst�rke. </summary>
		///<param name="fFogStrength">St�rke des Nebels </param>
		void SetFogStrength(float fFogStrength);

		///<summary> Setzt die Schneest�rke auf dem Boden. </summary>
		///<param name="frSnowStrength">St�rke des Bodenschnees (0.0=kein Schnee liegt auf dem Boden ... 1.0 = alles voller Schnee) </param>
		void SetSnowStrength(float frSnowStrength);

		///<summary> Setzt die Bew�lkungsst�rke. </summary>
		///<param name="frCloudStrength">Setzt die Bew�lkungsst�rke </param>
		void SetCloudStrength(float frCloudStrength);

		///<summary> Setzt die St�rke des Niederschlags. <para></para>
		/// Ist die Temperatur unter dem Gefrierpunkt, kommt der Noederschlag als Schnee herunter, ansonsten als Regen.</summary>
		///<param name="fPrecipitation">St�rke des Niederschlags </param>
		void SetPrecipitationStrength(float fPrecipitation);

		///<summary> Setzt die aktuelle Temperatur des Szene. <para></para>
		/// Die physikalischen Parameter als auch die Art des Niederschlages werden dann demensprechen berechnet.</summary>
		///<param name="fTemperature">Temperatur in Grad Celsius </param>
		void SetTemperature(float fTemperature);

		///<summary> Schaltet zuf�lliges Wetter ein.<para></para>
		/// Sonnenschein, Wind, Regen, Schnee, etc. werden dann entsprechend der Erdposition, der Tages- und Jahreszeit sinnf�llig zuf�llig berechnet. </summary>
		void SetRandomWeatherOn();

		///<summary> Schaltet automatischen Wechsel zwischen Tag und Nacht bzw. Sommer und Winter ein.</summary>
		///<param name="fFlowFactor">Faktor, um wieviel die virtuelle Zeit schneller als die Reale Welt ist. </param>
		void SetHeavenFlowOn(float fFlowFactor);

		// -----------------------
		// Physikalische Methoden:
		// -----------------------

		///<summary> Setzt die maximale Wind- bzw. Wassergeschwindigkeit.<para></para>
		/// Nur wichtig, falls physikalische Objekte in der Szene vorhanden sind (z.B. Rauchpartikel).</summary>
		///<param name="fWindVelocityMax">Maximale Windgeschwindigkeit in m/s</param>
		void SetWindVelocityMax(float fWindVelocityMax);

		///<summary> Setzt die Volatilit�t der Wind-bzw. Wasserbewegung.<para></para>
		/// Nur wichtig, falls physikalische Objekte in der Szene vorhanden sind (z.B. Rauchpartikel).</summary>
		///<param name="frWindVelocityVolatility">Volatilit�t der Wind-bzw. Wasserbewegung (0=Wind weht immer mit gleichem Betrag, je h�her der Wert, desto mehr variiert das.)</param>
		void SetWindVelocityVolatility(float frWindVelocityVolatility);

		///<summary> Setzt die Wind- bzw. Wasserrichtung.<para></para>
		/// Nur wichtig, falls physikalische Objekte in der Szene vorhanden sind (z.B. Rauchpartikel).</summary>
		///<param name="faWindDirection">Winkel der Wasser- bzw. Windrichtung. (0 = Osten ... HALFPI = Norden ... PI = Westen ... THREEHALFPI = S�den)</param>
		void SetWindDirection(float faWindDirection);

		///<summary> Setzt die Volatilit�t der Wind- bzw. Wasserrichtung.<para></para>
		/// Nur wichtig, falls physikalische Objekte in der Szene vorhanden sind (z.B. Rauchpartikel).</summary>
		///<param name="faWindDirectionVolatility">Richtungsvolatilit�tswinkel (0 = Wind bl�st immer aus der selben Richtung ... TWOPI = Wind bl�st aus allen Richtungen)</param>
		void SetWindDirectionVolatility(float faWindDirectionVolatility);

	protected: 

		///<summary> L�dt eine Szenenbeschreibung aus einer Vektoria-SzenenDatei (.vs).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="id">Eindeutige Identifikationsnummer der zu ladenden Szene</param>
		///<param name="fVersion">Vektoriaversion, um Aufw�rtskombabilit�t zu gew�hrleisten, z.B. 14.11 f�r die Version 14 Patch 11 </param>
		void Load(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

		///<summary> Speichert eine Szenenbeschreibung in eine Vektoria-Szenendatei (.vs).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="bWithID">Soll die eigene Identifikationsnummer in das Szenenfile mit abgespeichert werden?</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

	public:

		///<summary> Gibt true aus, wenn die Kamera pcamera in die Szene blickt.</summary>
		///<param name="pcamera">Pointer auf die Kamera</param>
		bool HasCamera(CCamera * pcamera);

		///<summary> Hierarchischer Draw-Call (wird automatisch aufgerufen).</summary>
		///<param name="pcamera">Pointer auf die Kamera</param>
		///<param name="iTick">Nummer des Ticks</param>
		void Draw(CCamera * pcamera, int & iTick);

		///<summary> Schaltet das FrustumCulling an. Dies beschleunigt manche Szenen enorm, allerdings k�nnen (in speziellen seltenen F�llen) ohne exakte Kalkulation der BVHs manchmal Bildteile fehlen.</summary>
		void SetFrustumCullingOn(); 

		///<summary> Schaltet das FrustumCulling aus.</summary>
		void SetFrustumCullingOff(); 

		///<summary> Schaltet die exakte Kalkulation des Bounding Volume Hierarchy an und verhindert damit (sehr seltene) Artefakte beim FrustumCulling. <para></para>
		// Achtung!!! Geht enorm auf die Frame Rate, daher nur in Ausnehmef�llen zu empfehlen!</summary>
		void SetBVHExactCalculationOn(); 

		///<summary> Schaltet die exakte Kalkulation des Bounding Volume Hierarchy aus (default).</summary> 
		void SetBVHExactCalculationOff(); 

		///<summary> Gibt das erste Placement aus, welches durch den Strahl r getroffen wird.</summary>
		///<param name="r">Suchstrahl durch die Szene</param>
		///<param name="ePlacementSearch">Suchparameter: <para></para> 
		///ePlacementSearch_All = Alle Placements werden gesucht.<para></para> 
		///ePlacementSearch_OnlyWithDirectGeos = Nur Placements werden gesucht, an denen direkt untendran eine Geometrie angeh�ngt ist.<para></para> 
		///ePlacementSearch_OnlyWithDirectWribels = Nur Placements werden gesucht, an denen direkt untendran eine Wribels angeh�ngt ist.</param>
		CPlacement * PickPlacement(CRay & r, EPlacementSearch ePlacementSearch = ePlacementSearch_All);

		///<summary> Gibt alle Placements aus, welche durch den Strahl r getroffen werden.</summary>
		///<param name="r">Suchstrahl durch die Szene</param>
		///<param name="pzps">Instanziierter Container, indem danach alle gepickten Placements stehen.</param>
		///<param name="ePlacementSearch">Suchparameter: <para></para> 
		///ePlacementSearch_All = Alle Placements werden gesucht.<para></para> 
		///ePlacementSearch_OnlyWithDirectGeos = Nur Placements werden gesucht, an denen direkt untendran eine Geometrie angeh�ngt ist.<para></para> 
		///ePlacementSearch_OnlyWithDirectWribels = Nur Placements werden gesucht, an denen direkt untendran eine Wribels angeh�ngt ist.</param>
		void PickPlacements(CRay & r, CPlacements * zps, EPlacementSearch ePlacementSearch = ePlacementSearch_All);

		///<summary> Z�hlt die Anzahl der Geometrien in der Szene (Verschiedene Instanzen ein- und derselben Geometrie werden nur einmal gez�hlt).</summary>
		int CountGeos(); 

		///<summary> Kreiert die Szene (wird automatisch vor dem ersten Tick aufgerufen).</summary>
		void Create(); 

		///<summary> Sammelt alle Materialien in der Szene.</summary>
		void CollectMaterials(); 

		//-----------------
		// Membervariablen:
		// ----------------

		///<summary> Ursprung der Szene.</summary>
		CHMat m_mGlobal; 

		///<summary> Flag, welches true ist, falls das FrustumCulling an ist.</summary>
		bool m_bFrustumCulling; 

		///<summary> Flag, welches true ist, falls die Bounding Volume Hierarchy exakt berechnet werden soll (normalerweise nicht anzuraten, da Bildwiederholrate leidet)</summary>
		bool m_bBVHExactCalculation; 

		///<summary> Pointer auf eine Containerklasse, in der die angehangenen Placements liegen.</summary>
		CPlacements * m_pplacements;  

		///<summary> Containerklasse, in der die Parallellichter liegen.</summary>
		CLightParallels m_lightparallels; 

		///<summary> Containerklasse, in der die ambienten Sounds der Szene liegen.</summary>
		CAudios m_audios; 

		///<summary> Pointer auf die konnektierten Viewports (Kenntnis wichtig f�r die Rendercalls von Lichtern).</summary>
		CViewports * m_pviewports; 

		///<summary> Ambiente Hintergrundfarbe.</summary>
		CColor m_colorAmbient; 

		///<summary> pointer auf die Klasse f�r die physikalischen Parameter und Berechnungen der Szene.</summary>
		CScenePhysics * m_pscenephysics;

		///<summary> pointer auf die Klasse f�r die Wetterberechnungen der Szene.</summary>
		CSceneWeather * m_psceneweather;



	protected: 

		///<summary> Hilfsflag, welches true ist, wenn es sich um den ersten Tick handelt.</summary>
		bool m_bFirstTick;

		///<summary> Hier m�ssen alle Cameras verzeichnet sein, welche irgendwo die Szene betrachten.</summary>
		CCameras m_cameras;

	};

}