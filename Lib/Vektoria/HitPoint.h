#pragma once
#include "Geo.h"


//------------------------------------
// CHitPoint
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Copyright: Moyzelle Vektoria
//------------------------------------
namespace Vektoria
{


	class CHitPoint
	{
	public:
		///<summary> Konstruktor.</summary>
		CHitPoint();

		///<summary> Destruktor.</summary>
		~CHitPoint();

		///<summary> Kopieroperator.</summary>
		///<param name = "hitpoint"> Zu kopierender Hitpoint.</param>
		CHitPoint operator=(CHitPoint & hitpoint);

		///<summary> Kopiermethode.</summary>
		///<param name = "hitpoint"> Zu kopierender Hitpoint.</param>
		void Copy(CHitPoint & hitpoint);

		//-----------------
		// Membervariablen:
		//-----------------

		///<summary> Pointer auf die getroffene Geometrie.</summary>
		CGeo * m_pzg;

		///<summary> Nummer der Instanz der getroffenen Geometrie.</summary>
		int m_iInstanceTick;

		///<summary> Position des getroffenen Punktes.</summary>
		CHVector m_vPos;

		///<summary> Gemittelte Flächennormale an der Position des getroffenen Punktes.</summary>
		CHVector m_vNormal;

		///<summary> Die Entfernung zum getroffenen Punkt im Quadrat (Quadrat, da schneller zu berechnen).</summary>
		float m_fDistanceSquare;

	};

}