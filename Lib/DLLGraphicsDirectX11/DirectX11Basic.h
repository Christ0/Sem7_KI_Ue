#pragma once

//------------------------------------------------------------------
// CDirectX11Basic: Klasse zur DirectX-11-Anbindung (Basic-Renderer)
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt) 
//-------------------------------------------------------------------

#ifdef COMPILE_GRAPHICSDIRECTX11
#define GRAPHICSDIRECTX11_EXPORT __declspec(dllexport)
#else
#define GRAPHICSDIRECTX11_EXPORT __declspec(dllimport)
#endif


// #define DEBUG_EXTENDED 

#include "../Vektoria/ApiRender.h"
#include "../Vektoria/Vertex.h"
#include "../VektoriaMath/HMat.h"
#include "../Vektoria/GeoQuad.h"

#include "../DLLGraphicsCommon/DXBuffers.h"
#include "../DLLGraphicsCommon/Shadercache.h"
#include "../DLLGraphicsCommon/DrawObjects.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <D3DCompiler.h>
#include <d3dx10.h>
#include <Windows.h>
#include <xnamath.h>
#include <D3D11shader.h>
#include <vector>
#include <thread>

#include "..\Vektoria\ApiCyberglasses.h"





// if we are debugging, then change compiling mode for shader  // Führte bei manchen Rechnern (insbesondere Laborrechner) zum Absturz!!! Musste es leider rausnehmen (TB) 
/*
@TB: Try to install the Windows 8 SDK on those PCs. At least that fixed the issue for me. (MR)
D3D11_CREATE_DEVICE_DEBUG:
"To use this flag, you must have D3D11*SDKLayers.dll installed; otherwise, device creation fails. To get D3D11_1SDKLayers.dll, install the SDK for Windows 8."
*/


#pragma comment (lib, "d3d11.lib")


#ifdef _DEBUG

#pragma comment (lib, "d3dx11d.lib")
#pragma comment (lib, "d3dx10d.lib")


#ifdef DEBUG_LABOR_ERROR
#define D3D_DEBUG_INFO // Führte bei manchen Rechnern (insbesondere Laborrechner) zum Absturz!!! Musste es leider rausnehmen, kann aber leicht wieder durch ein define angeschaltet werden (TB)
#endif

#ifdef DEBUG_LABOR_ERROR
#define SHADER_COMPILEFLAGS D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION | D3D10_SHADER_SKIP_VALIDATION | D3D10_SHADER_OPTIMIZATION_LEVEL0 // rausgenommen, s.o. (TB)
#define DIRECTX_DEVICE_FLAGS D3D11_CREATE_DEVICE_DEBUG // rausgenommen, s.o. (TB)
#else
#define SHADER_COMPILEFLAGS D3D10_SHADER_OPTIMIZATION_LEVEL0
#define DIRECTX_DEVICE_FLAGS 0
#endif

#else

#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#define SHADER_COMPILEFLAGS D3D10_SHADER_OPTIMIZATION_LEVEL0
#define DIRECTX_DEVICE_FLAGS 0
#endif

// object count to allocate when out of memory
#define I_ALLOCBLOCK 1000

struct ID3DX11Scan;


namespace Vektoria
{
	class CViewport;
	class CMaterial;
	class CCamera;
	class TriangleList;
	class TriangleStrip;
	class Light;
	class LightParallel;
	class LightRadial;
	class LightSpot;
	class CParticleRenderer;
	class CDXUtilities;
	class CLightUtil;

	struct SVertexBuffer
	{
		FLOAT fx, fy, fz;								// Position
		FLOAT fxNormal, fyNormal, fzNormal;				// Normale 
		FLOAT fxTangent, fyTangent, fzTangent;			// Tangente 
		FLOAT fxBitangent, fyBitangent, fzBitangent;	// Bitangente
		FLOAT fu, fv;									// uv-Mapping fuers Texturing
	};

	struct SLightStructure  // Wird übergeben an Shader
	{
		FLOAT fx, fy, fz;	          //  0- 2: Position
		UINT type;			          //  3   : Light source type (parallel, point, spot)

		D3DXCOLOR color;	          //  4- 7: Light's color

		FLOAT dx, dy, dz;	          //  8-10: Direction
		FLOAT fInnerCosAngle;         //  11  : 

