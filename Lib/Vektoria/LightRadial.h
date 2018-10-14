#pragma once
#include "Light.h"

//---------------------------------------------------
// CLightRadial: Klasse für Punktlichter
//
// Autoren: Prof. Dr. Tobias Breiner, Florian Schnell
// Firma  : Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{

class CLightRadial : public CLight
{
	friend class CPlacement;
	friend class CEmitter;
	friend class CLightRadials;
public:
	///<summary> Konstruktor.</summary>
	CLightRadial();

	///<summary> Destruktor.</summary>
	~CLightRadial();

	///<summary> Kopieroperator.</summary>
	///<param name ="lightradial">  Ins vorliegende Punktlicht zu kopierendes Punktlicht </param>
	CLightRadial operator=(CLightRadial & lightradial);

	///<summary> Kopiermethode.</summary>
	///<param name ="lightradial">  Ins vorliegende Punktlicht zu kopierendes Punktlicht </param>
	void Copy(CLightRadial & lightradial);

	///<summary> Initialisiert das Punktlicht.</summary>
	///<param name ="color">  Farbe des Lichtes, wenn color=(1,1,1) ist es helles weißes Licht.</param>
	void Init(CColor color);

	///<summary> Initialisiert das Punktlicht.</summary>
	///<param name ="color">  Farbe des Lichtes, wenn color=(1,1,1) ist es helles weißes Licht.</param>
	///<param name ="color">  Stärke des Lichtes (0.0 = aus ... 1.0 = volle Pulle).</param>
	void Init(CColor color, float frIntensity);

	///<summary> Initialisiert ein weißes Punktlicht.</summary>
	void Init();

	///<summary> Deinitialisiert das Punktlicht.</summary>
	void Fini();

	///<summary> Setzt den maximalen Lichtradius (nur wichtig beim FP-Renderer).</summary>
	void SetRadius(float fRadius);

	///<summary> Lädt eine Punktlichtbeschreibung aus einer Vektoria-Pumktlichtdatei.(.vlr)</summary>
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyLightRadial.vlr" oder ".\\Lights\\MyLightRadial.vlr </param>
	bool Load(char * acPath);

	///<summary> Speichert eine Punktlichtbeschreibung in eine Vektoria-Punktlichttdatei.(.vlr)</summary>
	/// Gibt true aus, falls es funktioniert hat.</summary>		
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyLightRadial.vlr" oder ".\\Lights\\MyLightRadial.vlr </param>
	bool Save(char * acPath);

protected:

	///<summary>  Lädt eine Punktlichtbeschreibung aus einer Vektoria-Punktlichtdatei. (.vlr)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "id"> Die eigene Viewport-ID.</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

	///<summary>  Speichert eine Punktlichtbeschreibung in eine Vektoria-Punktlichttdatei. (.vlr)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "bWithID"> Flag, ob die eigene Sprite-ID mit abgespüeichert werden soll.</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

	///<summary> Rendert Licht, wird automatisch von der darüber liegenden Hierarchie aufgerufen.</summary>
	void Draw(CHMat & mGlobal);

	///<summary> Erzeugt eine Lichtinstanz, indem es auf der Grafikkarte´angemeldet wird.</summary>
	void Create();


public:
	///<summary> Der maximale Lichtradius (nur wichtig beim FP-Renderer).</summary>
	float m_fRadius;
};

}