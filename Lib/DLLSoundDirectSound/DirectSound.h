#pragma once

//------------------------------------------------------------------
// DirectSound: Klasse zur DirectX-Anbindung
//
// Autor: Prof. Dr. Tobias Breiner 
// Firma: Vektoria UG (haftungsbeschränkt)
//-------------------------------------------------------------------


#ifdef COMPILE_SOUNDDIRECTSOUND
#define SOUNDDIRECTSOUND_EXPORT __declspec(dllexport)
#else
#define SOUNDDIRECTSOUND_EXPORT __declspec(dllimport)
#endif


#include <stdio.h>
#include "windows.h" 
#include <mmsystem.h>

#include "..//Vektoria//ApiSound.h"
#include "..//VektoriaMath//HMat.h"
#include "..//VektoriaMath//HVector.h"
#include "..//Vektoria//UtilLogFile.h"
#include "..//VektoriaMath//Ray.h"



#include "dsound.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

#pragma comment(lib, "winmm.lib") // Ist das überhaupt notwedig einzubinden?

#define HAVETOSLACK 0
#define HAVETOLOOP 1 
#define HAVETOSTART 2 
#define HAVETOSTOP 3
#define ISLOOPING 4 
#define HASSTARTED 5




namespace Vektoria
{

	class CSingleSound
	{
	public:
		CSingleSound();

		void Init(IDirectSound8* m_lpDS);
		void Init3D(float & fRadius, IDirectSound8* m_lpDS);
		void Tick(CHMat & mAudio, float & fTimeDelta, int & iTick);
		void Fini();

		void Start();	// Startet einen Klang, spielt ihn einmal ab
		void Loop();	// Startet einen Klang, spielt ihn immer wieder ab
		void Pause();	// Pausiert einen gestarteten Klang
		void Stop();	// Beendet einen gestarten Klang 

		void SetVolume(float & frVolume); // Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr) 
		void SetRadius(float & fRadius); // Modifiziert den Wirkradius in Units eines 3D-Klanges 
		void SetDoppler(float & fFactor); // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
		void SetFrequency(float & fFrequency); // Setzt die Frequenz in Hertz
		void SetPan(float & ftPan); // Stereoeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts) 
		void ResetFrequency(); // Setzt die Frequenz auf die originale Frequenz 

		void PauseCauseLoD(int & iAudio); // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
		void ContinueCauseLoD(int & iAudio);  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 
		void Listen(CHMat & mListener, int & iAudio); // Hilfsroutine für 3D-Soundberechnung, positioniert Mikrop im 3D-Raum

		float GetAmplitudeCurrent(int & iAudio); // Gibt die aktuelle Amplitude des Sounds des aktuellen Samples in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!)
		float GetAmplitudeAverage(int & iAudio, int & iSamples); // Gibt die aktuelle Amplitude des Sounds der letzten i Samples in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!)
		float GetAmplitudeMax(int & iAudio, int & iSamples); // Gibt die maximale Amplitude des Sounds der letzten i Samples in einer Skala zwischen -1 und +1 ausgeben (Achtung alpha, noch ungetestet!)

		IDirectSoundBuffer8** m_alpDSBSecondary;
		IDirectSound8* m_lpDS;


		IDirectSound3DBuffer8** m_alpDS3DBSecondary;
		int m_iSecondary3DBufferAllocs;
		int m_iSecondary3DBufferInits;

		int m_iInstances;

		bool m_bDoppler; // true, wenn Doppler-Effekt berechnet werden soll
		float m_fRadius;  // Eingestellter Wirkradius in Units eines 3D-Klanges, Default = 1.0F 
		float m_frVolume; // eingestellte Lautstärke (0.0F=aus 1.0F= volles Rohr), Default = 1.0F 
		bool m_bHaveToLoop;
		bool m_bHaveToStart;
		bool m_bHaveToStop;

		bool m_bHaveToSetVolume;
		bool m_bHaveToSetFrequency;
		bool m_bHaveToSetPan;

		int * m_aeStatus; // 0 = not initialized, 1 = gestartet, 2 = looping, 3 = stopped, 4 = paused while started, 5 = paused  while looping

		IDirectSoundBuffer* m_lpDSB;
		long m_lVolume;
		long m_lFrequency;
		long m_lPan;

		bool CreateSecondaryBuffer(int iAudio);
		int  m_iAllocStep;
		// Neu für 3D audio: 
		bool m_b3D;
		IDirectSound3DListener8* m_lpListener;



		CHVector m_vListenerOld;
		CHVector m_vAudioOld;