		FLOAT fOuterCosAngle;		  //  12  : 
		FLOAT fAttenuationConstant;   //  13  : 
		FLOAT fAttenuationLinear;     //  14  : 
		FLOAT fAttenuationQuadratic;  //  15  :

		BOOL bCauseShadow;            //  16  :
		BOOL bSoftShadow;             //  17  :
		BOOL bCone;                   //  18  :
		FLOAT frShadowStrength;       //  19  :

		XMFLOAT4X4 mLightViewProj;    //  20..
	};

	struct SLightStructureAdditional // Wird nicht übergeben an Shader
	{
		unsigned int id;
		unsigned int uViewportsAnchestor;
		unsigned int * aidViewportAnchestor;
		XMFLOAT4X4 mProj;
		XMFLOAT4X4 mView;
		bool bOn;
	};


	// changed data type to xmfloat4x4, because
	// xmmatrix cant be used in class (memory alignment on x86!)
	struct SPostprocessingShaderConstants
	{
		XMFLOAT4X4 mWorldViewProjection;
	};


	
	

	// constant buffer structure for shadow map
	struct SShadowmapShaderConstants
	{
		XMFLOAT4X4 mWorld;
		XMFLOAT4X4 mLightView;
		int iBuffer1[16];
		XMFLOAT4X4 mProjection;
		int iBuffer2[8];
	};

	struct SDrawObject
	{
		unsigned int id;
		int idTexture;
		float & fDistanceToCameraSquare;
		CHMat mGlobal;
		unsigned int iLightsAffectIndices[LIGHTS_MAX]; // TODO Macht kein Sinn mehr!
		unsigned int iLightsAffectCount;
	};

	struct STextureInfo
	{
		char acPath[MAX_PATH];
		ID3D11ShaderResourceView *ptex;
		int iUsedByMaterials;
	};

	struct SMaterialInfo
	{
		int iImage;
		int iGlow;
		int iSpecular;
		int iBump;
		int iEnvironment;
		int iHeight;
		int iThickness;
		bool bChanged;
	};

	struct SMaterialParametersHost
	{
		XMFLOAT4X4 mColorModification;	// 00: Farbveraenderungsmatrix  
		//---------16

		float fBumpStrength;
		float fHeightStrength;
		float fGlowStrength;
		float fSpecularStrength;

		float fSpecularSharpness;       
		float fDiffuseSharpness;
		float fGlowSharpness;
		float frTransparency;

		float fHazeStrength;
		float frFresnel;
		float fRefractionRatio;
		float frTransparencyEdge;

		XMFLOAT4 d3dxcolorSSS;			// Materialfarbe des Subsurface

		//---------32
		XMFLOAT4 f4SSSBRDFParams;		// Parameter für BRDF/SSS

		unsigned uImage; // C9
		unsigned uGlow;
		unsigned uSpecular;
		unsigned uBump;

		unsigned uImageBlack; // C10
		unsigned uGlowAsImage;
		unsigned uSpecularAsImage;
		unsigned uHeightAsImage;

		unsigned uImageWhite; // C11
		unsigned uGlowWhite;
		unsigned uSpecularWhite;
		unsigned uHeight;
		
		//---------48
		unsigned uShadingOn; // C12
		unsigned uGlowAsAmbient;
		unsigned uChromaKeying;
		unsigned uEnvironment;
		
		unsigned uPOM; // C13
		unsigned uPostprocessing;
		unsigned uTexSSS;
		unsigned uReflectionMap;
		
		unsigned uAni; // C14
		float fPic;
		unsigned uixPics;
		unsigned uiyPics;

		ETextureAddressMode eTextureAddressMode; // C15
		unsigned uLightScattering;
		unsigned uDummy2;
		unsigned uDummy3;
	};

	struct SPostprocessingBufferHost
	{
		float frBloomStrengthNear;
		float frBloomStrengthFar;
		float fBloomOriginalSaturation;
		float fBloomSaturation;
		float fRayExposure;
		float fRayDecay;
		float fRayDensity;
		float fRayWeight;
		float fTime;
		float frBloomDepthDecay;
		float fDoFFar;
		float fDoFNear;
		float fFocalDistance;
		unsigned int uOutlining;
		unsigned int uBloom;
		unsigned int uBlur;
		XMVECTOR f4GodRayPos;
		XMVECTOR f4rcpFrameOpt;
		XMVECTOR f4ColorOutline;
		float frDepthBlurStrength;
		float frBlurStrength;
		float frBloomWidth;
		float fDepthBlurSharpness;

