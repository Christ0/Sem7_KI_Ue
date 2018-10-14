#pragma once
#include "Node.h"
#include "Textures.h"
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Color.h"

//---------------------------------------------------
// CMaterial: Klasse für Materialien
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2016-02-01
//---------------------------------------------------

//  0 = Diffuse,		 4 = Glow,			 8 = Specular,			12 = Bump
// 16 = DiffuseBlack,	20 = GlowAsDiffuse,	24 = SpecularAsDiffuse,	28 = HeightAsImage
// 32 = DiffuseWhite,	36 = GlowWhite,		40 = SpecularWhite,		44 = Height
// 48 = ShadingOff,		52 = Environment,	56 = POM


#define TEXFLAG_NODIFFUSE 0
#define TEXFLAG_DIFFUSE 1
#define TEXFLAG_DIFFUSEBLACK 2
#define TEXFLAG_DIFFUSEWHITE 3
#define TEXFLAG_DIFFUSEPURE 4

#define TEXFLAG_NOGLOW 0
#define TEXFLAG_GLOW 1
#define TEXFLAG_GLOWASDIFFUSE 2
#define TEXFLAG_GLOWWHITE 3

#define TEXFLAG_NOSPECULAR 0
#define TEXFLAG_SPECULAR 1
#define TEXFLAG_SPECULARASDIFFUSE 2
#define TEXFLAG_SPECULARWHITE 3

#define TEXFLAG_NOBUMP 0
#define TEXFLAG_BUMP 1
#define TEXFLAG_HEIGHTASDIFFUSE 2
#define TEXFLAG_HEIGHT 3

#define TEXFLAG_NOENVIRONMENTAL 0
#define TEXFLAG_ENVIRONMENTAL_SPHERICAL 1
#define TEXFLAG_ENVIRONMENTAL_CUBIC 2

#define TEXFLAG_POSTPROCESSING_OFF 0
#define TEXFLAG_POSTPROCESSING_ON 1
#define TEXFLAG_POSTPROCESSING_ON_WITH_HAZE 2

#define TEXFLAG_NOPOM 0
#define TEXFLAG_POM	  1

#define TEXFLAG_NOTHICKNESS 0
#define TEXFLAG_THICKNESS	1

#define TEXFLAG_NOREFLECTIONMAP 0
#define TEXFLAG_REFLECTIONMAP 1


namespace Vektoria
{
	enum ETextureAddressMode
	{
		eTextureAdressMode_Wrap = 0,
		eTextureAdressMode_Mirror,
		eTextureAdressMode_Clamp
	};

	enum ETransparencyKind
	{
		eTransparencyKind_No = 0,
		eTransparencyKind_BinaryByAlphaTest,
		eTransparencyKind_BinaryByChromaKey,
		eTransparencyKind_Continual,
		eTransparencyKind_Complete
	};


	class CGeos;
	class CFrames;
	class CEmitters;

	class CMaterial : public CNode
	{
		friend class CMaterials;
		friend class CGeo;
		friend class CSprite;
	private:
		///<summary> Wird indirekt von CRoot aufgerufen, frames sind dabei ALLE geaddeten Frames, auf diesem wie auf allen Remote-Computern.</summary>
		void Tick(float & fTimeDelta, CFrames & frames);  

		///<summary> Setzt die Ahnenszenen (Hilfsroutine für Verknüfungsmethoden).</summary>
		void SetScene(CScene * pscene);

	public:
		///<summary> Konstruktor.</summary>
		CMaterial();

		///<summary> Destruktor.</summary>
		~CMaterial();

		///<summary> Kopiermethode.</summary>
		///<param name = "material"> Zu kopierendes Material.</param>
		CMaterial operator=(CMaterial & material);

		///<summary> Kopieroperator.</summary>
		///<param name = "material"> Zu kopierendes Material.</param>
		void Copy(CMaterial & material);

		///<summary> Initialisierungsroutine zum Reset aller Werte, bei der Initialisierung.<para></para>
		///Normalerweise nicht notwendig, da Werte schon im Konstruktor auf Grundwerte gesetzt werden.</summary>
		void Init(); 

		///<summary> Abschlussroutine, nicht unbedingt notwendig.</summary> 
		void Fini();

		//----------------------------
		// Lade- und Speichermethoden:
		//----------------------------

		///<summary> Lädt vorgefertigtes Material über ein Skriptfile mit dem Namen acName mit allen Parametern, Texturen, etc. aus der Materialbibliothek,<para></para> 
		///diese befindet sich in Lib/Materials.</summary>
		///<param name = "acName"> Name des vorgefertigten Materials, z.B.:<para></para>
		///"Blood","BricksClincker","BricksClinckerColored","CobblestoneMarble","Concrete","CounterDigital","EarthCracked","EggshellBrown","Equalizer","LeatherBlack","MetalChromeCircuit","MetalRustyFlaking","MirrorPure","PanoPlate","Perl","Quicksilver","RockMossy","RubberBlack","Suede","TilesDirty","TilesMarbleWhite","Vanish","Water","WindowGothicStained","WoodPlanks","WoodPlanksBankirai"   </param>
		bool LoadPreset(char * acName);

