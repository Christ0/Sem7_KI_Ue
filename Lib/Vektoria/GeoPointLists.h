#pragma once

#include "GeoPointList.h"

//------------------------------------
// CGeoPointLists, Pluralklasse von CGeoPointList
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CGeoPointLists
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
	CGeoPointLists();
	~CGeoPointLists();
	CGeoPointLists operator=(CGeoPointLists pointlists);

	void Init();
	void Fini();

	void Add(CGeoPointList * ppointlist);
	bool Sub(CGeoPointList * ppointlist);

	CGeoPointList * Make();
	bool Kill(CGeoPointList * ppointlist);

	CGeoPointList * Get(unsigned int id);

	CGeoPointList ** m_appointlist;
	int m_iPointListAllocs;
	int m_iAllocBlock;
	int m_iPointLists;
};

}