#pragma once
#include "../VektoriaMath/AABB.h"
#include "../VektoriaMath/HMat.h"

//---------------------------------------------
// CNodeInstance: Klasse f�r eine Knoteninstanz
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------

///<summary> Fortlaufende Z�hlung der Knotenobjekte, mir f�llt leider keine bessere M�glichkeit ein, als eine globale Variable. </summary>
static unsigned int g_idInstance = 0;




namespace Vektoria
{

	class CNodeInstance
	{
	public:
		///<summary> Konstruktor.</summary>
		CNodeInstance();

		///<summary> Destruktor.</summary>
		~CNodeInstance();

		///<summary> Alternativer Konstruktor.</summary>
		void Init();

		///<summary> Globale Matrix.</summary>
		CHMat m_mGlobal;

		///<summary> Axis Aligned Bounding Box.</summary>
		CAABB m_aabb;

		///<summary> Boolsches Flag, das anzeigt, ob die Instanz schon im Tick gezeichnet wurde.</summary>
		bool m_bDrawed;

		///<summary> Boolsches Flag, das anzeigt, ob die Instanz schon erzeugt wurde.</summary>
		bool m_bCreated;

		///<summary> Eindeutige Instanzen-ID, wird in der Methode Inot vergeben.</summary>
		unsigned int m_idInstance;

	};
}
