#pragma once
#include "..\\VektoriaMath\\HMat.h"
#include "..\\VektoriaMath\\HVector.h"

//-------------------------------------------------------------------
// CEmitter: Partikelringpuffer für den CPU-basierter Partikelemitter
//
// Autor: Tobias Breiner
//-------------------------------------------------------------------

namespace Vektoria
{
	class CNode;
	class CPlacement;


	class CEmitterParticles
	{
		friend class CEmitter;
	public:
		///<summary> Constructor.</summary>
		CEmitterParticles();

		///<summary> Destructor.</summary>
		~CEmitterParticles();

		///<summary> Alternative Constructor.</summary>
		void Init();

		///<summary> Alternative Destructor.</summary>
		void Fini();

		///<summary> Erhöht die Anzahl der allokierten Partikel im Ringpuffer, erweitert den Ringpuffer.</summary>
		void ChangeParticlesMax(int iParticlesMaxNew, CPlacement * pplacementNew);

		///<summary> Gibt das Positions-Mittel aller Partikel aus.</summary>
		CHVector GetMid();

		///<summary> Inkrementiert die Anzahl der Partikel.</summary>
		void Inc();

		///<summary> Dekrementiert die Anzahl der Partikel.</summary>
		void Dec();

		//-----------------
		// Membervariablen:
		//-----------------

		///<summary> Ringpuffer für die Partikel.</summary>
		CPlacement ** m_applacementAlive;

		///<summary> Array der aktuellen Lebenszeiten der Partikel.</summary>
		float * m_afTimeOfLife;

		///<summary> Nummer des ersten Partikels im Ringpuffer.</summary>
		int m_iFirst;

		///<summary> Nummer des ersten Partikels im Ringpuffer.</summary>
		int m_iLast;

		///<summary> Anzahl der gerade lebenden Partikel.</summary>
		int m_iAlive;

		///<summary> Anzahl der allokierten Partikel.</summary>
		int m_iParticlesAllocated;

	protected:
		///<summary> Anzahl der pro Schritt zu allokierten Partikel.</summary>
		int m_iAllocBloc;
	};
}
