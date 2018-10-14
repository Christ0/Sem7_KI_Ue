#pragma once
#include "Node3D.h"
#include "..\\VektoriaMath\\GraphNoise.h"
#include "EmitterParticles.h"


//--------------------------------------------
// CEmitter: CPU-basierter Partikelemitter
//
// Autor: Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------

namespace Vektoria
{

#define S_TOGGLEPARAM_VOLUME 1
#define S_TOGGLEPARAM_COLOR 2
#define S_TOGGLEPARAM_POS 3


class CPlacement;
class CPlacements;
class CApiRender;
class CGeo;
class CLight;
class CTimer;
class CScenes;
class CEmitters;

enum EEmitterShape
{
	eEmitterShape_Conical,
	eEmitterShape_Radial,
	eEmitterShape_Planar,
	eEmitterShape_Linear
};

struct SToggle
{
	CNode3D * pnode3D;
	float frRateFactor;
	float fSmoothness;
	CColor color;
	int eKindTo;
	int eKindFrom;
	int eParamTo;
};

class CEmitter : public CNode3D
{
	friend class CGeo;
	friend class CGeoTriangleTable;
	friend class CGeoTriangleList;
	friend class CGeoTriangleStrip;
	friend class CGeoPointList;
	friend class CGeoLineList;
	friend class CPlacement;
	friend class CScene;
	friend class CEmitter;
	friend class CEmitters;
	friend class CMaterial;

protected: 
	///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "iInst"> Nummer der Instanz </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	/// <param name= "pnodeParent"> Pointer auf den aktuellen Elternknoten </param>
	void Tick(CHMat & mGlobal, int & iTick, int &iInst, float & fTimeDelta, CNode * pnodeParent);

	void SetScene(CScene * pscene);

	float GetLifeStrength(float & fTimeOfLife);

	void Draw(CHMat & mGlobal, CCamera * pcamera, int & itFatherIsInFrustum, int & iTick);

public:
	///<summary> Konstruktor. </summary>
	CEmitter();

	///<summary> Destruktor. </summary>
	~CEmitter();

	///<summary> Kopiert den Emitter mit Verküfungsliste. <para></para>
	/// Erzeugt keine neuen Instanzen, beide Emitter verweisen also danach auf dieselben Knotenobjekte.</summary>
	///<param name="emitter">Zu kopierender Emitter</param>
	void Copy(CEmitter & emitter);

	///<summary> Kopiert nur die Parameter des Emitters, die Verküpfungen werden belassen.</summary>
	///<param name="emitter">Zu kopierender Emitter</param>
	void CopyParameters(CEmitter & emitter);

	///<summary> Kopiert den Emitter mitsamt der gesamten Unterhierarchie.<para></para>
	/// Erzeugt also neue Instanzen.</summary>
	///<param name="emitter">Zu kopierender Emitter</param>
	void CopyHierarchy(CEmitter & emitter);

	///<summary> Finalisiert Emitter. </summary>
	void Fini();

	///<summary> Hängt einen Unteremitter an den vorliegenden Emitter an.</summary>
	///<param name="pemitter">Zeiger auf den anzuhängenden Unteremitter</param>
	void AddEmitter(CEmitter * pemitter);

	///<summary> Hängt den Emitter wieder von dem vorliegenden Emitter ab, gibt true aus, wenn es funktioniert hat.</summary>
	///<param name="pemitter">Zeiger auf den abzuhängenden Emitter</param>
	bool SubEmitter(CEmitter * pemitter);

	///<summary> Hängt ein anderes Placement an den vorliegenden Emitter an.</summary>
	///<param name="pplacement">Zeiger auf das anzuhängende Placement</param>
	void AddPlacement(CPlacement * pplacement);

	///<summary> Hängt das Unterplacement wieder von dem vorliegenden Emitter ab, gibt true aus, wenn es funktioniert hat.</summary>
	///<param name="pplacement">Zeiger auf das abzuhängende Unterplacement</param>
	bool SubPlacement(CPlacement * pplacement);

	///<summary> Hängt ein Placement an den vorliegenden Emitter an, das Placement mit der darunter liegenden Hierarchie wird dann vervielfältigt und als Partikel ausgesandt.</summary>
	///<param name="pplacement">Zeiger auf das anzuhängende Placement</param>
	void SetPlacementParticle(CPlacement * pplacement);

