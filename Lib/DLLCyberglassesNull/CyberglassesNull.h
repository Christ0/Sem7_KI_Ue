#pragma once
#include "..\Vektoria\ApiCyberglasses.h"

namespace Vektoria
{
	class CCyberglassesNull : public CApiCyberglasses
	{
	public:

		//-----------------------
		// Schnittstellenroutinen
		//-----------------------

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

		// Haptic:
		void Haptic(unsigned int & iController, int & iAxis, float & fr);

		// Rendering:
		void SetTextureEyeLeft(void * pRenderTexture);
		void SetTextureEyeRight(void * pRenderTexture);


	};
}
