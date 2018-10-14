#pragma once
#include "MakrosConfig.h"
#include "Scenes.h"
#include "Hardwares.h"
#include "Geo.h"
#include "GeoBezierTable.h"
#include "GeoQuad.h"
#include "GeoSkybox.h"
#include "GeoTube.h"
#include "GeoFrustum.h"
#include "GeoCone.h"
#include "GeoSweep.h"
#include "GeoSlice.h"
#include "GeoCylinder.h"
#include "GeoArrow.h"
#include "GeoInfoVertex.h"
#include "GeoInfoGeo.h"
#include "GeoEllipsoid.h"
#include "GeoCube.h"
#include "GeoTetrahedron.h"
#include "GeoIcosahedron.h"
#include "GeoOctahedron.h"
#include "GeoDodecahedron.h"
#include "GeoTetrahedronWire.h"
#include "GeoIcosahedronWire.h"
#include "GeoOctahedronWire.h"
#include "GeoDodecahedronWire.h"
#include "GeoCubeWire.h"
#include "GeoDodecahedronWerk.h"
#include "GeoTetrahedronWerk.h"
#include "GeoIcosahedronWerk.h"
#include "GeoOctahedronWerk.h"
#include "GeoCubeWerk.h"
#include "GeoGrid.h"
#include "GeoWall.h"
#include "GeoWindow.h"
#include "GeoWing.h"
#include "GeoSphere.h"
#include "GeoDome.h"
#include "GeoUtahTeapot.h"
#include "GeoUtahCup.h"
#include "ApiRender.h"
#include "Materials.h"
#include "FileX3D.h"
#include "File3DS.h" 
#include "FileBlender.h"
#include "FileWavefront.h"
#include "Images.h"
#include "Wribel.h"
#include "Wribels.h"
#include "Splash.h"
#include "GeoEllipsoidTiled.h"
#include "GeoSphereTiled.h"
#include "GeoDomeTiled.h"
#include "GeoTriangle.h"
#include "Placements.h"
#include "dinput.h" // TODO aus Vektoria-Core raus, da windows-spezifisch! Nur Wichtig füre DIK_...

#include "ApiSound.h"
#include "UtilLogFile.h"

#include "../VektoriaMath/Quaternion.h"
#include "../VektoriaMath/Plane.h"
#include "../VektoriaMath/Ray.h"

//---------------------------------------------------
// CRoot: Klasse für die Wurzel des Szenegrafen-Baumes
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------


namespace Vektoria
{

	class CApiRender;
// 	class CRenderDistributed;

	class CRoot : public CNode
	{
	public:
		///<summary> Konstruktor.</summary> 
		CRoot();

		///<summary> Destruktor.</summary>
		~CRoot();

		///<summary> Kopieroperator (etwas sinnlos, nur der Vollständigkeit halber drin).</summary>
		CRoot operator=(CRoot & root);

		///<summary> Kopiermethode (etwas sinnlos, nur der Vollständigkeit halber drin).</summary>
		void Copy(CRoot & root);

		///<summary> Holt die Vektoria-Versionsnummer inklusive Patch (für das Patch sind die zwei Nachkommastellen reserviert).</summary>
		float GetVersion();

		///<summary> Initialisiert die Wurzel, muss denSplashscreen übergeben bekommen, welches schon aufgerufen werden.<para></para>
		///Achtung 1: Die Funktion muss ganz am Anfang vor allen anderen Funktionen aufgerufen werden, weil sie das System freischaltet!<para></para>
		///Achtung 2: Splashscreen muss schon aufgerufen worden sein!</summary>
		///<param name="psplash">Zeiger auf den Splash-Screen</param>
		void Init(CSplash * psplash);

		///<summary> Diese Methode muss jedes Frame aufgerufen werden.</summary>
		///<param name="fTimeDelta">Zeit in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		bool Tick(float & fTimeDelta);

		///<summary> Finalisiert die Wurzel. Sollte ebenfalls aufgerufen werden.</summary>
		void Fini(); 

		///<summary> Hängt eine Szene an die Wurzel an.</summary>
		///<param name="pscene">Pointer auf die hinzuzufügende Szene</param>
		void AddScene(CScene * pscene);

		///<summary> Hängt eine Szene von der Wurzel ab, gibt false aus, wenn die angegebene Szene nicht ein Kind der Wurzel ist oder überhaupt nicht existiert, bei Erfolg wird true ausgegeben.</summary>
		///<param name="pscene">Pointer auf die zu löschende Szene</param>
		bool SubScene(CScene * pscene);

