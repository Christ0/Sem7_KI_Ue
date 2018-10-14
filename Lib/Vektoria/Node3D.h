////////////////////////////////////////////////////
// Klasse: Node3D.h
// Autor: Tobias Breiner
// Copyright: (c) Vektoria UG (haftungsbeschränkt)
////////////////////////////////////////////////////

#pragma once

#include "Vertex.h"
#include "Node.h"
#include "NodeInstance.h"
#include "../VektoriaMath/HVector.h"

namespace Vektoria
{

	enum EPlacementSearch
	{
		ePlacementSearch_All,
		ePlacementSearch_OnlyWithDirectWribels,
		ePlacementSearch_OnlyWithDirectGeos
	};


	class CGeoCube;
	class CRoot;
	class CPlacement;

	class CNode3D : public CNode
	{
		friend class CNodes;
		friend class CCamera;
		friend class CEmitter;
		friend class CPlacements;
		friend class CPlacement;
		friend class CGeoWall;
		friend class CGeoWindow;
		friend class CGeoWing;
		friend class CGeos;
		friend class CGeo;
		friend class CScene;
		friend class CGeoTriangleList;
		friend class CGeoTriangleStrip;
	protected:
		int Tick(CHMat & m, int & iTick);

		///<summary> Lädt eine 3D-Knotenbeschreibung aus einem Vektoria-Materialfile, vererbbare Hilfmethode.</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		void Load(CFileVektoria & filevektoria);

		///<summary> Speichert eine D-Knotenbeschreibung in ein Vektoria-Materialfile, vererbbare Hilfsmethode.</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		void Save(CFileVektoria & filevektoria);


	public:
		///<summary> Konstruktor.</summary>
		CNode3D(void);

		///<summary> Destruktor.</summary>
		~CNode3D(void);

		///<summary> Kopiert 3D-Knoteninformationen in den vorliegenden Knoten.</summary>
		///<param name=pnode3D>Zu kopierender 3D-Knoten</param>
		void Copy(CNode3D & pnode3D);

		///<summary> Initialisierungsmethode (wird automatisch von der darüber liegenden Hierarchie aufgerufen).</summary>
		void Init();

		///<summary> Beendigungsmethode (wird automatisch von der darüber liegenden Hierarchie aufgerufen).</summary>
		void Fini();

		///<summary> Gibt die Axis Aliened Bounding Box aus.</summary>
		CAABB * GetAABB();

		///<summary> Löscht die Daten der Axis Aliened Bounding Box.</summary>
		void ClearAABB();

		///<summary> Schaltet die Berechnung der Bounding Boxen für diesen Node und seine gesamte Unterhierarchie an.</summary>
		void EnableAABBs();

		///<summary> Schaltet die Berechnung der Bounding Boxen für diesen Node und seine gesamte Unterhierarchie aus.</summary>
		void DisableAABBs();

		///<summary> Führt eine Strahl/AABB Intersection nur für diesen Knoten durch. <para></para>
		/// Gibt true aus, falls etwas getroffen wurde.</summary>
		///<param name="r">Strahl</param>
		///<param name="fDistance">Entfernung vom Startpunt (Ausgabeparameter)</param>
		///<param name="iInstance">Nummer der zu überprüfenden Instanz (Default = 0)</param>
		bool Intersects(CRay & r, float & fDistance, int iInstance = 0);

		//-----------------
		// Membervariablen:
		//-----------------


		///<summary> Aktuelle globale Matrix (=Instanz) während des Ticks.</summary>
		int m_iInstanceTick;

		///<summary> Anzahl der globalen Matrizen (=Anzahl der Knoteninstanzen).</summary>
		int m_iInstances;

		///<summary> Anzahl der allokierten globalen Matrizen (=Anzahl der Knoteninstanzen).</summary>
		int m_iInstanceTickAllocs;

		///<summary> Größe des nächsten Allokierungsschrittes.</summary>
		int m_iAllocStep;

		///<summary> Anzahl der Ticks, die seit Spielbeginn vergangen sind.</summary>
		int m_iTick;

		///<summary> Flag, um die AABB des Knotens aus (false) bzw</summary> an (true) zu schalten.</summary>
		bool m_bAABBOn;

		///<summary> Flag, welches angibt, ob die AABB im nächsten Tick neu berechnet werden muss.</summary>
		bool m_bAABBUpdateNeeded;

		///<summary> Flag, welches angibt, ob die AABB im nächsten Tick gesäubert werden muss.</summary>
		bool m_bClearUpdateAABB;

		///<summary> Flag, welches angibt, ob der 3D-Knoten fixiert ist.</summary>
		bool m_bFixed;

		///<summary> Flag, welches beim allerersten Tick automatisch auf true gesetzt wird. (Wird für die automatische Realisierungs-KI gebraucht).</summary>
		bool m_bFirstTick;

		///<summary> Liste der Knoteninstanzen.</summary>
		CNodeInstance * m_anodeinstance;
	protected:

		///<summary> Zeichen-Instanzennummer, wird beim Traversieren automatisch gesetzt.</summary>
		int m_iInstanceDraw;

	};

}