		///<summary> Speichert das erstellte Material in ein Skriptfile mit dem Namen acName.vem an die richtige Stelle in der Materialbiliothek.<para></para>
		///Die diesbezüglichen Texturen sollten schon am richtigen Platz liegen.</summary> 
		///<param name = "acName"> Name des vorgefertigten Materials</param>
		bool SavePreset(char * acName);

		///<summary> Lädt ein Material aus einer Vektoria-Materialdatei (.vm).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Materialdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyMaterial.vm" oder ".\\Materials\\MyMaterial.vm" </param>
		bool Load(char * acPath);

		///<summary> Speichert das Material in eine Material-Vektoriadatei (.vm).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>		
		///<param name="acPath">ASCII-Pfadangabe der Materialdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyMaterial.vm" oder ".\\Materials\\MyMaterial.vm" </param>
		bool Save(char * acPath);

	protected:

		///<summary> Lädt eine komplette Materialbeschreibung aus einem Vektoria-Materialdatei (.vm).</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Materials innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
		///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
		void Load(CFileVektoria & filevektoria, int id = -1, float fVersion = 14.11f);

		///<summary> Speichert eine komplette Materialbeschreibung in ein Vektoria-Materialdatei (.vm).</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name = "bWithID"> Flag, ob die eigene Material-ID mit abgespeichert werden soll.</param>
		///<param name = "bCalcConverging"> Flag, ob die Berechnung konvergierender Hierarchien durchgeführt werden soll.</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false, bool bCalcConverging = true);

	public:

		//---------------------
		// Verknüfungsmethoden:
		//---------------------

		///<summary> Hängt einen Emitter an das vorliegende Material an.</summary>
		///<param name="pemitter">Zeiger auf den anzuhängenden Emitter</param>
		void AddEmitter(CEmitter * pemitter);

		///<summary> Hängt den Emitter wieder von dem vorliegenden Material ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pemitter">Zeiger auf den abzuhängenden Emitter</param>
		bool SubEmitter(CEmitter * pemitter);

		///<summary> Hängt eine Textur an, die für Skymaps, Skydomes etc. geeignet ist (Siehe auch -> MakeTextureSky).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureSky(CTexture *ptexture);

		///<summary> Hängt eine diffuse Textur an (Siehe auch -> MakeTextureDiffuse).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureDiffuse(CTexture *ptexture);

		///<summary> Hängt eine Glow-Textur an (Siehe auch -> MakeTextureGlow),</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureGlow(CTexture *ptexture);

		///<summary> Hängt eine spekulare Textur an (Siehe auch -> MakeTextureSpecular).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureSpecular(CTexture *ptexture);

		///<summary> Hängt eine Normal-Map-Textur an (Siehe auch -> MakeTextureBump).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureBump(CTexture *ptexture);

		///<summary> Hängt eine POM-Textur an (Siehe auch -> MakeTextureHeight).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureHeight(CTexture *ptexture);

		///<summary> Hängt eine Haze-Textur an (Siehe auch -> MakeTextureHaze).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureHaze(CTexture *ptexture);

		///<summary> Hängt eine Environment-Textur an (Siehe auch -> MakeTextureEnvironment).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		///<param name = "bCubic">Flag, ob es sich um eine kubische (nach Vektoria) oder sphärische Textur handelt</param>
		void SetTextureEnvironment(CTexture *ptexture, bool bCubic);

		///<summary> Hängt eine Dicken-Textur an (Siehe auch -> MakeTextureThickness).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureThickness(CTexture* ptexture);

		///<summary> Hängt eine Textur an, die für Sprites wie Backgrounds, Overlays, Writings und WritingChars geeignet ist  .(Siehe auch -> MakeTextureSprite).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureSprite(CTexture *ptexture);

		///<summary> Hängt eine Textur an, die für Billboards und Wribels geeignet ist.(Siehe auch -> MakeTextureSprite).</summary>
		///<param name = "ptexture">Zeiger auf die anzuhängende Textur</param>
		void SetTextureBillboard(CTexture *ptexture);

