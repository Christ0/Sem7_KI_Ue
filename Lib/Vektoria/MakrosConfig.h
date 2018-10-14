#pragma once

///<summary> Makro, um eine Videobrille zu betreiben. <para></para> 
/// Muss in den Header der Klasse CGame geschrieben werden.</summary>
#define CONF_HMD_H \
CRoot m_zr; \
CFrame m_zf; \
CDeviceVRController m_zdv1; \
CDeviceVRController m_zdv2; \
CPlacement m_zpController1; \
CPlacement m_zpController2; \
CDeviceHMD m_zdh; \
CViewport m_zvLeft; \
CViewport m_zvRight; \
CScene m_zs; \
CCamera m_zcLeft; \
CCamera m_zcRight; \
CPlacement m_zpHMD; \
CPlacement m_zpCamera; \
CPlacement m_zpCameraLeft; \
CPlacement m_zpCameraRight; \
CGeos m_zgsCollisionItems; \
float m_fNearClipping = 0.0f; \
float m_fFarClipping = 0.0f; 


///<summary> Makro, um eine Videobrille zu betreiben. <para></para> 
/// Muss in die Init-Routine der Klasse CGame geschrieben werden.</summary>
///<param name = "d_fNearClipping"> Abstand der vorderern Sichschnittebene (Near Clipping Plane des View Frustums) in Units. <para></para>
/// Muss vom Typ float sein. </param>
///<param name = "d_fFarClipping"> Abstand der hinteren Sichschnittebene (Far Clipping Plane des View Frustums) in Units. <para></para>
/// Muss vom Typ float sein. </param>
#define CONF_HMD_INIT(d_fNearClipping,d_fFarClipping) \
m_zr.Init(psplash); \
m_fNearClipping = d_fNearClipping; \
m_fFarClipping = d_fFarClipping; \
m_zr.AddFrame(&m_zf); \
m_zf.AddDeviceVRController(&m_zdv1); \
m_zf.AddDeviceVRController(&m_zdv2); \
m_zf.AddDeviceHMD(&m_zdh); \
m_zf.AddViewport(&m_zvLeft); \
m_zf.AddViewport(&m_zvRight); \
m_zf.Init(hwnd, procOS, eApiRender_DirectX11_Shadermodel50_Standard, eApiInput_DirectInput, eApiSound_DirectSound, eApiCyberglasses_OpenVR); \
m_zvLeft.Init(&m_zcLeft, CFloatRect(0.02, 0.05, 0.48, 0.91)); \
m_zvRight.Init(&m_zcRight, CFloatRect(0.5, 0.05, 0.48, 0.91)); \
m_zcLeft.Init(QUARTERPI, d_fNearClipping, d_fFarClipping); \
m_zcRight.Init(QUARTERPI, d_fNearClipping, d_fFarClipping); \
m_zr.AddScene(&m_zs); \
m_zs.AddPlacement(&m_zpCamera); \
m_zpCamera.AddPlacement(&m_zpHMD); \
m_zpHMD.AddPlacement(&m_zpCameraRight); \
m_zpHMD.AddPlacement(&m_zpCameraLeft); \
m_zpCameraLeft.AddCamera(&m_zcLeft); \
m_zpCameraRight.AddCamera(&m_zcRight); 

///<summary> Makro, um eine Videobrille zu betreiben. <para></para> 
/// Muss in die Tick-Routine der Klasse CGame geschrieben werden.</summary>
///<param name = "d_zgsCollisionItems"> Liste dejenigen Objekte, mit denen der Spieler kollidieren kann. <para></para>
/// Muss vom Typ CGoes sein. </param>
///<param name = "d_bEarth"> Flag, welches angibt, ob es sich um eine erdgebundene Controller-Steuerung handelt (Horizont bleibt horizontal). <para></para>
/// Muss vom Typ bool sein. </param>
#define CONF_HMD_TICK(d_bEarth) \
CHMat mHMD = m_zdh.GetMatHead(); \
m_zpHMD.SetMat(mHMD); \
CHMat mEyeLeft = m_zdh.GetMatEyeLeft(); \
CHMat mEyeRight = m_zdh.GetMatEyeRight(); \
CHMat mProjLeft = m_zdh.GetMatProjLeft(m_fNearClipping, m_fFarClipping); \
CHMat mProjRight = m_zdh.GetMatProjRight(m_fNearClipping, m_fFarClipping); \
m_zpCameraLeft.SetMat(mEyeLeft); \
m_zpCameraRight.SetMat(mEyeRight); \
m_zcLeft.m_mProjection.m_fx00 = mProjLeft.m_fx00; \
m_zcRight.m_mProjection.m_fx00 = mProjRight.m_fx00; \
m_zcLeft.m_mProjection.m_fx11 = mProjLeft.m_fx11; \
m_zcRight.m_mProjection.m_fx11 = mProjRight.m_fx11; \
m_zcLeft.SetMatProjection(m_zcLeft.m_mProjection); \
m_zcRight.SetMatProjection(m_zcRight.m_mProjection); \
if (m_zdv2.MoveWithCollisionDetection(m_zpCamera, m_zpHMD, m_zpController2, m_zgsCollisionItems, fTimeDelta, d_bEarth)) \
m_zdv2.Vibrate(1.0f); \
m_zr.Tick(fTimeDelta);

#define CONF_NORMAL_H \
CRoot m_zr; \
CFrame m_zf; \
CViewport m_zv; \
CDeviceKeyboard m_zdk; \
CScene m_zs; \
CPlacement m_zpCamera; \
CCamera m_zc; \
CGeos m_zgsCollisionItems;

#define CONF_NORMAL_INIT(d_fFov,d_fNearClipping,d_fFarClipping) \
m_zr.Init(psplash); \
m_zf.Init(hwnd, procOS, eApiRender_DirectX11_Shadermodel50_Standard, eApiInput_DirectInput, eApiSound_DirectSound, eApiCyberglasses_None); \
m_zv.InitFull(&m_zc); \
m_zc.Init(d_fFov, d_fNearClipping, d_fFarClipping); \
m_zr.AddFrame(&m_zf); \
m_zr.AddScene(&m_zs); \
m_zf.AddDeviceKeyboard(&m_zdk); \
m_zf.AddViewport(&m_zv); \
m_zs.AddPlacement(&m_zpCamera); \
m_zpCamera.AddCamera(&m_zc); 

#define CONF_NORMAL_TICK(d_bEarth) \
m_zdk.PlaceWASDWithCollisionDetection(m_zpCamera, m_zgsCollisionItems, fTimeDelta, d_bEarth);\
m_zr.Tick(fTimeDelta);


