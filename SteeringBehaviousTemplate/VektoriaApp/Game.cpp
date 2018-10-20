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
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
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
	m_numberofboids =  5;
	for (size_t i = 0; i < m_numberofboids; i++)
	{
		Boid *aboid = new Boid();
		aboid->getKinematik()->orientierung = DEGREES_TO_RADIANS(180.f);
		aboid->getKinematik()->position = randomposition();
		aboid->setMaterial();
		m_boid.push_back(aboid);
	}

	m_numberoftargets = 1;
	for (size_t i = 0; i < m_numberoftargets; i++)
	{
		Boid *atarget = new Boid();
		atarget->getKinematik()->orientierung = DEGREES_TO_RADIANS(30.f);
		atarget->getKinematik()->position = randomposition();
		atarget->setMaterialTarget();
		m_target.push_back(atarget);
	}

	m_steeringbehaviourCharakter = new SteeringBehaviourKinematicSeek(&m_spielfeld);
	m_steeringbehaviourZiel = new SteeringBehaviourKinematicSeek(&m_spielfeld);
	m_steeringbehaviourCharakter->settarget(&m_target);

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
	// Hier die Echtzeit-Veränderungen einfügen:
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

	//Reset Boids + Targets
	if (m_zdKeyboard.KeyDown(DIK_R)) {
		for (size_t i = 0; i < m_boid.size(); i++) {
			m_boid[i]->reset(randomposition());
		}
		for (size_t i = 0; i < m_target.size(); i++) {
			m_target[i]->reset(randomposition());
		}
	}
	//SeekKine
	if (m_zdKeyboard.KeyDown(DIK_S)) {
		delete m_steeringbehaviourCharakter;
		m_steeringbehaviourCharakter = new SteeringBehaviourKinematicSeek(&m_spielfeld);
		m_steeringbehaviourCharakter->settarget(&m_target);
	}

	//FleeKine
	if (m_zdKeyboard.KeyDown(DIK_F)) {
		delete m_steeringbehaviourCharakter;
		m_steeringbehaviourCharakter = new SteeringBehaviourKinematicFlee(&m_spielfeld);
		m_steeringbehaviourCharakter->settarget(&m_target);
	}

	//ArriveKine
	if (m_zdKeyboard.KeyDown(DIK_A)) {
		delete m_steeringbehaviourCharakter;
		m_steeringbehaviourCharakter = new SteeringBehaviourKinematicArrive(&m_spielfeld);
		m_steeringbehaviourCharakter->settarget(&m_target);
	}


	//SeekDyna
	if (m_zdKeyboard.KeyDown(DIK_X)) {
		delete m_steeringbehaviourCharakter;
		m_steeringbehaviourCharakter = new SteeringBehaviourDynamicSeek(&m_spielfeld);
		m_steeringbehaviourCharakter->settarget(&m_target);
	}

	//FleeDyna
	if (m_zdKeyboard.KeyDown(DIK_Z)) {
		delete m_steeringbehaviourCharakter;
		m_steeringbehaviourCharakter = new SteeringBehaviourDynamicFlee(&m_spielfeld);
		m_steeringbehaviourCharakter->settarget(&m_target);
	}

	//ArriveDyna
	if (m_zdKeyboard.KeyDown(DIK_C)) {
		delete m_steeringbehaviourCharakter;
		m_steeringbehaviourCharakter = new SteeringBehaviourDynamicArrive(&m_spielfeld);
		m_steeringbehaviourCharakter->settarget(&m_target);
	}




	m_steeringbehaviourCharakter->Tick(fTime, fTimeDelta, m_boid.at(0));

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
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
	
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
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