	///<summary>  Steuert die Position (Lokal) eines Placement-Objektes in Abhängigkeit von der Position der Partikel.</summary>
	///<param name="pplacement">Zeiger auf das zu steuernde Placement</param>
	///<param name="fSmoothnessTicks">Weichheitsfaktor(je höher dieser Wert, desto mehr letzte Ticks werden interpoliert) </param>
	///<param name="bQuick">Bei True werden nicht alle Partikel bezüglich ihrer Position interpoliert, sondern nur 12 zufällig ausgewählte</param>
	void TogglePlacementPos(CPlacement * pplacement, float fSmoothnessTicks, bool bQuick = true);

	///<summary>  Steuert den Lautstärkeparameter eines Audio-Objektes in Abhängigkeit von der Auswurfrate des Emitters.</summary>
	///<param name="paudio">Zeiger auf das zu steuernde Audio</param>
	///<param name="frRateFactor">Gewichtungsfaktor (Auswurfrate mal RateFactor = Volume) </param>
	void ToggleAudioVolume(CAudio * paudio, float frRateFactor);

	///<summary>  Steuert die Intensität eines Licht-Objektes in Abhängigkeit von der Auswurfrate des Emitters.</summary>
	///<param name="plight">Zeiger auf das zu steuernde Licht</param>
	///<param name="frRateFactor">Gewichtungsfaktor (Auswurfrate mal Ursprungsfarbe mal Gewichtungsfaktor = resultierende Lichtfarbe) </param>
	///<param name="color">Ursprungsfarbe (Auswurfrate mal Ursprungsfarbe mal Gewichtungsfaktor = resultierende Lichtfarbe) </param>
	void ToggleLightColor(CLight * plight, float frRateFactor, CColor color);

	///<summary>  Schaltet den Emitter ab, belässt allerdings da Licht.</summary>
	void SwitchOffButLight();

	///<summary>  Schaltet den Emitter wieder an, nachdem SwitchOffButLight aufgerufen wurde.</summary>
	void SwitchOnButLight();

	///<summary> Setzt den maximalen Radius der emittierten Partikel (für eventuelles Frustum Culling.</summary>
	///<param name="fRadius">Radius bis wohin die Partikel maximal von der Quelle emittiert werden</param>
	void SetRadius(float fRadius);

	///<summary> Setzt den Auswurf-Rate.</summary>
	///<param name="fRate">Emissionsrate in Partikel pro Sekunde (bei nicht abhängigen Emittern) bzw. in Prozent/100 (bei von den Elternemittern abhängigen Emittern) </param>
	void SetRate(float fRate);

	///<summary> Setzt die Auswurf-Rate, bei denen Partikel gespawnt werden.<para></para>
	/// Ist sinnvoll, um Unteremitter bei verschiedenen Stärken umzuschalten (z.B. bei Tröpfeln einen anderen Emitter zu verwenden, als bei einem Regenguss. </summary>
	///<param name="fRateMinLower">Emissionsrate in Partikel pro Sekunde ab der mit dem Auswurf angefangen wird </param>
	///<param name="fRateMinUpper">Emissionsrate in Partikel pro Sekunde ab der mit dem Auswurf voll angefangen wird </param>
	///<param name="fRateMaxLower">Emissionsrate in Partikel pro Sekunde ab der mit dem Auswurf wieder angefangen wird aufzuhören </param>
	///<param name="fRateMaxUpper">Emissionsrate in Partikel pro Sekunde ab der mit dem Auswurf wieder voll zum Stillstand kommt </param>
	void SetRateLimits(float fRateMinLower, float fRateMinUpper, float fRateMaxLower, float fRateMaxUpper);

	///<summary> Schaltet die Abhängikeit von eventuellen Elternemittern an.</summary>
	void SetDependentOn();

	///<summary> Setzt die maximale Auswurfgeschwindigkeit.</summary>
	///<param name="fVelocity">Auswurfgeschwindigkeit in Metern pro Sekunde </param>
	void SetVelocity(float fVelocity);

	///<summary> Setzt die maximale Auswurfdrehgeschwindigkeit.</summary>
	///<param name="fAngularVelocity">Auswurfdrehgeschwindigkeit im Bogenmaßwinkel pro Sekunde </param>
	void SetAngularVelocity(float fAngularVelocity);

	///<summary> Setzt die Veränderugsrate der Auswürfe.</summary>
	///<param name="frRateVolatility">Veränderugsrate der Auswurfgeschwindigkeiten (0.0= Partikel werden immer gleich viel ausgeworfen ... 1.0= Partikel werden manchal gar nicht emmitiert, manchmal mit maximaler Anzahl)</param>
	void SetRateVolatility(float frRateVolatility);

