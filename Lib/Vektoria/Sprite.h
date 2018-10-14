//------------------------------------
// CSprite: Basisklasse f�r Backgrounds, Overlays und damit indirekt Writings und WritingChars
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

#pragma once
#include "Texture.h"
#include "../VektoriaMath/FloatRect.h"
#include "GeoQuad.h"
#include "image.h"


namespace Vektoria
{

#define SKINDSPRITE_N 0
#define SKINDSPRITE_B 1
#define SKINDSPRITE_O 2
#define SKINDSPRITE_W 3
#define SKINDSPRITE_WS 4


	class CSprite : public CNode
	{
	friend class CViewport;
	protected:

		///<summary>Setzt den Pointer auf das �bergeordnete Viewport. Wird beim Anh�ngen automatisch aufgerufen.</summary>
		void SetViewport(CViewport * pviewport);

		///<summary>Wird vom �bergeordneten Viewport jeden Tick automstisch aufgerufen.</summary>
		void Tick();

		///<summary>Sammelt Materialien. Wird beim Starten im ersten Tick automatisch aufgerufen.</summary>
		void CollectMaterials();

		///<summary>Beendigungsmethode (wird automatisch von der dar�ber liegenden Hierarchie aufgerufen).</summary>
		void Fini();

	public:
		///<summary>Konstruktor.</summary>
		CSprite(void);

		///<summary>Destruktor.</summary>
		~CSprite(void);

		///<summary>Kopiermethode.</summary>
		///<param name = "sprite">Zu kopierendes Sprite</param>
		void Copy(CSprite & sprite);

		///<summary>Setzt den virtuellen Layerabstand vom Beobachter.</summary>
		///<param name = "fLayerDistance"> Virtueller "Abstand" des Layers vom Beobachter. <para></para>
		/// Wertebereich[0, 0..1, 0), Achtung, 1, 0 wird nicht mehr dargestellt!</param>
		void SetLayer(float fLayerDistance); 

		///<summary>Erfr�gt den virtuellen "Abstand" des Layers vom Beobachter,  Wertebereich [0,0..1,0).</summary>
		float GetLayer(); 

		///<summary>Initialisierungsmethode.</summary> 
		///<param name = "acPath"> ASCII-Pfadangabe der dazuzustellen Bilddatei, CTexture- und CImage-Hierarchie wird automatisch erzeugt</param>
		///<param name = "floatrect"> Relative Ausma�e des Sprites bez�glich dem �bergeordnetem Viewport</param>
		///<param name = "bChromaKeying"> Flag, ob Bilddagtei mit einem Farbschl�ssel angezeigt werden soll. <para></para>
		/// Der Farbwert des linken, oberen Pixels wird als Farbschl�ssel (Chroma Key) verwendet. <para></para>
		/// Alle Pixel mit diesem Farbwert werden dann durchsichtig. </param>
		void Init(char * acPath, CFloatRect & floatrect, bool bChromaKeying = false);


		///<summary>Initialisierungsmethode.</summary> 
		///<param name = "pimage"> Pointer auf eine Bildklasseninstanz.</param>
		///<param name = "floatrect"> Relative Ausma�e des Sprites bez�glich dem �bergeordnetem Viewport.</param>
		///<param name = "bChromaKeying"> Flag, ob Bilddagtei mit einem Farbschl�ssel angezeigt werden soll. <para></para>
		/// Der Farbwert des linken, oberen Pixels wird als Farbschl�ssel (Chroma Key) verwendet. <para></para>
		/// Alle Pixel mit diesem Farbwert werden dann durchsichtig. </param>
		void Init(CImage * pimage, CFloatRect & floatrect, bool bChromaKeying = false);

		///<summary>Initialisierungsmethode. </summary>
		///<param name = "pmaterial"> Pointer auf das Material, welches auf dem 2D-Sprite liegen soll<para></para>
		/// Achtung, das Material sollte ein Sprite-Material sein, sonst k�nnten Artefakte entstehen!</param>
		///<param name = "floatrect"> Relative Ausma�e des Sprites bez�glich dem �bergeordnetem Viewport.</param>
		void Init(CMaterial * pmaterial, CFloatRect & floatrect);

		///<summary>Initialisierungsmethode auf die volle Gr��e des �bergeordneten Viewports.</summary>
		///<param name = "acPath"> ASCII-Pfadangabe der dazuzustellen Bilddatei, CTexture- und CImage-Hierarchie wird automatisch erzeugt</param>
		///<param name = "bChromaKeying"> Flag, ob Bilddagtei mit einem Farbschl�ssel angezeigt werden soll. <para></para>
		/// Der Farbwert des linken, oberen Pixels wird als Farbschl�ssel (Chroma Key) verwendet. <para></para>
		/// Alle Pixel mit diesem Farbwert werden dann durchsichtig. </param>
		void InitFull(char * acPath, bool bChromaKeying = false);

