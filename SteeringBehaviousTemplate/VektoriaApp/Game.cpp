#include "StdAfx.h"
#include "Game.h"

CGame::CGame(void)
{

}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einf�gen:
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	m_zf.Init(hwnd, procOS);
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(5.0f, 5.0f, 3.0f), CColor(1.0f, 1.0f, 1.0f));

	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zf.AddDeviceKeyboard(&m_zdKeyboard);

	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);

	m_zpCamera.RotateXDelta(DEGREES_TO_RADIANS(-45));
	m_zpCamera.TranslateYDelta(150.0f);
	m_zpCamera.TranslateZDelta(150.0f);

	srand(timeGetTime());
	
	//KI Objekte
	m_numberofboids =  50;
	for (size_t i = 0; i < m_numberofboids; i++)
	{
		Boid *aboid = new Boid();
		aboid->getKinematik()->orientierung = DEGREES_TO_RADIANS(180.f);
		aboid->getKinematik()->position = randomposition();
		aboid->setMaterial();
		m_boid.push_back(aboid);
	}

	m_numberoftargets = 10;
	for (size_t i = 0; i < m_numberoftargets; i++)
	{
		Boid *atarget = new Boid();
		atarget->getKinematik()->orientierung = DEGREES_TO_RADIANS(30.f);
		atarget->getKinematik()->position = randomposition();
		atarget->setMaterialTarget();
		m_target.push_back(atarget);
	}

	m_steeringbehaviourCharakter = new SteeringBehaviour(&m_spielfeld);
	m_steeringbehaviourZiel = new SteeringBehaviour(&m_spielfeld);

	for (size_t i = 0; i < m_boid.size(); i++)
	{
		m_zs.AddPlacement(m_boid[i]->getPlacement());
	}

	for (size_t i = 0; i < m_target.size(); i++)
	{
		m_zs.AddPlacement(m_target[i]->getPlacement());
	}

	m_zs.AddPlacement(m_spielfeld.getPlacement());

	m_SB_Mode = DYNAMIC;

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Ver�nderungen einf�gen:
	m_zr.Tick(fTimeDelta);

	m_spielfeld.Tick(fTime, fTimeDelta);

	for (size_t i = 0; i < m_boid.size(); i++)
	{
		m_boid[i]->Tick(fTime, fTimeDelta);
	}

	for (size_t i = 0; i < m_target.size(); i++)
	{
		m_target[i]->Tick(fTime, fTimeDelta);
	}

	//Interface
	this->keyboardUI();
}

CHVector CGame::randomposition(){
	int x = m_spielfeld.getDimension()->x;
	int z = m_spielfeld.getDimension()->z;
	return CHVector(rand() % (2 * x) - x, 0, rand() % (2 * z) - z);
}

void CGame::keyboardUI(){
	//Reset Charakters
	
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einf�gen:
	
	for (size_t i = 0; i < m_boid.size(); i++)
	{
		delete m_boid[i]; 
	}

	for (size_t i = 0; i < m_target.size(); i++)
	{
		delete m_target[i];
	}
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergr��e ver�ndert wurde.
	// Hier kannst Du dann die Aufl�sung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}