		float fOutliningStrength;
		float frOutliningThreshold ;
		float frOutliningDepthWeight;
		unsigned int uAA;

		unsigned int uHaze;
		unsigned int uStyleColor;
		unsigned int uToonSteps;
		float fHazeDummy3;

		XMFLOAT4X4 mColorModification;	// 00: Farbveraenderungsmatrix  
	};

	struct SViewportstyleBufferHost
	{
		XMFLOAT4 d3dxcolorAmbient;		// Ambientlight
		XMFLOAT4 d3dxcolorMistParams;	// Nebel-Parameter

		unsigned uPostprocessing;
		unsigned uMist;
		unsigned uSnow;
		float fFarClipping;
	};



#pragma pack(push, 1)
	struct SMaterialParameters
	{
		XMFLOAT4X4 mColorModification;	// 00: Farbveraenderungsmatrix  
		//---------16

		float fBumpStrength;
		float fHeightStrength;
		float fGlowStrength;
		float fSpecularStrength;

		float fSpecularSharpness;
		float fDiffuseSharpness;
		float fGlowSharpness;
		float frTransparency;

		float fHazeStrength;
		float frFresnel;
		float fRefractionRatio;
		float frTransparencyEdge;

		XMVECTOR d3dxcolorSSS;			// Materialfarbe des Subsurface

		//---------32
		XMVECTOR f4SSSBRDFParams;		// Parameter für BRDF/SSS

		unsigned uImage; // C9
		unsigned uGlow;
		unsigned uSpecular;
		unsigned uBump;

		unsigned uImageBlack; // C10
		unsigned uGlowAsImage;
		unsigned uSpecularAsImage;
		unsigned uHeightAsImage;

		unsigned uImageWhite; // C11
		unsigned uGlowWhite;
		unsigned uSpecularWhite;
		unsigned uHeight;

		//---------48
		unsigned uShadingOn; // C12
		unsigned uGlowAsAmbient;
		unsigned uChromaKeying;
		unsigned uEnvironment;

		unsigned uPOM; // C13
		unsigned uPostprocessing;
		unsigned uTexSSS;
		unsigned uReflectionMap;

		unsigned uAni; // C14
		float fPic;
		unsigned uixPics;
		unsigned uiyPics;

		
		ETextureAddressMode eTextureAddressMode;
		unsigned uLightScattering;
		unsigned uDummy2;
		unsigned uDummy3;
		

	};
	
	struct SPostprocessingBuffer
	{
		float frBloomStrengthNear;
		float frBloomStrengthFar;
		float fBloomOriginalSaturation;
		float fBloomSaturation;
	
		float fRayExposure;
		float fRayDecay;
		float fRayDensity;
		float fRayWeight;
		
		float fTime;
		float frBloomDepthDecay;
		float fDoFFar;
		float fDoFNear;
		
		float fFocalDistance;
		unsigned int uOutlining;
		unsigned int uBloom;
		unsigned int uBlur;

		XMVECTOR f4GodRayPos;
		XMVECTOR f4rcpFrameOpt;
		XMVECTOR f4ColorOutline;

		float frDepthBlurStrength;
		float frBlurStrength;
		float frBloomWidth;
		float fDepthBlurSharpness;

		float fOutliningStrength;
		float frOutliningThreshold;
		float frOutliningDepthWeight;
		unsigned int uAA;

		unsigned int uHaze;
		unsigned int uStyleColor;
		unsigned int uToonSteps;
		float fHazeDummy3;

		XMMATRIX mColorModification; // Farbveraenderungsmatrix

	};

	struct SViewportstyleBuffer
	{
		XMVECTOR d3dxcolorAmbient;		// Kontur-Viewportfarbe
		XMVECTOR d3dxcolorMistParams;	// Nebel-Parameter
		unsigned uPostprocessing;
		unsigned uMist;
		unsigned uSnow;
		float fFarClipping;

	};


