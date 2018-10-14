#pragma once

//--------------------------------------------------------------
// CGraphNoise: Klasse zur Konstuktion fraktaler Zufallsgraphen
// 
// Autor: Prof. Dr. Tobias Breiner
//--------------------------------------------------------------

namespace Vektoria
{

	enum EKindGraphNoise
	{
		eKindGraphNoise_Normal,
		eKindGraphNoise_MidQuadratic,
		eKindGraphNoise_LowQuadratic
	};

	class CGraphNoise
	{
	public:
		CGraphNoise(int iPotenzMax =15, float fTimeWaveMax = 32768.0f, EKindGraphNoise eKindGraphNoise = eKindGraphNoise_Normal);
		~CGraphNoise();


		float CalcValueNext(int & i);
		void SetTimeWaveMax(float & fTimeWaveMax);

		float GetValue(float & fTimeDelta);

		float GetValueAbs(float & fTime);

		float * m_afAdd;
		float * m_afValue;

		float m_afValueLast;
		float m_afValueNext;
		float m_fTimeWaveMax;
		float m_fTimeStep;
		float m_fTimeAccumulated;

		int m_iEntries;
		int m_iPotenzMax;
		EKindGraphNoise m_eKindGraphNoise;
	};

}