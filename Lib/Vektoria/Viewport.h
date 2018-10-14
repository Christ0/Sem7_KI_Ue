#pragma once
#include "Backgrounds.h"
#include "Overlays.h"
#include "Writings.h"
#include "WritingChar.h"
#include "Camera.h"
#include "../VektoriaMath/Color.h"
#include "Placement.h"
#include <windows.h>


//--------------------------------------------------------------------------------------------
// Klasse: CViewport
// Beschreibung: Klasse für einen Bildschirmausschnitt zum Rendern
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------

#define PP_GAUSSIAN_BLUR 1
#define PP_NOGAUSSIAN_BLUR 0
#define PP_ENHANCED_EDGES 1
#define PP_NOENHANCED_EDGES 0
#define PP_MEAN_FILTER 1
#define PP_NOMEAN_FILTER 0
#define PP_FXAA 1
#define PP_NOFXAA 0

namespace Vektoria
{

	class CRoot;
	class CFrame;

	struct SShadowParameter;
	struct SVPLParameter;

	struct SBloomParameter
	{
		float fOriginalIntensity;
		float fOriginalSaturation;
		float frBloomStrength;
		float fBloomSaturation;
		float fBlurDistance;

		SBloomParameter()
			: fOriginalIntensity(1.f),
			  fOriginalSaturation(1.f),
			  frBloomStrength(1.3f),
			  fBloomSaturation(1.3f),
			  fBlurDistance(0.0005f)
		{}
	};

	struct SGodRayParameter
	{
		float fExposure;
		float fDecay;
		float fDensity;
		float fWeight;
		CHVector vLightPos;

		SGodRayParameter()
			: fExposure(0.0024f),
			  fDecay(1.f),
			  fDensity(0.5f),
			  fWeight(8.f),
			  vLightPos(0.f, 0.f, 0.f, 1.f)
		{}
	};

	class CViewport : public CNode
	{
		friend class CRoot;
		friend class CFrame;
		friend class CBackgrounds;
		friend class CViewports;
		friend class CWribels;
		friend class CVektoriaClient;

	protected:
		void Tick(float & fTimeDelta, int & iTick);
		void SetFrame(CFrame * pframe);
		void SetRoot(CRoot * proot);
		void CollectMaterials();

	public:
		// ==============
		// Basismethoden:
		// ==============

		///<summary> Konstruktor.</summary>
		CViewport();

		///<summary> Destruktor.</summary>
		~CViewport();

		///<summary> Kopieroperator.</summary>
		///<param name = "viewport"> Zu kopierender Viewport</param>
		CViewport operator=(CViewport & viewport);

		///<summary> Kopiermethode.</summary>
		///<param name = "viewport"> Zu kopierender Viewport</param>
		void Copy(CViewport & viewport);

		///<summary> Initialisiert Viewport, so dass er das ganze Frame ausfüllt.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		void InitFull(CCamera * pcamera);

		///<summary> Initialisiert Viewport, so dass er die linke Hälfte des Frames ausfüllt.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		void InitHalfLeft(CCamera * pcamera);

		///<summary> Initialisiert Viewport, so dass er die rechte Hälfte des Frames ausfüllt.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		void InitHalfRight(CCamera * pcamera);

		///<summary> Initialisiert Viewport, so dass er die obere Hälfte des Frames ausfüllt.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		void InitHalfUpper(CCamera * pcamera);

		///<summary> Initialisiert Viewport, so dass er die untere Hälfte des Frames ausfüllt.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		void InitHalfLower(CCamera * pcamera);
		
		///<summary> Initialisiert Viewport mit relativen Maßen zum übergeordneten Frame.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		///<param name = "frx"> X-Wert der linken obere Ecke relativ zum übergeordneten Frame (0.0 = linker Rand des Frames ... 0.5 = Mitte ... 1.0 = Rechter Rand des Frames)</param>
		///<param name = "fry"> Y-Wert der linken obere Ecke relativ zum übergeordneten Frame (0.0 = oberer Rand des Frames ... 0.5 = Mitte ... 1.0 = Unterer Rand des Frames)</param>
		///<param name = "frWidth"> Breite des Viewports relativ zum übergeordneten Frame (0.0 = unendlich schmal in X-Richtung ... 0.5 = halb so breit wie Frame ... 1.0 = genau so breit wie Frame)</param>
		///<param name = "frHeight"> Höhe des Viewports relativ zum übergeordneten Frame (0.0 = unendlich schmal in Y-Richtung ... 0.5 = halb so hoch wie Frame ... 1.0 = genau so hoch wie Frame)</param>
		void Init(CCamera * pcamera, float frx, float fry, float frWidth, float frHeight);

		///<summary> Initialisiert Viewport mit relativen Maßen zum übergeordneten Frame floatrect.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		///<param name = "floatrect"> Position und Größe des Viewports (als Rechteck) relativ zum übergeordneten Frame</param>
		void Init(CCamera * pcamera, CFloatRect floatrect);

		///<summary> Deinitialisiert Viewport.</summary>
		void Fini();

		///<summary> Kann dem Viewport nach dem Init eine neue Kamera verpassen.</summary>
		///<param name = "pcamera"> Pointer auf die Kamera, deren Sicht der Viewport anzeigen soll</param>
		void SetCamera(CCamera * pcamera);

		///<summary> Verändert die relative Größe des Viewports zum Frame.</summary>
		///<param name = "frx"> X-Wert der linken obere Ecke relativ zum übergeordneten Frame (0.0 = linker Rand des Frames ... 0.5 = Mitte ... 1.0 = Rechter Rand des Frames)</param>
		///<param name = "fry"> Y-Wert der linken obere Ecke relativ zum übergeordneten Frame (0.0 = oberer Rand des Frames ... 0.5 = Mitte ... 1.0 = Unterer Rand des Frames)</param>
		///<param name = "frWidth"> Breite des Viewports relativ zum übergeordneten Frame (0.0 = unendlich schmal in X-Richtung ... 0.5 = halb so breit wie Frame ... 1.0 = genau so breit wie Frame)</param>
		///<param name = "frHeight"> Höhe des Viewports relativ zum übergeordneten Frame (0.0 = unendlich schmal in Y-Richtung ... 0.5 = halb so hoch wie Frame ... 1.0 = genau so hoch wie Frame)</param>
		void ReSize(float frx, float fry, float frWidth, float frHeight);

