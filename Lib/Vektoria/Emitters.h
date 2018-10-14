#pragma once

#include "Emitter.h"

//------------------------------------
// CEmitters, Pluralklasse von CEmitter
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CEmitters
{
	friend class CPlacements;
	friend class CPlacement;
	friend class CGeo;

protected:
	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	/// <param name= "pnodeParent"> Pointer auf den aktuellen Elternknoten </param>
	void Tick(CHMat & mGlobal, int & iTick, int &iInst, float & fTimeDelta, CNode * pnodeParent);

public:

	CEmitters();
	~CEmitters();

	void Copy(CEmitters & emitters);

	CEmitters operator=(CEmitters & emitters);

	void Init();
	void Fini();

	void Add(CEmitter * pemitter);
	bool Sub(CEmitter * pemitter);

	CEmitter * Make(CPlacements * pplacements);
	bool Kill(CEmitter * pemitter);

	void Draw(CHMat & mGlobal, CCamera * pcamera, int & itFatherIsInFrustum, int & iTick);

	CEmitter ** m_apemitter;
	int m_iEmitterAllocs;
	int m_iAllocBlock;
	int m_iEmitters;
};

}