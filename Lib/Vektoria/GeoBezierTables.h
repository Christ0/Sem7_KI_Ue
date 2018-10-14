#pragma once

#include "GeoBezierTable.h"

//------------------------------------
// CGeoBezierTables, Pluralklasse von CGeoBezierTable
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CGeoBezierTables
{
protected:
	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat & mGlobal, int & iTick, float & fTimeDelta);

public:
	CGeoBezierTables();
	~CGeoBezierTables();
	CGeoBezierTables operator=(CGeoBezierTables beziertables);

	void Init();
	void Tick(CHMat & m, int & iTick);
	void Fini();

	void Add(CGeoBezierTable * pbeziertable);
	bool Sub(CGeoBezierTable * pbeziertable);

	CGeoBezierTable * Make();
	bool Kill(CGeoBezierTable * pbeziertable);

	CGeoBezierTable * Get(unsigned int id);

	CGeoBezierTable ** m_apbeziertable;
	int m_iBezierTableAllocs;
	int m_iAllocBlock;
	int m_iBezierTables;
};

}