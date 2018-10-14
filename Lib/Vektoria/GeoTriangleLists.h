#pragma once

#include "GeoTriangleList.h"

//------------------------------------
// CGeoTriangleLists, Pluralklasse von CGeoTriangleList
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CGeoTriangleLists
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
	CGeoTriangleLists();
	~CGeoTriangleLists();
	CGeoTriangleLists operator=(CGeoTriangleLists trianglelists);

	void Init();
	void Fini();

	void Add(CGeoTriangleList * ptrianglelist);
	bool Sub(CGeoTriangleList * ptrianglelist);

	CGeoTriangleList * Make();
	bool Kill(CGeoTriangleList * ptrianglelist);

	CGeoTriangleList * Get(unsigned int id);

	CGeoTriangleList ** m_aptrianglelist;
	int m_iTriangleListAllocs;
	int m_iAllocBlock;
	int m_iTriangleLists;
};

}