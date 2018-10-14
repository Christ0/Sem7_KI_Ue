#pragma once
#include "GeoBezierTable.h"
#include "Face.h"

namespace Vektoria
{

class CGeoUtahTeapot : public CGeoBezierTable
{
public:
	CGeoUtahTeapot(void);
	~CGeoUtahTeapot(void);
	void SetAxis(EAxis eAxis);
	void Init(float fHeight, CMaterial * pmaterial, int iVerticesPerPatchEdge = 8, bool bGroundZero = false, bool bMain = true, bool bTop = true, bool bBottom = true, bool bGrip = true, bool bMouth = true, bool bInside = false, CMaterial  * pmaterialInside = nullptr); // Initialisiert einen Utah Teapot

	EAxis m_eAxis;
	CGeoUtahTeapot * m_pzgInside;
};

}