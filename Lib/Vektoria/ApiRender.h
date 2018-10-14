#pragma once
#include "../VektoriaMath/HMat.h"
#include "ApiCyberglasses.h"
#include "Material.h"
#include <Windows.h>
#include "Emitter.h"

//---------------------------------------------------
// CApiRender - Schnittstelle für alle Rendering-Module
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{


// Maximale Lichteranzahl, die eine einzige Geometrie beeinflussen kann  
// Erklärung: Es können quasi beliebig viele Lichter in einer Szene vorhanden sein, aber aus Shader-Kapazitäts-Gründen beeinflussen immer nur eine begrenzte Maxcimalanzahl von Lichtern eine einzige Geometrie beleuchten  
#define LIGHTS_MAX 16
#define LIGHTS_MAX_MINUS_ONE LIGHTS_MAX-1


#define DRAWOBJECT_3D_OPAQUE 0 // undurchsichtige Textur ohne Alpha oder Transparent
#define DRAWOBJECT_3D_TRANSPARENT_CONTINUAL 1 // z.B. Textur mit Alphakanal > 1Bit
#define DRAWOBJECT_3D_TRANSPARENT_BINARY 2 // z.B. ChromaKeying-Textur
#define DRAWOBJECT_3D_TRANSPARENT_COMPLETE 3 // z.B. Wird nicht gezeichnet
#define DRAWOBJECT_2D_OVERLAY_OPAQUE 4  // Undurchsichtige Overlay-Textur
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_CONTINUAL 5// z.B. Textur mit Alphakanal > 1Bit
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_BINARY 6 // z.B. ChromaKeying-Textur
#define DRAWOBJECT_2D_OVERLAY_TRANSPARENT_COMPLETE 7 // z.B. Wird nicht gezeichnet
#define DRAWOBJECT_2D_BACKGROUND 8 // Undurchsichtige Background-Textur

	class CViewports;
	class CViewport;
	class CVertex;
	class CGeoPointList;
	class CGeoLineList;
	class CGeoTriangleTable;
	class CGeoTriangleList;
	class CGeoTriangleStrip;
	class CLight;

	/// <summary>Render-API:</summary>
	enum EApiRender
	{
		eApiRender_Null, // Shader, der die Renderbefahle ins Leere laufen lässt (für Debuggig und Optimierungszwecke)
		eApiRender_DirectX11_Shadermodel41, // DirectX-Renderer mit Shadermodell 4.1 (downgrade für alte Rechner) 
		eApiRender_DirectX11_Shadermodel50_Own, // DirectX-Renderer mit eigenen Shadern
		eApiRender_DirectX11_Shadermodel50_Minimalistic, // Minimalistischer schneller DirectX-Renderer, der so aussieht, als käme die Szene aus den 90er-Jahren
		eApiRender_DirectX11_Shadermodel50_Monolight, // DirectX-Renderer für Szenen mit nur einem einzigen Licht
		eApiRender_DirectX11_Shadermodel50_MonolightAA, // DirectX-Renderer für Szenen mit nur einem einzigen Licht mit Antialiasing
		eApiRender_DirectX11_Shadermodel50_Standard, // Standard-DirectX-Renderer (default)
		eApiRender_DirectX11_Shadermodel50_StandardAA, // Standard-DirectX-Renderer mit Antialiasing
		eApiRender_DirectX11_ForwardPlus, // Forward-Plus-Renderer mit Physically Based Shading, nur in der kostenpflichtigen Luxus-Version vorhanden
		eApiRender_DirectX12, // In Arbeit
		eApiRender_OpenGL40, // Nur in der kostenpflichtigen Version		
		eApiRender_Vulcan, // Noch nicht implementiert
		eApiRender_Own	// Falls man eine eigene DLL schreiben will
	};

	/// <summary>Erstellungsmodus für Shader:</summary>
	enum EShaderCreation
	{
		eShaderCreation_ForceCompile,		// Leere den Cache und kompiliere alle Shader neu
		eShaderCreation_CompileChanges,		// Kompiliere die Shader, die sich geändert haben
		eShaderCreation_UseCached			// Benutze nur die Shader aus dem Cache		
	};

	/// <summary>Automatisches Shader-Rekompilieren:</summary>
	enum EShaderAutoRecompilation
	{
		eShaderAutoRecompilation_Disabled, // Shader nur beim Programmstart kompilieren
		eShaderAutoRecompilation_Enabled   // Automatisches Rekompilieren von Shadern
	};

	/// <summary>Arten der Renderobjekte, die an den Shader übergeben werden können:</summary>
	enum ERenderObjectType
	{
		eRenderObjectType_Undefined = -1,
		eRenderObjectType_TriangleList,
		eRenderObjectType_TriangleStrip,
		eRenderObjectType_TriangleTable,
		eRenderObjectType_PointList,
		eRenderObjectType_LineList
	};


class CApiRender
{
public:

	// --------------------------
	// Geburt, Leben und Sterben:
	// --------------------------

	/// <summary>Initalisiert die Sound-API.</summary>
	/// <param name= "hwnd"> Handle auf das Window-Fenster, welches rendern soll.</param>
	/// <param name= "iWidthWindow"> Breite des Window-Fensterbereichs in Pixel.</param>
	/// <param name= "iHeightWindow"> Höhe des Window-Fensterbereichs in Pixel.</param>
	///<param name = "eApiRender"> Zu verwendende Render-API. 
	/// Mögliche Werte: <para></para>
	/// - eApiRender_DirectX11_Shadermodel41 (sinnvoll, wenn ein älterer Rechner von ca. 2008/09 vorhanden ist)<para></para> 
	/// - eApiRender_DirectX11_Shadermodel50_Minimalistic (Shader mit den allerwichtigsten Funktionen, schnell aber hässlich) <para></para>
	/// - eApiRender_DirectX11_Shadermodel50_Monolight (sollte erste Wahl sein, wenn nur ein Licht pro Szene vorhanden ist, schneller als Standard-Shader) <para></para>
	/// - eApiRender_DirectX11_Shadermodel50_MonolightAA (wie oben, nur mit Antialiasing) <para></para>		
	/// - eApiRender_DirectX11_Shadermodel50_Own (diese Option muss angeschaltet werden, wenn ein eigener Shader geschrieben werden soll) <para></para>
	/// - eApiRender_DirectX11_Shadermodel50_Standard (Defaultwert: Normaler DirectX11-Shader)<para></para> 
	/// - eApiRender_DirectX11_Shadermodel50_StandardAA (wie oben, nur mit Antialiasing)<para></para> 
	/// - eApiRender_Null (Renderbefehle laufen ins Leere, für Debugging-Zwecke sinnvoll) <para></para>
	/// - eApiRender_OpenGL_40 (OpenGL-Renderer, wird seit V14 nicht mehr unterstützt) </param>
	///<param name = "eApiCyberglasses"> Zu verwendende API für Oculus Rift, HTCVive, HoloLens und andere HMDs. <para></para>
	/// Mögliche Werte: <para></para>
	/// - eApiCyberglasses_OpenVR (Defaultwert) <para></para>
	/// - eApiCyberglasses_Null (VR-Befehle laufen ins Leere, für Debugging-Zwecke sinnvoll) </param>
	///<param name = "eShaderCreation"> Wann soll der Shader kompiliert werden? <para></para>
	/// Mögliche Werte: <para></para>
	/// - eShaderCreation_CompileChanges (Es soll nur bei Shaderveränderungen compiliert werden, Achtung, vor dieser Einstellung Backups der kompilierten Shader machen!) <para></para>
	/// - eShaderCreation_ForceCompile (Es soll immer kompiliert werden. Achtung, vor dieser Einstellung Backups der kompilierten Shader machen!) <para></para>
	/// - eShaderCreation_UseCached (Es sollen die vorkompilierten Shader verwendet werden, Defaultwert) </param>
	///<param name = "eShaderAutoRecompilation"> Soll der Shader auch während der Laufzeit kompiliert werden? <para></para>
	/// Mögliche Werte: <para></para>
	/// - eShaderAutoRecompilation_Disabled (Defaultwert, Es sollen nur bei Programmstart kompiliert werden)<para></para> 
	/// - eShaderAutoRecompilation_Enabled (Der Shader soll auch während der Laufzeit kompiliert werden) </param>
	virtual void Init(HWND hwnd, int iWidthWindow, int iHeightWindow, EApiRender eApiRender, EApiCyberglasses eApiCyberglasses, EShaderCreation eShaderCreation, EShaderAutoRecompilation eShaderAutoRecompilation) = 0;


	/// <summary>Wird bei jedem Bildrendern am Schluss einmal aufgerufen.</summary>
	virtual void Tick() = 0;

	/// <summary>Wird am Schluss aufgerufen.</summary>
	virtual void Fini() = 0;

	// ---------
	// Viewport:
	// ---------

	virtual void CreateViewport(unsigned int & idViewport, CViewport *pviewport) = 0;
	virtual void UpdateViewport(unsigned int & idViewport, CViewport *pviewport) = 0;
	virtual void UpdateViewportState(unsigned int & idViewport, CViewport *pviewport, bool bCullNone = false) = 0;
	virtual void DeleteViewport(unsigned int & idViewport) = 0;
	virtual void RenderViewport(CHMat & mProjection, CHMat & mView, CHVector & vCamPos, CViewport &viewport) = 0;

	// ------------
	// Materialien:
	// ------------

	virtual void CreateMaterial(CMaterial * pmaterial) = 0;
	virtual void UpdateMaterial(CMaterial * pmaterial) = 0;
	virtual void UpdateMaterialAni(CMaterial * pmaterial) = 0;
	virtual bool DeleteMaterial(CMaterial * pmaterial) = 0;

	// --------
	// Lichter:
	// --------

	virtual void CreateLightParallel(unsigned int & idLight, unsigned int * aidViewportConnected, unsigned int & uViewportsConnected, CColor & color, CHVector & vDirection) = 0;
	virtual void CreateLightSpot(unsigned int & idLight, unsigned int * aidViewportConnected, unsigned int & uViewportsConnected, CColor & color, CHMat & mProjection, bool & bCauseShadow, bool & bSoftShadow, bool & bCone, int & ixShadowMap, int & iyShadowMap, float & fAttenuationConstant, float & fAttenuationLinear, float & fAttenuationQuadratic, float & fOuterCosAngle, float & fInnerCosAngle, float & fRadius) = 0;
	virtual void CreateLightRadial(unsigned int & idLight, unsigned int * aidViewportConnected, unsigned int & uViewportsConnected, CColor & color, float & fAttenuationConstant, float & fAttenuationLinear, float & fAttenuationQuadratic) = 0;
	virtual void UpdateLightPos(unsigned int & idLight, CHMat & m) = 0;
	virtual void UpdateLightColor(unsigned int & idLight, CColor & color) = 0;
	virtual void UpdateLightDir(unsigned int & idLight, CHVector & vDirection) = 0;
	virtual void UpdateLightSwitch(unsigned int & idLight, bool & bOn) = 0;
	virtual void UpdateLightShadow(unsigned int & idLight, bool bCauseShadow, bool bSoftShadow, bool bCone, float frShadowStrength) = 0;
	virtual void DeleteLight(unsigned int & idLight) = 0;
	virtual void RenderLight(unsigned int & idLight, CViewport *pviewport) = 0;

	// -------
	// Szenen:
	// -------

	virtual void RenderScene() = 0;

	// -----------
	// Geometrien:
	// -----------

	virtual void CreateGeoPointList(unsigned int & idGeo, CGeoPointList *ppointlist) = 0;
	virtual void UpdateGeoPointList(unsigned int & idGeo, CGeoPointList *ppointlist) = 0;
	virtual void CreateGeoLineList(unsigned int & idGeo, CGeoLineList *plinelist) = 0;
	virtual void UpdateGeoLineList(unsigned int & idGeo, CGeoLineList *pLinelist) = 0;
	virtual void CreateGeoTriangleTable(unsigned int & idGeo, CGeoTriangleTable *ptriangletable) = 0;
	virtual void UpdateGeoTriangleTable(unsigned int & idGeo, CGeoTriangleTable *ptriangletable) = 0;
	virtual void CreateGeoTriangleList(unsigned int & idGeo, CGeoTriangleList *ptrianglelist) = 0;
	virtual void UpdateGeoTriangleList(unsigned int & idGeo, CGeoTriangleList *ptrianglelist) = 0;
	virtual void CreateGeoTriangleStrip(unsigned int & idGeo, CGeoTriangleStrip *ptrianglestrip) = 0;
	virtual void UpdateGeoTriangleStrip(unsigned int & idGeo, CGeoTriangleStrip *ptrianglestrip) = 0;
	virtual void DeleteGeo(unsigned int & idGeo) = 0;
	virtual void RenderGeo(unsigned int & idGeo, int & idTexture, float & fDistanceToCameraSquare, int iKind, CHMat & mGlobal, unsigned int aidLightsAffect[LIGHTS_MAX], unsigned int iLightsAffectCount) = 0;

	// --------
	// Emitter:
	// --------

	virtual void CreateEmitter(unsigned int & idEmitter, CEmitter * pemitter) = 0;
	virtual void UpdateEmitter(unsigned int & idEmitter, CEmitter * pemitter) = 0;
	virtual void DeleteEmitter(unsigned int & idEmitter) = 0;

	// ---------
	// Changing:
	// ---------

	virtual void ResizeResolution(CViewport *pviewport) = 0;
	virtual void ResizeResolutionHMD(int ix, int iy) = 0;
	virtual void ResizeResolutionShadowMap(int ix, int iy) = 0;

	// -----------------
	// Log-File & Debug:
	// -----------------

	virtual void SetLogFileData(FILE* pfile, unsigned int uStartTime, char * acFile) = 0;

	// ----------------
	// Membervariablen:
	// ----------------

	// Anzahl Remotecomputer (wichtig für eventuelles verteiltes Rendering)
	int m_iHardwares = 0;
};

}