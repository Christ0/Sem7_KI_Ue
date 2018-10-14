#pragma once

#include "GeoTriangleStrip.h"

//------------------------------------
// CGeoTriangleStrips, Pluralklasse von CGeoTriangleStrip
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CGeoTriangleStrips
{
protected: 
	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat & mGlobal, int & iTick, float & fTimeDelta);
public:
	CGeoTriangleStrips();
	~CGeoTriangleStrips();
	CGeoTriangleStrips operator=(CGeoTriangleStrips trianglestrips);

	void Init();
	void Fini();

	void Add(CGeoTriangleStrip * ptrianglestrip);
	bool Sub(CGeoTriangleStrip * ptrianglestrip);

	CGeoTriangleStrip * Make();
	bool Kill(CGeoTriangleStrip * ptrianglestrip);

	CGeoTriangleStrip * Get(unsigned int id);

	CGeoTriangleStrip ** m_aptrianglestrip;
	int m_iTriangleStripAllocs;
	int m_iAllocBlock;
	int m_iTriangleStrips;
};

}