		///<summary> Erzeugt eine Texturhierarchie für eine Farb-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureDiffuse(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie für eine Glow-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureGlow(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie für eine Spacular-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureSpecular(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie für eine Dot3-Normal-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureBump(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie für Parallax Occlusion Map-Hierarchie mit Heightmap.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureHeight(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie für Haze-Effekte mit Heightmap.<para></para>
		///<summary> Achtung! Der Haze-Filter im Viewoport muss naturgemäß eingeschaltet sein, damit diese Textur einen Effekt hat. <para></ para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureHaze(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie für Environmental-Map-Hierarchie für Reflektion und Refraktion.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		///<param name = "bIsCubicMap"> Wenn bCubicMap false ist, wird bei der Environmental Map sphärisches Mapping verwendet (default), ansonsten kubisches Mapping (nach Vektoria).</param>
		CImage * MakeTextureEnvironment(char * acPath, bool bIsCubicMap = false);

		///<summary> Erzeugt eine Texturhierarchie, die für Skymaps, Skydomes etc. geeignet ist.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureSky(char * acPath);

		///<summary> Materialdickebeschreibung für Subsurfacescattering und Farbe des Subsurfaces.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureThickness(char * acPath, CColor colorSSS);

		///<summary> Erzeugt eine Texturhierarchie, die für Billboards und Wribels geeignet ist.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureBillboard(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie, die für Sprites wie Backgrounds, Overlays, Writings und WritingChars geeignet ist.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zurück.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureSprite(char * acPath);

		///<summary> Erzeugt ein animiertes Material.</summary> 
		///<param name = "ixPics">Anzahl der Unterbilder in X-Richtung</param>
		///<param name = "iyPics">Anzahl der Unterbilder in Y-Richtung</param>
		///<param name = "fFps">Bildwiederholrate in Frames per Second bzw. Bilder pro Hertz</param>
		void SetAni(int ixPics, int iyPics, float fFps);

		///<summary> Erzeugt ein steuerbares Bot-Material.</summary> 
		///<param name = "ixPics">Anzahl der Unterbilder in X-Richtung</param>
		///<param name = "iyPics">Anzahl der Unterbilder in Y-Richtung</param>
		void SetBot(int ixPics, int iyPics); 

		///<summary> Setzt das Unterbild eines steuerbaren Bot-Materials (siehe auch Methode SetBot!).</summary> 
		///<param name = "ixPic">Gewähltes Unterbild in X-Richtung</param>
		///<param name = "iyPic">Gewähltes Unterbild in Y-Richtung</param>
		void SetPic(int ixPic, int iyPic); 

		///<summary> Schaltet das Shading an (default).</summary>
		void SetShadingOn(); 

		///<summary> Schaltet das Shading aus.</summary>
		void SetShadingOff(); 

		///<summary> Setzt die unbeleuchtete Seite auf Weiß.</summary>
		void SetTextureGlowWhite(); 

		///<summary> Setzt die unbeleuchtete Seite auf komplett schwarz.</summary>
		void SetTextureGlowBlack();  

		///<summary> Setzt den internen Texturpointer für die unbeleuchtete Seite auf die diffuse Textur.<para></para> 
		/// (spart Speicherplatz im Texturspeicher der Graka)</summary>
		void SetTextureGlowAsDiffuse();  
		
		///<summary> Lässt die Glow-Textur auch auf der beleuchteten Seite leuchten und ignoriert die Diffuse-Textur.<para></para> 
		/// Damit lassen sich beispielsweise Sonnen, Feuerbälle, etc. herstellen.</summary>  
		void SetGlowEverywhere();

		///<summary> Setzt Glanzlicht überall auf volle Stärke (siehe auch Methode MakeTextureSpecular).</summary>
		void SetTextureSpecularWhite(); 

		///<summary> Schaltet Glanzlicht komplett aus (siehe auch Methode MakeTextureSpecular).<para></para>
		/// (spart Speicherplatz im Texturspeicher der Graka)</summary>
		void SetTextureSpecularBlack();

		///<summary> Setzt den internen Glanzlichttexturpointer auf die diffuse Textur.</summary>
		void SetTextureSpecularAsDiffuse(); 

		///<summary> Schaltet das Postprocessing für diese Textur aus (default = an).</summary> 
		void SetPostprocessingOff(); 

		///<summary> Schaltet das Postprocessing für diese Textur an (default).</summary> 
		void SetPostprocessingOn();

		///<summary> Setzt Alphakanal der Environmentmap als Reflectionmap (veraltet).<para></para> 
		/// ACHTUNG!!! Nur der Aufwärtskompatibilität halber drin, wird es ab V16 nicht mehr geben!</summary>
		void SetReflectionMap();
		
		///<summary> Setzt den Brechungsindex.</summary>
		///<param name = "fRectractionRatio">Brechungsindex (nur Werte zwischen -1 und 1 sind sinnvoll)< para></para>
		/// Wichtige Werte:  <para></para>
		/// Luft zu Wasser = 0,752 <para></para>
		/// Luft zu Eis = 0,76 <para></para>
		/// Luft zu Fensterglas = 0.657 <para></para>
		/// Luft zu Diamant = 0.413</param>
		void SetRefractionRatio(float fRectractionRatio);

