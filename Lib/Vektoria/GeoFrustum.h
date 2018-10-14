#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoFrustum: Klasse zum Erzeugen einer Pyramidenstumpfgeometrie
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt) 
//-------------------------------------------------------------------



namespace Vektoria
{

	class CGeoFrustum : public CGeoTriangleList
	{
	public:

		///<summary> Konstruktor.</summary>
		CGeoFrustum();

		///<summary> Destruktor.</summary>
		~CGeoFrustum();

		///<summary> Erzeugt einen Pyramidenstumpf um die Z-Achse, der Geometrietyp ist CGeoTriangleList. </summary>
		///<param name = "fzHeight"> Höhe des Pyramidenstumpfes</param>
		///<param name = "fxBaseX"> Breite der Pyramidenstumpfbasis</param>
		///<param name = "fxBaseY"> Höhe der Pyramidenstumpfbasis</param>
		///<param name = "fxTopX"> Breite der Pyramidenstumpfspitze</param>
		///<param name = "fxTopY"> Höhe der Pyramidenstumpfspitze</param>
		///<param name = "pmaterial"> Pointer auf das Material des Pyramidenstumpfes, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Pyramidenstumpf erzeugt</param>
		///<param name = "fTextureRepeat"> Wie oft sollen die Materialtexturen pro Seite wiederholt werden?</param>
		///<param name = "bFlip"> Flag, ob die Flächennormalen nach Innen zeigen sollen</param>
		void Init(float fzHeight, float fxBaseX, float fyBase, float fxTop, float fyTop, CMaterial * pmaterial, float fTextureRepeat = 1, bool bFlip = false);


		///<summary> Visualisiert den aktuellen Pyramidenstumpf einer Kamera, dieser kann natürlich nur mit einer anderen Kamera betrachtet werden, der Geometrietyp ist CGeoTriangleList. </summary>
		///<param name = "camera"> Höhe des Pyramidenstumpfes</param>
		///<param name = "pmaterial"> Pointer auf das Material des Pyramidenstumpfes, bei Angabe von NULL wird mit dem Defaultmaterial ein weißer Pyramidenstumpf erzeugt</param>
		void Init(CCamera & camera, CMaterial & material);

		// ----------------
		// Membervariablen:
		// ----------------


		///<summary> Die 24 Vertices  des Pyramidenstumpfes (8 Ecken mit je drei Vertices).</summary>
		CVertex m_avertex[24];

	};

}
