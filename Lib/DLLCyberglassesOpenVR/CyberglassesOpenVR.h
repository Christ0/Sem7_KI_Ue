#pragma once
#include "..\Vektoria\ApiCyberglasses.h"

#include "..\..\Lib\OpenVR\headers\openvr.h"
#include "..\..\Lib\OpenVR\headers\openvr_capi.h"



using namespace vr;


namespace Vektoria
{
	class CCyberglassesOpenVR : public CApiCyberglasses
	{
	public:

		//------------------------
		// Schnittstellenroutinen:
		//------------------------

		// Geburt, Leben und Sterben:
		bool Init();
		void Tick();
		void Fini();

		// Log-File & Debug:
		void SetLogFileData(FILE * pfile, unsigned int uStartTime, char * acFile);

		// Systentatusabfragen:
		int GetEyePixelsX();
		int GetEyePixelsY();
		int GetNumControllers();

		// Matrixabfragen:
		bool GetMatHMD(CHMat & m);
		bool GetMatEyeLeft(CHMat & m);
		bool GetMatEyeRight(CHMat & m);
		bool GetMatProjLeft(CHMat & m, float & fNear, float & fFar);
		bool GetMatProjRight(CHMat & m, float & fNear, float & fFar);
		bool GetMatController(unsigned int & iController, CHMat & m);

		// Abfrage:
		bool IsTouched(unsigned int & iController, EHmdButtonKind eButton);
		bool IsPressed(unsigned int & iController, EHmdButtonKind eButton);
		bool IsDown(unsigned int & iController, EHmdButtonKind eButton);
		bool IsUp(unsigned int & iController, EHmdButtonKind eButton);

		// Koordinatenabfage:
		float GetAbsoluteX(unsigned int & iController, int & iAxis);
		float GetAbsoluteY(unsigned int & iController, int & iAxis);

		// Haptik:
		void Haptic(unsigned int & iController, int & iAxis, float & fr);

		// Rendermethoden:
		void WaitGetPoses();
		void SetTextureEyeLeft(void * pRenderTexture);
		void SetTextureEyeRight(void * pRenderTexture);


		// ----------------
		// Membervariablen:
		// ----------------

		
		IVRSystem * m_pHMD = nullptr;
		IVRCompositor * m_pCompositor = nullptr;

		unsigned int m_uxEyePixels = 0; 
		unsigned int m_uyEyePixels = 0;
		bool bInitialized = false;
		int m_iDevices = 0;
		int m_iControllers = 0;
		int m_iHMDs = 0;
		int m_iGenericTrackers = 0;
		int m_iTrackingReferences = 0;
		char * m_acKindDevice = nullptr;

		int m_aiController[vr::k_unMaxTrackedDeviceCount];


		vr::VRControllerState_t m_avrcontrollerstateControllerOld[vr::k_unMaxTrackedDeviceCount];
		vr::VRControllerState_t m_avrcontrollerstateController[vr::k_unMaxTrackedDeviceCount];
		vr::TrackedDevicePose_t m_aposeController[vr::k_unMaxTrackedDeviceCount];

		vr::VRControllerState_t m_vrcontrollerstateHMD;
		vr::TrackedDevicePose_t m_poseHMD;

		vr::TrackedDevicePose_t m_apose[vr::k_unMaxTrackedDeviceCount];

		vr::EVRCompositorError m_compositorerr;
		vr::VRTextureBounds_t m_textureboundsLeft;
		vr::VRTextureBounds_t m_textureboundsRight;



		
	};
}
