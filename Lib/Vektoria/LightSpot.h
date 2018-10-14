#pragma once
#include "Light.h"

//-------------------------------------------------------------------------
// CLightRadial: Klasse für Spotlight
//
// Autoren: Prof. Dr. Tobias Breiner, Florian Schnell & Patrick Fleischmann
// Firma: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------------

namespace Vektoria
{

class CLightSpot : public CLight
{
	friend class CPlacement;
	friend class CLightSpots;
	friend class CEmitter;

public:
	///<summary>Konstruktor.</summary>
	CLightSpot();

	///<summary>Destruktor.</summary>
	~CLightSpot();

	///<summary>Kopieroperator.</summary>
	CLightSpot operator=(CLightSpot & spotlight);

	///<summary>Kopiermethode.</summary>
	void Copy(CLightSpot & spotlight);

	///<summary>Initialisierung des Scheinwerferlichtes (mit voller Intensität).</summary>
	///<param name = "color"> Farbe des Lichtes in RGB</param>
	///<param name = "faInner"> Innerer Lichtkegelradius im Bogenmaß</param>
	///<param name = "faOuter"> Äußerer Lichtkegelradius im Bogenmaß (muss größer sein als faInner und kleiner als QUARTERPI)</param> 
	void Init(CColor color, float faInner, float faOuter);

	///<summary>Initialisierung des Scheinwerferlichtes.</summary>
	///<param name = "color"> Farbe des Lichtes in RGB</param>
	///<param name = "faInner"> Innerer Lichtkegelradius im Bogenmaß</param>
	///<param name = "faOuter"> Äußerer Lichtkegelradius im Bogenmaß (muss größer sein als faInner und kleiner als QUARTERPI)</param> 
	///<param name = "fIntensity"> Stärke des Lichtes, 0.0 = aus ... 1.0 = volle Pulle </param>
	void Init(CColor color, float faInner, float faOuter, float fIntensity);

	///<summary>Deinitialisierung des Scheinwerferlichtes.</summary>
	void Fini();

	///<summary>Setzt die maximale Leuchtdistanz des Scheinwerfers.</summary>
	///<param name="fMaxDistance"> Maximale Leuchtdistanz des des Scheinwerfers (bis zu welcher Distanz vom LightSpot wirkt das Licht? sollte größer sein als fMinDistance)</param>
	void SetMaxDistance(float fMaxDistance);

	///<summary>Setzt die minimale Distanz des Scheinwerfers (sollte kleiner sein als fMaxDistance).</summary>
	///<param name="fMinDistance"> Minimale Leuchtdistanz des des Scheinwerfers (ab welcher Distanz vom LightSpot wirkt das Licht? Der Wert sollte kleiner sein als fMaxDistance.) </param>
	void SetMinDistance(float fMinDistance);

	///<summary>Setzt äußeren Lichtkegelwinkel.</summary>
	///<param name="faOuter"> Äußerer Lichtkegelwinkel im Bogenmaß (muss größer sein als faInner und kleiner als QUARTERPI) </param>
	void SetOuterAngle(float faOuter);

	///<summary>Setzt inneren Lichtkegelwinkel.</summary>
	///<param name="faInner"> Innerer Lichtkegelwinkel im Bogenmaß (muss kleiner sein als faOuter und größer als Null) </param>
	void SetInnerAngle(float faInner);

	///<summary>Setzt inneren und äußeren Lichtkegelwinkel.</summary>
	///<param name="faInner"> Innerer Lichtkegelwinkel im Bogenmaß (muss kleiner sein als faOuter und größer als Null) </param>
	///<param name="faOuter"> Äußerer Lichtkegelwinkel im Bogenmaß (muss größer sein als faInner und kleiner als QUARTERPI) </param>
	void SetAngles(float faInner, float faOuter);

	///<summary>Setzt den maximalen Lichtradius (nur wichtig beim FP-Renderer).</summary>
	///<param name="fRadius"> Leuchtradius in Units </param>
	void SetRadius(float fRadius);

