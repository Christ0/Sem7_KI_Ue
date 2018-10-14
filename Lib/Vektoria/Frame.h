#pragma once
#include "Viewports.h"
#include "ApiRender.h"
#include "ApiSound.h"
#include "ApiInput.h"
#include "ApiCyberglasses.h"
#include "DeviceKeyboard.h"
#include "DeviceMouse.h"
#include "DeviceGameController.h"
#include "DeviceVRControllers.h"
#include "DeviceCursor.h"
#include "DeviceHMD.h"


//------------------------------------------------------------------
// CFrame: Klasse f�r ein Betriebssystemfenster zur Anzeige von 3D-Daten
//
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschr�nkt) 
//-------------------------------------------------------------------



namespace Vektoria
{
	class CRoot;
	class CFrames;

	class CFrame: public CNode
	{
		friend class CRoot;
		friend class CHardwares;
		friend class CHardware;
		friend class CFrames;
	protected:
		// --------------
		// Basismethoden:
		// --------------

		///<summary> Wird vom �bergeordneten Knoten automatisch jedes Frame aufgerufen.</summary>
		///<param name= "iTick"> Angabe, um den wievielten Tick seit Spielbeginn es sich handelt </param>
		void Tick(int & iTick);

		///<summary> Setzt den Root-Pointer. �berladene Funktion.</summary>
		void SetRoot(CRoot* proot);
	public:
		///<summary> Konstruktor.</summary>
		CFrame();

		///<summary> Destuktor.</summary>
		~CFrame();

		///<summary> Kopieroperator des Frames.</summary>
		///<param name = "frame"> zu kopierender Frame</param>
		CFrame operator=(const CFrame & frame);

		///<summary> Kopiert die Daten von frame in den vorlegenden Frame.</summary>
		///<param name = "frame"> zu kopierender Frame</param>
		void Copy(const CFrame & frame);

