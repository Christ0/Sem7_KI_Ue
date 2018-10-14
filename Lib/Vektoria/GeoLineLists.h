#pragma once

#include "GeoLineList.h"

//------------------------------------
// CGeoLineLists, Pluralklasse von CGeoLineList
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CGeoLineLists
{
	friend class CGeos;
	friend class CGeoWing;
protected:
	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat & mGlobal, int & iTick, float & fTimeDelta);


public:
	CGeoLineLists();
	~CGeoLineLists();
	CGeoLineLists operator=(CGeoLineLists linelists);

	void Init();
	void Fini();

	void Add(CGeoLineList * plinelist);
	bool Sub(CGeoLineList * plinelist);

	CGeoLineList * Make();
	bool Kill(CGeoLineList * plinelist);

	CGeoLineList * Get(unsigned int id);

	CGeoLineList ** m_aplinelist;
	int m_iLineListAllocs;
	int m_iAllocBlock;
	int m_iLineLists;
};

}