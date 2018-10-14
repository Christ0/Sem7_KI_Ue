#pragma once

#include <d3d11.h>
#include "../Vektoria/ApiRender.h"


//------------------------------------
// CDXBuffer
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.08.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{


	class CDXBuffer
	{
	public:
		CDXBuffer(unsigned int & id, ID3D11Buffer * pbuffer, ID3D11Buffer * pbufferIndexed, ERenderObjectType & eRenderObjectType);
		CDXBuffer();
		~CDXBuffer();
		CDXBuffer operator=(CDXBuffer & dxbuffer);
		void Copy(CDXBuffer & dxbuffer);

		void Init();
		void Fini();
		
		ERenderObjectType m_eRenderObjectType;
		ID3D11Buffer * m_pbuffer;
		ID3D11Buffer * m_pbufferIndexed;
		unsigned int m_id;
	};
}