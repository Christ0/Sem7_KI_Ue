//#pragma once
//
//
//#ifdef _WIN64
//#ifdef _DEBUG
//#pragma comment (lib, "Vektoria_Debug64.lib")
//#pragma comment (lib, "VektoriaMath_Debug64.lib")
//#pragma comment (lib, "ApiUtils_Debug64.lib")
//#pragma comment (lib, "ApiNullRenderer_Debug64.lib")
//#pragma comment (lib, "ApiDirectX11Basic_Debug64.lib")
//#pragma comment (lib, "ApiDirectInput08_Debug64.lib")
//#pragma comment (lib, "ApiDirectX11FP_Debug64.lib")
//#pragma comment (lib, "ApiOpenGL40_Debug64.lib")
//#pragma comment (lib, "ApiNullSound_Debug64.lib")
//#pragma comment (lib, "ApiDirectSound_Debug64.lib")
//#pragma comment (lib, "ApiRenderDistributed_Debug64.lib")
//#else
//#pragma comment (lib, "Vektoria_Release64.lib")
//#pragma comment (lib, "VektoriaMath_Release64.lib")
//#pragma comment (lib, "ApiUtils_Release64.lib")
//#pragma comment (lib, "ApiNullRenderer_Release64.lib")
//#pragma comment (lib, "ApiDirectX11Basic_Release64.lib")
//#pragma comment (lib, "ApiDirectInput08_Release64.lib")
//#pragma comment (lib, "ApiDirectX11FP_Release64.lib")
//#pragma comment (lib, "ApiOpenGL40_Release64.lib")
//#pragma comment (lib, "ApiNullSound_Release64.lib")
//#pragma comment (lib, "ApiDirectSound_Release64.lib")
//#pragma comment (lib, "ApiRenderDistributed_Release64.lib")
//#endif
//#else
//#ifdef _DEBUG
//#pragma comment (lib, "Vektoria_Debug.lib")
//#pragma comment (lib, "VektoriaMath_Debug.lib")
//#pragma comment (lib, "ApiUtils_Debug.lib")
//#pragma comment (lib, "ApiNullRenderer_Debug.lib")
//#pragma comment (lib, "ApiDirectX11Basic_Debug.lib")
//#pragma comment (lib, "ApiDirectInput08_Debug.lib")
//#pragma comment (lib, "ApiDirectX11FP_Debug.lib")
//#pragma comment (lib, "ApiOpenGL40_Debug.lib")
//#pragma comment (lib, "ApiNullSound_Debug.lib")
//#pragma comment (lib, "ApiDirectSound_Debug.lib")
//#pragma comment (lib, "ApiRenderDistributed_Debug.lib")
//#else
//#pragma comment (lib, "Vektoria_Release.lib")
//#pragma comment (lib, "VektoriaMath_Release.lib")
//#pragma comment (lib, "ApiUtils_Release.lib")
//#pragma comment (lib, "ApiNullRenderer_Release.lib")
//#pragma comment (lib, "ApiDirectX11Basic_Release.lib")
//#pragma comment (lib, "ApiDirectInput08_Release.lib")
//#pragma comment (lib, "ApiDirectX11FP_Release.lib")
//#pragma comment (lib, "ApiOpenGL40_Release.lib")
//#pragma comment (lib, "ApiNullSound_Release.lib")
//#pragma comment (lib, "ApiDirectSound_Release.lib")
//#pragma comment (lib, "ApiRenderDistributed_Release.lib")
//#endif
//#endif
#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif

#include "Spielfeld.h"
#include "Boid.h"
#include "SteeringBehaviour.h"
#include "SteeringBehaviourKinematicSeek.h"
#include "SteeringBehaviourKinematicFlee.h"
#include "SteeringBehaviourKinematicArrive.h"
#include "SteeringBehaviourDynamicSeek.h"
#include "SteeringBehaviourDynamicFlee.h"
#include "SteeringBehaviourDynamicArrive.h"
#include "SteeringBehaviourDynamicWander.h"

#include "Vektoria\Root.h"

using namespace Vektoria;


class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat

	enum SB_Mode { KINEMATIC, DYNAMIC };
private:
    //Vektoriaobjekte:
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	
 
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CLightParallel m_zl;

	CDeviceKeyboard m_zdKeyboard;

	//KI Klassen
	Spielfeld m_spielfeld;
	int m_numberofboids;
	int m_numberoftargets;

	std::vector<Boid*> m_boid;
	std::vector<Boid*> m_target;

	SteeringBehaviour *m_steeringbehaviourCharakter; //Bewegung im Spielfeld
	SteeringBehaviour *m_steeringbehaviourZiel; //Bewegung im Spielfeld

	SB_Mode m_SB_Mode;

	void keyboardUI();
	CHVector randomposition();

};


