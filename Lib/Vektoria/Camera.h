#pragma once
#include "Node3D.h"
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Frustum.h"
#include "FileVektoria.h"

//------------------------------------------------------------------
// CCamera: Klasse f�r eine Kamera
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//-------------------------------------------------------------------

namespace Vektoria
{

	class CPlacement;
	class CViewports;

	class CCamera : public CNode3D
	{
		friend class CPlacement;
		friend class CCameras;
	public:
		///<summary> Konstruktor.</summary>
		CCamera();

		///<summary> Destuktor.</summary>
		~CCamera();

		/// <summary>Zuweisungsoperator.</summary>
		/// <param name= "camera"> Die zu kopierende Kamera </param>
		CCamera operator=(CCamera & camera);

		/// <summary>Kopiert die Kameradaten von camera in die vorliegende Kamera. </summary>
		/// <param name= "camera"> Die zu kopierende Kamera </param>
		void Copy(CCamera & camera);

		/// <summary>Initalisiert eine Kamera.</summary>
		/// <param name= "faFovHorizontal"> Horizontaler Kamera�ffnungswinkel im Bogenma�, der vertikale �ffnungswinkel wird automatisch daraus berechnet. </param>
		/// <param name= "fNearClipping"> Abstand der vorderen Clippingebene des Kamera-Frustums in Units (ab welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		/// <param name= "fFarClipping"> Abstand der hinteren Clippingebene des Kamera-Frustums in Units (bis zu welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		void Init(float faFovHorizontal = 2.0F, float fNearClipping = 0.1F, float fFarClipping = 30000.0F);

		/// <summary>Initalisiert eine Kamera mit dedizierter Angabe von horizontalem und vertikalem Kamera�ffnungswinkel.</summary>
		/// <param name= "faFovHorizontal"> Horizontaler Kamera�ffnungswinkel im Bogenma� </param>
		/// <param name= "faFovVertical"> Vertikaler Kamera�ffnungswinkel im Bogenma� </param>
		/// <param name= "fNearClipping"> Abstand der vorderen Clippingebene des Kamera-Frustums in Units (ab welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		/// <param name= "fFarClipping"> Abstand der hinteren Clippingebene des Kamera-Frustums in Units (bis zu welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		void InitRatioFixed(float faFovHorizontal = HALFPI, float faFovVertical = HALFPI, float fNearClipping = 0.1F, float fFarClipping = 30000.0F);

		/// <summary>Initalisiert eine orthogonale Kamera (Kamera mit Parallelprojektion).</summary>
		/// <param name= "fOrthoScalingHorizontal"> Breite der Parallelprojektion in Units, die H�he wird automatisch daraus berechnet. </param>
		/// <param name= "fNearClipping"> Abstand der vorderen Clippingebene des Kamera-Frustums in Units (ab welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		/// <param name= "fFarClipping"> Abstand der hinteren Clippingebene des Kamera-Frustums in Units (bis zu welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		void InitOrtho(float fOrthoScalingHorizontal = 100.0F, float fNearClipping = 0.1F, float fFarClipping = 30000.0F);

		/// <summary> Deinitalisiert die Kamera.</summary>
		void Fini();

		///<summary> Berechnet die Axis Aligned Bounding Boxen neu.</summary>
		virtual void UpdateAABB();

		///<summary> Rechnet die homogene Projektionsmatrix der Kamera aus, wird automatisch aufgerufen, wenn notwendig.</summary>
		void CalcMat();

		///<summary> Schaltet die spiegelverkehrte Aufnahme an (sinnvoll z.B. f�r R�ckspiegel).</summary>
		void SetMirrorOn();

		///<summary> Schaltet die spiegelverkehrte Aufnahme wieder aus.</summary>
		void SetMirrorOff();

		///<summary> Setzt die Projektionmatrix der Kamera, sie wird dann nicht mehr explizit ausgerechnet.</summary>
		///<param name = "fOrthoScalingHorizontal"> horizontaler Skalierungsfaktor in Units</param>
		void SetMatProjection(CHMat mProjection);

		///<summary> Schaltet die Kamera in den Othogonalprojektionsmodus und gibt gleichzeitig den horizontalen Skalierungsfaktor an.</summary>
		///<param name = "fOrthoScalingHorizontal"> horizontaler Skalierungsfaktor in Units</param>
		void SetOrtho(float fOrthoScalingHorizontal);