		///<summary> Verändert Größe des Viewports bei Veränderung der Größe des Frames, wird automatisch von der übergeordneten Hierarchie aufgerufen).</summary>
		void ReSize(); 

		///<summary> Berechnet absolute Ausmaße des Viewports neu.</summary>
		void CalcSize(); 

		///<summary> Lädt eine Viewportbeschreibung aus einem Vektoria-Viewportfile (.vv).</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name = "id"> Die eigene Viewport-ID.</param>
		void Load(CFileVektoria & filevektoria, int id);

		///<summary> Speichert eine Viewportbeschreibung in ein Vektoria-Viewportfile (.vv).</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name = "bWithID"> Flag, ob die eigene Sprite-ID mit abgespüeichert werden soll.</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

		///<summary> Holt die mit dem Viewport assoziierte Kamera.</summary>
		CCamera * GetCamera(); 

		///<summary> Holt die mit dem Viewport assoziierte Szene.</summary>
		CScene * GetScene(); 

		///<summary> Übersetzt die Koordinaten des Frames in Koordinaten des Viewports, gibt true aus, wenn Cursor innerhalb des Viewports liegt.</summary>
		///<param name="frx">Die fraktionale X-Position (Linke Kante des Viewports = 0, rechte Kante des Viewports = 1.0)</param>
		///<param name="fry">Die fraktionale Y-Position (Obere Kante des Viewports = 0, untere Kante des Viewports = 1.0)</param>
		bool FrameToViewportCoord(float & frx, float & fry);

		// ---------------------
		// Verknüpfungsmethoden:
		// ---------------------

		///<summary> Hängt ein 2D-Overlay-Sprite an den Viewport an.</summary>
		///<param name="poverlay">Pointer auf den anzuhängenden 2D-Overlay-Sprite</param>
		void AddOverlay(COverlay * poverlay); 

		///<summary> Hängt ein vorhandenes 2D-Sprite vom Viewport wieder ab, gibt true aus, wenn's geklappt hat.</summary>
		///<param name="poverlay">Pointer auf den abzuhängenden 2D-Overlay-Sprite</param>
		bool SubOverlay(COverlay * poverlay);

		///<summary> Hängt einen 2D-Hintergrund an den Viewport an.</summary>
		///<param name="pbackground">Pointer auf den anzuhängenden 2D-Hintergrundssprite</param>
		void AddBackground(CBackground * pbackground);

		///<summary> Hängt ein vorhandenes 2D-Background vom Viewport ab, gibt true aus, wenn's geklappt hat.</summary>
		///<param name="pbackground">Pointer auf den abzuhängenden 2D-Hintergrundssprite</param>
		bool SubBackground(CBackground * pbackground);

		///<summary> Hängt ein Writing-Textfeld an den Viewport an.</summary>
		///<param name="pwriting">Pointer auf den anzuhängenden Textfeldsprite</param>
		void AddWriting(CWriting * pwriting);

		///<summary> Hängt ein vorhandenes Writing-Textfeld vom Viewport ab, gibt true aus, wenn's geklappt hat.</summary>
		///<param name="pwriting">Pointer auf den abzuhängenden Textfeldsprite</param>
		bool SubWriting(CWriting * pwriting);

		///<summary> Hängt ein Writing-Buchstabenfeld an den Viewport an.</summary>
		///<param name="pwritingchar">Pointer auf den anzuhängenden Buchstabenfeldsprite</param>
		void AddWritingChar(CWritingChar * pwritingchar);

		///<summary> Hängt ein vorhandenes Writing-Buchstabenfeld vom Viewport ab, gibt true aus, wenn's geklappt hat.</summary>
		///<param name="pwritingchar">Pointer auf den abzuhängenden Buchstabenfeldsprite</param>
		bool SubWritingChar(CWritingChar * pwritingchar);

		// --------------
		// Nebelmethoden:
		// --------------

		///<summary> Schaltet gleichmäßigen Nebel bzw. Dunst an.</summary>
		void SetMistOn();

		///<summary> Schaltet gleichmäßigen Nebel bzw. Dunst aus.</summary>
		void SetMistOff();

		///<summary> Gibt die Dunstfarbe an (Default = weiß).</summary>
		///<param name="color">Dunstfarbe (RGB-Werte zwischen 0 und 1, A-Wert wird ignoriert)</param>
		void SetMistColor(CColor color);

		///<summary> Gibt die Dunststärke an.</summary>
		///<param name="fMistStrength">Dunststärke (Undurchdringlichkeit pro Einheit, z.B. kann man bei 0.2 fünf Einheiten weit sehen) , Default = 0.01</param>
		void SetMistStrength(float fMistStrength);

		// ---------------
		// Schneemethoden:
		// ---------------

		///<summary> Schaltet Schnee an.</summary>
		void SetSnowOn();

		///<summary> Schaltet Schnee aus.</summary>
		void SetSnowOff();

		///<summary> Gibt die Schneestärke an.</summary>
		///<param name="frSnowStrength">Schneestärke (0 = kein Schnee, 1.0 = viel Schnee) , Default = 0.01</param>
		void SetSnowStrength(float frSnowStrength);

		// --------------------
		// Rendering-Methoden:
		// --------------------

		///<summary> Schaltet Backfaceculling an (Default: an).</summary>
		void SetBackfaceCullingOn();

