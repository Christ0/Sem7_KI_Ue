#pragma once

#include "Scene.h"

//------------------------------------
// CScenes, Pluralklasse von CScene
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 29.03.2012
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CScenes
{
	friend class CRoot;
protected: 
	///<summary> Wird automatisch jedes Frame von Root aus aufgerufen.</summary>
	///<param name="iTick">Nummer des Ticks</param>
	///<param name="fTimeDelta">Zeit in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	void Tick(int & iTick, float & fTimeDelta);

public:
	///<summary> Konstruktor.</summary>
	CScenes();

	///<summary> Destruktor.</summary>
	~CScenes();

	///<summary> Kopiermethode.</summary>
	///<param name="scenes">Zu kopierende Szenen</param>
	void Copy(CScenes & scenes);

	///<summary> Kopieroperator.</summary>
	///<param name="scenes">Zu kopierende Szenen</param>
	CScenes operator=(CScenes & scenes);

	///<summary> Initialisiert den Szenencontainer, wird normalerweise nicht benötigt, da der Konstruktor schon initialisiert.</summary>
	void Init();

	///<summary> Finalisiert den Szenencontainer, wird normalerweise nicht benötigt, da der Denstruktor schon finalisiert.</summary>
	void Fini();

	///<summary> Fügt der Szenenliste eine Szene hinzu.</summary>
	///<param name="pscene">Die hinzuzufügende Szene</param>
	void Add(CScene * pscene);

	///<summary> Fügt eine Szene nur dann in die Liste hinzu, wenn sie noch nicht in der Liste eingetragen ist (Verhindert Doppeltabspeicherungen).</summary>
	///<param name="pscene">Die hinzuzufügende Szene</param>
	bool AddOnce(CScene * pscene);

	bool Sub(CScene * pscene);
	// Gibt true aus, wenn Szene in der Liste vorhanden ist
	bool Has(CScene * pscene); 

	void Draw(CCamera * pcamera, int & iTick);

	// Fügt Szeneelemente nur dann in die Liste hinein, wenn sie noch nicht in der Liste eingetragen ist (Verhindert Doppeltabspeicherungen)
	bool AddOnce(CScenes * pscenes); 

	CScene * Make();
	bool Kill(CScene * pscene);

	CScene ** m_apscene;
	int m_iSceneAllocs;
	int m_iAllocBlock;
	int m_iScenes;
	void SetRoot(CRoot * m_proot);
	CRoot * m_proot;
};

}