	///<summary> Setzt die Auswurgeschwindigkeitsveränderungsrate.</summary>
	///<param name="frVelocityVolatility">Auswurgeschwindigkeitsveränderungsrate (0.0= Partikel werden immer gleich schnell ausgeworfen ... 1.0= Partikel werden manchal mit der Geschwindigkeit Null und manchmal mit maximaler Geschwindigkeit emittiert) </param>
	void SetVelocityVolatility(float frVelocityVolatility);

	///<summary> Setzt die minimale Durchsichtigkeit.</summary>
	///<param name="frVelocityVolatility">Minimaldurchsichtigkeit (0.0 = am Punkt ihrer maximlaen Sichtbarkeit sind die Partikel opak ... 0.5 am Punkt ihrer maximlaen Sichtbarkeit sind die Partikel halbtransparent   ... 1.0 Partikel sind die ganze Zeit undurchsichtig </param>
	void SetTransparency(float frTransparency);

	///<summary> Setzt den Endskalierungsfaktor.</summary>
	///<param name="frScalingAnimation">Endskalierungsfaktor (um wieviel ist der Partkel am Ende größer (Werte größer 1.0) oder kleiner (Werte kleiner 1.0) </param>
	void SetScalingAnimation(float frScalingAnimation);

	///<summary> Setzt die Wartezeit, bis der Partikel nach der Emittierung anfängt zu erscheinen.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (fTimeToWait), Erscheinungszeit (fTimeToCome), Haltezeit (fTimeToStay) und Verblassungszeit (fTimeToFade)</summary>
	///<param name="fTimeToWait">Wartezeit in Sekunden </param>
	void SetTimeToWait(float fTimeToWait);

	///<summary> Setzt die Erscheinungszeit, bis der Partikel nach der Wartezeit seine volle Sichtbarkeit erreicht hat.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (fTimeToWait), Erscheinungszeit (fTimeToCome), Haltezeit (fTimeToStay) und Verblassungszeit (fTimeToFade)</summary>
	///<param name="fTimeToCome">Wartezeit in Sekunden </param>
	void SetTimeToCome(float fTimeToCome);

	///<summary> Setzt die Haltezeit, also die Zeit die der Partikel seine volle Sichtbarkeit hat.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (fTimeToWait), Erscheinungszeit (fTimeToCome), Haltezeit (fTimeToStay) und Verblassungszeit (fTimeToFade)</summary>
	///<param name="fTimeToStay">Haltezeit in Sekunden </param>
	void SetTimeToStay(float fTimeToStay);

	///<summary> Setzt die Verblassungszeit, also die Zeit die der Partikel am Schluss brauch, um zu verschwinden.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (fTimeToWait), Erscheinungszeit (fTimeToCome), Haltezeit (fTimeToStay) und Verblassungszeit (fTimeToFade)</summary>
	///<param name="fTimeToFade">Verblassungszeit in Sekunden</param>
	void SetTimeToFade(float fTimeToFade);

	///<summary> Setzt die Frame Rates, ab denen nicht mehr neuze Partikel gespawnt werden sollen <para></para>
	/// Kann in einem Spiel dafür verwendet werden, um die FrameRate einigerma0en konstanz zu halten.</summary>
	///<param name="fFrameRateLower">Untere Bildwiederholrate (darunter werden überhaupt keine Partikel mehr ausgeworfen)</param>
	///<param name="fFrameRateUpper">Obere Bildwiederholrate (darüber werden so viele Partikel ausgeworfen, wie in SetRate angegeben)</param>
	void SetFrameRateLimits(float fFrameRateLower, float fFrameRateUpper);

	///<summary> Aktualisiert die Axis-Aligned Boundiung Boxen rekursiv in der Hierarchie hoch. </summary>
	void UpdateAABBAnchestors();

	///<summary> Updated die Axis-Aligned Boundiung Boxen.</summary>
	virtual void UpdateAABB();

	///<summary> Kopiert alle Frustum-Eigenschaften des Emitters rekursiv in der Hierarchie hinunter, belässt die Eigenschaften, wo ein Entry-Flag gesetzt wurde.</summary>
	void CopyDownwards();

	//----------------------------
	// Lade- und Speichermethoden:
	//----------------------------

