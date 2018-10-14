#pragma once

#include "Material.h"

//--------------------------------------------------------------------------------------------
// CWritingFont: Klasse für Schriftarten (Spezielles Bot-Material mit ASCII-Sortierung)
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

class CWritingFont : public CMaterial 
{
public:
	///<summary> Konstruktor.</summary>
	CWritingFont();

	///<summary> Destruktor.</summary> 
	~CWritingFont();

	///<summary> Kopieroperator.</summary> 
	///<param name = "writing"> Zu kopierendes Writing</param>
	CWritingFont operator=(CWritingFont & writing);

	///<summary> Kopiermethode.</summary> 
	///<param name = "writing"> Zu kopierendes Writing</param>
	void Copy(CWritingFont & writing);

	///<summary> Initialisiert SchriftartMaterial durch Pfadangabe.</summary> 
	///<param name = "acPath"> Pfadangabe zum Font-Bild (Achtung! Muss Bild sein und kein Fontfile!) </param>
	///<param name = "bChromaKeying> Chromatischer Farbschlüssel (Der RGB-Wert des linken oberen Pixels des Fontbildes wird dann als ChromaKey verwendet) </param>
	void Init(char * acPath, bool bChromaKeying); 

	///<summary>Finalisiert die Schriftart.</summary>
	void Fini(); 

	///<summary> Setzt die Feldgröße in Buchstaben im übergebenen ASCII-Feld.</summary>
	///<param name = "ixTable"> Anzahl der Buchstaben im Fontbild in X-Richtung</param>
	///<param name = "iyTable"> Anzahl der Buchstaben im Fontbild in Y-Richtung</param>
	void SetTableSize(int ixTable, int iyTable);

	///<summary> Setzt den Anfangsbuchstabens im übergebenen Fontbild.</summary>.
	///<param name = "iTableStartASCII">ASCII-Wert des Anfangsbuchstabens im übergebenen Fontbild</param>
	void SetTableStartASCII(int iTableStartASCII);

	///<summary> Lädt ein vorgefertigtes Font aus der Bibliothek. <para></para>
	///Die Farbe des Fonts kann danach mit der Methode SetHue verändert werden.</summary>.
	///<param name = "acName">Name des Fonts, z.B.: 
	///"CreatorWhite", "LucidaConsoleWhite", "LucidaConsoleBlack", "LucidaConsoleRed",
	///"OCRAExtendedWhite", "OCRAExtendedBlack", "OCRAExtendedRed",
	///"PrestigeEliteWhite", "RodWhite", "RodRed", "SimSunWhite" 
	///"TannenbergBoldWhite", "TannenbergBoldBlack", "TannenbergBoldRed", "TannenbergBoldRedOutlined" </param>
	void LoadPreset(char * acName);

	///<summary> Lädt eine komplette Fontbeschreibung aus einem Vektoria-Fontfile. (.vmf)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Fonts innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
	void Load(CFileVektoria & filevektoria, int id = -1);

	///<summary> Speichert eine komplette Fontbeschreibung in ein Vektoria-Fontfile.(.vmf)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "bWithID"> Flag, ob die eigene Material-ID mit abgespeichert werden soll.</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);


	// -----------------
	// Member-Variablen:
	// -----------------

	///<summary>ASCII-Wert des Startbuchstabens im Fontbild.</summary>
	int m_iTableStartASCII;

	///<summary>Flag, ob chromatischer Farbschlüssel verwendet wird (Der RGB - Wert des linken oberen Pixels des Fontbildes wird dann als ChromaKey verwendet).</summary>
	bool m_bChromaKeying;

	///<summary>Startbuchstabe</summary>
	char m_c;
};

}