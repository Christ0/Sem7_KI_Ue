#pragma once

#include "Sprite.h"
#include "WritingChars.h"
#include <stdio.h>
//--------------------------------------------------------------------------------------------
// CWriting: Klasse f�r Textfelder (spezielle Overlay-Sprites)
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

class CWriting : public COverlay
{
	friend class CWritings;
	friend class COverlays;
	friend class COverlay;
protected:
	/// <summary> Wird automatisch aufgefufen.</summary>
	void Tick(float & fTimeDelta, CFloatRect & floatrectFather);

	/// <summary> Wird automatisch aufgerufen.</summary>
	void SetViewport(CViewport * pviewport);

	/// <summary> Wird automatisch aufgerufen. Muss �berschrieben sein, weil ein Writing viele WritingChars hat</summary>
// 	void SetRoot(CViewport * pviewport);


public:
	/// <summary> Konstruktor.</summary>
	CWriting(); 

	/// <summary> Destruktor.</summary>
	~CWriting(); 

	/// <summary> Kopieroperator.</summary>
	/// <param name ="writing"> Dasjenige Writing, dessen Werte ins vorliegende Writing kopiert werden. </param>
	CWriting operator=(CWriting & writing);

	/// <summary> Kopiermethode.</summary>
	/// <param name ="writing"> Dasjenige Writing, dessen Werte ins vorliegende Writing kopiert werden. </param>
	void Copy(CWriting & writing);

	/// <summary> Initialisiert ein Textfeldsprite.</summary> 
	/// <param name ="floatrect"> Die relative 2D-Gr��e des Textfeldes zum �bergeordneten Viewport </param>
	/// <param name ="ixChars"> die Maximalanzahl der Buchstaben, die im Textfeld angezeigt werden k�nnen</param>
	/// <param name ="pwritingfont"> Pointer auf ein ASCII-Schriftsatzmaterial</param> 
	void Init(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont);

	/// <summary> Finalisiert das Textfeldsprite.</summary> 
	void Fini(); 

	/// <summary> Aktualisiert das ASCII-Schriftsatzmaterial.</summary> 
	/// <param name ="pwritingfont"> Pointer auf ein ASCII-Schriftsatzmaterial</param> 
	void SetFont(CWritingFont * pwritingfont);

	/// <summary> Aktualisiert das ASCII-Schriftsatzmaterial im Buchstabenbereich iCharStart bis iCharStartEnd.</summary> 
	/// <param name ="pwritingfont"> Pointer auf ein ASCII-Schriftsatzmaterial</param> 
	/// <param name ="iCharStart"> Anfangsbuchstabe, ab dem der Font ausgewechselt wird</param> 
	/// <param name ="iCharEnd"> Endbuchstabe, bis zu dem der Font ausgewechselt wird</param> 
	void SetFont(CWritingFont * pwritingfont, int & iCharStart, int & iCharEnd);

	/// <summary> Setzt die Farbwertwinkel der Schrift. <para></para>
	/// Achtung, funktioniert nur bei roten Zeichen!</summary> 
	/// <param name ="fa"> Farbwertwinkel im Bogenma� (0=Rot ... THIRDPI = Gr�n.. TWOTHIRDPI = Blau) </param> 
	void RotateHue(float fa);


	/// <summary> Setzt die Farbwertwinkel der Schrift. <para></para>
	/// Achtung, funktioniert nur bei roten Zeichen!</summary> 
	/// <param name ="fa"> Farbwertwinkel im Bogenma� (0=Rot ... THIRDPI = Gr�n.. TWOTHIRDPI = Blau) </param> 
	/// <param name ="iCharFrom"> Ab welchem Buchstaben soll eingef�rbt werden (erster Buchstabe hat Index 0)</param> 
	/// <param name ="iCharTo"> Bis zu welchem Buchstaben exklusive soll eingef�rbt werden (erster Buchstabe hat Index 0)</param> 
	void RotateHue(float fa, int iCharFrom, int iCharTo);

	// ----------------
	// Schreibmethoden:
	// ----------------

	/// <summary> �quivalent zu "printf" im Konsolenfenster.</summary> 
	void PrintF(LPCSTR szMsg, ...); 

	/// <summary> Schreibt eine Integerzahl.</summary> 
	void PrintInt(int i); 

	/// <summary> Schreibt eine Float-Gleitkommazahl. </summary>
	void PrintFloat(float f); 

	/// <summary> Schreibt einen Text. </summary>
	void PrintString(char * ac); 

	// ----------------------------------------------------------------------------------------
	// �berladene Funktionen, da alle untergeordneten WritingChars auch ver�ndert werden m�ssen:
	// ----------------------------------------------------------------------------------------

	/// <summary> Setzt die Z-Distanz des Writings. </summary>
	void SetLayer(float fLayerDistance); 

	/// <summary> Schaltet das Zeichnen an. </summary>
	void SetDrawingOn();

	/// <summary> Schaltet das Zeichnen aus, die Positionen werden trotzdem berechnet. </summary>
	void SetDrawingOff();

	/// <summary> Schaltet Writing an. </summary>
	void SwitchOn();

	/// <summary> Schaltet Writing aus. </summary>
	void SwitchOff();

	/// <summary> Schaltet Inner-Funktion an. (Nur sinnvoll, wenn Writing an ein anderes Overlay angeh�ngt wurde). </summary>
	void SetInnerOn();

	/// <summary> Schaltet Inner-Funktion aus. (Nur sinnvoll, wenn Writing an ein anderes Overlay angeh�ngt wurde). </summary>
	void SetInnerOff();

	/// <summary> Setzt Au�ma�e des Writings bez�glich des �bergeordneten Frames. Kann auch w�hrend der Laufzeit neu gesetzt werden. </summary>
	void SetRect(CFloatRect floatrect);

	// ----------------
	// Membervariablen:
	// ----------------

	/// <summary> Text, der angezeigt wird, mit Nullterminator</summary>
	char *m_ac;

	/// <summary> Container f�r die angezeigten Buchstaben</summary>
	CWritingChars m_writingchars;

	/// <summary> Maximalzahl der anzeigbaren Buchstaben</summary>
	int m_ixChars;
};

}