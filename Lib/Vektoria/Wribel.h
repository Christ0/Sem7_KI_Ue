#pragma once

#include "Placement.h"
#include "GeoQuad.h"
#include <stdio.h>

//--------------------------------------------------------------------------------------------
// CWribel: Klasse für Textlabels (WRIBEL = WRIting + LaBEL)
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{
	class CWritingFont;

	class CWribel : public CPlacement
	{
		friend class CWribels;
	protected:
		///<summary>Wird automatisch aufgefufen.</summary>
		void Tick(CHMat & mGlobalFather, int & iTick, int & iInst, float & fTimeDelta);

	public:
		///<summary>Konstruktor.</summary>
		CWribel(); 

		///<summary>Destruktor.</summary>
		~CWribel(); 

		///<summary>Kopieroperator.</summary>
		///<param name="wribel">Zu kopierendes Wribel</param>
		CWribel operator=(CWribel & wribel);

		///<summary>Kopiermethode, kopiert die Informationen von writing in das vorliegende Writing.</summary>
		///<param name="wribel">Zu kopierendes Wribel</param>
		void Copy(CWribel & wribel);

		///<summary>Initialisiert ein Textfeldsprite.</summary> 
		///<param name="floatrect">Die 2D-Größe des Textfeldes</param>
		///<param name="ixChars">Die Maximalanzahl der Buchstaben</param>
		///<param name="pwritingfont">Ein Pointer auf ein ASCII-Schriftsatz vom Typ CWritingFont</param>
		///<param name="fzOffset">Eventuelle Zusatzverschiebung in Z-Richtung (Default = 0)</param>
		void Init(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont, float fzOffset = 0.0F);
		
		///<summary>Finalisiert das Textfeldsprite.</summary>
		void Fini(); 

		///<summary>Aktualisiert das ASCII-Schriftsatzmaterial.</summary>
		///<param name="pwritingfont">Ein Pointer auf ein ASCII-Schriftsatz vom Typ CWritingFont</param>
		void SetFont(CWritingFont * pwritingfont);

		///<summary>Aktualisiert das ASCII-Schriftsatzmaterial im Buchstabenbereich iCharStart bis iCharStartEnd.</summary>
		///<param name="pwritingfont">Ein Pointer auf ein ASCII-Schriftsatz vom Typ CWritingFont</param>
		///<param name="iCharStart">Anfangsbuchstabe (inklusive) innerhalb des Wribels, ab dem der Font ausgewechselt wird.</param>
		///<param name="iCharEnd">Endbuchstabe (exklusive) innerhalb des Wribels, bis zu dem dem der Font ausgewechselt wird.</param>
		void SetFont(CWritingFont * pwritingfont, int & iCharStart, int & iCharEnd);

		///<summary>Äquivalent zu "printf" im Konsolenfenster bis Wert 128.</summary>
		///<param name="szMsg">Parameter, äquivalent zu printf</param>
		void PrintF(LPCSTR szMsg, ...);

		///<summary>Schreibt eine Integerzahl.</summary>
		///<param name="i">Anzuzeigende Ganzzahl</param>
		void PrintInt(int i);

		///<summary>Schreibt eine Float-Gleichtkommazahl.</summary>
		///<param name="f">Anzuzeigende Gleitkommazahl</param>
		void PrintFloat(float f);

		///<summary>Schreibt einen Text.</summary>
		///<param name="ac">Anzuzeigende Zeichenkette</param>
		void PrintString(char * ac);

		///<summary> Lädt ein Wribel aus einer Vektoria-Wribel-Datei (.vpw).</summary>
		///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
		///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Wiribels innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
		///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
		void Load(CFileVektoria & filevektoria, int id = -1, float fVersion = 14.11f);

		///<summary> Speichert ein Wribel in eine Vektoria-Wribel-Datei (.vpw).</summary>
		///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
		///<param name= "bWithID"> Flag, ob die eigene Knoten-ID mit abgespeichert werden soll</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

		//-----------------
		// Membervariablen:
		//-----------------

		///<summary>Pointer auf die Billboard-Quadliste für die Buchstaben.</summary>
		CGeoQuad ** m_apgeoquadChar;

		///<summary>Pointer auf die jeweiligen Buchstabenmaterialien.</summary>
		CMaterial ** m_apmaterial;

		///<summary>Maximalanzahl der Buchstaben.</summary>
		int m_ixChars;

		///<summary>Anzahkl der allokierte Buchstaben.</summary>
		int m_ixCharAllocs;

		///<summary>Anzahl der Allokationsschritte.</summary>
		int m_iAllocBlock;

		///<summary>Flag, ob beim letzten Tick der Font verändert wurde.</summary>
		bool m_bChangedFont;

		///<summary>Pointer auf den ASCII-Schriftsatz.</summary>
		CWritingFont * m_pwritingfont;
	};

}