#pragma once

#include "DXBuffer.h"

//------------------------------------
// CDXBuffers, Pluralklasse von CDXBuffer
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	class CDXBuffers
	{
	public:
		CDXBuffers();
		~CDXBuffers();
		CDXBuffers operator=(CDXBuffers dxbuffers);

		void Init();
		void Fini();

		void Add(unsigned int & id, CDXBuffer * pdxbuffer);
		bool Sub(CDXBuffer * pdxbuffer);

		bool Sub(unsigned int & id);

		void Overwrite(unsigned int & id, ID3D11Buffer * pbuffer, ID3D11Buffer * pbufferIndexed);

		CDXBuffer * GetByID(unsigned int & id);
		ID3D11Buffer *   GetDXBufferByID(unsigned int & id);

//		void Sort();

		CDXBuffer * Make(unsigned int & id, ID3D11Buffer * pbuffer, ID3D11Buffer * pbufferIndexed, ERenderObjectType eRenderObjectType);
		bool Kill(CDXBuffer * pdxbuffer);
		bool Kill(unsigned int & id);

		CDXBuffer ** m_apdxbuffer;
		CDXBuffer ** m_apdxbufferByID;

		int m_iDXBufferAllocs;
		int m_iDXBufferByIDAllocs;
		int m_iAllocBlock;
		int m_iDXBuffers;
	};
}