		///<summary> Setzt den horizontalen Skalierungsfaktor bei orthogonalen Kameras.<para></para>
		/// Der vertikale Skalierungsfaktor wird daraus automatisch berechnet. <para></para>
		/// Die Methdoe hat bei Fov-Kameras keine Wirkung.</summary>
		///<param name = "fOrthoScalingHorizontal"> horizontaler Skalierungsfaktor in Units</param>
		void SetOrthoScaling(float fOrthoScalingHorizontal); 

		///<summary> Gibt den orthogonalen Skalierungsfaktor aus</summary>
		float GetOrthoScaling();

		/// <summary> Setzt den Kameraabstand der vorderen Schnittebene des Sichtpyramidenstumpfes.</summary> 
		/// <param name= "fNearClipping"> Abstand der vorderen Clippingebene des Kamera-Frustums in Units (ab welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		void SetNearClipping(float fNearClipping);

		/// <summary> Setzt den Kameraabstand der hinteren Schnittebene des Sichtpyramidenstumpfes.</summary>
		/// <param name= "fFarClipping"> Abstand der hinteren Clippingebene des Kamera-Frustums in Units (bis zu welcher Entfernung von der Kamera werden die Objekte gerendert)</param>
		void SetFarClipping(float fFarClipping);

		/// <summary> Schaltet die Kamera in den Othogonalprojektionsmodus (=Parallelprojektion).</summary>
		void SetOrthoOn();

		/// <summary> Schaltet die Kamera wieder in den normalen fovealen Projektionsmodus (default).</summary>
		void SetOrthoOff();

		/// <summary> Setzt den Fokussierungsabstand (Abstand der maximalen Kamerasch�rfe). <para></para>
		/// Wirkt sich nur aus, wenn Kameratiefenunsch�rfe (Depth Blur) in entsprechendem Viewport angeschaltet ist. </summary> 
		/// <param name= "fFocalDistance"> Fokussierungsabstand (Abstand der besten Kamerasch�rfe in Units) </param>
		void SetFocalDistance(float fFocalDistance);

		/// <summary> Setzt den horizontalen Kamera�ffnungswinkel. Der Vertikale wird daraus automatisch berechnet.</summary> 
		/// <param name= "faFovHorizontal"> Horizontaler Kamera�ffnungswinkel im Bogenma� </param>
		void SetFov(float faFovHorizontal);

		/// <summary> Setzt den horizontalen und den vertikalen Kamera�ffnungswinkel. Falls die Kamera in Ortho-Modus sein sollte, swird in in den Fov-Modus zur�ckgeschaltet.</summary> 
		/// <param name= "faFovHorizontal"> Horizontaler Kamera�ffnungswinkel im Bogenma� </param>
		/// <param name= "faFovVertical"> Vertikaler Kamera�ffnungswinkel im Bogenma� </param>
		void SetFov(float faFovHorizontal, float faFovVertical);

		/// <summary> Gibt den horizontalen Kamera�ffnungswinkel im Bogenma� aus.</summary>
		float GetFovHorizontal();

		/// <summary> Gibt den vertikalen Kamera�ffnungswinkel im Bogenma� aus.</summary>
		float GetFovVertical();

		/// <summary> Gibt den Kameraabstand der vorderen Schnittebene des Sichtpyramidenstumpfes aus.</summary>
		float GetNearClipping();

		/// <summary> Gibt den Kameraabstand der hinteren Schnittebene des Sichtpyramidenstumpfes aus.</summary>
		float GetFarClipping();

		/// <summary> Erzeugt einen Sichtstrahl im View Frustum der Kamera.</summary>
		/// <param name= "frx"> Fraktionaler Anteil der Strahlposition zwischen linker und rechter Klippingebene des Frustums (links = 0.0 ... rechts = 1.0)</param>
		/// <param name= "fry"> Fraktionaler Anteil der Strahlposition zwischen oberer und unterer Klippingebene des Frustums (oben = 0.0 ... unten = 1.0)</param>
		/// <param name= "r"> Berechneter Strahl</param>
		void CalcRay(float frx, float fry, CRay & r);

		/// <summary> Berechnet Sichtpyramidenstumpf der Kamera. </summary> 
		void CalcFrustum();

		/// <summary> Gibt die angezeigte Szene aus.</summary> 
		CScene * GetScene();

