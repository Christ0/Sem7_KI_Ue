#pragma once

#include "GeoTriangleTable.h"

//------------------------------------
// CGeoTriangleTables, Pluralklasse von CGeoTriangleTable
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CGeoTriangleTables
{
protected:
	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat & mGlobal, int & iTick, float & fTimeDelta);
public:
	CGeoTriangleTables();
	~CGeoTriangleTables();
	CGeoTriangleTables operator=(CGeoTriangleTables triangletables);

	void Init();
	void Fini();

	void Add(CGeoTriangleTable * ptriangletable);
	bool Sub(CGeoTriangleTable * ptriangletable);

	CGeoTriangleTable * Make();
	bool Kill(CGeoTriangleTable * ptriangletable);

	CGeoTriangleTable * Get(unsigned int id);

	CGeoTriangleTable ** m_aptriangletable;
	int m_iTriangleTableAllocs;
	int m_iAllocBlock;
	int m_iTriangleTables;
};

}