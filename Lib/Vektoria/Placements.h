#pragma once

#include "Placement.h"
#include "Cameras.h"

//------------------------------------
// CPlacements: Pluralklasse von CPlacement
// Copyright: Prof. Dr. Tobias Breiner
// Pfungstadt
//------------------------------------

namespace Vektoria
{

class CPlacements
{
	friend class CScene;
	friend class CEmitter;
	friend class CPlacement;
protected: 
	///<summary> Setzt den Pointer zum Wurzelknoten (wird automatisch von der dar�ber liegenden Hierarchie aufgerufen).</summary>
	///<param name = "proot"> Pointer auf die Wurzel</param>
	void SetRoot(CRoot * proot);

	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von �berhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des �bergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "iInst"> Nummer der Instanz </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat & m, int & iTick, float & fTimeDelta);

	///<summary>Zeichnet alle Placements der Liste.</summary>
	void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, int & iTick);

	///<summary>Zeichnet die Placements der Liste nicht.</summary>
	void DontDraw(int & iTick);
public:
	///<summary>Konstruktor</summary>
	CPlacements();

	///<summary>Destruktor</summary>
	~CPlacements();

	///<summary>Kopiert Pointerliste.</summary>
	///<param name=placements>Placement-Liste, welches in die vorliegende Placement-Liste kopiert wird</param>
	void Copy(CPlacements & placements);

	///<summary>Kopiert komplette darunter liegende Hierarchie und kreiiert daf�r neue Instanzen.</summary>
	///<param name=placements>Placement-Liste, welches in die vorliegende Placement-Liste kopiert wird</param>
	void CopyHierarchy(CPlacements & placements);

	///<summary>Kopieroperator, kopiert Pointerliste.</summary>
	///<param name=placements>Placement-Liste, welches in die vorliegende Placement-Liste kopiert wird</param>
	CPlacements operator=(CPlacements placements);

	///<summary>Initialisiert Liste. <para></para>
	/// Normalerweise unn�tig, da alle Parameter schon durch den Konstruktor initialisisert werden, Aufruf nur bei "malloc"-Allokation bzw. Reset notwendig.</summary>
	void Init();

	///<summary>Finalisiert Liste. <para></para>
	/// Normalerweise unn�tig, da alle Parameter schon durch den Destruktor finalisisert werden, Aufruf nur bei "free"-Deallokation notwendig.</summary>
	void Fini();

	///<summary>F�gt ein Placement zur Liste hinzu.</summary>
	///<param name=pplacement>Pointer zum hinzuzuf�genden Placement</param>
	void Add(CPlacement * pplacement);

	///<summary>Schaut, ob Placement schon in der Liste vorhanden ist, nur wenn nicht,  wird es hinzugef�gt und true ausgegeben.</summary>
	///<param name=pplacement>Pointer zum hinzuzuf�genden Placement</param>
	bool AddOnce(CPlacement * pplacement);

	///<summary>F�gt gleich eine ganze Reihe von Placments dazu.</summary>
	///<param name=pplacement>Pointer zu den hinzuzuf�genden Placements</param>
	void Add(CPlacements * pplacements);

	///<summary>Schaut, ob ein Placement in der Liste vorhanden ist, wenn ja, wird true ausgegeben.</summary>
	///<param name=pplacement>Pointer zum zu �berpr�fenden Placement</param>
	bool Has(CPlacement * pplacement);

	///<summary>H�ngt ein Placement von der Liste ab, gibt true aus, wenn es geklappt hat.</summary>
	///<param name=pplacement>Pointer zum abzuh�ngenden Placement</param>
	bool Sub(CPlacement * pplacement);

	///<summary>L�scht die gesamte Liste.</summary>
	void Clear();

	///<summary>Erzeugt ein Placement und h�ngt es in die Liste, gibt einen Pointer auf das neu erzeugte Placement aus.</summary>
	CPlacement * Make();

	///<summary>Zerst�rt das Placement und h�ngt von der Liste ab, gibt true aus, falls es geklappt hat.<para></para>
	/// Achtung! Sollte nur f�r mit Make generierte Placements verwendet werden, ansonsten sind Allokierungsabstz�rze m�glich.</summary>
	///<param name=pplacement>Pointer zum zu zerst�renden Placement</param>
	bool Kill(CPlacement * pplacement);


	///<summary>Ermittelt rekursiv alle Kameras, die unter dem Placement oder Unterplacements h�ngen.</summary>
	///<param name=pcameras>Pointer auf eine Kameraliste</param>
	void SearchForCameras(CCameras * pcameras);

	///<summary>Gibt das erste Placement aus, welches der Strahl r trifft.</summary>
	///<param name=r>Picking-Strahl</param>
	CPlacement * Pick(CRay & r);

	//------------------
	//  Membervariablen:
	//------------------

	///<summary>Pointerliste auf die Placements.</summary>
	CPlacement ** m_applacement;

	///<summary>Anzahl der allokierten Placements.</summary>
	int m_iPlacementAllocs;

	///<summary>Anzahl der beim n�chsten Schritt zu allokierten Placements.</summary>
	int m_iAllocBlock;

	///<summary>Anzahl der Placements.</summary>
	int m_iPlacements;

	///<summary>Instzanzennummer des i. Placements f�r den Vater.</summary>
	int * m_aiInst; 

protected: 

	///<summary>Pointer zur Wurzel.</summary>
	CRoot * m_proot;
};

}