		///<summary> Setzt den Fresnel-Faktor.</summary> 
		///<param name = "frFresnel">Fresnel-Faktor (nur Werte zwischen 0.0 und 1.0 sind sinnvoll)< para></para>
		/// frFresnel =     0.0: keine Fresnelberechnung (=default)<para></para> 
		/// frFresnel =     1.0: volles Rohr<para></para> 
		/// frFresnel = ca. 0.9: Wasser, Glas, etc.<para></para> 
		/// frFresnel = ca. 0.7: normale Materialien </param>
		void SetFresnel(float frFresnel); 

//		void SetBrightness(float fr); // Erhöht Helligkeit (Werte>1), vermindert Helligkeit (Werte 0..1) bzw. invertiert Farbe (Wert<0) 
//		void SetBrightness(CColor c); // Erhöht Helligkeit (Werte>1), vermindert helligkeit (Werte 0..1) bzw. invertiert Farbe (Wert<0) jeweils getrennt nach RGB-Werten 

		// ------------------
		// Farbveränderungen: 
		// ------------------

		///<summary> Skaliert Farbveränderungsmatrix zur Helligkeitsveränderung der diffusen Textur.</summary>
		///<param name = "fr">Skalierungsfaktor<para></para>
		/// fr größer 1: Erhöht Helligkeit<para></para> 
		/// fr gleich 1: Belässt Helligkeit (sinnlos)<para></para> 
		/// fr zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// fr gleich 0: löscht Bildausgabe (sinnlos)<para></para> 
		/// fr kleiner 0: Invertiert Farbe</param>  
		void Scale(float fr); 

		///<summary> Skaliert Farbveränderungsmatrix zur Helligkeitsveränderung der diffusen Textur, belässt vorherige Farbwertveränderungen.</summary> 
		///<param name = "fr">Skalierungsfaktor<para></para>
		/// fr größer 1: Erhöht Helligkeit<para></para> 
		/// fr gleich 1: Belässt Helligkeit (sinnlos)<para></para> 
		/// fr zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// fr gleich 0: löscht Bildausgabe (sinnlos)<para></para> 
		/// fr kleiner 0: Invertiert Farbe</param>  
		void ScaleDelta(float fr);

		///<summary> Skaliert Farbveränderungsmatrix zur Helligkeitsveränderung der diffusen Textur jeweils getrennt zu R,G und B.</summary> 
		///<param name = "c">Skalierungsfaktoren für Rot, Grün und Blau<para></para>
		/// Werte größer 1: Erhöht Helligkeit<para></para> 
		/// Werte gleich 1: Belässt Helligkeit (sinnlos)<para></para> 
		/// Werte zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// Werte gleich 0: löscht Bildausgabe (sinnlos)<para></para> 
		/// Werte kleiner 0: Invertiert Farbe</param>  
		void Scale(CColor c);

		///<summary> Skaliert Farbveränderungsmatrix zur Helligkeitsveränderung der diffusen Textur jeweils getrennt zu R,G und B, belässt vorherige Farbwertveränderungen.</summary>  
		///<param name = "c">Skalierungsfaktoren für Rot, Grün und Blau<para></para>
		/// Werte größer 1: Erhöht Helligkeit<para></para> 
		/// Werte gleich 1: Belässt Helligkeit (sinnlos)<para></para> 
		/// Werte zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// Werte gleich 0: löscht Bildausgabe (sinnlos)<para></para> 
		/// Werte kleiner 0: Invertiert Farbe</param>  
		void ScaleDelta(CColor c);

		///<summary> Setzt Farbwertzusammensetzung der Textur auf Farbe c als Mittelwert.</summary>   
		///<param name = "c">Farbwerte für Rot, Grün und Blau<para></para> 
		/// Werte größer 0: Farbwert wird erhöht <para></para> 
		/// Werte gleich 0: Farbwert bleibt <para></para> 
		/// Werte kleiner 0: Farbwert wird vermindert </param> 
		void Translate(CColor c);

		///<summary> Setzt Farbwertzusammensetzung der Textur, belässt vorherige Werte.</summary>   
		///<param name = "c">Farbwerte für Rot, Grün und Blau<para></para> 
		/// Werte größer 0: Farbwert wird erhöht <para></para> 
		/// Werte gleich 0: Farbwert bleibt <para></para> 
		/// Werte kleiner 0: Farbwert wird vermindert </param> 
		void TranslateDelta(CColor c);

		///<summary> Rotiert die Farbwerte (Hue) (R->G->B->).</summary> 
		///<param name = "fa">Rotationswinkel im Bogenmaß</param> 
		void RotateHue(float fa);