	///<summary> Lädt einen vorgefertigen Emitter über ein Skriptfile mit dem Namen acName.ve mit allen Parametern, Texturen, etc.aus der Emitterbibliothek, <para>< / para>
	///diese befindet sich in Lib/Emitters.<para>< / para>
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name = "acName"> Name des vorgefertigten Emitters, z.B.:<para></para>
	/// "CloudSingle", "Drops", "Fire","FireSparks", "Fog", ""HeatHaze","Rain","Smoke","Snow","Steam", ... </param>
	bool LoadPreset(char * acName);

	///<summary> Speichert vorgefertigen Emitter mit dem Dateinamen "acName.ve" in den Ordner "Emitter/acName" der Lib.<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name= "acName">Objektnamen</param>
	bool SavePreset(char * acName);

	///<summary> Lädt die Parameterdaten mitsamt untergeordneter Hieracrhie aus einer Vektoria-Emitter-Datei (.ve).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Geometriedatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyEmitter.ve" oder ".\\emitters\\MyEmitter.ve" </param>
	bool Load(char * acPath);

	///<summary> Speichert die Parameterdaten mitsamt untergeordneter Hieracrhie in eine Vektoria-Emitter-Datei (.ve).<para></para> 
	/// Gibt true aus, falls es funktioniert hat.</summary>
	///<param name="acPath">ASCII-Pfadangabe der Geometriedatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyEmitter.ve" oder ".\\emitters\\MyEmitter.ve" </param>
	bool Save(char * acPath);

protected:

	///<summary> Lädt ein Emitter aus einer Vektoria-Emitter-Datei (.ve).</summary>
	///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
	///<param name="id">Eindeutige Identifikationsnummer der zu ladenden Geometrie innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id = -1, float fVersion = 14.11f);

	///<summary> Speichert eine Emitter in eine Vektoria-Geometrie-Datei (.ve).</summary>
	///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
	///<param name= "bWithID"> Flag, ob die eigene Knoten-ID mit abgespeichert werden soll</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

public:

	//-----------------
	// Membervariablen:
	//-----------------

	///<summary> Flag, ob es sich um einen von den Eltern abhängigen Emitter handelt.</summary>
	bool m_bDependent;

	///<summary> Maximalradius bis wohin die Emitter ausgehend von der Quelle fliegen können.</summary>
	float m_fRadius;
	
	///<summary> Auswurfrate in Partikel pro Sekunde.</summary>
	float m_fRate;

	///<summary> Minimale Auswurfrate in Partikel pro Sekunde (untere Grenze, dazwischen wird interpoliert).</summary>
	float m_fRateMinLower;

	///<summary> Minimale Auswurfrate in Partikel pro Sekunde  (oberere Grenze, dazwischen wird interpoliert).</summary>
	float m_fRateMinUpper;

	///<summary> Maximale Auswurfrate in Partikel pro Sekunde (untere Grenze, dazwischen wird interpoliert).</summary>
	float m_fRateMaxLower;

	///<summary> Maximale Auswurfrate in Partikel pro Sekunde  (oberere Grenze, dazwischen wird interpoliert).</summary>
	float m_fRateMaxUpper;

	///<summary> Fraktionaler Auswurfratenveränderungsfaktor.</summary>
	float m_frRateVolatility;

	///<summary> Auswurfgeschwindigkeit in Metern pro Sekunde.</summary>
	float m_fVelocity;

	///<summary> Fraktionaler Auswurfgeschwindigkeitsveränderungsfaktor.</summary>
	float m_frVelocityVolatility;
	
	///<summary> Rotationsauswurfgeschwindigkeit in Bogenmaß pro Sekunde.</summary>
	float m_fAngularVelocity;

	///<summary> Fraktionaler Auswurfwinkelgeschwindigkeitsveränderungsfaktor.</summary>
	float m_frAngularVelocityVolatility;

	///<summary> Wartezeit, bis der Partikel nach der Emittierung anfängt zu erscheinen.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (m_fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (m_fTimeToWait), Erscheinungszeit (m_fTimeToCome), Haltezeit (m_fTimeToStay) und Verblassungszeit (m_fTimeToFade)</summary>
	float m_fTimeToWait;

	///<summary> Erscheinungszeit, bis der Partikel nach der Wartezeit seine volle Sichtbarkeit erreicht hat.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (m_fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (m_fTimeToWait), Erscheinungszeit (m_fTimeToCome), Haltezeit (m_fTimeToStay) und Verblassungszeit (m_fTimeToFade)</summary>
	float m_fTimeToCome;