	struct SObjectShaderConstants
	{
		XMFLOAT4X4 mWorld;
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mProjection;
		XMFLOAT3 f3CamPos;
		unsigned  uLightsAffectCount;
//		unsigned  auLightsAffectIndices[4];
	};
	
#pragma pack(pop)

	class GRAPHICSDIRECTX11_EXPORT CDirectX11Basic : public CApiRender
	{
		friend class CDXUtilities;
	public:
		void Construct();

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

		// LogFile:
		void SetLogFileData(FILE* pfile, unsigned int uStartTime, char * acFile);

		// ---------------------------//
		// END SCHNITTSTELLENMETHODEN // 
		// ---------------------------//

		HWND m_hwnd;



	protected:

		// HMD:



		int m_ixHMD;
		int m_iyHMD;
		bool m_bHMD;

		HINSTANCE  m_hinstLibCyberglasses;

		///<summary> Art der Api für HMDs</summary>
		EApiCyberglasses m_eApiCyberglasses;



		///<summary> Pointer zur Api für Head Mounted Displays (Oculus Rift, HTC Vive, HoloLens, etc.).</summary>
		CApiCyberglasses* m_papicyberglasses;



		// Hauptvariablen:
		CDXUtilities *m_pUtils;
		IDXGISwapChain *m_pswapchain;

		CViewport *m_pcurrentViewort;
		IDXGISwapChain *m_pswapChain;
		ID3D11Device *m_pdevice;
		ID3D11DeviceContext *m_pdevicecontext;
		ID3D11RenderTargetView *m_prendertargetviewBackBuffer;

		ID3D11Buffer *m_pbufferViewportStyle;

		SLightStructure * m_alightstructure;
		SLightStructure * m_alightstructureApplied;
		SLightStructureAdditional * m_alightstructureadditional;
		int m_iLightAllocs;

		D3D11_BUFFER_DESC m_bufferdescVertex;
		ID3D11Buffer *m_pVBuffer;
		ID3D11Buffer *m_pbufferLights;
		ID3D11ShaderResourceView *m_pshaderresourceviewLights;
		SVertexBuffer *m_pvertexGeo;
		CDXBuffers m_dxbuffers;

		SObjectShaderConstants m_objectshaderconstants;
		SObjectShaderConstants m_objectshaderconstantsParallelProjection;
		SObjectShaderConstants m_objectshaderconstantsParallelProjectionMirror;
		ID3D11SamplerState *m_psamplerstateLinearWrap;
		ID3D11SamplerState *m_psamplerstateLinearClamp;
		ID3D11SamplerState *m_psamplerstateLinearMirror;
		ID3D11InfoQueue * m_pInformationQueue;
		int m_iCurMsg;
		ID3D11Query * m_pEventQuery;

		// Depth Stencil:
		ID3D11DepthStencilView *m_pdepthstencilview;
		ID3D11Texture2D *m_ptextureDepthStencil;
		ID3D11ShaderResourceView * m_pshaderresourceviewDepthStencil;

		// Hauptshader: 
		ID3D11PixelShader *m_ppixelshader;
		ID3D11VertexShader *m_pvertexshader;
		ID3D11InputLayout *m_pinputlayout;
		D3D11_INPUT_ELEMENT_DESC* m_pinputLayoutDesc;
		ID3D11Buffer *m_pbufferProjectionMatrix;
		ID3D11Buffer *m_pbufferTexInfo;
		ID3D11Buffer *m_pbufferGPU;
		SMaterialParametersHost * m_amaterialparameters;
		SViewportstyleBufferHost m_viewportstylebuffer;
		D3D11_RASTERIZER_DESC * m_arasterizerdesc;
		ID3D11RasterizerState ** m_aprasterizerstate;
		ID3D11SamplerState * m_psamplerstateActive;

		// Shadowmapping
		SShadowmapShaderConstants m_shadowmapshaderconstants;
		ID3D11Buffer *m_pbufferProjectionMatrixShadowMap;
		ID3D11VertexShader *m_pvertexshaderShadowMap;
		ID3D11PixelShader *m_ppixelshaderShadowMap;
		ID3D11Texture2D *m_ptextureShadowMap;
		ID3D11DepthStencilView *m_pdepthstencilviewShadowMap;
		ID3D11ShaderResourceView *m_pshaderresourceviewShadowMap;
		ID3D11SamplerState *m_psamplerstateShadow;