		///<summary> Rotiert die Farbwerte weiter (Hue) (R->G->B->).</summary>  
		///<param name = "fa">Rotationswinkel im Bogenmaß</param> 
		void RotateHueDelta(float fa);

		///<summary> Setzt die Colorshift-Matrix.</summary> 
		///<param name = "mColor">Colorshift-Matrix</param> 
		void SetMat(CHMat mColor);

		// --------------------------
		// Allgemeine Setzfunktionen:
		// --------------------------

		///<summary> Setzt die Stärke der Bumpmap (Dot3-Normal Map).</summary> 
		///<param name = "fBumpStrength">Stärke der Bumpmap, Default = 1.0f, auch negative Werte sind erlaubt</param> 
		void SetBumpStrength(float fBumpStrength);

		///<summary> Setzt die Stärke der Heightmap (Parallax Occlution Map).</summary>    
		///<param name = "fHeightStrength">Stärke der Heightmap, Default = 1.0f, auch negative Werte sind erlaubt, führen aber dann nicht zum besten Ergebnis</param> 
		void SetHeightStrength(float fHeightStrength);

		///<summary> Setzt die Stärke des Glowmap (Leucht-Map).</summary>    
		///<param name = "fGlowStrength">Stärke des Glows <para></para> 
		/// - Default = 1.0f.<para></para>
		/// - Über 1 gibt es einen Bloom-Effekt, falls Bloom-Filtger im Viewport angeschaltet ist.<para></para>
		/// - Auch negative Werte sind erlaubt und ergeben satanische "schwarze Lichter", die der Umgebung Licht rauben.</param> 
		void SetGlowStrength(float fGlowStrength);

		///<summary> Setzt die Stärke des Glanzlichtes.</summary>    
		///<param name = "fSpecularStrength">Stärke des Glanzlichtes <para></para> 
		/// - Default = 1.0f.<para></para>
		/// - Über 1 gibt es einen Bloom-Effekt, falls Bloom-Filtger im Viewport angeschaltet istq.<para></para>
		/// - Auch negative Werte sind erlaubt und ergeben satanische "schwarze Glanzlichter", wie von einer Schwarzen Sonne, die der Umgebung Licht rauben.</param> 
		void SetSpecularStrength(float fSpecularStrength);

		///<summary> Setzt die Schärfe des Glanzlichtes.</summary> 
		///<param name = "fSpecularStrength">Glanzlicht-Schärfe, je höher, desto kleiner und akzentuierter ist das Highlight (default = 25)</param>
		void SetSpecularSharpness(float fSpecularSharpness);

		///<summary> Setzt die Schärfe zwischen diffuser und ambienter Seite.</summary> 
		///<param name = "fDiffuseSharpness">Schärfe zwischen Diffuser und Nachtseite, je höher, desto kleiner und akzentuierter ist der Übergang</param>
		void SetDiffuseSharpness(float fDiffuseSharpness);

		///<summary> Setzt die Schärfe zwischen Glow- und nicht-Glow-Bereich (default = 1).</summary> 
		///<param name = "fGlowSharpness">Schärfe zwischen Glow und Nicht-Glow-Bereich, je höher, desto kleiner und akzentuierter ist der Übergang</param> 
		void SetGlowSharpness(float fGlowSharpness);

		///<summary> Setzt die Haze-Stärke.<para></para> 
		/// Wirkt sich nur aus, wenn A.) zusätzlich SetHazeOn() aufgerufen wird und B.= im Viewport der Haze-Postprocessing-Filter mit SetHazeOn() angeschaltet ist.</summary> 
		///<param name = "fHazeStrength">Haze-Stärke, je höher, desto mehr wird das Bild verschoben (default = 1)</param> 
		void SetHazeStrength(float fHazeStrength);

		///<summary> Schaltet Haze an und damit auch notwendigerweise das Postprocessing an.</summary> 
		void SetHazeOn();

		///<summary> Setzt die Durchsichtigkeit.</summary>  
		///<param name = "frTransparancy">Durchsichtigkeit <para></para> 
		/// - frTransparency gleich 0: undurchsichtig,opak<para></para>
		/// - frTransparency zwischen 0 und 1: Teildurchsichtig<para></para>
		/// - frTransparency gleich 1: komplett durchsichtig (meist sinnlos)</param>
		void SetTransparency(float frTransparancy); 

		///<summary> Setzt die Durchsichtigkeit der Sihouette, funktioniert nur vernünftig bei konvexen Objekten (Kugeln, Ellipsoide, Stanford bunnies, etc.).</summary> 
		///<param name = "frTransparancy">Durchsichtigkeitsstärke </param> 
		void SetTransparencyEdge(float frTransparancyEdge);