		///<summary> Schaltet Backfaceculling aus (Default: an).</summary>
		void SetBackfaceCullingOff();

		///<summary> Schaltet Antialiasing an (Default: aus). <para></para>
		/// Achtung, nur Antialiasing für GeoLineLists und GeoPointLists, für allgemeines Antialiasing AA-Shader beim initialisieren des Frames anwählen!</summary>
		void SetAntialiasingOn();

		///<summary> Schaltet Antialiasing aus (Default: aus).</summary>
		void SetAntialiasingOff();

		///<summary> Schaltet Drahtgittermodellmodus an (Default: aus).</summary>
		void SetWireframeOff();

		///<summary> Schaltet Drahtgittermodellmodus aus (Default: aus).</summary>
		void SetWireframeOn();

		///<summary> Schaltet Schatten für den Viewport an (Default: an).</summary>
		void SetShadowRenderingOn();

		///<summary> Schaltet Schatten für den Viewport aus (Default: an).</summary>
		void SetShadowRenderingOff();

		///<summary> Schaltet Punktlichter für den Viewport an (Default: an).</summary>
		void SetLightRadialRenderingOn();

		///<summary> Schaltet Punktlichter für den Viewport aus (Default: an).</summary>
		void SetLightRadialRenderingOff();

		///<summary> Schaltet Parallellichter für den Viewport an (Default: an).</summary>
		void SetLightParallelRenderingOn();

		///<summary> Schaltet Parallellichter für den Viewport aus (Default: an).</summary>
		void SetLightParallelRenderingOff();

		///<summary> Schaltet Schweinwerferlichter für den Viewport an (Default: an).</summary>
		void SetLightSpotRenderingOn();

		///<summary> Schaltet Scheinwerferlichter für den Viewport aus (Default: an).</summary>
		void SetLightSpotRenderingOff();

		//---------------
		// Stil-Methoden:
		//---------------

		///<summary> Schaltet auf Pop-Style-Anmutung.</summary>
		void StylePopArt(); 

		///<summary> Schaltet auf Cartoon-Anmutung (hat im Gegensatz zu Toon keine Toon-Steps).</summary>
		void StyleCartoon(); 

		///<summary> Schaltet auf Toon-Anmutung.</summary>
		void StyleToon();

		///<summary> Schaltet die Monochrome-Anmutung an (Bild wird eingefärbt). </summary>
		///<param name="color"> Farbe der Monocrome-Anmutung</param>
		void StyleMonochrome(CColor color); 

		///<summary> Schaltet Sepia-Anmutung an.</summary>
		void StyleSepia(); 

		///<summary> Schaltet Zeichenstift-Anmutung an.</summary>
		void StylePencil();

		///<summary> Schaltet Mal-Anmutung an.</summary>
		void StylePainting();

		///<summary> Schaltet auf PurpleHaze-Anmutung.</summary>
		void StylePurpleHaze(); 

		///<summary> Schaltet BlueDream-Anmutung an.</summary>
		void StyleBlueDream(); 

		///<summary> Schaltet Schwarzweiß-Anmutung an.<para<</para>
		/// Das Bild sieht danach aus, wie aus einem alten Schwarzweiß-Fernseher.</summary>
		void StyleBlackWhite(); 

		///<summary> Schaltet auf Nachtsichtgeräte bzw. Radar-Anmutung.<para<</para>
		/// Das Bild sieht danach aus, wie als ob man durch ein Nachtsichtgerät schauen würde.</summary>
		void StyleRadar();

		///<summary> Schaltet alle Stile bzw. Anmutungen (wie Sepia, Schwarzweiß, etc.) wieder aus.</summary>
		void StyleOff(); 

		//-------------------------------------
		// Postprocessing-Methoden (allgemein):
		//-------------------------------------

		///<summary> Setzt einen Sicherheitsabstand an den Rändern des Viewports für die Postprocessing-Aktionen. <para></para>
		/// Dies verhindert schwarze Ränder oder sonstige Artefakte am Rand!<para></para>
		/// Achtung 1! Zu hohe Werte ergeben Treppenstufen im Bild und verlangsamen die Verarbeitung.<para></para>
		/// Achtung 2! Aus technischen Gründen kann die Anzeige und das Picking von Overlays ungenau werden.</summary>
		///<param name="frPostprocessingBorder"> Rand bezüglich des Viewports: (1.0 = kein Rand ... 1.01 = 1% Rand ... 1.02 = 2% Rand ...) </param>
		void SetPostprocessingBorder(float frPostprocessingBorder);

		///<summary> Gibt true aus, wenn irgendein Postprocessing-Filter angeschaltet ist.</summary>
		bool IsPostprocessingOn();

		//-------------------------------------------
		// Postprocessing-Methoden für den FP-Shader:
		//-------------------------------------------

		///<summary> Setzt eine alternative Postprocessing-Geometrie. <para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer.!</summary>
		void SetPostProcessingGeo(CGeoTriangleList* pgeo); 

		///<summary> Setzt Unschärfefilter mit Radius.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetGaussianBlur(float fRadius); 

		///<summary> Schaltet Unschärfefilter wieder aus.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetGaussianBlurOff();

		///<summary> Schaltet schärfere Kanten und höhere Kontraste mit horizontalen und vertikalen Sobel-Operatoren ein. <para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetEnhancedEdgesOn();

		///<summary> Schaltet schärfere Kanten und höhere Kontraste mit horizontalen und vertikalen Sobel-Operatoren wieder aus. <para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetEnhancedEdgesOff();

		///<summary> Schaltet Filter mit gleichverteilter Unschärfe ein.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetMeanFilterOn();

		///<summary> Schaltet Filter mit gleichverteilter Unschärfe wieder aus.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetMeanFilterOff();

		///<summary> Schaltet FXAA-Filter ein.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetFXAAOn();