		///<summary> Hängt ein Frame (des aktuellen Computers) an die Wurzel an. Ersetzt das frühere (vor V14) AddFrameHere().</summary>
		///<param name="pframe">Pointer auf das hizuzufügende Frame</param>
		void AddFrame(CFrame * pframe);

		///<summary> Hängt dem aktuellen Computer an die Wurzel an, und an diesen wiederum den angegebenen Frame VERALTET, nur noch bis V15 der Aufwärtskompabilität halber unterstützt.</summary>
		///<param name="pframe">Pointer auf das hizuzufügende Frame</param>
		void AddFrameHere(CFrame * pframe);

		///<summary> Hängt einen fremden Computer bzw. ein Smartphone an die Wurzel an, für das Verteilte Rendering wichtig.</summary>
		///<param name="pmaterial">Pointer auf die hizuzufügende Hardware</param>
		void AddHardware(CHardware * phardware);

		///<summary> Fügt ein weiteres Material in die Materialliste der Wurzel hinzu.</summary>
		///<param name="pmaterial">Pointer auf das hizuzufügende Material</param>
		void AddMaterial(CMaterial * pmaterial);

		///<summary> Löscht ein Material aus der Materialliste der Wurzel, gibt true aus, wenn es funktioniert hat. </summary>
		///<param name="pmaterial">Pointer auf das zu löschende Material</param>
		bool SubMaterial(CMaterial * pmaterial);
		
		///<summary> Löscht alle Materialien  aus der Materialliste der Wurzel (außer dem Defaultmaterial), bei Erfolg wird true ausgegeben. <para></para>
		///Diese Methode ist sinnvoll vor dem Laden eines neuen Levels mit komplett neuen Texturen. Die neuen Metarialien müssen dann extra bei der Root angemeldet werden.</summary>
		bool SubAllMaterials();	 

		///<summary> Initialisiert Fortschrittsanzeiger (Progress bar). Wird automatisch beim Ladestart aufgerufen.</summary>
		void InitBar(int iFrames, int iViewports, int iGeos, int iMaterials, int iAudios); 

		///<summary> Rückt Fortschrittsanzeiger (Progress bar) um eine Einheit, die in InitBar vereinbart wurde, weiter. Wird automatisch beim jedem Laden einer Textur/Geometrie/Szene aufgerufen.</summary>
		void TickBar(char acNode); 

		///<summary> Versteckt und finilasiert den Fortschrittstandsanzeiger (Progress bar). Wird automatisch beim Ladeende aufgerufen.</summary>
		void FiniBar(); 

		///<summary> Zeigt den Fortschrittstandsanzeiger (Progress bar) und stellt ihn auf fr Anteile (z.B. 0= ganz links, 0.5 = Mitte, 1.0 = ganz rechts).</summary>
		///<param name="frProgress">Ladefortschritt: 0.0 = Anfang des Ladens ... 0.5 = Halb geladen ... 1.0 Ganz geladen</param>
		void ShowBar(float frProgress);
	
		///<summary> Versteckt explizit den Fortschrittstandsanzeiger (Progress bar). </summary>
		void HideBar(); 

		///<summary> Zählt die Anzahl aller Geometrien, die in der Gesamthierarchie hängen.</summary>
		int CountGeos();

		///<summary> Zählt die Anzahl aller Viewports, die in der Gesamthierarchie hängen.</summary>
		int CountViewports();

		///<summary> Setzt den Pfad zur Standard-Bibliothek. Kann sinnvoll sein, wenn man eine Release-Version mit einer eigenen Ordnerhierarchie erstellen will.</summary>
		///<param name="acPath">Pfad (absolut oder relativ) zur Library. Muss nur dann aufgerufen werden, falls Dateistruktur anders ist als normal.</param>
		void SetLibPath(char * acPath);

		///<summary> Setzt das Geheimwort, für das "Sesam öffne Dich", wenn richtig, werden wunderbare Sonderfunktionen freigeschaltet.</summary>
		///<param name="ac">ASCII-Geheimwort - bei Vektoria UG (haftungsbeschränkt) für Premiumkunden erhältlich</param>
		void OpenSesamy(char * ac);

		///<summary> Lädt das Konfigurationsfile (.vrh), welches die Konbfiguration definiert, auf der das Verteilte Rendering läuft.  <para></para>
		///Funktioniert nur, wenn die Kamerabewegungen synchron von einem Placment gesteuert werden.</summary>
		///<param name="hwnd">Handle auf das Window (Einfach weiterreichen)</param>
		///<param name="(HWND hwnd, unsigned int uWndFlags)">Callbackfunktion (Einfach weiterreichen)</param>
		///<param name="frameMain">Hauptframe</param>
		///<param name="placementCamerasSingle">Placmeent, welches die Kameras bewegt</param>
		void LoadRealHierachy(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CFileVektoria & filevektoria, CFrame & frameMain, CPlacement & placementCamerasSingle);