		/// <summary> L�dt die Daten aus einem Vektoria-Kamerafile (.vc).</summary> 
		///<param name="acPath">ASCII-Pfadangabe der Audiodatei (mit Suffix), absolute und relative Pfade sind m�glich, z.B. "C:\\MyCamera.vc" oder ".\\Cameras\\MyCamera.vc" </param>
		void Load(char * acPath);

		/// <summary> Speichert die Daten in ein Vektoria-Kamerafile (.vc).</summary> 
		///<param name="acPath">ASCII-Pfadangabe der Audiodatei (mit Suffix), absolute und relative Pfade sind m�glich, z.B. "C:\\MyCamera.vc" oder ".\\Cameras\\MyCamera.vc" </param>
		void Save(char * acPath);

	protected:
	
		/// <summary> L�dt die Daten aus einem Vektoria-Kamerafile (.vc).</summary> 
		/// <param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
		/// <param name= "bWithID"> Die eigene Knoten-ID, -1 falls keine ID mit abgespeichert werden soll</param>
		/// <param name="fVersion">Vektoriaversion, um Aufw�rtskombabilit�t zu gew�hrleisten, z.B. 14.11 f�r die Version 14 Patch 11 </param>
		void Load(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

		/// <summary> Speichert die Daten in ein Vektoria-Kamerafile (.vc).</summary> 
		/// <param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
		/// <param name= "bWithID"> Flag, ob die eigene Konten-ID mit abgespeichert werden soll</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

		///<summary> Wird vom �bergeordneten Knoten automatisch jedes Frame aufgerufen.</summary>
		/// <param name= "m"> Globale Matrix des �bergeordneten Knotens </param>
		/// <param name= "iTick"> Angabe, um den wievielten Tick seit Spielbeginn es sich handelt </param>
		void Tick(CHMat & m, int & iTick);

	public:
		//------------------
		// Member-Variablen:
		//------------------

		// Kamerasichtpyramidenstumpf (TODO f�r V15: Es muss eigentlich f�r jede Kamerainstanz ein eigenes Frustum geben, sonst kkann eine Kamera keine zwei verschiedenen Eltern haben!)
		CFrustum m_frustum;

		// Die von der Kamera angezeigte Szene (muss Pointer sein, da ansonsten Kreuzinkluding)
		CScene * m_pscene;

		// Die konnektierten Viewports (muss Pointer sein, da ansonsten Kreuzinkluding)
		CViewports * m_pviewports;

		// Projektionsmatrix der Kamera
		CHMat m_mProjection;

		// Wenn true (default), wird der vertikale Kamera�ffnungswinkel (m_faFovVertical) aus dem hoizontalen Kamera�ffnungswinkel (m_faFovHorizontal) und dem Verzerrungsverh�ltnis (m_fViewportAspectRatio) berechnet, ansonsten muss vertikale dediziert angegeben werden 
		bool m_bCalcFovVertical;

		// Horizontaler Kamera�ffnungswinkel (vertikaler wird normalerwiese aus horizontaler Kamera�ffnungswinkel7Verzerrungsverh�ltnis berechnet), bei orthogonaler Kamera ist es der horizontale Skalierungsfaktor
		float m_faFovHorizontal;

		// Vertikaler Kamera�ffnungswinkel (vertikaler wird aus horizontaler Kamera�ffnungswinkel7Verzerrungsverh�ltnis berechnet), bei orthogonaler Kamera ist es der horizontale Skalierungsfaktor
		float m_faFovVertical;

		// Seitenverh�ltnis des Viewports, welcher die Kamerasicht anzeigt.
		float m_fViewportAspectRatio;

		// Abstand zwischen der Kamera und der vorderen Schnittebene des Sichtpyramidenstumpfes.
		float m_fNearClipping;

		// Abstand zwischen der Kamera und der hinteren Schnittebene des Sichtpyramidenstumpfes.
		float m_fFarClipping;

		// Flag, true, wenn es sich um eine orthogonale Kamera handelt, ansonsten ist es eine normale Fov-Projektionskamera.
		bool m_bOrtho;

		// Horizontaler Skalierungsfaktor bei orthogonalen Kameras.
		float  m_fOrthoScalingHorizontal;

		// Flag, das anzeigt, ob die Kamera die Szene spiegelverkehrt anzeigen soll.
		bool m_bMirror;

		// Fokussierungsabstand der Kamera.
		float m_fFocalDistance;

		// True, falls die Projektionsmatrix extern gesetzt wird.
		float m_bMatProjectionExternal;


	};

}