		///<summary> Schaltet FXAA-Filter wieder aus.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetFXAAOff();

		///<summary> Schaltet Godrays ein.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetGoodRaysOn();

		///<summary> Schaltet Godrays wieder aus.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetGoodRaysOff();

		///<summary> Schaltet VPLs-Filter ein.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetVPLsOn();

		///<summary> Schaltet VPLs-Filter wieder aus.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void SetVPLsOff();

		///<summary> Setzt Samplingstufe für das Antialiasing.<para></para>
		/// Achtung, funktioniert nur mit entsprechender Grafikkarte, wird ansonsten ignoriert!</summary>
		/// <param name="iSamples"> vernünftige Samplingsstufen: 1, 2 oder 4</param>
		void SetMSAASamples(int iSamples);

		///<summary> Schatten werden nicht neu berechnet.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void FixedLightSpotShadow();

		///<summary> Schatten werden nicht neu berechnet.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void FixedLightRadialShadow();

		///<summary> Schatten werden pro Tick neu berechnet.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void DynamicLightSpotShadow();

		///<summary> Schatten werden pro Tick neu berechnet.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		void DynamicLightRadialShadow();

		///<summary> Auflösung der Punktlichtschatten.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		/// <param name="uShadowRes"> Auflösung des Schattens in Pixel pro Kante</param>
		void SetPointShadowRes(unsigned uShadowRes);

		///<summary> Auflösung der Spotlichtschatten.<para></para>
		/// Achtung, funktioniert bis jetzt nur im FP-Renderer!</summary>
		/// <param name="uShadowRes"> Auflösung des Schattens in Pixel pro Kante</param>
		void SetSpotShadowRes(unsigned uShadowRes);

		///<summary> Setzt die ambiente Lichtfarbe.<para></para>
		/// Achtung, nur im FP-Renderer wichtig!</summary>
		void SetAmbientColor(CColor colorAmbientUp, CColor colorAmbientDown);

		///<summary> Setzt der Parameter für den VPL-Filter.<para></para>
		/// Achtung, nur im FP-Renderer wichtig!</summary>
		void SetNewVPLParams(SVPLParameter* pVplParams);

		///<summary> Setzt der Parameter für die Schatten.<para></para>
		/// Achtung, nur im FP-Renderer wichtig!</summary>
		void SetNewShadowParams(SShadowParameter* pShadowparams);

		///<summary> Setzt der Parameter für den Bloom-Filter.<para></para>
		/// Achtung, nur im FP-Renderer wichtig!</summary>
		void SetNewBloomParams(SBloomParameter* pBloomParams);

		///<summary> Setzt der Parameter für die GodRays. <para></para>
		/// Achtung, nur im FP-Renderer wichtig!</summary>
		void SetNewGodRayParams(SGodRayParameter* pGodRayParams);

		///<summary> Setzt die Entfernungsabnahme des Bloom-Effektes.<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Bloom-Filter. </summary>
		///<param name="frBloomDepthDecay">Abnahe des Bloom-Effektes bezüglich Entfernung (0.0=Keine Entfernungsabnahme(default) ... 1.0=Lichter haben bei der FarClippingPlane keinen Bloom-Effekt mehr!)</param>
		void SetBloomDepthDecay(float frBloomDepthDecay);

		//------------------------------------------------------
		// Postprocessing-Methoden für Farbveränderungs-Effekte:
		//------------------------------------------------------

		///<summary> Schaltet Farbveränderungs-Postprocessing ein.</summary>
		void SetColorModificationOn();

		///<summary> Schaltet Farbveränderungs-Postprocessing wieder aus.</summary>
		void SetColorModificationOff();

		///<summary> Schaltet Farbveränderungs-Postprocessing zurück.</summary>
		void ResetColorModification();

		///<summary> Verändert den Kontrast des Bildes getrennt nach RGB-Werten. </summary>
		///<param name="fr"> Kontrastveränderung: negative Werte vermindern Kontrast, 0 belässt Kontrast, positive Werte erhöhen Kontrast</param>
		void SetContrast(float fr);

		///<summary> Verändert den Kontrast des Bildes getrennt nach RGB-Werten. <para></para>
		/// Mischt diese Farbveränderung mit den vorherigen Farbveränderungen. </summary>
		///<param name="fr"> Kontrastveränderung: negative Werte vermindern Kontrast, 0 belässt Kontrast, positive Werte erhöhen Kontrast</param>
		void SetContrastDelta(float fr);

		///<summary> Verändert den Kontrast des Bildes getrennt nach RGB-Werten. </summary>
		///<param name="color"> Kontrastfarbe der Monocrome-Anmutung  Erhöht Kontrast (Werte>0) bzw. vermindert Kontrast (negative Werte) jeweils getrennt nach RGB-Werten.</summary>
		void SetContrast(CColor color);

		///<summary> Verändert den Kontrast des Bildes getrennt nach RGB-Werten. <para></para>
		/// Mischt diese Farbveränderung mit den vorherigen Farbveränderungen. </summary>
		///<param name="color"> Kontrastfarbe der Monocrome-Anmutung  Erhöht Kontrast (Werte>0) bzw. vermindert Kontrast (negative Werte) jeweils getrennt nach RGB-Werten.</summary>
		void SetContrastDelta(CColor color);

		///<summary> Verändert die Basis-Helligkeit des Bildes. </summary>
		///<param name="fr"> Helligkeitsveränderung: negative Werte setzen Farbgewichting zurück, 0 belässt Helligkeit, größer 0 erhöht Helligkeit, Werte größer 1 erhöhen Helligkeit</param>
		void SetLightness(float fr);

		///<summary> Verändert die Basis-Helligkeit des Bildes. <para></para>
		/// Mischt diese Farbveränderung mit den vorherigen Farbveränderungen. </summary>
		///<param name="fr"> Helligkeitsveränderung: negative Werte setzen Farbgewichting zurück, 0 belässt Helligkeit, größer 0 erhöht Helligkeit, Werte größer 1 erhöhen Helligkeit</param>
		void SetLightnessDelta(float fr);

