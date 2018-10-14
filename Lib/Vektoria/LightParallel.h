#pragma once
#include "Light.h"
#include "../VektoriaMath/HVector.h"

//------------------------------------
// CLightParallel, Klasse für Parallellichter
// 
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//------------------------------------


namespace Vektoria
{

class CLightParallel : public CLight
{
	friend class CScene;
	friend class CEmitter;
	friend class CLightParallels;
public:
	///<summary> Konstruktor.</summary>
	CLightParallel();

	///<summary> Destruktor.</summary>
	~CLightParallel();

	///<summary> Kopieroperator.</summary>
	///<param name = "lightparallel"> Das ins vorliegende Parallellicht zu kopierende Parallellicht</param>
	CLightParallel operator=(CLightParallel & lightparallel);

	///<summary> Kopiermethode.</summary>
	///<param name = "lightparallel"> Das ins vorliegende Parallellicht zu kopierende Parallellicht</param>
	void Copy(CLightParallel & lightparallel);

	///<summary> Initialisiert das Parallellicht.</summary>
	///<param name = "vDirection"> Lichtrichtung (Achtung die Richtung zum Licht und nicht vom Licht!)</param>
	///<param name = "color"> Farbe des Lichtes, wenn color=(1,1,1) ist es helles weißes Licht.</param>
	void Init(CHVector vDirection, CColor color = CColor(1.0f, 1.0f, 1.0f, 0.0f));

	///<summary> Deinitialisiert das Parallellicht.</summary>
	void Fini();

	///<summary> Setzt die Richtung des Parallellichtes neu, kann auch während der Laufzeit angewandt werden.</summary>
	///<param name = "vDirection"> Lichtrichtung (Achtung die Richtung zum Licht und nicht vom Licht!)</param>
	void SetDirection(CHVector vDirection);

	///<summary>  Lädt die Daten aus einer Vektoria-Parallellichtdatei.(.vlp)</summary>
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyLightParallel.vlp" oder ".\\Lights\\MyLightParallel.vlp </param>
	bool Load(char * acPath);

	///<summary>  Speichert die Daten in eine Vektoria-Parallellichtdatei.(.vlp)</summary>
	/// Gibt true aus, falls es funktioniert hat.</summary>		
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyLightParallel.vlp" oder ".\\Lights\\MyLightParallel.vlp </param>
	bool Save(char * acPath);

protected:

	///<summary>  Lädt eine Parallellichtbeschreibung aus einer Vektoria-Parallellichtdatei. (.vlp)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "id"> Die eigene Viewport-ID.</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

	///<summary>  Speichert eine Parallellichtbeschreibung in eine Vektoria-Parallellichttdatei.(.vlp)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "bWithID"> Flag, ob die eigene Sprite-ID mit abgespüeichert werden soll.</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

	///<summary> Rendert Licht, wird automatisch von der darüber liegenden Hierarchie aufgerufen.</summary>
	void Draw();

	///<summary> Erzeugt eine Lichtinstanz, indem es auf der Grafikkarte´angemeldet wird.</summary>
	void Create();

public:
	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die Lichtrichtung.</summary> 
	CHVector m_vDirection;

	///<summary> Flag, welches angiebt, ob die Lichtrichtung verändert wurde.</summary>
	bool m_bChangedDir;
};

}