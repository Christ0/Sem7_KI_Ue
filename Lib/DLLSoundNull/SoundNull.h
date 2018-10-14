#pragma once

//------------------------------------------------------------------
// SoundNull: Klasse zur Null-Sound-Anbindung
//
// Autor: Prof. Dr. Tobias Breiner 
//-------------------------------------------------------------------

#include "../Vektoria/ApiSound.h"
#include "..//VektoriaMath/HMat.h"

#ifdef COMPILE_SOUNDNULL
#define SOUNDNULL_EXPORT __declspec(dllexport)
#else
#define SOUNDNULL_EXPORT __declspec(dllimport)
#endif


namespace Vektoria
{

	class SOUNDNULL_EXPORT CSoundNull : public CApiSound
	{
	public:
		// Geburt, Leben und Sterben:
		bool Init(HWND & hwnd);  // Initialisiert die Sound-Api
		void Fini();

		// Wird jedes Frame Aufgerufen (Äquivalent zu Draw-Aufrufen beim Renderer):
		void Listen(CHMat & mListener, int & iAudio, int & idSound); // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener
		void PosSound(CHMat & mAudio, float & fTimeDelta, int & iTick, int & idSound); //Updated einen Klang mit 3D-Audio, muss bei jeden Frame aufgerufen werden, mAudio ist die globale Matrix der Klangquelle, fTimeDelta ist die verstrichene Zeit seit dem letzten Tick 
		int AddSound(char *stringWavFile);  // Initialisiert einen Klang ohne 3D-Audio, dieser kann nicht in den Szenengraf eingebaut werden, die Funktion gibt die ID aus, falls die Initailisierung erfolgreich war, ansonsten -1 
		int AddSound3D(char *stringWavFile, float & fRadius); // Initialisiert einen Klang mit 3D-Audio, die Funktion gibt die ID aus, falls die Initailisierung erfolgreich war, ansonsten -1

															  // Schaltfunktionen:
		void Start(int & idSound);	// Startet einen Klang, spielt ihn einmal ab
		void Loop(int & idSound);	// Startet einen Klang, spielt ihn immer wieder ab
		void Pause(int & idSound);	// Pausiert einen gestarteten Klang
		void Stop(int & idSound);	// Beendet einen gestarten Klang 

									// Parametrisierungsfunktionen:
		void SetVolume(float & frVolume, int & idSound); // Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr) 
		void SetRadius(float & fRadius, int & idSound); // Modifiziert den Wirkradius in Units eines 3D-Klanges 
		void SetDoppler(float & fFactor, int & idSound); // fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F
		void SetFrequency(float & fFrequency, int & idSound); // Setzt die Frequenz in Hertz
		void SetPan(float & ftPan, int & idSound); // Stereoeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts) 
		void ResetFrequency(int & idSound); // Setzt die Frequenz auf die originale Frequenz 

											// Sound-LoD-Funktionen:
		void PauseCauseLoD(int & iAudio, int & idSound); // Pausiert den Zuhörer beim 3D-Audio wegen LoD 
		void ContinueCauseLoD(int & iAudio, int & idSound);  // Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort 

															 // GetAmplitude-Funktionen
		float GetAmplitudeCurrent(int & iAudio, int & idSound); // Soll die Amplitude des aktuellen Samples in einer Skala zwischen -1 und +1 ausgeben (Achtung, noch ungetestet!)
		float GetAmplitudeAverage(int & iAudio, int & idSound, int & iSamples); // Soll die aktuelle gemittelte Amplitude des Sounds der letzten i Samples in einer Skala zwischen -1 und +1 ausgeben (Achtung, noch ungetestet!)
		float GetAmplitudeMax(int & iAudio, int & idSound, int & iSamples); // Soll die aktuelle maximale Amplitude des Sounds der letzten i Samples in einer Skala zwischen -1 und +1 ausgeben (Achtung, noch ungetestet!)

	};

}