		///<summary> Verändert die Basis-Helligkeit des Bildes. <para></para>
		/// Tipp: Mit dieser Methode lässt sich das Bild in eine bestimmte Farbe "eintauchen".  </summary>
		///<param name="color"> Helligkeitsveränderung getrennt nach Farbwerten: negative Werte setzen Farbgewichting zurück, 0 belässt Helligkeit, größer 0 erhöht Helligkeit, Werte größer 1 erhöhen Helligkeit</param>
		void SetLightness(CColor color);

		///<summary> Verändert die Basis-Helligkeit des Bildes. <para></para>
		/// Mischt diese Farbveränderung mit den vorherigen Farbveränderungen. <para></para>
		/// Tipp: Mit dieser Methode lässt sich das Bild in eine bestimmte Farbe "eintauchen".  </summary>
		///<param name="color"> Helligkeitsveränderung getrennt nach Farbwerten: negative Werte setzen Farbgewichting zurück, 0 belässt Helligkeit, größer 0 erhöht Helligkeit, Werte größer 1 erhöhen Helligkeit</param>
		void SetLightnessDelta(CColor color);

		///<summary> Verändert die Helligkeit des Bildes (Dunkle Farben bleiben dunkel, helle werden heller). </summary>
		///<param name="fr"> Helligkeitsveränderung: negative Werte invertieren Farbe, Werte zwischen 0 und 1 vermindern Helligkeit, 1 belässt Helligkeit, Werte größer 1 erhöhen Helligkeit</param>
		void SetBrightness(float fr);

		///<summary> Verändert die Helligkeit des Bildes (Dunkle Farben bleiben dunkel, helle werden heller). <para></para>
		/// Mischt diese Farbveränderung mit den vorherigen Farbveränderungen. </summary>
		///<param name="fr"> Helligkeitsveränderung: negative Werte invertieren Farbe, Werte zwischen 0 und 1 vermindern Helligkeit, 1 belässt Helligkeit, Werte größer 1 erhöhen Helligkeit</param>
		void SetBrightnessDelta(float fr);

		///<summary> Verändert die Helligkeit des Bildes, getrennt nach Farbwerten.  </summary>
		///<param name="color"> Erhöht Helligkeit (Werte>1), vermindert Helligkeit (Werte 0..1), invertiert Farbe (negative Werte)  jeweils getrennt nach RGB-Werten.</param>
		void SetBrightness(CColor color);

		///<summary> Verändert die Helligkeit des Bildes, getrennt nach Farbwerten.  <para></para>
		/// Mischt diese Farbveränderung mit den vorherigen Farbveränderungen. </summary>
		///<param name="color"> Erhöht Helligkeit (Werte>1), vermindert Helligkeit (Werte 0..1), invertiert Farbe (negative Werte)  jeweils getrennt nach RGB-Werten.</param>
		void SetBrightnessDelta(CColor color);

		///<summary> Rotiert Farbwerte im Farbkreis.</summary>
		///<param name="faHue"> Drehwinkel im RGB-Farbkreis im Bogenmaß</param>
		void RotateHue(float faHue);

		///<summary> Rotiert Farbwert um den Winkel fa im Bogenmaß weiter.</summary>
		///<param name="faHueDelta"> Drehwinkel im RGB-Farbkreis im Bogenmaß</param>
		void RotateHueDelta(float faHueDelta);

		///<summary> Invertiert alle Farben.</summary>
		void Inverse();

		///<summary> Invertiert alle Farben.</summary>
		void InverseDelta();

		//------------------------------------------
		// Postprocessing-Methoden für Haze-Effekte:
		//------------------------------------------

		///<summary> Schaltet Haze-Postprocessing ein.</summary>
		void SetHazeOn();

		///<summary> Schaltet Haze-Postprocessing wieder aus.</summary>
		void SetHazeOff();

		//-------------------------------------------
		// Postprocessing-Methoden für Bloom-Effekte:
		//-------------------------------------------

		///<summary> Schaltet Bloom-Postprocessing ein.</summary>
		void SetBloomOn();

		///<summary> Schaltet Bloom-Postprocessing wieder aus.</summary>
		void SetBloomOff();

		///<summary> Setzt die Breite des Bloom-Effektes.<para></para>
		/// Funktioniert nur bei angeschalteten Bloom-Postprocessingfilter. <para></para>
		/// Aus technischen Gründen beträgt die maximale Bloom-Breite 19 Pixel entsprechend frBloomStrength gleich 1. </summary>
		///<param name="frBloomWidth">Bloom-Breite (0.0=Kein Bloom ... 1.0=Default(19 PixelBreite), >1 Breiter als 19 Pixel, kann aber aus Ttechnischen Gründne Artefakte hervorrufen) </param>
		void SetBloomWidth(float frBloomWidth);

		///<summary> Setzt die Stärke des Bloom-Effektes an der Near Clipping Plane.<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Bloom-Postprocessingfilter.<para></para>
		/// Aus technischen Gründen beträgt die maximale Bloom-Breite 19 Pixel entsprechend frBloomStrength gleich 1. </summary>
		///<param name="frBloomStrengthNear">Breite des Blooms bei der Near Clipping Plane (0.0f = aus ... 0.5 = 9 Pixel Durchmesser ... 1.0 = aus technischen Gründen 18 Pixel Durchmesser = default).</param>
		void SetBloomStrengthNear(float frBloomStrengthNear);

		///<summary> Setzt die Stärke des Bloom-Effektes an der Far Clipping Plane.<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Bloom-Postprocessingfilter.</summary>
		///<param name="frBloomStrengthFar">Breite des Blooms bei der Far Clipping Plane (0.0f = aus ... 0.5 = 9 Pixel Durchmesser ... 1.0 = aus technischen Gründen 18 Pixel Durchmesser = default).</param>
		void SetBloomStrengthFar(float frBloomStrengthFar);

