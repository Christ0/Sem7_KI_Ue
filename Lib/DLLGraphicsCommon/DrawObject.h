#pragma once

//------------------------------------
// CDrawObject
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.08.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

#include "../VektoriaMath/HMat.h"
#include "../Vektoria/ApiRender.h"
#include "../Vektoria/Light.h"
//#include <xnamath.h>


namespace Vektoria
{
	
	

	class CDrawObject
	{
	public:
		// Dies ist ein zeitkritisches Objekt! Aus Geschwindigkeitsgr�+nden kein Konstruktor vorhanden (Ansonsten g�be es ein Heap-Aufruf mehr)
	
		/*
		CDrawObject();
		~CDrawObject();
		*/
		CDrawObject operator=(CDrawObject & drawobject);
		void Copy(CDrawObject & drawobject);

		void Reset();
		void Init(unsigned int & id, int & idTexture, float & fDistanceToCameraSquare, CHMat & mGlobal, unsigned int * aiLightsAffectIndices, unsigned int & iLightsAffectCount);


		void Tick(float & fTimeDelta);
		void Fini();


		/*
		void SetDrawParams(OBJECT_SHADER_CONSTANTS & objectshaderconstants);

		void CopyCHMatToXMFLOAT4X4(CHMat &m, XMFLOAT4X4 &f4);
		void CopyXMFLOAT4X4ToCHMat(XMFLOAT4X4 &f4, CHMat &m);
		*/
		unsigned int m_id;
//		SRenderObjectHandle m_handle;

		int m_idTexture;
		float m_fDistanceToCameraSquare;
		CHMat m_mGlobal;
		unsigned int m_aiLightsAffectIndices[LIGHTS_MAX];
		unsigned int m_iLightsAffectCount;
	};

}