		struct WaveHeaderType
		{
			char chunkId[4];				//  0.. 3 Enthält "RIFF" im ASCII-Format
			unsigned long chunkSize;		//  4.. 7 Größe des Datenfeldes minus 8 Byte (also die Größe nach diesem Feld)
			char format[4];					//  8..11 Enthält "WAVE"
			char subChunkId[4];				// 12..15 Enthält "fmt "
			unsigned long subChunkSize;		// 16..19 Hier sollte normalerweise 16 for PCM, also die Größe restlichen Subchunks, die dieser Variable folgt, stehen, manchmal steht auch 18 da, dann ist der Header 2 Byte länger
			unsigned short audioFormat;	    // 20, 21 Hier sollte der Wert 1 stehen (unkomprimiert, Linear quantization), Werte größer 1 stehen für komprimierte Daten
			unsigned short numChannels;		// 22, 23 1 = Mono, 2 = Stereo
			unsigned long sampleRate;		// 24..27 Samplerate (z.B. 8000, 44100, etc.)
			unsigned long bytesPerSecond;   // 28..31 == SampleRate * NumChannels * BitsPerSample/8
			unsigned short blockAlign;		// 32, 33 == NumChannels * BitsPerSample / 8 (also die Anzahl der Byte für einen Abtastwert)
			unsigned short bitsPerSample;	// 34, 35 Also 8 bits = 8, 16 bits = 16, etc.
			unsigned short asAdditional[20];// Achtung! Hier eventuell noch 2 oder 4 Bytes für extra Parameter (siehe subChunkSize)
			char dataChunkId[4];			// 36(+2)..39 Enthält data"
			unsigned long dataSize;			// 40(+2)..== NumSamples * NumChannels * BitsPerSample/8
		};

		// Hilfsmethode für LoadfWave und LoadWave3D
		bool LoadWaveHeader(char *acFile); 
		bool LoadWave(char *acFile);
		bool LoadWave3D(char *acFile);
		float m_fTimeDelta;

		char m_acFile[MAX_PATH];
		FILE * m_file;
		WaveHeaderType m_waveFileHeader;
		DSBUFFERDESC m_bufferdescPrimary;
		WAVEFORMATEX m_waveformatPrimary;
		DSBUFFERDESC m_bufferdescSecondary;
		WAVEFORMATEX m_waveformatSecondary;
		int m_iSampleRate;
		int m_iBitsPerSample;
		float m_fMaxAmplitudePossible;
		float m_fMaxAmplitudePossibleHalf;
		int m_iTick;
		bool m_bInitialized;


	};

	class SOUNDDIRECTSOUND_EXPORT CDirectSound : public CApiSound
	{
	public:
		// CDirectSound(void);
		// ~CDirectSound(void);

		// Geburt, Leben und Sterben:
		virtual bool Init(HWND & hwnd); // Initialisiert die Sound-Api
		virtual void Fini(); // Finalisiert einen Klang, egal ob mit oder ohne 3D-Audio

		virtual int AddSound(char *stringWavFile);  // Initialisiert einen Klang ohne 3D-Audio, dieser kann nicht in den Szenengraf eingebaut werden, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false 
		virtual int AddSound3D(char *stringWavFile, float & fRadius); // Initialisiert einen Klang mit 3D-Audio, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false
		virtual void PosSound(CHMat & mAudio, float & fTimeDelta, int & iTick, int & idSound); //Updated einen Klang mit 3D-Audio, muss bei jeden Frame aufgerufen werden, mAudio ist die globale Matrix der Klangquelle, fTimeDelta ist die verstrichene Zeit seit dem letzten Tick 

		virtual void Listen(CHMat & mListener, int & iAudio, int & idSound); // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener

		virtual void Start(int & idSound);	// Startet einen Klang, spielt ihn einmal ab
		virtual void Loop(int & idSound);	// Startet einen Klang, spielt ihn immer wieder ab
		virtual void Pause(int & idSound);	// Pausiert einen gestarteten Klang
		virtual void Stop(int & idSound);	// Beendet einen gestarten Klang 

		virtual void SetVolume(float & frVolume, int & idSound); // Modifiziert die Lautstärke (0.0F=aus 1.0F=volles Rohr) 
		virtual void SetRadius(float & fRadius, int & idSound); // Modifiziert den Wirkradius in Units eines 3D-Klanges 
		virtual void SetDoppler(float & fFactor, int & idSound); // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
		virtual void SetFrequency(float & fFrequency, int & idSound); // Setzt die Frequenz in Herz
		virtual void ResetFrequency(int & idSound); // Setzt die Frequenz auf die originale Frequenz 
		virtual void SetPan(float & ftPan, int & idSound); // Setzt den Pan 

		virtual void PauseCauseLoD(int & iAudio, int & idSound); // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
		virtual void ContinueCauseLoD(int & iAudio, int & idSound);  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 

		virtual float GetAmplitudeCurrent(int & iAudio, int & idSound); // Gibt die aktuelle Amplitude des Sounds in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!)
		virtual float GetAmplitudeAverage(int & iAudio, int & idSound, int & iSamples); // Gibt die aktuelle Amplitude des Sounds in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!)
		virtual float GetAmplitudeMax(int & iAudio, int & idSound, int & iSamples); // Gibt die maximale Amplitude des Sounds der letzten i Samples in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!)


		bool m_bFirstCommit;
		IDirectSound8* m_lpDS;

		int m_iSounds;
		int m_iSoundsAllocated;
		int m_iAllocStep;
		CSingleSound * m_asinglesound;

		bool m_bInitialized;
		HWND m_hwnd;


	};




}