		//---------------------------------------------------------
		// Postprocessing-Methoden für Blur und Depth Blur-Effekte:
		//---------------------------------------------------------

		///<summary> Schaltet Tiefenunschärfe-Postprocessing ein.</summary>
		void SetDepthBlurOn();

		///<summary> Schaltet Tiefenunschärfe-Postprocessing wieder aus.</summary>
		void SetDepthBlurOff();

		///<summary> Schaltet den Gausschen Unschärfefilter ein.<para></para>
		/// Mit der Methode SetBlurStrength muss danach noch die Unschärfestärke gesetzt werden. </summary>
		void SetBlurOn();

		///<summary> Schaltet den Gausschen Unschärfefilter wieder aus.</summary>
		void SetBlurOff();

		///<summary> Setzt die Stärke des allgemeinen Gausschen Unschärfefilters.<para></para>
		/// Funktioniert nur bei angeschalteten Blur- oder DepthBlur-Postprocessingfilter. <para></para>
		/// Addiert sich bei eingeschaltetem Tiefenunschärfefilter mit der DepthBlurStrength. Daher können auch negative Werte sinmnvoll sein.</summary>
		///<param name="frBlurStrength">Gaussche Unschärfenstärke (1.0=Default, 0.0=keine Unswchärfe)</param>
		void SetBlurStrength(float frBlurStrength);

		///<summary> Setzt die Stärke der Tiefenunschärfe.<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten DepthBlur-Postprocessingfilter. </summary>
		///<param name="frDepthBlurStrength">Tiefenunschärfenstärke (1.0=Default, 0.0=aus 10.0=Zehnfach starke Tiefenunschärfe)</param>
 		void SetDepthBlurStrength(float frDepthBlurStrength);

		///<summary> Setzt den inversen Bereich der Tiefenunschärfe, <para></para>
		/// je höher der Wert desto kleiner ist der logarithmische Bereich, wo scharf gerendert wird.<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Blur- oder DepthBlur-Postprocessingfilter. </summary>
		///<param name="fDepthBlurSharpness">Tiefenunschärfenbereich (1.0=Default, 0.0=aus 10.0=Zehnfach starke Tiefenunschärfe)</param>
		void SetDepthBlurSharpness(float fDepthBlurSharpness);

		//---------------------------------------
		// Postprocessing-Methoden zum Outlining:
		//---------------------------------------

		///<summary> Schaltet Umrandungs-Postprocessing ein.</summary>
		void SetOutliningOn();

		///<summary> Schaltet Umrandungs-Postprocessing wieder aus.</summary>
		void SetOutliningOff();

		///<summary> Setzt die Konturfarbe zur Parametrisierung eines Renderingstiles (Default = Schwarz).</summary>
		///<param name="colorOutline"> Farbe der Umrandung</param>
		void SetOutliningColor(CColor colorOutline);

		///<summary> Setzt die Verdunkelungsstärke der Umrandung.	<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Outlining-Postprocessingfilter. </summary>
		///<param name="fOutliningStrength">Verdunkelungsstärke (0.0=aus ... 1.0=Default ... 10.0=Zehnfach starke Stärke)</param>
		void SetOutliningStrength(float fOutliningStrength);

		///<summary> Setzt den Grenzwert der Farb- bzw. Tiefendifferenz, ab dem umranded wird.	<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Outlining-Postprocessingfilter. </summary>
		///<param name="frOutliningThreshold">Grenzwert (0.0=Nur Farbunterschiede führen zur Umrandung ... 0.5 Die Umrandung wird halb aus Farb- halb aus Tiefeninformationen erzeugt ...1.0=Default nur Tiefeninformationen führen zur Umrandung</param>
		void SetOutliningThreshold(float frOutliningThreshold);

		///<summary> Setzt die Gewichtung zwischen Tiefeninformation und Farbinformation für die Umrandung.	<para></para>
		/// Funktioniert naturgemäß nur bei angeschalteten Outlining-Postprocessingfilter. </summary>
		///<param name="frDepthWeight">Gewicht für die Entfernungsabhängigkeit (0.0=aus ... 1.0=Bei FarClippingPlkane keine Umrandung mehr)</param>
		void SetOutliningDepthWeight(float frDepthWeight);

		//------------------------------------------
		// Postprocessing-Methoden für Toon-Effekte:
		//------------------------------------------

		///<summary> Schaltet ToonSteps-Postprocessing-Filter ein und gibt gleich die Anzahl der ToonSteps an.</summary>
		///<param name="iToonSteps">Anzahl der ToonSteps</param>
		void SetToonSteps(int iToonSteps);

		///<summary> Schaltet ToonSteps-Postprocessing-Filter wieder aus.</summary>
		void SetToonStepsOff();

		// ================
		// Membervariablen:
		// ================

		// ---------------------------------------
		// Container für angehängte Knotenobjekte:
		// ---------------------------------------

		///<summary> Container für die an das Viewport angehängten Overlays.</summary>
		COverlays m_overlays;

		///<summary> Container für die an das Viewport angehängten Backgrounds.</summary>
		CBackgrounds m_backgrounds;

		///<summary> Container für die an das Viewport angehängten Writings.</summary>
		CWritings m_writings;

		// ---------------------------------------------------------------------
		// Zeiger auf Knotenobjekte, mit denen der Viewport in Verbindung steht:
		// ---------------------------------------------------------------------

		///<summary> Zeiger auf die Kamera, welche das Viewport anzeigt.</summary>
		CCamera * m_pcamera;

		///<summary> Zeiger auf das Frame, welches dem Viewport übergeordnet ist.</summary>
		CFrame * m_pframe;

