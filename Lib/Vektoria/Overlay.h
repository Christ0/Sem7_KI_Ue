#pragma once
#include "Sprite.h"
#include "../VektoriaMath/FloatRect.h"

//------------------------------------
// COverlay
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschr�nkt)
//------------------------------------

namespace Vektoria
{

	class CViewport;
	class COverlays;
	class CWriting;
	class CWritingChar;

	class COverlay : public CSprite
	{
		friend class COverlays;
		friend class CWriting;
		friend class CWritingChar;
		friend class CWritings;
	protected:

		///<summary> Wird von dem �bergeordnetem Viewport automatisch jeden Tick aufgerufen, der Programmierer braucht sich normalerweise um diese Methode nicht zu k�mmern.</summary>
		void Tick(float & fTimeDelta, CFloatRect & floatrectFather); 

		///<summary> Setzt den Pointer auf das �bergeordnete Viewport. �berladene Funktion, da Sprite::SetViewport nicht Unteroverlays ansprechen kann.</summary>
		void SetViewport(CViewport * pviewport); 

		///<summary> Holt einen Pointer auf die Render-Api.</summary>
		CApiRender * GetApiRender();

	public:
		///<summary> Konstruktor. </summary>
		COverlay();

		///<summary> Destruktor.</summary>
		~COverlay();

		///<summary> Kopieroperator.</summary>
		COverlay operator=(COverlay & overlay);

		///<summary> Deinitialisiert das Overlay.</summary>
		void Fini();

		///<summary> H�ngt ein Kind-Overlay an das vorliegende Overlay an.</summary>
		/// <param name="poverlay">Pointer auf das anzuh�ngende Kinderoverlay </param>
		void AddOverlay(COverlay * poverlay); 

		///<summary> H�ngt das Kind-Overlay poverlay vom vorliegenden Overlay wieder ab, gibt true aus, wenn's geklappt hat.</summary>
		/// <param name="poverlay">Pointer auf das abzuh�ngende Kinderoverlay </param>
		bool SubOverlay(COverlay * poverlay);
		
		///<summary> H�ngt ein Unter-Writing-Textfeld an den Overlay an.</summary>
		/// <param name="pwriting">Pointer auf das anzuh�ngende Kinderwriting </param>
		void AddWriting(CWriting * pwriting); 

		///<summary> H�ngt ein vorhandenes Unter-Writing-Textfeld vom Overlay ab, gibt true aus, wenn's geklappt hat.</summary>
		/// <param name="pwriting">Pointer auf das abzuh�ngende Kinderwriting </param>
		bool SubWriting(CWriting * pwriting);

		///<summary> H�ngt ein Unter-Writing-Buchstabenfeld an den Overlay an.</summary>
		/// <param name="pwritingchar">Pointer auf das abzuh�ngende Kinderwritingchar </param>
		void AddWritingChar(CWritingChar * pwritingchar);

		///<summary> H�ngt ein vorhandenes Unter-Writing-Buchstabenfeld vom Overlay ab, gibt true aus, wenn's geklappt hat.</summary>
		/// <param name="pwritingchar">Pointer auf das abzuh�ngende Kinderwritingchar </param>
		bool SubWritingChar(CWritingChar * pwritingchar);

		///<summary> L�sst Overlay innerhalb vom Vateroverlay erscheinen.</summary>
		void SetInnerOn(); 

		///<summary> L�sst Overlay au�erhalb vom Vateroverlay (aber trotzdem ausgerichtet an Vaterkoordinaten) erscheinen (Default). </summary> 
		void SetInnerOff();  

		///<summary> Gibt f�r die relativen Texturkoordinaten frx, fry aus, ob das Overlay getroffen wurde.</summary> 
		/// <param name="frx">Relative X-Position (relativ zum Elternoverlay/Elternviewport)</param>
		/// <param name="fry">Relative Y-Position (relativ zum Elternoverlay/Elternviewport)</param>
		bool IsPicked(float frx, float fry);

		///<summary> L�dt ein� Overlaybeschreibung aus einem Vektoria-Overlayfile (.vo).</summary> 
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Backgrounds</param>
		void Load(CFileVektoria & filevektoria, int id);

		///<summary> Speichert eine Overlaybeschreibung in ein Vektoria-Overlayfile (.vo).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="bWithID">Soll die eigene Identifikationsnummer in das Backgroundfile mit abgespeichert werden?</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

		// -----------------
		// Member-Variablen:
		// -----------------

		///<summary> Pointer auf die Kinder-Overlays.</summary>
		COverlays * m_poverlays;

		///<summary> Flag, ob das Overlay im Inneren des Elternoverlays erscheinen soll. (Die Koordiaten oirientieren sich dann am Elternoverlay und nicht am Viewport).</summary>
		bool m_bInner;

		///<summary> Fraktionale Au�ma�e des Overlays bez�glich seines Viewports.</summary>
		CFloatRect m_floatrectGlobal;
	
		///<summary> Lokale Matrix.</summary>
		CHMat m_mLocal;

		///<summary> Globale Matrix.</summary>
		CHMat m_mGlobal;

	};

}