	///<summary>Schaltet die Schattenberechnung an.</summary>
	void SetShadowOn();

	///<summary>Schaltet die Schattenberechnung aus.</summary>
	void SetShadowOff();

	///<summary>Setzt die Stärke des Schattens.</summary>
	///<param name="frShadowStrength"> Schattenstärke: 0.0f = kein Schatten ... 1.0f voller Schatten (default)</param>
	void SetShadowStrength(float frShadowStrength);

	///<summary>Schaltet die Schattenberechnung inklusive Gausschen Blurring an.</summary>
	void SetSoftShadowOn();

	///<summary>Schaltet die Schattenberechnung inklusive Kaskadierung an. Funktioniert nur im FP-Renderer.</summary>
	void SetCascadedShadowOn();

	///<summary>Schaltet die Lichtkegelberechnung an (default).</summary>
	void SetConeOn();

	///<summary>Schaltet die Lichtkegelberechnung aus.</summary>
	void SetConeOff();

	///<summary>  Lädt eine Schweinwerferlichtbeschreibung aus einer Vektoria-Schweinwerferlichtdatei.(.vls)</summary>
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyLightSpot.vls" oder ".\\Lights\\MyLightSpot.vls </param>
	bool Load(char * acPath);

	///<summary>  Speichert eine Schweinwerferlichtbeschreibung in eine Vektoria-Schweinwerferlichttdatei.(.vls)</summary>
	/// Gibt true aus, falls es funktioniert hat.</summary>		
	///<param name="acPath">ASCII-Pfadangabe der Texturdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyLightSpot.vls" oder ".\\Lights\\MyLightSpot.vls </param>
	bool Save(char * acPath);

protected:

	///<summary> Lädt eine Schweinwerferlichtbeschreibung aus einer Vektoria-Schweinwerferlichtdatei.(.vls)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "id"> Die eigene Viewport-ID.</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

	///<summary> Speichert eine Schweinwerferlichtbeschreibung in eine Vektoria-Schweinwerferlichttdatei.(.vls)</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	///<param name = "bWithID"> Flag, ob die eigene Sprite-ID mit abgespeichert werden soll.</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

	///<summary>Rendert das Licht.</summary>
	void Draw(CHMat & mGlobal);

	///<summary> Erzeugt eine Lichtinstanz, indem es auf der Grafikkarte´angemeldet wird.</summary>
	void Create();

public:

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Ferndistanz (wie weit scheint das Licht).</summary>
	float m_fFarClipping;

	///<summary> Nahdistanz (ab welcher Distanz wird das Licht gerendert, sollte aus shadertechnischen Gründen nicht Null sein).</summary>
	float m_fNearClipping;

	///<summary> Äußerer Kegelöffnungswinkel des Lichtes.</summary>
	float m_faOuter;

	///<summary> Kosinus des äußeren Kegelöffnungswinkel des Lichtes.</summary>
	float m_fOuterCosAngle;

	///<summary> Innerer Kegelöffnungswinkel des Lichtes.</summary>
	float m_faInner;

	///<summary> Kosinus des inneren Kegelöffnungswinkel des Lichtes.</summary>
	float m_fInnerCosAngle;

	///<summary> Flag, ob die Schatten mit eiunem Gausschen Weichheitsfilter berechnet werden sollen.</summary>
	bool m_bSoftShadow;

	///<summary> Flag, ob kaskadierte Schatten berechnet werden sollen, funktioniert nur mit m_bSoftShadows = true im FP-Renderer.</summary>
	bool m_bCascadedShadow;

	///<summary> Flag, ob Lichtkegelberechnung (default = true), Schattenberechnung wird trotzdem nur auf äußeren Lichtkegel bezogen.</summary>
	bool m_bCone;

	///<summary> Schattenstärke.</summary>
	float m_frShadowStrength;

	///<summary> Maximaler Wirkradius, nur wichtig für den FP-Renderer.</summary>
	float m_fRadius;
};

}