#pragma once
#include "Node3D.h"
#include "../VektoriaMath/Color.h"
#include "ApiRender.h"
#include "Geo.h"

//---------------------------------------------------
// CLight: Klasse für Lichter
//
// Autoren: Prof. Dr. Tobias Breiner
//---------------------------------------------------



namespace Vektoria
{

struct SShadowParameter
{
	float fPointBlurSize; // default 2.5f
	float fPointShadowBias; // default 10.f
	float fSpotShadowBias; // default 1.2f

	SShadowParameter() :
		fPointBlurSize(2.5f),
		fPointShadowBias(100.f),
		fSpotShadowBias(12.f)
	{}
};

struct SVPLParameter
{
	float fVPLSpotStrength; // default 80
	float fVPLPointStrength; // default 20
	float fVPLSpotRadius; // default 10
	float fVPLPointRadius; // default 10
	float fVPLColorThreshold; // default 70
	float fVPLBrightnessCutoff; // default 18
	float fVPLBackFaceContribution; // default 50

	SVPLParameter() :
		fVPLSpotStrength(30),
		fVPLPointStrength(30),
		fVPLSpotRadius(15),
		fVPLPointRadius(10.f),
		fVPLColorThreshold(70),
		fVPLBrightnessCutoff(18),
		fVPLBackFaceContribution(99)
	{}
};

// Fortlaufende Zählung der Lichtobjekte, Id 0 ist für Sonderobjete vorgesehen (Mir fällt leider keine besser Möglichkeit ein, als eine globale Variable).
static unsigned int g_idLight = 0; 

class CScenes;
class CViewports;

class CLight : public CNode3D
{
	friend class CEmitter;
	friend class CPlacement;
	friend class CLights;
	friend class CLightParallels;
	friend class CLightRadials;
	friend class CLightSpots;
	friend class CVektoriaClient;
	friend class CRoot;
	friend class CDirectX11FP;

protected: 
	///<summary> Wird jeden Tick von der übergeordneten Hierarchie automatisch aufgerufen.</summary>
	///<param name = "m"> Zu kopierendes Licht.</param>
	///<param name = "iTick"> Nummer des Ticks.</param>
	void Tick(CHMat & m, int & iTick);

public:
	///<summary> Konstruktor.</summary>
	CLight();

	///<summary> Destruktor.</summary>
	~CLight();

	///<summary> Kopieroperator.</summary>
	///<param name = "light"> Zu kopierendes Licht.</param>
	CLight operator=(CLight & light);

	///<summary> Kopiermethode.</summary>
	///<param name = "light"> Zu kopierendes Licht.</param>
	void Copy(CLight & light);

	///<summary> Initialisiert das Licht mit der Farbe color.</summary>
	///<param name = "color"> Lichtfarbe, z.B. wenn color=CColor(1,1,0) ist es gelbes Licht.</param>
	void Init(CColor color);

	///<summary> Deinitialisiert das Licht.</summary>
	void Fini();

	///<summary> Findet Lichter, welche die Geometrie pgeo unter der Sicht pcamera beeinflussen.</summary>
	///<param name = "pgeo"> Lichtfarbe</param>
	static void FindLights(CGeo * pgeo, CCamera * pcamera);

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie ein (überladene Funktion).</summary>
	void SwitchOn(); 

	///<summary> Schaltet Knoten mitsamt seiner Unterhierarchie aus (überladene Funktion).</summary>
	void SwitchOff(); 

	///<summary> Aktualisiert die Axis Aligned Bounding Boxen.</summary>
	virtual void UpdateAABB();

	///<summary> Setzt die Farbe des Lichtes, kann auch während der Laufzeit aufgerufen werden. </summary>
	///<param name = "color"> Lichtfarbe, z.B. wenn color=CColor(1,1,0) ist es gelbes Licht.</param>
	void SetColor(CColor color);

	///<summary> Setzt den linearen Lichtabfall (unnatürlich, aber leicht zu justieren. </summary>
	///<param name = "fAttenuationLinear"> linearer Lichtabfall<para></para>
	/// Beispiele:<para></para>
	/// 0.0=kein Lichtabfall (default) <para></para>
	/// 0.01=In Entferung von einer Unit ist nur noch 99% des Lichtes und nach 100 Metern ist kein Licht mehr vorhanden<para></para>
	/// 0.02=In Entferung von einer Unit ist nur noch 98% des Lichtes und nach 50 Metern ist kein Licht mehr vorhanden<para></para>
	/// 0.1=In Entferung von einer Unit ist nur noch 90% des Lichtes und nach 10 Metern ist kein Licht mehr vorhanden</param>
	void SetAttenuationLinear(float fAttenuationLinear);

