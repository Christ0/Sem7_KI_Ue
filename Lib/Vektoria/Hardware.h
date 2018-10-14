#pragma once
#include "Frames.h"

//---------------------------------------------------
// CHardware: Klasse für Rendercomputer und ähnliches, welche in einer Szenengraph-Hierarchie eingebunden werden können 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{

class CHardware : public CNode
{
	friend class CHardwares;
	friend class CFrames;
	friend class CFrame;
	friend class CRoot;
protected:
	// Hilfsmethode für SetIP
	bool CheckIfByte(int & i, int & iPart); 

	// Wird von CRoot aufgerufen.
	void Tick(int & iTick); 
public:

	// Konstruktor.
	CHardware();

	// Destruktor.
	~CHardware();

	// Kopieroperator
	CHardware operator=(CHardware & hardware);

	// Kopiert die Hardware
	void Copy(CHardware & hardware); 

	// Initialisiert die Hardware mit seinem Hostnamen (über ipconfig /all herausfindbar).
	void Init(char * acHost); 

	// Finalisiert die Hardware.
	void Fini(); 

	// Hängt ein Frame an die Hardware an.
	void AddFrame(CFrame * pframe); 

	// Setzt den Namen des Computers.
	void SetHostName(char * acHost); 

	// Setzt die IP Adresse, falls eine ungültige Adresse eingegeben wurde, wird false ausgegeben.
	bool SetIP(char * acAddress); 

	// Überprüft, ob die IP-Adresse mit der aktuellen übereinstimmt.
	bool IsIP(char * acAddress); 

	// Lädt eine Hardwarebeschreibung aus einem Vektoria-Hardwarefile.
	void Load(CFileVektoria & filevektoria, int id); 

	// Speichert eine Hardwarebeschreibung in ein Vektoria-Hardwarefile.
	void Save(CFileVektoria & filevektoria, bool bWithID = false); 

	// ----------------
	// Membervariablen:
	// ----------------

	// Liste der angehängten Frames.
	CFrames m_frames; 

	// Die IP4-Adresse der Hardware.
	char m_acIPAddress[100]; 

	// Der Hostname der Hardware (beim Verteilten Rendering wird dieser verwendet).
	char m_acHost[256]; 
};

}