	///<summary> Haltezeit, also die Zeit die der Partikel seine volle Sichtbarkeit hat.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (m_fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (m_fTimeToWait), Erscheinungszeit (m_fTimeToCome), Haltezeit (m_fTimeToStay) und Verblassungszeit (m_fTimeToFade)</summary>
	float m_fTimeToStay;

	///<summary> Verblassungszeit, also die Zeit die der Partikel am Schluss brauch, um zu verschwinden.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (m_fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (m_fTimeToWait), Erscheinungszeit (m_fTimeToCome), Haltezeit (m_fTimeToStay) und Verblassungszeit (m_fTimeToFade)</summary>
	float m_fTimeToFade;

	///<summary> Gesamte Lebensdauer eines Partikels.<para></para>
	/// Hintergrundsinfo: Die Gesamtlebensdauer (m_fTimeToLive) setzt sich bei Vektoria-Emittern zusammen aus: Wartezeit (m_fTimeToWait), Erscheinungszeit (m_fTimeToCome), Haltezeit (m_fTimeToStay) und Verblassungszeit (m_fTimeToFade)</summary>
	float m_fTimeToLive;

	///<summary> Minimale Transparenz der Partikel.</summary>
	float m_frTransparency;

	///<summary> Flag, ob Skaliert werden soll.</summary>
	bool m_bScalingAnimation;

	///<summary> Skalierungsfaktor.</summary>
	float m_frScalingAnimation;

	///<summary> Zyklischer Zufallsgraph (Um die Volatilitäs-Veränderungen zu berechnen).</summary>
	CGraphNoise * m_pgraphnoise;

	///<summary> Container für die Unteremiiter.</summary>
	CEmitters * m_pemitters;

	///<summary> Pointer auf das zu klonende Unterplacment.</summary>
	CPlacement * m_pplacement;

	///<summary> Szenenliste, mit denen der Emitter verbunden ist.</summary>
	CScenes * m_pscenesAnchestor;

	///<summary> Aktuelle Emissionsrate in Partikel pro Sekunde.</summary>
	float m_fRateAct;
	
	///<summary> Untere Zeitspanne, wird aus der oberen Bildwiderholrate berechnet.</summary>
	float m_fTimeDeltaLower;

	///<summary> Oberere Zeitspanne, wird aus der unteren Bildwiderholrate berechnet.</summary>
	float m_fTimeDeltaUpper;

	///<summary> Flag, ob das Frustum Culling für die Unterhierarchie angeschaltet ist.</summary>
	bool m_bFrustumCulling;

	///<summary> Flag, ob das Frustum Culling von den Elternknoten überschrieben wird.</summary>
	bool m_bFrustumCullingEntry;

	///<summary> Flag, ob die Bounding Volume Hierarchie genau berechnet werden soll (langsam!) (Default = false).</summary>
	bool m_bBVHExactCalculation;

	///<summary> Flag, ob die Bounding Volume Hierarchie-Informationen von den Eltern an die Kinder weitergereicht weitergereicht werden sollen (Default = false).</summary>
	bool m_bBVHExactCalculationEntry;

	///<summary> Pointer auf Liste der Unterplacements, wenn keine Unterplacements vorhanden sind, ist der Pointer = NULL.</summary>
	CPlacements * m_pplacements;

	///<summary> Liste der Toggles.</summary>
	SToggle * m_atoggle;

	///<summary> Anzahl der Toggles.</summary>
	int m_iToggles;

	///<summary> Anzahl der allokierten Toggles.</summary>
	int m_iTogglesAllocated;

	///<summary> Partikelringpuffer.</summary>
	CEmitterParticles * m_aemitterparticles;

	///<summary> Anzahl der Ringpuffer.</summary>
	int m_iEmitterParticles;

	///<summary> Anzahl der allokierten Ringpuffer.</summary>
	int m_iEmitterParticlesAllocated;

	///<summary> Flag, welches anzeigt, ob Partikelsystem ausgeschaltet wurde, ohne das Partikellicht abzuschalten.</summary>
	bool m_bSwitchOffButLight;

protected: 
	void ToggleInit(SToggle & toggle);

	bool m_bMaterialsCollected;
	float m_frInRate;
	bool m_bHasRateLimits;

	int m_iAllocBloc;
	int m_iDraw;
	int m_iTickEmitter;
};

}