	///<summary> Setzt den quadratischen Lichtabfall (physikalisch korrekter Abfall, aber schwer zu justieren). </summary>
	///<param name = "fAttenuationQuadratic"> quadratischer Lichtabfall<para></para>
	/// Beispiele:<para></para>
	/// 0.0=kein Lichtabfall (default) <para></para>
	/// 0.01=In Entferung von einer Unit ist nur noch 90% des Lichtes und nach 10 Metern ist nur noch 10% vorhanden</param>
	void SetAttenuationQuadratic(float fAttenuationQuadratic);

	///<summary> Gibt true aus, wenn das Licht direkt oder indirekt an die Szene angehängt ist.</summary>
	///<param name = "pscene"> Pointer auf die Szene</param>
	bool IsConnectedToScene(CScene * pscene);

	///<summary> Gibt true aus, wenn das Licht indirekt vom Viewport pviewport angezeigt wird.</summary>
	///<param name = "pviewport"> Pointer auf den Viewport</param>
	bool IsConnectedToViewport(CViewport * pviewport);

	///<summary> Berechnet, welche Viewports aktuell mit der Camera verbunden sind,  und schreibt diese in die Pluralklasse m_pviewportsAnchestor.</summary>
	void CalcViewportsAnchestor(); 

	///<summary> Setzt die Auflösung der Schatten-Textur (je höher die Werte, desto schöner sehen die Schatten aus).</summary>
	///<param name = "ixPixels"> Breite der Shadow-Map in Pixeln.</param>
	///<param name = "iyPixels"> Höhe der Shadow-Map in Pixeln.</param>
	void SetShadowMapResolution(int ixPixels, int iyPixels);

	///<summary>  Lädt eine Lichtbeschreibung aus einer Vektoria-Lichtdatei.</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	void Load(CFileVektoria & filevektoria);

	///<summary>  Speichert eine Parallellichtbeschreibung in eine Vektoria-Parallellichttdatei.</summary>
	///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
	void Save(CFileVektoria & filevektoria);

	// -----------
	// Parameter:
	// -----------

	///<summary> Farbe des Lichtes in RGB-Werten</summary>
	CColor m_color;

	///<summary> Konstanter Lichtabnahmefaktor</summary>
	float m_fAttenuationConstant;

	///<summary> Linearer Lichtabnahmefaktor</summary>
	float m_fAttenuationLinear;

	///<summary> Quadratischer Lichtabnahmefaktor (am natürlichsten)</summary>
	float m_fAttenuationQuadratic;

	// -------------------
	// Schatten-Parameter:
	// -------------------

	///<summary> true, falls Licht Schatten werden soll (funktioniert aktuell nur für Spotlights).</summary>
	bool m_bCauseShadow; 

	///<summary> Projektionsmatrix des Lichtes.</summary>
	CHMat m_mProjection;

	///<summary> View-Matrix des Lichtes.</summary>
	CHMat m_mView;

	///<summary> Breite der Shattentextur in Pixeln.</summary>
	int m_iShadowMapWidth;

	///<summary> Höhe der Shattentextur in Pixeln.</summary>
	int m_iShadowMapHeight;

	///<summary> Konnektierte Szenen.</summary>
	CScenes * m_pscenesAnchestor;

	///<summary> Konnektierte Viewports.</summary>
	CViewports * m_pviewportsAnchestor; 

	///<summary> Flag, welches true ist, falls die ShadowMap-Auflösung verändert wurde.</summary>
	bool m_bChangedShadowMapResolution;

	///<summary> Flag, welches true ist, falls die Position oder Orientierung des Lichtes verändert wurde.</summary>
	bool m_bChangedPos;

	///<summary> Flag, welches true ist, falls die Farbe des Lichtes verändert wurde.</summary>
	bool m_bChangedColor;

	///<summary> Flag, welches true ist, falls ein Schattenparameter verändert wurde.</summary>
	bool m_bChangedShadow;

	///<summary> Eindeutige Licht-ID (Nicht zu verwechseln mit der Knoten-ID!).</summary>
	unsigned int m_idLight;

	///<summary> Die aktuelle Lichtinstanz, welche gerade in Bearbeitung ist.</summary>
	static int s_iLightInstance;

	///<summary> Die Anzahl aller Lichtinstanzen.</summary>
	static int s_iLightInstances;

	///<summary> Flag, ob eine Neubrechnung der Lichtinstanzen notwenig ist.</summary>
	static bool s_bRecalcLightInstances;

protected:


	///<summary> Anzahl der Lichter (Hilfsparameter)</summary>
	static unsigned int s_iLightCount;

	///<summary> Pointer auf ein Lichterarray</summary>
	static CLight **s_ppLights;

	///<summary> True, falls noch nicht gezeichnet. </summary>
	bool m_bFirstDraw;
};

}