		// -----------------------------------------------------------------------
		// Absolute Pixelparameter des Viewports relativ zum übergeordneten Frame:
		// -----------------------------------------------------------------------

		///<summary> X-Position der linken oberen Ecke in Pixel.</summary>
		int m_ix;

		///<summary> Y-Position der linken oberen Ecke in Pixel.</summary>
		int m_iy;

		///<summary> Breite des Viewports in Pixel.</summary>
		int m_iWidth;

		///<summary> Höhe des Viewports in Pixel.</summary>
		int m_iHeight;

		// -----------------------------------------------------------------------
		// relative Pixelparameter des Viewports relativ zum übergeordneten Frame:
		// -----------------------------------------------------------------------

		///<summary> X-Position der linken Viewportkante in fraktionalen Werten bezüglich des übergeordneten Frames (0.0 = linke Kante des Frames ... 1.0 = linke Kante des Frames). </summary>
		float m_frx;

		///<summary> Y-Position der oberen Viewportkante in fraktionalen Werten bezüglich des übergeordneten Frames (0.0 = obere Kante des Frames ... 1.0 = untere Kante des Frames). </summary>
		float m_fry;

		///<summary> Breite des Viewports in fraktionalen Werten bezüglich des übergeordneten Frames (0.0 = keine Breite ... 1.0 = Volle Framebreite). </summary>
		float m_frWidth;

		///<summary> Höhe des Viewports in fraktionalen Werten bezüglich des übergeordneten Frames (0.0 = keine Höhe ... 1.0 = Volle Framehöhe). </summary>
		float m_frHeight;

		// --------------------------------------
		// Parameter für das Verteilte Rendering: 
		// --------------------------------------

		///<summary> Eventueller Hostname der übergeordneten Hardware (aus Performanzgründen redundant zu anderen Klassen wie CFrame und CHardware).</summary>
		char m_acHost[100];

		///<summary> Eventuelle IP-Adresse der übergeordneten Hardware (aus Performanzgründen redundant zu anderen Klassen wie CFrame und CHardware).</summary>
		char m_acIPAddress[100];

		// -------------
		// Anzeigeflags:
		// -------------

		///<summary> Flag, ob Backfaceculling angeschaltet ist.</summary>
		bool m_bBackfaceCulling;

		///<summary> Flag, ob Antialiasing (Kantenglättung) angeschaltet ist. Funktioniert nur bei kantenglättungsfähigen Grafikkarten.</summary>
		bool m_bAntialiasing;

		///<summary> Flag, ob Drahtgittermodellmodus angeschaltet ist.</summary>
		bool m_bWireframe;

		///<summary> Flag, ob Parallellichter anzezeigt werden sollen. (Achtung, sie werden trotzdem berechnet!)</summary>
		bool m_bLightParallelRendering;

		///<summary> Flag, ob Scheinwerferlichter anzezeigt werden sollen. (Achtung, sie werden trotzdem berechnet!)</summary>
		bool m_bLightSpotRendering;

		///<summary> Flag, ob Punktlichter anzezeigt werden sollen. (Achtung, sie werden trotzdem berechnet!)</summary>
		bool m_bLightRadialRendering;

		///<summary> Flag, ob Schatten berechnet soll. </summary>
		bool m_bShadowRendering;

		///<summary> Flag, ob Schatten angezeigt werden.</summary>
		bool m_bShadowsEnabled;

		///<summary> Flag, ob Antialiasing angezeigt wird.</summary>
		bool m_bMSAAEnabled;

		///<summary> Anzahl, wieviel Antialiasingstufen.</summary>
		int m_iMSAASamples;

		// --------------
		// Nebelparmeter:
		// --------------

		///<summary> Flag, ob Nebelberechnung.</summary>
		bool m_bMist;

		///<summary> Inverse Nebelstärke.</summary>
		float m_fMistStrengthInv;

		///<summary> NebelFarbe.</summary>
		CColor m_colorMist;

		// ---------------
		// Schneeparmeter:
		// ---------------

		///<summary> Flag, ob Schneberechnung.</summary>
		bool m_bSnow;

		///<summary> Schneestärke.</summary>
		float m_frSnowStrength;

		// ------------------------
		// Weitere Membervariablen:
		// ------------------------

		///<summary> Seitenverhältnis des Viewports (Breite durch Höhe).</summary>
		float m_fAspectRatio;

		///<summary> Flag, ob die Methode Init schon aufgerufen wurde.</summary>
		bool m_bInit;

		///<summary> Hilfsabzählnummer für das Loading und Saving (für Anwender uninteressant).</summary>
		int m_i;

		///<summary> Zeiger auf die Wurzel.</summary>
		CRoot * m_proot;

		///<summary> Pointer auf Geometrie für eventuelles Postporocessing.</summary>
		CGeoTriangleList* m_pzgPostprocessing;  

		///<summary> Flag, welches true ist, bis Postprocessing zum ertsen Mal ausgeführt wurde.</summary>
		bool m_bFirstDrawPostprocessing;

		///<summary> Pointer auf Geometrie für eventuelles Postporocessing.</summary>
		CGeoTriangleList* m_pzgDepth;

		// -------------------------
		// Postprocessing-Parameter:
		// -------------------------

		///<summary> Flag, ob Postprocessing benötigt wird.</summary>
		bool m_bPostprocessing;

		///<summary> Flag, welches true ist, bis Postprocessing zum ertsen Mal ausgeführt wurde.</summary>
		bool m_bFirstDrawDepth;

		///<summary> Sicherheitsrand für Postprocessing.</summary>
		float m_frPostprocessingBorder;

		///<summary> Flag, ob der Farbmodifikations-Postprocessingfilter angeschaltet ist.</summary>
		bool m_bColorModification;

		///<summary> Flag, ob Outlining-Postprocessingfilter angeschaltet ist.</summary>
		bool m_bOutlining;

