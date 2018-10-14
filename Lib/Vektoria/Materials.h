#pragma once

#include "Material.h"

//------------------------------------
// CMaterials, Pluralklasse von CMaterial
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{
	class CHardware;

class CMaterials
{
public:
	CMaterials();
	~CMaterials();
	CMaterials operator=(CMaterials materials);

	void Init();
	void Tick(float & fTimeDelta, CFrames & frames);
	void Fini();
	
	bool Add(CMaterial * pmaterial); // Trägt Material in die Liste ein
	bool AddOnce(CMaterial * pmaterial); // Trägt Material nur dann in die Liste ein, wenn noch nicht vorhanden
	bool Sub(CMaterial * pmaterial);

	bool Has(CMaterial * pmaterial);
	CMaterial * Make();
	bool Kill(CMaterial * pmaterial);

	CMaterial * Get(unsigned int id); // Gibt Materialpointer desjenigen Materials mit der entsprechenden ID aus, falls nicht existent, wird ein nullptr ausgegeben

	CMaterial ** m_apmaterial;
	int m_iMaterialAllocs;
	int m_iAllocBlock;
	int m_iMaterials;
};

}