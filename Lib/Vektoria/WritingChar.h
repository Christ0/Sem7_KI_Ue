#pragma once

#include "Sprite.h"
#include "Overlay.h"
#include "WritingFont.h"

//--------------------------------------------------------------------------------------------
// CWritingChar: Klasse f�r Zeichenfelder (spezielle Overlay-Sprites)
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

	class CWritingChar : public COverlay
	{
		friend class CWritingChars;
		friend class CWriting;
	protected:
		// Wird automatisch jeden Tick aufgerufen, der Programmierer braucht sich normalerweise um diese Methode nicht zu k�mmern.
		void Tick(float & fTimeDelta, CFloatRect & floatrectFather); 

		// �bergibt die Daten an die Render-API zum Malen. Wird automatisch aufgerufen. 
//		void Draw();

		/// <summary> Setzt die Farbwertwinkel der Schrift. <para></para>
		/// Achtung, funktioniert nur bei roten Zeichen!</summary> 
		/// <param name ="fa"> Farbwertwinkel im Bogenma� (0=Rot ... THIRDPI = Gr�n.. TWOTHIRDPI = Blau) </param> 
		void RotateHue(float fa);


	public:
		/// <summary> Konstruktor.</summary>
		CWritingChar(); 

		/// <summary> Destruktor.</summary>
		~CWritingChar(); 

		/// <summary> Kopieroperator.</summary>
		/// <param name ="writingchar"> Dasjenige WritingChar, dessen Werte ins vorliegende WritingChar kopiert werden. </param>
		CWritingChar operator=(CWritingChar & writingchar);

		/// <summary> Kopiermethode.</summary>
		/// <param name ="writingchar"> Dasjenige WritingChar, dessen Werte ins vorliegende WritingChar kopiert werden. </param>
		void Copy(CWritingChar & writingchar);

		/// <summary> Initialisiert ein Buchstabenfeldsprite.</summary> 
		/// <param name ="floatrect"> Die relative 2D-Gr��e des Buchstabenfeldes zum �bergeordneten Viewport </param>
		/// <param name ="pwritingfont"> Pointer auf ein ASCII-Schriftsatzmaterial</param> 
		void Init(CFloatRect & floatrect, CWritingFont * pwritingfont);

		/// <summary> Finalisiert Zeichensprite.</summary> 
		void Fini(); 

		/// <summary> Aktualisiert den angezeigten ASCII-Character.</summary>
		/// <param name ="c"> Anzuzeigender ASCII-Character </param>
		void SetChar(char c);

		/// <summary> Aktualisiert den WritingFont (= das Schriftart-Material) .</summary>
		/// <param name ="c"> Pointer auf den WritingFont </param>
		void SetFont(CWritingFont * pwritingfont);

		// ----------------
		// Membervariablen:
		// ----------------

		// Ein Pointer auf den verwendeten Font (Schriftartmaterial).
		CWritingFont * m_pwritingfont;

		// Ein Pointer auf die Render-API.
		CApiRender * m_papirender;

		// Angezeigter ASCII-Character.
		char m_c;

		// Flag, ob die Werte bez�glich des Buchstabens so ver�ndert wurden, dass sie an die Grafikkarte neu �bergeben werden m�ssen.
		bool m_bChangedAni;
	};

}