		///<summary> Ändert nach dem Loaden den Pfad für die Environmental-Textur.</summary> 
		///<param name = "acPath">ASCII-Pfad für die Environmental-Textur mit Suffix</param> 
		///<param name = "bCubic">Flag, ob es sich um eine kubische (nach Vektoria) oder sphärische Textur handelt</param>
		void AlterEnvPath(char * acPath, bool bCubic);

		// ----------------------------------------------
		// Subsurface-Scattering-Parametersetzfunktionen:
		// ----------------------------------------------

		///<summary> Schaltet Subsurfaces Scattering für das Licht ein.<para></para>
		/// Helles Licht scheint damit in Abhängigkeit der Tiefentextur durch das Material durch.<para></para>
		/// Für Wolken, Dampf und Ähnliches geeignet.</summary> 
		void SetLightScatteringOn();

		///<summary> Setzt die Stärke der Reflektionen des BRDF beim Subsurface Scattering.</summary> 
		///<param name = "fReflectance">Reflektionsstärke<param> 
		void SetBRDFReflectance(float fReflectance);

		///<summary> Setzt die absolute Materialdicke für das Subsurfacescattering.</summary>
		///<param name = "fThickness">absolute Materialdicke<param> 
		void SetAbsoluteMaterialThickness(float fThickness);

		///<summary> Stärke der Glanzlichter des Subsurfacescattering.</summary>
		///<param name = "fRimStrength">Glanzlichtstärke beim SSS<param> 
		void SetRimLightStrength(float fRimStrength);

		///<summary> Setzt die Subsurface-Farbe für das Subsurface Scattering, funktioniert auch im Basic-Renderer.</summary>
		///<param name = "color">Subsurface-Farbe (RGB-Werte zwischen 0 und 1, Alpha wird ignoriert)<param> 
		void SetSubSurfaceColor(CColor color);

		// --------------------------------------------------------------------------------------------------------------
		// Setzfunktionen für das physikalisch basierte Rendering, die nur im Forward-Plus-Renderer einen Einfluss haben:
		// --------------------------------------------------------------------------------------------------------------

		///<summary> Setzt Rauheit der Oberfläche, nur im FP-Render.</summary>
		void SetRoughness(float fRoughness); 

		///<summary> Setzt die Spiegelunsstärke, nur im FP-Renderer.</summary>
		void SetSpecular(float fSpecular);  

		///<summary> Wieviel Farbe von der Diffuse-Map geht ins Highlight rein, nur im FP-Renderer.</summary>
		void SetSpecularTint(float fSpeculatTint); 

		///<summary> Metallischer Faktor, nur im FP-Renderer.</summary>
		void SetMetallic(float fMetallic);  

		///<summary> kein Subsurface-Scattering!, nur im FP-Renderer.</summary>
		void SetSubsurface(float fSubsurface);

		///<summary> Speculare Highlights sind nicht mehr rund, sondern anisotrop, nur im FP-Renderer.</summary>
		void SetAnisotropic(float fAnistropic); 

		///<summary> Oberfläche leuchtet, niedriger Wert nehmen, nur im FP-Renderer.</summary>
		void SetSheen(float fSheen); 

		///<summary> Farbe von diffusen Material kommt dazu, nur im FP-Renderer.</summary>
		void SetSheenTint(float fSheenTint); 

		///<summary> Wie Plastik, schwarfe spekulare Highlights, nur im FP-Renderer.</summary>
		void SetClearCoat(float fClearCoat); 

		///<summary> Glossyness der spekularen Highlights, nur im FP-Renderer.</summary>
		void SetClearCoatGloss(float fClearCoatGloss); 

		///<summary> Setzt Brechungsindex, nur im FP-Renderer.</summary>
		void SetIndexOfRefraction(float fIOR);

		///<summary>Stärke der Enviromentmap verringern, nur im FP-Renderer.</summary> 
		void SetEnvironmentMapIntensityReduction(float fIntensity);  

		// --------------------
		// Transparenzmethoden:
		// --------------------

		///<summary> Gibt die Transparenzart an.</summary>
		///<param name = "eTransparencyKind">Transparenzart:<para></para>
		/// eTransparencyKind_No: opake Texturen <para></para>
		/// eTransparencyKind_BinaryByAlphaTest: ja-nein-Alpha-Texturen<para></para>
		/// eTransparencyKind_BinaryByChromaKey: Farbschlüsseltexturen<para></para>
		/// eTransparencyKind_Continual: Semitransparente Texturen mit Alphakanal<para></para>
		/// eTransparencyKind_Complete: Komplett unsichtbare Texturen (für Geisterobjekte)</param> 
		void SetTransparencyKind(ETransparencyKind eTransparencyKind);

		///<summary> Schaltet Durchsichtigkeit an.</summary>
		void SetTransparencyOn(); 

