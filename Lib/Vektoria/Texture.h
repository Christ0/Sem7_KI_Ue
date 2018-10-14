#pragma once
#include "Image.h"
#include "Node.h"

//--------------------------------------------------------------------------------------------
// CTexture: Klasse für Texturen
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haltungsbeschränkt)  
//--------------------------------------------------------------------------------------------


#define S_TEXTURE_DIFFUSE 0
#define S_TEXTURE_GLOW 1
#define S_TEXTURE_SPECULAR 2
#define S_TEXTURE_BUMP 3
#define S_TEXTURE_HEIGHT 4
#define S_TEXTURE_ENVIROMENTAL 5
#define S_TEXTURE_LIGHT 6
#define S_TEXTURE_THICKNESS 7

namespace Vektoria
{

class CTexture : public CNode
{
	friend class CTextures;
	friend class CMaterial;
protected:
	///<summary> Diese Methode wird automatisch jedes Frame aufgerufen.</summary>
	///<param name="fTimeDelta">Zeit in Sekunden, die seit dem letzten Tick verstrichen ist</param>
	void Tick(float & fTimeDelta);

public:
	///<summary>Konstruktor.</summary>
	CTexture();

	///<summary>Destruktor.</summary>
	~CTexture();

	///<summary>Kopieroperator.</summary>
	///<param name="texture">Zu kopierende Textur</param>
	CTexture operator=(CTexture & texture);

	///<summary>Kopiermethode.</summary>
	///<param name="texture">Zu kopierende Textur</param>
	void Copy(CTexture & texture);

	///<summary>Initialisierung.</summary>
	///<param name="pimage">Pointer auf das Image</param>
	///<param name="eKind">Image-Art (0: Diffuse, 1: Glow,...) </param>
	void Init(CImage * pimage, int eKind = 0);

	///<summary>Finalisierung.</summary>
	void Fini();

	///<summary>Hängt Image an die Textur an.</summary>
	///<param name="pimage">Pointer auf das Image</param>
	void SetImage(CImage * pimage);

	// ---------------------------
	// Lade- und Speichermethoden:
	// ---------------------------

	///<summary> Lädt eine Textur aus einer Vektoria-Texturdatei (.vt).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyTexture.vet" oder ".\\Textures\\MyTexture.vet </param>
	bool Load(char * acPath);

	///<summary> Speichert die in eine Vektoria-Texturdatei (.vt).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>		
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyTexture.vet" oder ".\\Textures\\MyTexture.vet </param>
	bool Save(char * acPath);

protected:

	///<summary> Lädt eine Texturbeschreibung aus einer Vektoria-Texturdatei (.vt).</summary>
	///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
	///<param name="id">Eindeutige Identifikationsnummer der zu ladenden Textur innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id = -1, float Version = 14.11f);

	///<summary> Speichert die Texturbeschreibung in eine Vektoria-Texturdatei (.vt).</summary>
	///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
	///<param name="bWithID">Flang, ob die eigene Identifikationsnummer mit abgespeichert werden soll</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

public:

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary>Art der Textur.</summary>
	int m_eKindTexture;

	///<summary>Pointer auf die Bildklasse.</summary>
	CImage * m_pimage;
};

}