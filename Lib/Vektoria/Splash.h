#pragma once
#include "Windows.h"

//------------------------------------------------------
// CSplash: Klasse für ein Splash-Fenster für MS Windows
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------

namespace Vektoria
{


	class CSplash
	{
		friend class CRoot;
	public:
		///<summary> Konstruktor.</summary>
		CSplash();

		///<summary> Destruktor.</summary>
		virtual ~CSplash();

		///<summary> Initialisierung des Splash-Screens.</summary>
		///<param name="hwnd">Handle auf das Window</param>
		///<param name="hinstance">Handle auf die Instanz</param>
		void Init(HWND hwnd, HINSTANCE hinstance);

		///<summary> Zeigt den Fortschritsanzeiger is einer speziellen Länge an.</summary>
		///<param name="frProgress">Fortschritt (0.0 = 0% ... 0.5 = 50% ... 1.0 = 100%) </param>
		void ShowProgressBar(float frProgress);

		///<summary> Versteckt den Fortschritsanzeiger wieder.</summary>
		void HideProgressBar();

		///<summary> Deaktiviert den Fortschritsanzeiger komplett, jeglicher Show-Methodenaufruf bleibt danach ohne Wirkung.</summary>
		void DeactivateProgressBar();

		///<summary> Aktiviert den Fortschritsanzeiger (Default).</summary>
		void ActivateProgressBar();

		///<summary> Zeigt den Vektoria Splash-Screen. </summary>
		void Show();

		///<summary> Versteckt den Splash-Screen. Darf aus Schutzgründen für die Vektoria-Crew nur automatisch von der Root aufgerufen werden, sonst funktioniert das System nicht mehr.</summary>
		void Hide();

		//------------------
		// Membervariablen:
		//------------------


		///<summary> Flag, ob Splash-Scrren gerade gezeigt wird. </summary>
		bool m_bShow;

		///<summary> Flag, ob Fortschrittsanzeiger gerade gezeigt wird. </summary>
		bool m_bShowProgressBar;

		///<summary> Flag, ob Fortschrittsanzeiger gerade deaktiviert ist. </summary>
		bool m_bProgressBarDeactivated;

		///<summary> Horizontale Pixelanzahl des Splash-Screens. </summary>
		int m_ixSplash;
		
		///<summary> Vertikale Pixelanzahl des Splash-Screens. </summary>
		int m_iySplash;

		///<summary> Horizontale Pixelanzahl des Elternfensters. </summary>
		int m_ixFather;
		
		///<summary> Vertikale Pixelanzahl des Elternfensters. </summary>
		int m_iyFather;

		///<summary> Horizontale Pixelanzahl des Gesamtfensters. </summary>
		int m_iWidth;
		
		///<summary> Vertikale Pixelanzahl des Gesamtfensters. </summary>
		int m_iHeight;

		///<summary> Ausmaße des Elternfensters. </summary>
		RECT m_rectFather;

	private:
		int CalcKey(char * szPath);

		UINT m_idTimer;
		HWND m_hwnd;
		HINSTANCE m_hinstance;
		HWND m_hwndParent;
		HWND m_hwndSplash;
		HWND m_hwndProgressBar;
		bool m_bShowed;
		int m_idInit;
		int m_idShow;

	};

}