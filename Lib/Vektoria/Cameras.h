#pragma once
#include "Camera.h"

//------------------------------------------------------------------
// CCameras: Pluralklasse für Kameras
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//-------------------------------------------------------------------

namespace Vektoria
{

class CCameras
{
public:
	CCameras();
	~CCameras();
	void Copy(CCameras & cameras);
	CCameras operator=(CCameras & cameras);

	void Init();
	void Tick(CHMat & m, int & iTick);
	void Fini();

	void Add(CCamera * pcamera);
	bool Sub(CCamera * pcamera);

	// gibt true aus, wen Camera in der Liste enthalten.
	bool Has(CCamera * pcamera); 

	CCamera * Make(float faFov, float fNearClipping, float fFarClipping);
	bool Kill(CCamera * pcamera);

	// Gibt den Pointer derjenigen Kamera mit der Identifikationsnummer id aus, falls nicht vorhanden, wird ein Nullpointer ausgegeben.
	CCamera * Get(unsigned int id); 

	CCamera ** m_apcamera;
	int m_iCameraAllocs;
	int m_iAllocBlock;
	int m_iCameras;
};

}