		///<summary> Stärke des Umrandung.</summary>
		float m_fOutliningStrength;

		///<summary> Grenzwert, ab wann Outlining angewandt werden soll.</summary>
		float m_frOutliningThreshold;

		///<summary> Gewichtung zwischwen Tiefeninformation und Farbinformation beim Outlining (0.0 = Nur Tiefeninfo ... 0.5 = halb Tiefeninfo, halb Farbinfo ... 1.0 = nur Farbinfo)</summary>
		float m_frOutliningDepthWeight;

		///<summary> Farbe für das Outline.</summary>
		CColor m_colorOutline;

		///<summary> Flag, ob Bloom-Postprocessingfilter angeschaltet ist.</summary>
		bool m_bBloom;

		///<summary> Abnahme des Blooms bei fernen Lichtern(0.0f = keine Abnahme ... 1.0 = Lichter haben bei der FarClippingPlane keinen Bloom mehr) .</summary>
		float m_frBloomDepthDecay;

		///<summary> Stärke des Blooms bei der Near Clipping Plane (0.0f = aus ... 1.0 = Normalstärke, Default).</summary>
		float m_frBloomStrengthNear;

		///<summary> Stärke des Blooms bei der Far Clipping Plane (0.0f = aus ... 1.0 = Normalstärke, Default).</summary>
		float m_frBloomStrengthFar;

		///<summary> Stärke des Blooms (0.0f = aus ... 0.5 = 9 Pixel Durchmesser ... 1.0 = aus technischen Gründen 18 Pixel Durchmesser = default).</summary>
		float m_frBloomWidth;

		///<summary> Flag, ob Kamera-Tiefenunschärfe-Postprocessingfilter angeschaltet ist.</summary>
		bool m_bDepthBlur;

		///<summary> Stärke der Tiefenunschärfe.</summary>
		float m_frDepthBlurStrength;

		///<summary> Inverser Abstand des Bereiches, in dem die Kamera bei angeschalteter Tiefenunschärfe scharf abbildet.</summary>
		float m_fDepthBlurSharpness;

		///<summary> Flag, ob Gaussche Unschärfe-Postprocessingfilter angeschaltet ist.</summary>
		bool m_bBlur;

		///<summary> Stärke der allgemeinen Gausschen Unschärfe.</summary>
		float m_frBlurStrength;

		///<summary> Flag, ob GodRays-Postprocessingfilter angeschaltet ist (nur für den FP-Renderer).</summary>
		bool m_bGodRays;

		///<summary> Flag, ob Haze-Postprocessingfilter angeschaltet ist.</summary>
		bool m_bHaze;

		///<summary> Zeit in Sekunden, die seit Start des Progarmmes vergangen ist.</summary>
		float m_fTime;

		///<summary> Anzahl der Toon-Steps.</summary>
		int m_iToonSteps;

		///<summary> Homogene Farbmodifikationsmatrix.</summary>
		CHMat m_mColorModification;


		// ------------------------------
		// Parameter für den FP-Renderer:
		// ------------------------------

		///<summary> AmbientLight Farbe nach oben, kann Parallellicht von oben simulieren, welches es im FP-Renderer nicht gibt (Parameter für FP-Renderer). </summary>
		CColor m_colorAmbientUp;

		///<summary> AmbientLight Farbe nach unten, kann AmbientLight bei Parallellicht von oben simulieren, welches es im FP-Renderer nicht gibt (Parameter für FP-Renderer). </summary>
		CColor m_colorAmbientDown;

		///<summary> Dof-Parameter für den FP-Renderer.</summary>
		CHVector m_vDofParams;

		///<summary> Vpl-Parameter für den FP-Renderer.</summary>
		SVPLParameter m_vplParams;

		///<summary> Schatten-Parameter für den FP-Renderer.</summary>
		SShadowParameter m_shadowParams;

		///<summary> Bloom-Parameter für den FP-Renderer.</summary>
		SBloomParameter m_bloomParams;

		///<summary> GodRay-Parameter für den FP-Renderer.</summary>
		SGodRayParameter m_godRayParams;

		///<summary> Flag für den FP-Renderer, ob Scheinwerferlichter still stehen.</summary>
		bool m_bFixedSpotShadows;

		///<summary> Flag für den FP-Renderer, ob Punktlichter still stehen.</summary>
		bool m_bFixedPointShadows;

		///<summary> Auflösung der Shadowmap bei Schweinwerferlichtern (nur für den FP-Renderer).</summary>
		unsigned m_uSpotShadowRes;

		///<summary> Auflösung der Shadowmap bei Punktlichtern (nur für den FP-Renderer).</summary>
		unsigned m_uPointShadowRes;

		///<summary> Flag, ob VPLS berechnet werden.</summary>
		bool m_bVPLSEnabled;

		///<summary> Tiefe der Kantenschäfung (nur für den FP-Renderer).</summary>
		unsigned int m_uiPP_EnhancedEdges;

		///<summary> Tiefe den Gausschan Filter (nur für den FP-Renderer).</summary>
		unsigned int m_uiPP_MeanFilter;

		///<summary> Tiefe der Antialiasings (nur für den FP-Renderer).</summary>
		unsigned int m_uiPP_FXAA;

		///<summary> Flag, ob DoF angeschaltet ist (nur für den FP-Renderer).</summary>
		bool m_bDoF;

		///<summary> Flag, ob der Gausscher Blur-Filter angeschaltet ist (nur für den FP-Renderer).</summary>
		unsigned int m_uiPP_GaussianBlur;

		///<summary> Radius des Gausscher Blur-Filters (nur für den FP-Renderer).</summary>
		float m_fGaussianBlurRadius;

	protected:

		///<summary> Interne ID der Kamera.</summary>
		int m_idCamera;

		///<summary> True, falls der erste Tick.</summary>
		bool m_bFirstTick;

	};

}