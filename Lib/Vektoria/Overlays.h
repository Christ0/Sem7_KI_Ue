#pragma once

#include "Overlay.h"

//------------------------------------
// COverlays, Pluralklasse von COverlay
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	enum EOverlaySearch
	{
		eOverlaySearch_NoWritings,
		eOverlaySearch_OnlyWritings,
		eOverlaySearch_All,
	};

class COverlays
{
	friend class CViewport;
	friend class COverlay;
protected:
	void SetRoot(CRoot * proot);
public:
	COverlays();
	~COverlays();
	COverlays operator=(COverlays overlays);

	void Init();
	void Tick(float & fTimeDelta, CFloatRect & floatrectFather);
	void Fini();

	void Add(COverlay * poverlay);
	bool Sub(COverlay * poverlay);

	COverlay * Make(CImage * pimage, CFloatRect & floatrect);
	bool Kill(COverlay * poverlay);

	COverlay * PickOverlay(float frxViewport, float fryViewport, float &fLayerDistance, EOverlaySearch eOverlaySearch = eOverlaySearch_All); // Pickt vorderstes Overlay bzw. Writing in Overlay-Hierachie
	void PickOverlays(float frxViewport, float fryViewport, COverlays * pzos, EOverlaySearch eOverlaySearch = eOverlaySearch_All); // Pickt alle Overlays oder Writings in Overlay-Hierarchie

	void SetViewport(CViewport * pviewport);
	void SetInnerOn();
	void SetInnerOff();

	COverlay ** m_apoverlay;
	int m_iOverlayAllocs;
	int m_iAllocBlock;
	int m_iOverlays;
	CViewport * m_pviewport;


};

}