		// Multiple Targets:

		ID3D11RenderTargetView ** m_aprendertargetviewMultiple;
		D3D11_RENDER_TARGET_VIEW_DESC * m_arendertargetviewdescMultiple;


		// Für Postprozessing (TB):
		D3D11_TEXTURE2D_DESC * m_atexdescPostprocessing;
		ID3D11Texture2D **m_aptexturePostprocessing; // Textur, in die das fertig gerenderte Bild zwischengespeichert wird, dort unterliegt es einem Postprozess und wird danach erst in den Backbuffer geschrieben
		ID3D11RenderTargetView ** m_aprendertargetviewPostprocessing;
		ID3D11ShaderResourceView ** m_apshaderresourceviewPostprocessing;
		D3D11_RENDER_TARGET_VIEW_DESC * m_arendertargetviewdescPostprocessing;
		D3D11_SHADER_RESOURCE_VIEW_DESC * m_ashaderresourceviewdescPostprocessing;
		SPostprocessingShaderConstants m_postprocessingShaderConstants;
		bool m_bFirstDrawPostprocessing;
		CGeoQuad m_zgQuadPostprocessing;
		CGeoTriangleList* m_pzgPostprocessing;
		CMaterial m_zmPostprocessing;
		bool m_bGeoIsSetPostprocessing;


		// Postprozess-Shader-Variablen:
		ID3D11VertexShader *m_pvertexshaderPostprocessing;
		ID3D11PixelShader *m_ppixelshaderPostprocessing;
		ID3D11InputLayout *m_pinputlayoutPostprocessing;
		ID3D11Buffer *m_pbufferProjectionMatrixPostprocessing;

		ID3D11Buffer *m_pbufferTexInfoPostprocessing;
		ID3D11Buffer *m_pbufferTexInfoDepth;

		SPostprocessingBufferHost m_viewportstylebufferPostprocessing;
		D3D11_RASTERIZER_DESC * m_arasterizerdescPostprocessing;
		ID3D11RasterizerState ** m_aprasterizerstatePostprocessing;

		// Depth-Shader:
		D3D11_TEXTURE2D_DESC * m_atexdescDepth;
		ID3D11Texture2D **m_aptextureDepth; // Textur, in die das fertig gerenderte Bild zwischengespeichert wird, dort unterliegt es einem Postprozess und wird danach erst in den Backbuffer geschrieben
//		ID3D11RenderTargetView ** m_aprendertargetviewDepth;
		ID3D11ShaderResourceView ** m_apshaderresourceviewDepth;
//		D3D11_RENDER_TARGET_VIEW_DESC * m_arendertargetviewdescDepth;
		D3D11_SHADER_RESOURCE_VIEW_DESC * m_ashaderresourceviewdescDepth;
		bool m_bFirstDrawDepth;
		CGeoQuad m_zgQuadDepth;
		CGeoTriangleList* m_pzgDepth;
		CMaterial m_zmDepth;
		bool m_bGeoIsSetDepth;



		ID3D11PixelShader *m_ppixelshaderDepth;
		ID3D11VertexShader *m_pvertexshaderDepth;
		ID3D11InputLayout *m_pinputlayoutDepth;
		D3D11_RASTERIZER_DESC * m_arasterizerdescDepth;
		ID3D11RasterizerState ** m_aprasterizerstateDepth;



		// OcculusRift:
		ID3D11VertexShader *m_pvertexShaderOcc;
		ID3D11PixelShader *m_ppixelShaderOcc;


		// Anderes:
		void CopyCHMatToXMFLOAT4X4(CHMat &m, XMFLOAT4X4 &f4);
		void CopyXMFLOAT4X4ToCHMat(XMFLOAT4X4 &f4, CHMat &m);



		// Alle Lichter:
		CLight **m_pplight;
		int m_iLights;

		int TexturePathExists(char *acPath);
		bool CreateTexture(CTexture * ptexture, int eDefaultImage, int & iTexture);

		void PassToGPU(unsigned int & idGeo, int & idTexture);
		void SetObjectDrawingParameters(CHMat &m, const unsigned int * pLightsAffectIndices, const unsigned int iLightsAffectCount);
		void SetSpriteDrawingParameters(CHMat &m);