		///<summary>Initialisierungsmethode auf die volle Gr��e des �bergeordneten Viewports.</summary>
		///<param name = "pimage"> Pointer auf eine Bildklasseninstanz.</param>
		///<param name = "bChromaKeying"> Flag, ob Bilddagtei mit einem Farbschl�ssel angezeigt werden soll. <para></para>
		/// Der Farbwert des linken, oberen Pixels wird als Farbschl�ssel (Chroma Key) verwendet. <para></para>
		/// Alle Pixel mit diesem Farbwert werden dann durchsichtig. </param>
		void InitFull(CImage * pimage, bool bChromaKeying = false);


		///<summary>Initialisierungsmethode auf die volle Gr��e des �bergeordneten Viewports.</summary>
		///<param name = "pmaterial"> Pointer auf das Material, welches auf dem 2D-Sprite liegen soll<para></para>
		/// Achtung, das Material sollte ein Sprite-Material sein, sonst k�nnten Artefakte entstehen!</param>
		void InitFull(CMaterial * pmaterial);


		///<summary>L�dt eine Spritebeschreibung aus einem Vektoria-File.</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name = "id"> Die eigene Sprite-ID.</param>
		void Load(CFileVektoria & filevektoria, int id);

		///<summary>Speichert eine Spritebeschreibung in ein Vektoria-File.</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		///<param name = "bWithID"> Flag, ob die eigene Sprite-ID mit abgesp�eichert werden soll.</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

		///<summary>Gibt die Durchsichtigkeit des 2D-Sprites an.</summary>
		///<param name = "frTransparency"> Durchsichtigkeit des 2D-Sprites (0= undurchsichtig = default ... 0,5 = halbdurchsichtig ... 1.0 nicht sichtbar).</param>
		void SetTransparency(float frTransparency); 		
		
		///<summary>Setzt das Material des 2D-Sprites.</summary>
		///<param name = "pmaterial"> Pointer auf das Material, welches auf dem 2D-Sprite liegen soll<para></para>
		/// Achtung, das Material sollte ein Sprite-Material sein, sonst k�nnten Artefakte entstehen!</param>
		void SetMaterial(CMaterial * pmaterial);

		///<summary>Setzt die Ausma�e des 2D-Sprites relativ zum �bergeordneten Viewport.</summary>
		///<param name = "floatrect"> Au�me�e des Sprite-Rechtecks. Beispiel: CFloatRect(0.0,0.5,0.5,0.5) wird im linken unteres Viertel des Viewports angezeigt</param>
		void SetRect(CFloatRect floatrect);

		///<summary>Gibt die Ausma�e des 2D-Sprites relativ zum �bergeordneten Viewport aus.</summary>
		CFloatRect GetRect(); 

		///<summary>Rotiert das 2D-Sprite mathematisch positiv um seinen Mittelpunkt.</summary>
		///<param name = "fa": Rotationswinkel gegen den Uhrzeigersinn im Bogenma�</param>
		void Rotate(float fa); 

		///<summary> Setzt das UV-Koordinatenrechteck. <para></para>
		/// Praktisch f�r Minimaps und �hnliches.<para></para>
		/// Kann auch w�hrend der Laufzeit aufgerufen werden, ist aber langsam.</summary>
		///<param name = "floatrect"> Au�me�e der UV-Koordinaten. Beispiel: CFloatRect(0.0,0.5,0.5,0.5) zeigt linkes unteres Viertel der Textur.</param>
		void SetUVRect(CFloatRect floatrect);

		//-----------------
		// Membervariablen:
		//-----------------

		// Pointer auf das Image, welches gezeigt wird.
		CImage * m_pimage;

		// Pointer auf die Sprite-Textur (mit angeh�ngtem Image), welche gezeigt wird.
		CTexture * m_ptexture;

		// Pointer auf das Sprite-Material (mit angeh�ngter Textur und Image), welche gezeigt wird.
		CMaterial * m_pmaterial;

		// Au�ma�e des Sprites bez�glich des �bergordneten Viewports.
		CFloatRect m_floatrect;

		// Pointer auf den des �bergordneten Viewport.
		CViewport * m_pviewport;

		// Unterart des Sprites. 
		int m_eKindSprite;

		// Virtueller "Abstand" des Layers vom Beobachter. 
		// Der Wertebereich [0,0..1,0), Achtung, 1,0 wird nicht mehr dargestellt! 
		float m_fLayer;

		// Flag, ob boosches Flag rotiert werden soll.
		bool m_bRotate;

		// Geometrie des Sprites.
		CGeoQuad m_geoquad;

		// Boolsches Flag, welches anzeigt, ob Material des Sprites schon bei der Wurzel angemeldet wurde.
		bool m_bMaterialAddedToRoot;

		// Rotationswinkel des Sprites (matematisch positiv im Bogenma�).
		float m_fa;

		// Flag, welches true beim ersten Tick ist.
		bool m_bFirstTick;

		// Renderart.
		int m_iRenderKind;

	};

}