		///<summary> Lädt das Konfigurationsfile (.vrh), welches die Konfiguration definiert, auf der das Verteilte Rendering läuft.<para></para>
		///Funktioniert auch für mehrere zu steuernde Kameras.</summary>
		///<param name="hwnd">Handle auf das Window (Einfach weiterreichen)</param>
		///<param name="(HWND hwnd, unsigned int uWndFlags)">Callbackfunktion (Einfach weiterreichen)</param>
		///<param name="frameMain">Hauptframe</param>
		///<param name="placementsCameras">Placementcontainer für die zu bewegenden Kameras</param>
		void LoadRealHierachy(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CFileVektoria & filevektoria, CFrame & frameMain, CPlacements & placementsCameras);

		///<summary> Speichert das Konfigurationsfile, welches die Konfiguration definiert, auf der das Verteilte Rendering läuft.</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="placementsCameras">Die Placements, welche die Kameras steuern</param>
		void SaveRealHierachy(CFileVektoria & filevektoria, CPlacements & placementsCameras);

		///<summary> Lädt alle Szenenbeschreibungen aus einem Vektoria-Rootfile für die Virtuelle Hierarchie (.vrv).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Rootdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyRoot.vrv" oder ".\\Roots\\MyRoot.vrv" </param>
		bool LoadVirtualHierarchy(char * acPath);

		///<summary> Speichert alle Szenenbeschreibungen in ein Vektoria-Rootfile für die Virtuelle Hierarchie (.vr).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Rootdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyRoot.vrv" oder ".\\Roots\\MyRoot.vrv" </param>
		bool SaveVirtualHierarchy(char * acPath);

	protected:

		///<summary> Lädt alle Szenenbeschreibungen aus einem Vektoria-Rootfile für die Virtuelle Hierarchie (.vr).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="id">Eindeutige Identifikationsnummer der zu ladenden Root</param>
		///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
		void LoadVirtualHierarchy(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

		///<summary> Speichert alle Szenenbeschreibungen in ein Vektoria-Rootfile für die Virtuelle Hierarchie (.vr).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="bWithID">Soll die eigene Identifikationsnummer in das Rootfile mit abgespeichert werden?</param>
		void SaveVirtualHierarchy(CFileVektoria & filevektoria, bool bWithID = false);

	public:

		///<summary> Checkt die Hierarchie auf renderbare Konsistenz.</summary>
		bool CheckHierarchy();

		// ----------------
		// Membervariablen:
		// ----------------

		///<summary> Art der GPU-Hardwarearchitektur, wird automatisch gesetzt.</summary>
		int m_iArchitecture;

		///<summary> Die Zeit, die seit Start des Programms vergangen ist.</summary>
		float m_fTime; 

		///<summary> Pointer zum Modul für ds Verteilte Rendering.</summary>
		// CRenderDistributed * m_prenderdistributed;
		CApiRender * m_prenderdistributed;

		///<summary> Containerklasse für alle bei der Root angemeldeten Materialien.</summary>
		CMaterials m_materials; 

		///<summary> Containerklasse für alle Szenen .</summary>
		CScenes m_scenes; 

		///<summary> Containerklasse für die Frames dieses Computers.</summary>
		CFrames m_frames; 

		///<summary> Containerklasse für alle Frames sowohl dieses Computers als auch aller Remotecomputer.</summary>
		CFrames m_framesAll; 

		///<summary> Containerklasse für alle Frames dieses Computers plus eventuell ein Remotecomputer (notwendig, da für Remotecomputer im Broadcast gesendet wird.</summary>
		CFrames m_framesAllThisOneThat; 

		///<summary> Containerklasse für fremde Computer im LAN.</summary>
		CHardwares m_hardwares;	

		///<summary> Das Defaultmaterial "Weiß".</summary>
		CMaterial m_zmDefault; 

		///<summary> true, wenn erster Tick, ansonsten false.</summary>
		bool m_bFirstTick; 

		///<summary> Wechselt, falls mehr als ein Frame vorhanden. Dies ist der dazugehörige Pointer.</summary>
		CApiSound * m_papisoundActual; 

		///<summary> Nummer des Ticks seit Begin des Programm.</summary>
		int m_iTick; 

		///<summary> Die Ursprungstransformation aller Szenen (normalerweise Unit-Matrix)).</summary>
		CHMat m_m;

	private:
		CSplash * m_psplash;
		bool m_bSesamy;
		bool m_bError;
		HINSTANCE  m_hinstLib;

	};


}