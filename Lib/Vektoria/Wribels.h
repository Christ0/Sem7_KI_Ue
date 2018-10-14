#pragma once

#include "Wribel.h"
#include "GeoQuad.h"

//------------------------------------
// CWribels, Pluralklasse von CWribel
// 
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	class CWribels
	{
		friend class CPlacement;
	protected: 
		void Tick(CHMat & mGlobalFather, int & iTick, int & iInst, float & fTimeDelta);
	public:
		CWribels();
		~CWribels();
		void Copy(CWribels & wribels);
		CWribels operator=(CWribels & wribels);

		void Init();
		void Fini();

		void Add(CWribel * pwribel);
		bool Sub(CWribel * pwribel);

		CWribel * Make(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont);
		bool Kill(CWribel * pwribel);

		void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, int & iTick);

		CWribel ** m_apwribel;
		int * m_aiInst;
		int m_iWribelAllocs;
		int m_iAllocBlock;
		int m_iWribels;
	};
}