		///<summary> Schaltet Durchsichtigkeit aus.</summary>
		void SetTransparencyOff(); 

		///<summary> Schaltes Farbschlüssel-Durchsichtigkeit an.<para></para>
		/// Das linke obere Pixel der Diffuse-Texture ist der Farbschlüssel.</summary>
		void SetChromaKeyingOn(); 

		///<summary> Schaltes Farbschlüssel-Durchsichtigkeit aus.</summary>
		void SetChromaKeyingOff(); 

		///<summary> Gibt true aus, falls es sich um eine vollkommen undurchsichtige Textur handelt, ansonsten, also wenn Chroma-Keying, Transparenz oder AlphaTest eingeschaltet ist wird false ausgegeben.</summary>
		bool IsOpaque(); 	

		// ----------------------------
		// Texturadressierungsmethoden:
		// ----------------------------

		///<summary> Setzt die Art, wie die Textur über ihren Grenzen behandelt wird (Clamping, Tiling, ...).</summary>
		///<param name = "eTextureAddressMode">Texturadressierungsungsart:<para></para>
		/// eTextureAddressMode_Clamp: Abgeschnittene Textur <para></para>
		/// eTextureAddressMode_Mirror: Gespiegelte Textur <para></para>
		/// eTextureAddressMode_Wrap: Gekachelte Textur (default = 1) </param> 
		void SetTextureAddressMode(ETextureAddressMode eTextureAddressMode);

		// -------------------------------------
		// Methoden für das Verteilte Rendering:
		// -------------------------------------

		///<summary> Materialien werden beim verteilten Rendering an Clients übermittelt (default).</summary>
		void SetDistributedOn(); 

		///<summary> Materialien werden beim verteilten Rendering den Clients vorenthalten, dies kann das Rendering bei vielen 2D-Overlays und Writings beschleunigen.</summary>
		void SetDistributedOff(); 

		//------------------
		// Member-Variablen:
		//------------------

		///<summary> Colorshift-Matrix, verändert den Farbwert von Glow- und Diffuse-Textur.</summary>
		CHMat m_mColor; 

		///<summary> Art der Transparenz.</summary>
		ETransparencyKind m_eTransparencyKind;

		///<summary> Zeiger auf die diffuse Textur.</summary>
		CTexture * m_ptextureDiffuse;

		///<summary> Zeiger auf die Glow-Textur.</summary>
		CTexture * m_ptextureGlow;

		///<summary> Zeiger auf die spekulare Textur.</summary>
		CTexture * m_ptextureSpecular;

		///<summary> Zeiger auf die Bumpmap-Textur.</summary>
		CTexture * m_ptextureBump;

		///<summary> Zeiger auf die Envirunment-Textur.</summary>
		CTexture * m_ptextureEnvironment;

		///<summary> Zeiger auf die Height-Textur.</summary>
		CTexture * m_ptextureHeight;

		///<summary> Zeiger auf die Dickentextur.</summary>
		CTexture * m_ptextureThickness;

		///<summary> Farbe des Subsurface-Scatterings.</summary>
		CColor m_colorSSS;

		///<summary> Brechungsindex.</summary>
		float m_fRefractionRatio; 

		///<summary> Fresnel-Faktor.</summary>
		float m_frFresnel; 

		///<summary> Schärfe zwischen Glow- und Nicht-Glow-Bereich.</summary>
		float m_fGlowSharpness;

		///<summary> Schärfe zwischen beleuchter und unbeleuchteter Seite.</summary>
		float m_fDiffuseSharpness;

		///<summary> Schärfe des Highlights (default = 25).</summary>
		float m_fSpecularSharpness;
		
		///<summary> Stärke des Haze-Effektes (default = 1, wikt sich nur aus wenn Haze sowohl im Material als auch im Viewport angeschaltet ist).</summary>
		float m_fHazeStrength;

		///<summary> Stärke des POM-Effektes (default = 1).</summary>
		float m_fHeightStrength;

		///<summary> Stärke des Bump-Effektes (default = 1).</summary>
		float m_fBumpStrength;

		///<summary> Stärke des Glow-Effektes (default = 1).</summary>
		float m_fGlowStrength;

		///<summary> Stärke des Heighlight-Effektes (default = 1).</summary>
		float m_fSpecularStrength;

		///<summary> Durchsichtigkeit (default = 0).</summary>
		float m_frTransparency;

		///<summary> Durchsichtigkeit der Ränder (default = 0).</summary>
		float m_frTransparencyEdge;

		///<summary> Dicke für das Subsurfacescattering.</summary>
		float m_fAbsoluteThickness;

		///<summary> BRDF Reflectance für das Subsurfacescattering.</summary>
		float m_fBRDFReflectance;

		///<summary> Highlight-Stärke für das Subsurfacescattering.</summary>
		float m_fRimLightStr;

