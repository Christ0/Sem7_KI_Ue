#pragma once
#include "Audio.h"

//--------------------------------------------------------------------------------------------
//  CAudios:  Klasse f�r Soundlisten
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte �nderung: 2011-08-07
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

class CAudios
{
	friend class CScene;
	friend class CPlacement;
protected:
	void Tick(CHMat & m, int & iTick, float & fTimeDelta);
public:

	CAudios(void);
	~CAudios(void);

	void Copy(CAudios & audios);

	CAudios operator=(CAudios & audios);

	void Init();
	bool Init(char *stringWavFile, int iAudios);
	void Fini();
	
	void Start();
	void Loop();
	void Stop();

	void SetVolume(float frVolume);

	void Add(CAudio * paudio);
	bool Sub(CAudio * paudio);

	CAudio * Make(char *stringWavFile);
	bool Kill(CAudio * paudio);

	void PauseCauseLoD(int iAudio);
	void ContinueCauseLoD(int iAudio);

	void Listen(CHMat & mListener, int iAudio); // Positioniert den Zuh�rer beim 3D-Audio mittels der globalen Matrix mListener

	CAudio ** m_apaudio;
	int m_iAudioAllocs;
	int m_iAllocBlock;
	int m_iAudios;
	int m_iAudio; // Akuelles Audio

};

}