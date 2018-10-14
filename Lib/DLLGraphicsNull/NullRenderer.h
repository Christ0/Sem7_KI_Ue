#pragma once

//------------------------------------------------------------------
// NullRenderer: Klasse, die nichts macht und einfach bezüglich Rendering "klasse" ist ;-)
//
// Autor: Prof. Dr. Tobias Breiner 
// Firma: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------

#ifdef COMPILE_GRAPHICSNULL
#define GRAPHICSNULL_EXPORT __declspec(dllexport)
#else
#define GRAPHICSNULL_EXPORT __declspec(dllimport)
#endif


#include "../Vektoria/ApiRender.h"

namespace Vektoria
{

class GRAPHICSNULL_EXPORT CNullRenderer : public CApiRender
{
public:
	// -----------------------------//
	// BEGIN SCHNITTSTELLENMETHODEN // 
	// -----------------------------//

	// Geburt, Leben und Sterben:
	void Init(HWND hwnd, int iWidthWindow, int iHeightWindow, EApiRender eApiRender, EApiCyberglasses eApiCyberglasses, EShaderCreation eShaderCreation, EShaderAutoRecompilation eShaderAutoRecompilation);
	void Tick();
	void Fini();

	// Viewport-Methoden:
	void CreateViewport(unsigned int & idViewport, CViewport *pviewport);
	void UpdateViewport(unsigned int & idViewport, CViewport *pviewport);
	void UpdateViewportState(unsigned int & idViewport, CViewport *pviewport, bool bCullNone = false);
	void DeleteViewport(unsigned int & idViewport);
	void RenderViewport(CHMat & mProjection, CHMat & mView, CHVector & vCamPos, CViewport &viewport);

	// Szenen:
	void RenderScene();

	// Materialien:
	void CreateMaterial(CMaterial * pmaterial);
	void UpdateMaterial(CMaterial * pmaterial);
	void UpdateMaterialAni(CMaterial * pmaterial);
	bool DeleteMaterial(CMaterial * pmaterial);

	// Lichter:
	void CreateLightParallel(unsigned int & idLight, unsigned int * aidViewportConnected, unsigned int & iViewportsConnected, CColor & color, CHVector & vDirection);
	void CreateLightSpot(unsigned int & idLight, unsigned int * aidViewportConnected, unsigned int & iViewportsConnected, CColor & color, CHMat & mProjection, bool & bCauseShadow, bool & bSoftShadow, bool & bCone, int & ixShadowMap, int & iyShadowMap, float & fAttenuationConstant, float & fAttenuationLinear, float & fAttenuationQuadratic, float & fOuterCosAngle, float & fInnerCosAngle, float & fRadius);
	void CreateLightRadial(unsigned int & idLight, unsigned int * aidViewportConnected, unsigned int & iViewportsConnected, CColor & color, float & fAttenuationConstant, float & fAttenuationLinear, float & fAttenuationQuadratic);
	void UpdateLightPos(unsigned int & idLight, CHMat & m);
	void UpdateLightColor(unsigned int & idLight, CColor & color);
	void UpdateLightDir(unsigned int & idLight, CHVector & vDirection);
	void UpdateLightSwitch(unsigned int & idLight, bool & bOn);
	void UpdateLightShadow(unsigned int & idLight, bool bCauseShadow, bool bSoftShadow, bool bCone, float frShadowStrength);
	void DeleteLight(unsigned int & idLight);
	void RenderLight(unsigned int & idLight, CViewport *pviewport);

	// Gemoetrien:
	void CreateGeoPointList(unsigned int & idGeo, CGeoPointList *ppointlist);
	void UpdateGeoPointList(unsigned int & idGeo, CGeoPointList *ppointlist);
	void CreateGeoLineList(unsigned int & idGeo, CGeoLineList *plinelist);
	void UpdateGeoLineList(unsigned int & idGeo, CGeoLineList *pLinelist);
	void CreateGeoTriangleTable(unsigned int & idGeo, CGeoTriangleTable *ptriangletable);
	void UpdateGeoTriangleTable(unsigned int & idGeo, CGeoTriangleTable *ptriangletable);
	void CreateGeoTriangleList(unsigned int & idGeo, CGeoTriangleList *ptrianglelist);
	void UpdateGeoTriangleList(unsigned int & idGeo, CGeoTriangleList *ptrianglelist);
	void CreateGeoTriangleStrip(unsigned int & idGeo, CGeoTriangleStrip *ptrianglestrip);
	void UpdateGeoTriangleStrip(unsigned int & idGeo, CGeoTriangleStrip *ptrianglestrip);
	void DeleteGeo(unsigned int & idGeo);
	void RenderGeo(unsigned int & idGeo, int & idTexture, float & fDistanceToCameraSquare, int iKind, CHMat & mGlobal, unsigned int aidLightsAffect[LIGHTS_MAX], unsigned int iLightsAffectCount);

	// Emitter:
	void CreateEmitter(unsigned int & idEmitter, CEmitter * pemitter);
	void UpdateEmitter(unsigned int & idEmitter, CEmitter * pemitter);
	void DeleteEmitter(unsigned int & idEmitter);

	// Changing:
	void ResizeResolution(CViewport *pviewport);
	void ResizeResolutionHMD(int ix, int iy);
	void ResizeResolutionShadowMap(int ix, int iy);


	// Log-File & Debug:
	void SetLogFileData(FILE* pfile, unsigned int uStartTime, char * acFile);


	// ---------------------------//
	// END SCHNITTSTELLENMETHODEN // 
	// ---------------------------//
};

}