		///<summary> EnvironmentInt, nur im FP-Renderer verwendet.</summary>
		float m_fEnvironmentInt;

		///<summary> Oberflächenrauheit, nur im FP-Renderer verwendet.</summary>
		float m_fRoughness;

		///<summary> IOR, Nur im FP-Renderer verwendet.</summary>
		float m_fIOR;

		///<summary> Specular, Nur im FP-Renderer verwendet.</summary>
		float m_fSpecular;

		///<summary> Speculare Tint, Nur im FP-Renderer verwendet.</summary>
		float m_fSpecularTint;

		///<summary> Metallic-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fMetallic;

		///<summary> Subsurface-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fSubsurface;

		///<summary> Anistropic-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fAnistropic;

		///<summary> Sheen-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fSheen;

		///<summary> Sheen Tint-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fSheenTint;

		///<summary> ClearCoat-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fClearCoat;

		///<summary> ClearCoatGloss-Stärke, Nur im FP-Renderer verwendet.</summary>
		float m_fClearCoatGloss;

		///<summary> Flags, wie die diffuse Textur verwendet werden soll.</summary>
		int m_iFlagsDiffuse;

		///<summary> Flags, wie die Glow-Textur verwendet werden soll.</summary>
		int m_iFlagsGlow;

		///<summary> Flags, wie die spekulare Textur verwendet werden soll.</summary>
		int m_iFlagsSpecular;

		///<summary> Flags, wie die Bumpmap-Textur verwendet werden soll.</summary>
		int m_iFlagsBump;

		///<summary> Flags, wie die Umgebungstextur verwendet werden soll.</summary>
		int m_iFlagsEnvironment;

		///<summary> Flags, wie die Highmap-Textur verwendet werden soll.</summary>
		int m_iFlagsPOM;

		///<summary> Flags, wie die Dickentextur für das Subsurface-Scattering verwendet werden soll.</summary>
		int m_iFlagsSSS;

		///<summary> Flags, wie die Reflectionmap-Textur verwendet werden soll.</summary>
		int m_iFlagsReflectionMap;

		///<summary> Flags, ob das Postprocessing verwendet werden soll, und wenn ja, wie. (0=kein PP, 1= PP 2= PP mit Haze)</summary>
		int m_iFlagsPostprocessing;

		///<summary> Flag, ob die Textur geshadet werden soll</summary>
		bool m_bShading;

		///<summary> Identifikationsnummer, Achtung!!! Nur der Aufwärtskompabilität halber noch drin, wird ab V16 umbenannt, da Überladung!!!</summary>
		int m_id; 

		///<summary> True, falls die Texturwerte verändert wurden und diese Veränderungen nooch nicht an die Grafikkarte übermittelt wurden.</summary>
		bool m_bChanged;

		///<summary> True, falls nur die speziellen Texturwerte für animierte Texturen verändert wurden und diese Veränderungen nooch nicht an die Grafikkarte übermittelt wurden.</summary>
		bool m_bChangedAni;

		///<summary>  True (default), wenn Materialänderungen im Verteilten Rendering an die Clients übermittelt werden sollen, false ansonsten, es empfiehlt sich, Materialien für 2D Sprites und Writings auf false zu setzen.</summary>
		bool m_bDistributed;  

		///<summary>  Liste aller Geometrien, die das Material verwenden.</summary>
		CGeos * m_pgeos; 

		///<summary>  Flag, ob Licht-Scattering angeschaltet ist (default=false).</summary>
		bool m_bLightScattering;

		// ------------------------------------------
		// Membervariablen für animierte Materialien:
		// ------------------------------------------

		///<summary>true, wenn animiertes Material.</summary>
		bool m_bAni; 

		///<summary>true, wenn steuerbares Material.</summary>
		bool m_bBot; 

		///<summary>Anzahl der Animationsbilder in X-Richtung.</summary>
		int m_ixPics; //  

		///<summary>Anzahl der Animationsbilder in Y-Richtung.</summary>
		int m_iyPics; 

		///<summary>Anzahl der Animationsbilder (insgesamt).</summary>
		int m_iPics;

		///<summary>Aktuelles Animationsbild mit Zwischenposition.</summary>
		float m_fPic;

		///<summary>Bildwiederholrate von animierten Materialien.</summary>
		float m_fFps; 

		///<summary>Texturaddressierungsmodus (eTextureAddressMode_Clamp, eTextureAddressMode_Mirror, eTextureAddressMode_Wrap).</summary>
		ETextureAddressMode m_eTextureAddressMode;

		///<summary>Pointer auf den Container für eventuelle angehäbgte Emitter.</summary>
		CEmitters * m_pemitters;

		///<summary>Liste auf Ahnen-Szenen.</summary>
		CScenes * m_pscenesAnchestor;
	};

}