		///<summary> Initaisiert den Frame.</summary>
		///<param name = "hwnd"> Handle auf das Window-Fenster (in der Template-Applikation einfach "hwnd" reinschreiben) </param>
		///<param name = "procOS"> Funktionspointer auf eine spezielle Callback-Routine des Betriebssystems (in der Template-Applikation einfach "procOS" reinschreiben!) </param>
		///<param name = "eApiRender"> Zu verwendende Render-API. 
		/// M�gliche Werte: <para></para>
		/// - eApiRender_DirectX11_Shadermodel41 (sinnvoll, wenn ein �lterer Rechner von ca. 2008/09 vorhanden ist)<para></para> 
		/// - eApiRender_DirectX11_Shadermodel50_Minimalistic (Shader mit den allerwichtigsten Funktionen, schnell aber h�sslich) <para></para>
		/// - eApiRender_DirectX11_Shadermodel50_Monolight (sollte erste Wahl sein, wenn nur ein Licht pro Szene vorhanden ist, schneller als Standard-Shader) <para></para>
		/// - eApiRender_DirectX11_Shadermodel50_MonolightAA (wie oben, nur mit Antialiasing) <para></para>		
		/// - eApiRender_DirectX11_Shadermodel50_Own (diese Option muss angeschaltet werden, wenn ein eigener Shader geschrieben werden soll) <para></para>
		/// - eApiRender_DirectX11_Shadermodel50_Standard (Defaultwert: Normaler DirectX11-Shader)<para></para> 
		/// - eApiRender_DirectX11_Shadermodel50_StandardAA (wie oben, nur mit Antialiasing)<para></para> 
		/// - eApiRender_Null (Renderbefehle laufen ins Leere, f�r Debugging-Zwecke sinnvoll) <para></para>
		/// - eApiRender_OpenGL_40 (OpenGL-Renderer, wird seit V14 nicht mehr unterst�tzt) </param>
		///<param name = "eApiInput"> Zu verwendende Input-API.<para></para> 
		/// M�gliche Werte: <para></para>
		/// - eApiInput_DirectInput (Defaultwert)<para></para>
		/// - eApiInput_Null (Input-Abfragen laufen ins leere, f�r Debugging-Zwecke sinnvoll)<para></para>
		/// - eApiInput_SDL</param>
		///<param name = "eApiSound"> Zu verwendende Sound-API. <para></para>
		/// M�gliche Werte: <para></para>
		/// - eApiSound_DirectSound (Defaultwert) <para></para>
		/// - eApiSound_Null (Soundbefehle laufen ins Leere, f�r Debugging-Zwecke sinnvoll) <para></para>
		/// - eApiSound_OpenAL (veraltete OpenAL-Sound-API, wird seit V14 nicht mehr unterst�tzt) <para></para>
		/// - eApiSound_XAudio2 (in Arbeit) </param>
		///<param name = "eApiCyberglasses"> Zu verwendende API f�r Oculus Rift, HTCVive, HoloLens und andere HMDs. <para></para>
		/// M�gliche Werte: <para></para>
		/// - eApiCyberglasses_None (falls keine Videobrille angeschlossen werden soll) <para></para>
		/// - eApiCyberglasses_Own (falls man seine eigene Schnittstelle programmieren will) <para></para>
		/// - eApiCyberglasses_OpenVR (Beste Schnittstelle f�r HMDs) <para></para>
		/// - eApiCyberglasses_Null (VR-Befehle laufen ins Leere, f�r Debugging-Zwecke sinnvoll) </param>
		///<param name = "eShaderCreation"> Wann soll der Shader kompiliert werden? <para></para>
		/// M�gliche Werte: <para></para>
		/// - eShaderCreation_CompileChanges (Es soll nur bei Shaderver�nderungen compiliert werden, Achtung, vor dieser Einstellung Backups der kompilierten Shader machen!) <para></para>
		/// - eShaderCreation_ForceCompile (Es soll immer kompiliert werden. Achtung, vor dieser Einstellung Backups der kompilierten Shader machen!) <para></para>
		/// - eShaderCreation_UseCached (Es sollen die vorkompilierten Shader verwendet werden, Defaultwert) </param>
		///<param name = "eShaderAutoRecompilation"> Soll der Shader auch w�hrend der Laufzeit kompiliert werden? <para></para>
		/// M�gliche Werte: <para></para>
		/// - eShaderAutoRecompilation_Disabled (Defaultwert, Es sollen nur bei Programmstart kompiliert werden)<para></para> 
		/// - eShaderAutoRecompilation_Enabled (Der Shader soll auch w�hrend der Laufzeit kompiliert werden) </param>
		void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), EApiRender eApiRender = eApiRender_DirectX11_Shadermodel50_Standard, EApiInput eApiInput = eApiInput_DirectInput, EApiSound eApiSound = eApiSound_DirectSound, EApiCyberglasses eApiCyberglasses = eApiCyberglasses_None, EShaderCreation eShaderCreation = eShaderCreation_UseCached, EShaderAutoRecompilation eShaderAutoRecompilation = eShaderAutoRecompilation_Disabled);

		///<summary> Schaltet Fullscreen an.</summary>
		void SetFullscreenOn(); 

		///<summary> Schaltet Fullscreen aus.</summary>
		void SetFullscreenOff(); 

		///<summary> Beendet den Frame.</summary>
		void Fini(); 

		///<summary> Erzeugt das Frame (wird normalerweise automatisch aufgerufen).</summary>
		void Create(); 

		///<summary> Setzt die Hintergrundsfarbe des Frames.<para></para>
		/// Achtung! Sollte m�glichst nur einmal vor dem Init des Frames aufgerufen werden, oder bei einmaligen Umschaltprozessen, da sehr langsam (ca. 30 ms) .</summary>
		///<param name = "color"> Hintergrundfarbe in RGB (jeweilige RGB-Werte zwischen 0 und 1) </param>
		void SetColorBackground(CColor color);

		///<summary> H�ngt einen Viewport an das Frame.</summary>
		///<param name = "pviewport"> Pointer auf den anzuh�ngenden Viewport</param>
		void AddViewport(CViewport * pviewport);

		///<summary> H�ngt eine Tastatur an das Frame.</summary>
		///<param name = "pdevicekeyboard"> Pointer auf die anzuh�ngende Tastatur</param>
		void AddDeviceKeyboard(CDeviceKeyboard * pdevicekeyboard);

		///<summary> H�ngt eine Maus an das Frame, nicht zu verwechseln mit dem Cursor!</summary>
		///<param name = "pdevicemouse"> Pointer auf die anzuh�ngende Tastatur</param>
		void AddDeviceMouse(CDeviceMouse * pdevicemouse);

		///<summary> H�ngt einen Gamecontroller (Joystick, Lenkrad, Gamepad, Tanzplatte, ...) an das Frame.</summary>
		///<param name = "pdevicegamecontroller"> Pointer auf den anzuh�ngenden Gamecontroller</param>
		void AddDeviceGameController(CDeviceGameController * pdevicegamecontroller);

		///<summary> H�ngt einen Mauszeiger (Cursor) an das Frame.</summary>
		///<param name = "pdevicecursor"> Pointer auf den anzuh�ngenden Cursor</param>
		void AddDeviceCursor(CDeviceCursor * pdevicecursor);

		///<summary> H�ngt ein Spezialcontroller f�r ein Head Mounted Display (HMD) an das Frame.</summary>
		///<param name = "pdevicevrcontroller"> Pointer auf den anzuh�ngendenSpezialcontroller</param>
		void AddDeviceVRController(CDeviceVRController * pdevicevrcontroller);

		///<summary> H�ngt ein Spezialcontroller f�r ein Head Mounted Display (HMD) an das Frame.</summary>
		///<param name = "pdevicevrcontroller"> Pointer auf den anzuh�ngendenSpezialcontroller</param>
		void AddDeviceHMD(CDeviceHMD * pdevicehmd);

		///<summary> Sollte stets aufgerufen werden, wenn die Fenstergr��e des Windows sich ver�ndert hat.</summary>
		///<param name = "iWidthWindow"> Neue Breite in Pixel</param>
		///<param name = "iHeightWindow"> Neue H�he in Pixel</param>
		void ReSize(int iWidthWindow, int iHeightWindow);

		///<summary> Ruft Fortschrittsanzeiger (Progress-Bar) ins Leben. Wird bei Start von Vektoria automatisch aufgerufen</summary>
		///<param name = "iFrames"> Anzahl der Frames in der Szenengraf-Hierarchie</param>
		///<param name = "iViewports"> Anzahl der Viewports in der Szenengraf-Hierarchie</param>
		///<param name = "iGeos"> Anzahl der Geometrien in der Szenengraf-Hierarchie</param>
		///<param name = "iMaterials"> Anzahl der Materialien in der Szenengraf-Hierarchie</param>
		///<param name = "iAudios"> Anzahl der Sounds in der Szenengraf-Hierarchie</param>
		void InitBar(int iFrames, int iViewports, int iGeos, int iMaterials, int iAudios);
		
		///<summary> Sendet ein Fortschritts-Event an die Progress-Bar.</summary>
		///<param name = "acNode"> An procOS codierter ASCII-Befehl</param>
		void TickBar(char acNode);

		///<summary> Schlie�t den Fortschrittsanzeiger (Progress-Bar).</summary>
		void FiniBar(); 

		///<summary> L�dt eine Framebeschreibung aus einem Vektoria-Framefile (.vf).</summary> 
		///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
		///<param name= "id"> Die eigene Knoten-ID</param>
		void Load(CFileVektoria & filevektoria, int id);

		///<summary> Speichert eine Framebeschreibung in ein Vektoria-Framefile (.vf).</summary> 
		///<param name= "filfektoria"> Vorinitialisiertes Vektoria-File</param>
		///<param name= "bWithID"> Flag, ob die eigene Knoten-ID mit abgespeichert werden soll</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);

		///<summary> Erzeugt die untergeordneten Viewports, wird normalerweise automatisch vom �bergeordneten Knoten aufgerufen.</summary>
		void CreateViewports();

		///<summary> Setzt die eigene IP-Addresse (wird automatisch aufgerufen, aus Performanzgr�nden redundant zur �bergeordeter Hardware).</summary>
		///<param name= "acAddress"> Die eigene IP-4-Adresse</param>
		void SetIP(char * acAddress);

		///<summary> Setzt die eigenen Hostnamen (wird automatisch aufgerufen, aus Performanzgr�nden redundant zur �bergeordeter Hardware).</summary>
		///<param name= "ac"> Der eigene Hostname</param>
		void SetHostName(char * ac);

		// -----------------
		// Member-Variablen:
		// -----------------

		///<summary> Funktionsvariable einer Callback-Funktion des Betriebssystems.</summary>
		void(*m_procOS)(HWND hwnd, unsigned int uWndFlags);

		///<summary> Liste der angeh�ngten Viewports</summary>
		CViewports m_viewports;		

		///<summary> Art der Render-Api</summary>
		EApiRender m_eApiRender;

		///<summary> Art der Input-Api</summary>
		EApiInput m_eApiInput;

		///<summary> Art der Sound-Api</summary>
		EApiSound m_eApiSound;

		///<summary> Art der Api f�r HMDs</summary>
		EApiCyberglasses m_eApiCyberglasses;

		///<summary> Art der Shadererzeugung</summary>
		EShaderCreation m_eShaderCreation;

		///<summary> Art des Shadererzeugungzeitpunktes</summary>
		EShaderAutoRecompilation m_eShaderAutoRecompilation;

		///<summary> Pointer zur Render-Api.</summary>
		CApiRender* m_papirender;	

		///<summary> Pointer zur Input-Api.</summary>
		CApiInput* m_papiinput;

		///<summary> Pointer zur Sound-Api.</summary>
		CApiSound* m_papisound;	

		///<summary> Pointer zur Api f�r Head Mounted Displays (Oculus Rift, HTC Vive, HoloLens, etc.).</summary>
		CApiCyberglasses* m_papicyberglasses;

		///<summary> Breite des Frames in Pixel.</summary>
		int m_iWidthWindow;			

		///<summary> H�he des Frames in Pixel</summary>
		int m_iHeightWindow;		

		///<summary> Flag, ob Fullscreen-Modus angeschaltet ist</summary>
		bool m_bFullscreen;			

		///<summary> Farbe des Frame-Hintergrundes (Default = Blau).</summary>
		CColor m_colorBackground;

		///<summary> Win32 window handle. (TODO: Keine OS-spezifischen Veriablen im Core, f�r sp�tere Linux-Variante!!!)</summary>
		HWND m_hwnd;				

		///<summary> Pointer zum Cursor.</summary>
		CDeviceCursor* m_pdevicecursor; 

		///<summary> Pointer zu den VR-Controllerliste.</summary>
		CDeviceVRControllers * m_pdevicevrcontrollers;

		///<summary> Pointer zum Head Mounted Display.</summary>
		CDeviceHMD * m_pdevicehmd;

		///<summary> IP-Adresse des mit dem Frame verbundenen Computers.</summary>
		char m_acIPAddress[100]; 

		///<summary> Hostname des mit dem Frame verbundenen Computers .</summary>
		char m_acHost[100]; 

		///<summary> true, wenn Frame auf einem Remote-Computer liegt und nur durch das Verteilte Rendering angesprochen wird</summary>
		bool m_bDistributed; 

		///<summary> Flag, ob Antialiasingshader ausgew�hlt wurde</summary>
		bool m_bAntialiasing;

		///<summary> Flag, ob der Frame schon erzeugt wurde</summary>
		bool m_bCreated; 

protected:
		bool m_bFirstTick;
		unsigned int m_uWndFlags;
		HINSTANCE  m_hinstLibDistri;
		HINSTANCE  m_hinstLibInput;
		HINSTANCE  m_hinstLibRender;
		HINSTANCE  m_hinstLibSound;
		HINSTANCE  m_hinstLibCyberglasses;


	};
}