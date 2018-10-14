#pragma once

#include "FileVektoria.h"
#include "Node.h"
//---------------------------------------------------
// CImage: Klasse für Pixel-Images
//
// Autoren: Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haltungsbeschränkt)  
//---------------------------------------------------

namespace Vektoria
{

class CImage : public CNode
{
	friend class CImages;
	friend class CTexture;
protected:

	///<summary> Diese Methode wird automatisch jedes Frame aufgerufen.</summary>
	///<param name="fTimeDelta">Zeit in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	void Tick(float & fTimeDelta);

public:

	///<summary>Konstruktor.</summary>
	CImage();

	///<summary>Destruktor.</summary>
	~CImage();

	///<summary>Kopieroperator.</summary>
	///<param name="image">Zu kopierendes Image</param>
	CImage operator=(CImage & image);

	///<summary>Kopiermethode.</summary>
	///<param name="image">Zu kopierendes Image</param>
	void Copy(CImage & image);

	///<summary>Initialisierung.</summary>
	///<param name="acPath">ASCII-Pfadangabe des Bildfiles (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MeinBild.jpg" </param>
	void Init(char * acPath);

	///<summary>Finalisierung.</summary>
	void Fini();

	///<summary> Lädt die Daten aus einer Vektoria-Imagedatei (.vi).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyImage.vi" oder ".\\Textures\\MyImage.vi </param>
	bool Load(char * acPath);

	///<summary> Speichert die Daten in eine Vektoria-Imagedatei (.vi).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>		
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyImage.vi" oder ".\\Textures\\MyImage.vi </param>
	bool Save(char * acPath);

	///<summary> Schaut, ob m_acPath ein Standardlibrary-Pfad ist, gibt true aus, falls ja.</summary>
	bool IsStdLibPath();

protected:

	///<summary> Lädt eine Texturbeschreibung aus einem Vektoria-Imagefile (.vi).</summary>
	///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
	///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Images</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id = -1, float fVersion = 14.11f);

	///<summary> Speichert die Texturbeschreibung in ein Vektoria-Imagefile (.vi).</summary>
	///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
	///<param name="bWithID">Flag, ob die eigene Identifikationsnummer mit abgespeichert werden soll</param>	
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

public:

	//-----------------
	// Membervariablen:
	//-----------------

	///<summary>Pfad des Bildfiles.</summary>
	char m_acPath[MAX_PATH];

};

}