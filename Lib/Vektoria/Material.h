#pragma once
#include "Node.h"
#include "Textures.h"
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Color.h"

//---------------------------------------------------
// CMaterial: Klasse f�r Materialien
//
// Autoren: Prof. Dr. Tobias Breiner
// Letzte �nderung: 2016-02-01
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

		///<summary> Setzt die Ahnenszenen (Hilfsroutine f�r Verkn�fungsmethoden).</summary>
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

		///<summary> L�dt vorgefertigtes Material �ber ein Skriptfile mit dem Namen acName mit allen Parametern, Texturen, etc. aus der Materialbibliothek,<para></para> 
		///diese befindet sich in Lib/Materials.</summary>
		///<param name = "acName"> Name des vorgefertigten Materials, z.B.:<para></para>
		///"Blood","BricksClincker","BricksClinckerColored","CobblestoneMarble","Concrete","CounterDigital","EarthCracked","EggshellBrown","Equalizer","LeatherBlack","MetalChromeCircuit","MetalRustyFlaking","MirrorPure","PanoPlate","Perl","Quicksilver","RockMossy","RubberBlack","Suede","TilesDirty","TilesMarbleWhite","Vanish","Water","WindowGothicStained","WoodPlanks","WoodPlanksBankirai"   </param>
		bool LoadPreset(char * acName);

		///<summary> Speichert das erstellte Material in ein Skriptfile mit dem Namen acName.vem an die richtige Stelle in der Materialbiliothek.<para></para>
		///Die diesbez�glichen Texturen sollten schon am richtigen Platz liegen.</summary> 
		///<param name = "acName"> Name des vorgefertigten Materials</param>
		bool SavePreset(char * acName);

		///<summary> L�dt ein Material aus einer Vektoria-Materialdatei (.vm).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Materialdatei (mit Suffix), absolute und relative Pfade sind m�glich, z.B. "C:\\MyMaterial.vm" oder ".\\Materials\\MyMaterial.vm" </param>
		bool Load(char * acPath);

		///<summary> Speichert das Material in eine Material-Vektoriadatei (.vm).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>		
		///<param name="acPath">ASCII-Pfadangabe der Materialdatei (mit Suffix), absolute und relative Pfade sind m�glich, z.B. "C:\\MyMaterial.vm" oder ".\\Materials\\MyMaterial.vm" </param>
		bool Save(char * acPath);

	protected:

		///<summary> L�dt eine komplette Materialbeschreibung aus einem Vektoria-Materialdatei (.vm).</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Materials innerhalb der Datei, muss -1 sein, falls die gesamte Datei geladen werden soll</param>
		///<param name="fVersion">Vektoriaversion, um Aufw�rtskombabilit�t zu gew�hrleisten, z.B. 14.11 f�r die Version 14 Patch 11 </param>
		void Load(CFileVektoria & filevektoria, int id = -1, float fVersion = 14.11f);

		///<summary> Speichert eine komplette Materialbeschreibung in ein Vektoria-Materialdatei (.vm).</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name = "bWithID"> Flag, ob die eigene Material-ID mit abgespeichert werden soll.</param>
		///<param name = "bCalcConverging"> Flag, ob die Berechnung konvergierender Hierarchien durchgef�hrt werden soll.</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false, bool bCalcConverging = true);

	public:

		//---------------------
		// Verkn�fungsmethoden:
		//---------------------

		///<summary> H�ngt einen Emitter an das vorliegende Material an.</summary>
		///<param name="pemitter">Zeiger auf den anzuh�ngenden Emitter</param>
		void AddEmitter(CEmitter * pemitter);

		///<summary> H�ngt den Emitter wieder von dem vorliegenden Material ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pemitter">Zeiger auf den abzuh�ngenden Emitter</param>
		bool SubEmitter(CEmitter * pemitter);

		///<summary> H�ngt eine Textur an, die f�r Skymaps, Skydomes etc. geeignet ist (Siehe auch -> MakeTextureSky).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureSky(CTexture *ptexture);

		///<summary> H�ngt eine diffuse Textur an (Siehe auch -> MakeTextureDiffuse).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureDiffuse(CTexture *ptexture);

		///<summary> H�ngt eine Glow-Textur an (Siehe auch -> MakeTextureGlow),</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureGlow(CTexture *ptexture);

		///<summary> H�ngt eine spekulare Textur an (Siehe auch -> MakeTextureSpecular).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureSpecular(CTexture *ptexture);

		///<summary> H�ngt eine Normal-Map-Textur an (Siehe auch -> MakeTextureBump).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureBump(CTexture *ptexture);

		///<summary> H�ngt eine POM-Textur an (Siehe auch -> MakeTextureHeight).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureHeight(CTexture *ptexture);

		///<summary> H�ngt eine Haze-Textur an (Siehe auch -> MakeTextureHaze).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureHaze(CTexture *ptexture);

		///<summary> H�ngt eine Environment-Textur an (Siehe auch -> MakeTextureEnvironment).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		///<param name = "bCubic">Flag, ob es sich um eine kubische (nach Vektoria) oder sph�rische Textur handelt</param>
		void SetTextureEnvironment(CTexture *ptexture, bool bCubic);

		///<summary> H�ngt eine Dicken-Textur an (Siehe auch -> MakeTextureThickness).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureThickness(CTexture* ptexture);

		///<summary> H�ngt eine Textur an, die f�r Sprites wie Backgrounds, Overlays, Writings und WritingChars geeignet ist  .(Siehe auch -> MakeTextureSprite).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureSprite(CTexture *ptexture);

		///<summary> H�ngt eine Textur an, die f�r Billboards und Wribels geeignet ist.(Siehe auch -> MakeTextureSprite).</summary>
		///<param name = "ptexture">Zeiger auf die anzuh�ngende Textur</param>
		void SetTextureBillboard(CTexture *ptexture);

		///<summary> Erzeugt eine Texturhierarchie f�r eine Farb-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureDiffuse(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie f�r eine Glow-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureGlow(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie f�r eine Spacular-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureSpecular(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie f�r eine Dot3-Normal-Map.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>		
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureBump(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie f�r Parallax Occlusion Map-Hierarchie mit Heightmap.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureHeight(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie f�r Haze-Effekte mit Heightmap.<para></para>
		///<summary> Achtung! Der Haze-Filter im Viewoport muss naturgem�� eingeschaltet sein, damit diese Textur einen Effekt hat. <para></ para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureHaze(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie f�r Environmental-Map-Hierarchie f�r Reflektion und Refraktion.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		///<param name = "bIsCubicMap"> Wenn bCubicMap false ist, wird bei der Environmental Map sph�risches Mapping verwendet (default), ansonsten kubisches Mapping (nach Vektoria).</param>
		CImage * MakeTextureEnvironment(char * acPath, bool bIsCubicMap = false);

		///<summary> Erzeugt eine Texturhierarchie, die f�r Skymaps, Skydomes etc. geeignet ist.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureSky(char * acPath);

		///<summary> Materialdickebeschreibung f�r Subsurfacescattering und Farbe des Subsurfaces.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureThickness(char * acPath, CColor colorSSS);

		///<summary> Erzeugt eine Texturhierarchie, die f�r Billboards und Wribels geeignet ist.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
		///<param name = "acPath">ASCII-Pfadangabe inklusive Suffix (kann absolut oder relativ zur EXE sein)<para></para>
		///Beispiele: "C:\\MeineTextur.jpg" oder "..\\..\\MeinOrdner\\MeineTextur.png"</param>
		CImage * MakeTextureBillboard(char * acPath);

		///<summary> Erzeugt eine Texturhierarchie, die f�r Sprites wie Backgrounds, Overlays, Writings und WritingChars geeignet ist.<para></para>
		/// Gibt optional einen Pointer zum neu erzeugten Image zur�ck.</summary>
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
		///<param name = "ixPic">Gew�hltes Unterbild in X-Richtung</param>
		///<param name = "iyPic">Gew�hltes Unterbild in Y-Richtung</param>
		void SetPic(int ixPic, int iyPic); 

		///<summary> Schaltet das Shading an (default).</summary>
		void SetShadingOn(); 

		///<summary> Schaltet das Shading aus.</summary>
		void SetShadingOff(); 

		///<summary> Setzt die unbeleuchtete Seite auf Wei�.</summary>
		void SetTextureGlowWhite(); 

		///<summary> Setzt die unbeleuchtete Seite auf komplett schwarz.</summary>
		void SetTextureGlowBlack();  

		///<summary> Setzt den internen Texturpointer f�r die unbeleuchtete Seite auf die diffuse Textur.<para></para> 
		/// (spart Speicherplatz im Texturspeicher der Graka)</summary>
		void SetTextureGlowAsDiffuse();  
		
		///<summary> L�sst die Glow-Textur auch auf der beleuchteten Seite leuchten und ignoriert die Diffuse-Textur.<para></para> 
		/// Damit lassen sich beispielsweise Sonnen, Feuerb�lle, etc. herstellen.</summary>  
		void SetGlowEverywhere();

		///<summary> Setzt Glanzlicht �berall auf volle St�rke (siehe auch Methode MakeTextureSpecular).</summary>
		void SetTextureSpecularWhite(); 

		///<summary> Schaltet Glanzlicht komplett aus (siehe auch Methode MakeTextureSpecular).<para></para>
		/// (spart Speicherplatz im Texturspeicher der Graka)</summary>
		void SetTextureSpecularBlack();

		///<summary> Setzt den internen Glanzlichttexturpointer auf die diffuse Textur.</summary>
		void SetTextureSpecularAsDiffuse(); 

		///<summary> Schaltet das Postprocessing f�r diese Textur aus (default = an).</summary> 
		void SetPostprocessingOff(); 

		///<summary> Schaltet das Postprocessing f�r diese Textur an (default).</summary> 
		void SetPostprocessingOn();

		///<summary> Setzt Alphakanal der Environmentmap als Reflectionmap (veraltet).<para></para> 
		/// ACHTUNG!!! Nur der Aufw�rtskompatibilit�t halber drin, wird es ab V16 nicht mehr geben!</summary>
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

//		void SetBrightness(float fr); // Erh�ht Helligkeit (Werte>1), vermindert Helligkeit (Werte 0..1) bzw. invertiert Farbe (Wert<0) 
//		void SetBrightness(CColor c); // Erh�ht Helligkeit (Werte>1), vermindert helligkeit (Werte 0..1) bzw. invertiert Farbe (Wert<0) jeweils getrennt nach RGB-Werten 

		// ------------------
		// Farbver�nderungen: 
		// ------------------

		///<summary> Skaliert Farbver�nderungsmatrix zur Helligkeitsver�nderung der diffusen Textur.</summary>
		///<param name = "fr">Skalierungsfaktor<para></para>
		/// fr gr��er 1: Erh�ht Helligkeit<para></para> 
		/// fr gleich 1: Bel�sst Helligkeit (sinnlos)<para></para> 
		/// fr zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// fr gleich 0: l�scht Bildausgabe (sinnlos)<para></para> 
		/// fr kleiner 0: Invertiert Farbe</param>  
		void Scale(float fr); 

		///<summary> Skaliert Farbver�nderungsmatrix zur Helligkeitsver�nderung der diffusen Textur, bel�sst vorherige Farbwertver�nderungen.</summary> 
		///<param name = "fr">Skalierungsfaktor<para></para>
		/// fr gr��er 1: Erh�ht Helligkeit<para></para> 
		/// fr gleich 1: Bel�sst Helligkeit (sinnlos)<para></para> 
		/// fr zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// fr gleich 0: l�scht Bildausgabe (sinnlos)<para></para> 
		/// fr kleiner 0: Invertiert Farbe</param>  
		void ScaleDelta(float fr);

		///<summary> Skaliert Farbver�nderungsmatrix zur Helligkeitsver�nderung der diffusen Textur jeweils getrennt zu R,G und B.</summary> 
		///<param name = "c">Skalierungsfaktoren f�r Rot, Gr�n und Blau<para></para>
		/// Werte gr��er 1: Erh�ht Helligkeit<para></para> 
		/// Werte gleich 1: Bel�sst Helligkeit (sinnlos)<para></para> 
		/// Werte zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// Werte gleich 0: l�scht Bildausgabe (sinnlos)<para></para> 
		/// Werte kleiner 0: Invertiert Farbe</param>  
		void Scale(CColor c);

		///<summary> Skaliert Farbver�nderungsmatrix zur Helligkeitsver�nderung der diffusen Textur jeweils getrennt zu R,G und B, bel�sst vorherige Farbwertver�nderungen.</summary>  
		///<param name = "c">Skalierungsfaktoren f�r Rot, Gr�n und Blau<para></para>
		/// Werte gr��er 1: Erh�ht Helligkeit<para></para> 
		/// Werte gleich 1: Bel�sst Helligkeit (sinnlos)<para></para> 
		/// Werte zwischen 0  und 1: Vermindert Helligkeit<para></para>  
		/// Werte gleich 0: l�scht Bildausgabe (sinnlos)<para></para> 
		/// Werte kleiner 0: Invertiert Farbe</param>  
		void ScaleDelta(CColor c);

		///<summary> Setzt Farbwertzusammensetzung der Textur auf Farbe c als Mittelwert.</summary>   
		///<param name = "c">Farbwerte f�r Rot, Gr�n und Blau<para></para> 
		/// Werte gr��er 0: Farbwert wird erh�ht <para></para> 
		/// Werte gleich 0: Farbwert bleibt <para></para> 
		/// Werte kleiner 0: Farbwert wird vermindert </param> 
		void Translate(CColor c);

		///<summary> Setzt Farbwertzusammensetzung der Textur, bel�sst vorherige Werte.</summary>   
		///<param name = "c">Farbwerte f�r Rot, Gr�n und Blau<para></para> 
		/// Werte gr��er 0: Farbwert wird erh�ht <para></para> 
		/// Werte gleich 0: Farbwert bleibt <para></para> 
		/// Werte kleiner 0: Farbwert wird vermindert </param> 
		void TranslateDelta(CColor c);

		///<summary> Rotiert die Farbwerte (Hue) (R->G->B->).</summary> 
		///<param name = "fa">Rotationswinkel im Bogenma�</param> 
		void RotateHue(float fa);

		///<summary> Rotiert die Farbwerte weiter (Hue) (R->G->B->).</summary>  
		///<param name = "fa">Rotationswinkel im Bogenma�</param> 
		void RotateHueDelta(float fa);

		///<summary> Setzt die Colorshift-Matrix.</summary> 
		///<param name = "mColor">Colorshift-Matrix</param> 
		void SetMat(CHMat mColor);

		// --------------------------
		// Allgemeine Setzfunktionen:
		// --------------------------

		///<summary> Setzt die St�rke der Bumpmap (Dot3-Normal Map).</summary> 
		///<param name = "fBumpStrength">St�rke der Bumpmap, Default = 1.0f, auch negative Werte sind erlaubt</param> 
		void SetBumpStrength(float fBumpStrength);

		///<summary> Setzt die St�rke der Heightmap (Parallax Occlution Map).</summary>    
		///<param name = "fHeightStrength">St�rke der Heightmap, Default = 1.0f, auch negative Werte sind erlaubt, f�hren aber dann nicht zum besten Ergebnis</param> 
		void SetHeightStrength(float fHeightStrength);

		///<summary> Setzt die St�rke des Glowmap (Leucht-Map).</summary>    
		///<param name = "fGlowStrength">St�rke des Glows <para></para> 
		/// - Default = 1.0f.<para></para>
		/// - �ber 1 gibt es einen Bloom-Effekt, falls Bloom-Filtger im Viewport angeschaltet ist.<para></para>
		/// - Auch negative Werte sind erlaubt und ergeben satanische "schwarze Lichter", die der Umgebung Licht rauben.</param> 
		void SetGlowStrength(float fGlowStrength);

		///<summary> Setzt die St�rke des Glanzlichtes.</summary>    
		///<param name = "fSpecularStrength">St�rke des Glanzlichtes <para></para> 
		/// - Default = 1.0f.<para></para>
		/// - �ber 1 gibt es einen Bloom-Effekt, falls Bloom-Filtger im Viewport angeschaltet istq.<para></para>
		/// - Auch negative Werte sind erlaubt und ergeben satanische "schwarze Glanzlichter", wie von einer Schwarzen Sonne, die der Umgebung Licht rauben.</param> 
		void SetSpecularStrength(float fSpecularStrength);

		///<summary> Setzt die Sch�rfe des Glanzlichtes.</summary> 
		///<param name = "fSpecularStrength">Glanzlicht-Sch�rfe, je h�her, desto kleiner und akzentuierter ist das Highlight (default = 25)</param>
		void SetSpecularSharpness(float fSpecularSharpness);

		///<summary> Setzt die Sch�rfe zwischen diffuser und ambienter Seite.</summary> 
		///<param name = "fDiffuseSharpness">Sch�rfe zwischen Diffuser und Nachtseite, je h�her, desto kleiner und akzentuierter ist der �bergang</param>
		void SetDiffuseSharpness(float fDiffuseSharpness);

		///<summary> Setzt die Sch�rfe zwischen Glow- und nicht-Glow-Bereich (default = 1).</summary> 
		///<param name = "fGlowSharpness">Sch�rfe zwischen Glow und Nicht-Glow-Bereich, je h�her, desto kleiner und akzentuierter ist der �bergang</param> 
		void SetGlowSharpness(float fGlowSharpness);

		///<summary> Setzt die Haze-St�rke.<para></para> 
		/// Wirkt sich nur aus, wenn A.) zus�tzlich SetHazeOn() aufgerufen wird und B.= im Viewport der Haze-Postprocessing-Filter mit SetHazeOn() angeschaltet ist.</summary> 
		///<param name = "fHazeStrength">Haze-St�rke, je h�her, desto mehr wird das Bild verschoben (default = 1)</param> 
		void SetHazeStrength(float fHazeStrength);

		///<summary> Schaltet Haze an und damit auch notwendigerweise das Postprocessing an.</summary> 
		void SetHazeOn();

		///<summary> Setzt die Durchsichtigkeit.</summary>  
		///<param name = "frTransparancy">Durchsichtigkeit <para></para> 
		/// - frTransparency gleich 0: undurchsichtig,opak<para></para>
		/// - frTransparency zwischen 0 und 1: Teildurchsichtig<para></para>
		/// - frTransparency gleich 1: komplett durchsichtig (meist sinnlos)</param>
		void SetTransparency(float frTransparancy); 

		///<summary> Setzt die Durchsichtigkeit der Sihouette, funktioniert nur vern�nftig bei konvexen Objekten (Kugeln, Ellipsoide, Stanford bunnies, etc.).</summary> 
		///<param name = "frTransparancy">Durchsichtigkeitsst�rke </param> 
		void SetTransparencyEdge(float frTransparancyEdge);

		///<summary> �ndert nach dem Loaden den Pfad f�r die Environmental-Textur.</summary> 
		///<param name = "acPath">ASCII-Pfad f�r die Environmental-Textur mit Suffix</param> 
		///<param name = "bCubic">Flag, ob es sich um eine kubische (nach Vektoria) oder sph�rische Textur handelt</param>
		void AlterEnvPath(char * acPath, bool bCubic);

		// ----------------------------------------------
		// Subsurface-Scattering-Parametersetzfunktionen:
		// ----------------------------------------------

		///<summary> Schaltet Subsurfaces Scattering f�r das Licht ein.<para></para>
		/// Helles Licht scheint damit in Abh�ngigkeit der Tiefentextur durch das Material durch.<para></para>
		/// F�r Wolken, Dampf und �hnliches geeignet.</summary> 
		void SetLightScatteringOn();

		///<summary> Setzt die St�rke der Reflektionen des BRDF beim Subsurface Scattering.</summary> 
		///<param name = "fReflectance">Reflektionsst�rke<param> 
		void SetBRDFReflectance(float fReflectance);

		///<summary> Setzt die absolute Materialdicke f�r das Subsurfacescattering.</summary>
		///<param name = "fThickness">absolute Materialdicke<param> 
		void SetAbsoluteMaterialThickness(float fThickness);

		///<summary> St�rke der Glanzlichter des Subsurfacescattering.</summary>
		///<param name = "fRimStrength">Glanzlichtst�rke beim SSS<param> 
		void SetRimLightStrength(float fRimStrength);

		///<summary> Setzt die Subsurface-Farbe f�r das Subsurface Scattering, funktioniert auch im Basic-Renderer.</summary>
		///<param name = "color">Subsurface-Farbe (RGB-Werte zwischen 0 und 1, Alpha wird ignoriert)<param> 
		void SetSubSurfaceColor(CColor color);

		// --------------------------------------------------------------------------------------------------------------
		// Setzfunktionen f�r das physikalisch basierte Rendering, die nur im Forward-Plus-Renderer einen Einfluss haben:
		// --------------------------------------------------------------------------------------------------------------

		///<summary> Setzt Rauheit der Oberfl�che, nur im FP-Render.</summary>
		void SetRoughness(float fRoughness); 

		///<summary> Setzt die Spiegelunsst�rke, nur im FP-Renderer.</summary>
		void SetSpecular(float fSpecular);  

		///<summary> Wieviel Farbe von der Diffuse-Map geht ins Highlight rein, nur im FP-Renderer.</summary>
		void SetSpecularTint(float fSpeculatTint); 

		///<summary> Metallischer Faktor, nur im FP-Renderer.</summary>
		void SetMetallic(float fMetallic);  

		///<summary> kein Subsurface-Scattering!, nur im FP-Renderer.</summary>
		void SetSubsurface(float fSubsurface);

		///<summary> Speculare Highlights sind nicht mehr rund, sondern anisotrop, nur im FP-Renderer.</summary>
		void SetAnisotropic(float fAnistropic); 

		///<summary> Oberfl�che leuchtet, niedriger Wert nehmen, nur im FP-Renderer.</summary>
		void SetSheen(float fSheen); 

		///<summary> Farbe von diffusen Material kommt dazu, nur im FP-Renderer.</summary>
		void SetSheenTint(float fSheenTint); 

		///<summary> Wie Plastik, schwarfe spekulare Highlights, nur im FP-Renderer.</summary>
		void SetClearCoat(float fClearCoat); 

		///<summary> Glossyness der spekularen Highlights, nur im FP-Renderer.</summary>
		void SetClearCoatGloss(float fClearCoatGloss); 

		///<summary> Setzt Brechungsindex, nur im FP-Renderer.</summary>
		void SetIndexOfRefraction(float fIOR);

		///<summary>St�rke der Enviromentmap verringern, nur im FP-Renderer.</summary> 
		void SetEnvironmentMapIntensityReduction(float fIntensity);  

		// --------------------
		// Transparenzmethoden:
		// --------------------

		///<summary> Gibt die Transparenzart an.</summary>
		///<param name = "eTransparencyKind">Transparenzart:<para></para>
		/// eTransparencyKind_No: opake Texturen <para></para>
		/// eTransparencyKind_BinaryByAlphaTest: ja-nein-Alpha-Texturen<para></para>
		/// eTransparencyKind_BinaryByChromaKey: Farbschl�sseltexturen<para></para>
		/// eTransparencyKind_Continual: Semitransparente Texturen mit Alphakanal<para></para>
		/// eTransparencyKind_Complete: Komplett unsichtbare Texturen (f�r Geisterobjekte)</param> 
		void SetTransparencyKind(ETransparencyKind eTransparencyKind);

		///<summary> Schaltet Durchsichtigkeit an.</summary>
		void SetTransparencyOn(); 

		///<summary> Schaltet Durchsichtigkeit aus.</summary>
		void SetTransparencyOff(); 

		///<summary> Schaltes Farbschl�ssel-Durchsichtigkeit an.<para></para>
		/// Das linke obere Pixel der Diffuse-Texture ist der Farbschl�ssel.</summary>
		void SetChromaKeyingOn(); 

		///<summary> Schaltes Farbschl�ssel-Durchsichtigkeit aus.</summary>
		void SetChromaKeyingOff(); 

		///<summary> Gibt true aus, falls es sich um eine vollkommen undurchsichtige Textur handelt, ansonsten, also wenn Chroma-Keying, Transparenz oder AlphaTest eingeschaltet ist wird false ausgegeben.</summary>
		bool IsOpaque(); 	

		// ----------------------------
		// Texturadressierungsmethoden:
		// ----------------------------

		///<summary> Setzt die Art, wie die Textur �ber ihren Grenzen behandelt wird (Clamping, Tiling, ...).</summary>
		///<param name = "eTextureAddressMode">Texturadressierungsungsart:<para></para>
		/// eTextureAddressMode_Clamp: Abgeschnittene Textur <para></para>
		/// eTextureAddressMode_Mirror: Gespiegelte Textur <para></para>
		/// eTextureAddressMode_Wrap: Gekachelte Textur (default = 1) </param> 
		void SetTextureAddressMode(ETextureAddressMode eTextureAddressMode);

		// -------------------------------------
		// Methoden f�r das Verteilte Rendering:
		// -------------------------------------

		///<summary> Materialien werden beim verteilten Rendering an Clients �bermittelt (default).</summary>
		void SetDistributedOn(); 

		///<summary> Materialien werden beim verteilten Rendering den Clients vorenthalten, dies kann das Rendering bei vielen 2D-Overlays und Writings beschleunigen.</summary>
		void SetDistributedOff(); 

		//------------------
		// Member-Variablen:
		//------------------

		///<summary> Colorshift-Matrix, ver�ndert den Farbwert von Glow- und Diffuse-Textur.</summary>
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

		///<summary> Sch�rfe zwischen Glow- und Nicht-Glow-Bereich.</summary>
		float m_fGlowSharpness;

		///<summary> Sch�rfe zwischen beleuchter und unbeleuchteter Seite.</summary>
		float m_fDiffuseSharpness;

		///<summary> Sch�rfe des Highlights (default = 25).</summary>
		float m_fSpecularSharpness;
		
		///<summary> St�rke des Haze-Effektes (default = 1, wikt sich nur aus wenn Haze sowohl im Material als auch im Viewport angeschaltet ist).</summary>
		float m_fHazeStrength;

		///<summary> St�rke des POM-Effektes (default = 1).</summary>
		float m_fHeightStrength;

		///<summary> St�rke des Bump-Effektes (default = 1).</summary>
		float m_fBumpStrength;

		///<summary> St�rke des Glow-Effektes (default = 1).</summary>
		float m_fGlowStrength;

		///<summary> St�rke des Heighlight-Effektes (default = 1).</summary>
		float m_fSpecularStrength;

		///<summary> Durchsichtigkeit (default = 0).</summary>
		float m_frTransparency;

		///<summary> Durchsichtigkeit der R�nder (default = 0).</summary>
		float m_frTransparencyEdge;

		///<summary> Dicke f�r das Subsurfacescattering.</summary>
		float m_fAbsoluteThickness;

		///<summary> BRDF Reflectance f�r das Subsurfacescattering.</summary>
		float m_fBRDFReflectance;

		///<summary> Highlight-St�rke f�r das Subsurfacescattering.</summary>
		float m_fRimLightStr;

		///<summary> EnvironmentInt, nur im FP-Renderer verwendet.</summary>
		float m_fEnvironmentInt;

		///<summary> Oberfl�chenrauheit, nur im FP-Renderer verwendet.</summary>
		float m_fRoughness;

		///<summary> IOR, Nur im FP-Renderer verwendet.</summary>
		float m_fIOR;

		///<summary> Specular, Nur im FP-Renderer verwendet.</summary>
		float m_fSpecular;

		///<summary> Speculare Tint, Nur im FP-Renderer verwendet.</summary>
		float m_fSpecularTint;

		///<summary> Metallic-St�rke, Nur im FP-Renderer verwendet.</summary>
		float m_fMetallic;

		///<summary> Subsurface-St�rke, Nur im FP-Renderer verwendet.</summary>
		float m_fSubsurface;

		///<summary> Anistropic-St�rke, Nur im FP-Renderer verwendet.</summary>
		float m_fAnistropic;

		///<summary> Sheen-St�rke, Nur im FP-Renderer verwendet.</summary>
		float m_fSheen;

		///<summary> Sheen Tint-St�rke, Nur im FP-Renderer verwendet.</summary>
		float m_fSheenTint;

		///<summary> ClearCoat-St�rke, Nur im FP-Renderer verwendet.</summary>
		float m_fClearCoat;

		///<summary> ClearCoatGloss-St�rke, Nur im FP-Renderer verwendet.</summary>
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

		///<summary> Flags, wie die Dickentextur f�r das Subsurface-Scattering verwendet werden soll.</summary>
		int m_iFlagsSSS;

		///<summary> Flags, wie die Reflectionmap-Textur verwendet werden soll.</summary>
		int m_iFlagsReflectionMap;

		///<summary> Flags, ob das Postprocessing verwendet werden soll, und wenn ja, wie. (0=kein PP, 1= PP 2= PP mit Haze)</summary>
		int m_iFlagsPostprocessing;

		///<summary> Flag, ob die Textur geshadet werden soll</summary>
		bool m_bShading;

		///<summary> Identifikationsnummer, Achtung!!! Nur der Aufw�rtskompabilit�t halber noch drin, wird ab V16 umbenannt, da �berladung!!!</summary>
		int m_id; 

		///<summary> True, falls die Texturwerte ver�ndert wurden und diese Ver�nderungen nooch nicht an die Grafikkarte �bermittelt wurden.</summary>
		bool m_bChanged;

		///<summary> True, falls nur die speziellen Texturwerte f�r animierte Texturen ver�ndert wurden und diese Ver�nderungen nooch nicht an die Grafikkarte �bermittelt wurden.</summary>
		bool m_bChangedAni;

		///<summary>  True (default), wenn Material�nderungen im Verteilten Rendering an die Clients �bermittelt werden sollen, false ansonsten, es empfiehlt sich, Materialien f�r 2D Sprites und Writings auf false zu setzen.</summary>
		bool m_bDistributed;  

		///<summary>  Liste aller Geometrien, die das Material verwenden.</summary>
		CGeos * m_pgeos; 

		///<summary>  Flag, ob Licht-Scattering angeschaltet ist (default=false).</summary>
		bool m_bLightScattering;

		// ------------------------------------------
		// Membervariablen f�r animierte Materialien:
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

		///<summary>Pointer auf den Container f�r eventuelle angeh�bgte Emitter.</summary>
		CEmitters * m_pemitters;

		///<summary>Liste auf Ahnen-Szenen.</summary>
		CScenes * m_pscenesAnchestor;
	};

}