		unsigned int GetMSAAQuality(unsigned int uiSamples, DXGI_FORMAT format);


		void InitShaderMain();
		void InitShaderPostprocessing();
	//	void InitShaderDepth();
		void InitShaderOcculus();
	public:
		EApiRender m_eApiRender;

		D3DXCOLOR m_d3dxcolor;
		D3DXCOLOR m_d3dxcolorPost;

		// Texturen:
		int m_iTextures;
		int m_iTextureAllocs;
		STextureInfo * m_atextureinfo;

		ID3D11Texture2D *m_ptextureBackBuffer;

		CDXUtilities* CDirectX11Basic::Utils();

		// void ChangeRenderStatePostprocessing(CViewport *pviewport);
		void RenderShadowMap(unsigned int & idGeo, CHMat &mGlobal);

		// custom buffer handling
		HRESULT CreateSRVFromFile(char const *pFileName, ID3D11ShaderResourceView **ppSRV);
		HRESULT CreateSamplerState(D3D11_SAMPLER_DESC const *pSamplerDesc, ID3D11SamplerState **ppSamplerState);

		void CopyBuffer(ID3D11Buffer *pDest, ID3D11Buffer *pSrc);

		// drawing
//		void SetShaderResources(int iShaderTypes, int iStartSlot, int iCount, ID3D11ShaderResourceView **apSRVs = 0);
//		void SetShaderSamplers(int iShaderTypes, int iStartSlot, int iCount, ID3D11SamplerState **apSamplers = 0);
	
		bool DeleteTexture(int iTexture);

		
		//debugging
		DXGI_ADAPTER_DESC QueryGraphicsCard(); // TODO: Wird nie aufgerufen!
		void InitProfiling();
		void WaitForShaderExecution();

		int m_iShaders;
		int m_iViewports;

	protected:
		void DrawPointList(ID3D11Buffer *pbuffer);
		void DrawLineList(ID3D11Buffer *pbuffer);
		void DrawTriangleTable(ID3D11Buffer *pbuffer, ID3D11Buffer *indexBuffer);
		void DrawTriangleList(ID3D11Buffer *pbuffer);
		void DrawTriangleStrip(ID3D11Buffer *pbuffer, ID3D11Buffer *indexBuffer);
	
		void DrawGeoPostprocessing(CViewport* pViewport);
		void DrawGeoDepth(CViewport* pViewport);

		void InitBackBuffer();
		ID3D11SamplerState * GetSamplerStateBasedOnTextureAddressMode(ETextureAddressMode eTextureAddressMode);

		void CalcCapacity(bool bAntialiasing);





		// -----------------------
		// andere Membervariablen:
		// -----------------------

		bool m_bFirstDraw;

		D3D11_TEXTURE2D_DESC m_texdescStencil;
		D3D11_DEPTH_STENCIL_VIEW_DESC m_depthstencilviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC m_shaderresourceviewdesc;

		D3D11_TEXTURE2D_DESC * m_atexdescShadow;
		D3D11_VIEWPORT * m_aviewport;
		D3D11_VIEWPORT * m_aviewportShadow;

		unsigned int m_uiSampleCount;
		unsigned int m_uiSampleQuality;

		D3D_FEATURE_LEVEL m_featurelevel;

		SMaterialInfo *m_amaterialinfo;
		int m_iMaterials;
		int m_iMaterialAllocs;

		// Variablen, um Objekte fuer die Transparenz bzw. Spites zu sortieren:
		CDrawObjects m_drawobjectsBackground;
		CDrawObjects m_drawobjectsSprite;
		CDrawObjects m_drawobjectsSpriteTransparent;
		CDrawObjects m_drawobjectsOpaque;
		CDrawObjects m_drawobjectsTransparent;
		CDrawObjects m_drawobjectsTransparentBinary;


		EShaderCreation m_eShaderCreation;
		EShaderAutoRecompilation m_eShaderAutoRecompilation;
		bool m_bInit;

		int m_iShadowMapWidth;
		int m_iShadowMapHeight;

		CHMat m_mProjectionOverlayMirror;
		CHMat m_mProjectionOverlay;
		CHMat m_mViewOverlay;
		CHMat m_mWorldOverlay;

		CShaderCache* m_pShaderCache;
	};

}