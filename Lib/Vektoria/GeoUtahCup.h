#pragma once
#include "GeoBezierTable.h"
#include "Face.h"

namespace Vektoria
{

class CGeoUtahCup : public CGeoBezierTable
{
public:
	CGeoUtahCup(void);
	~CGeoUtahCup(void);
	void SetAxis(EAxis eAxis);
	void Init(float fHeight, CMaterial * pmaterial, int iVerticesPerPatchEdge = 8, bool bGroundZero = false, bool bCup = true, bool bSaucer = true, bool bBottomUp = true, bool bBottomDown = true); // Initialisiert einen Utah Teapot

	EAxis m_eAxis;
};

}