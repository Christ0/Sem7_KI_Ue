#pragma once
#include <Windows.h>
#include "../VektoriaMath/HMat.h"

//---------------------------------------------------
// CApiSound - Genormtes Interface für externe Sound-DLLs
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{

	/// <summary>Auswahlmöglichkeiten für die Sound-API.</summary>
	enum EApiSound
	{
		eApiSound_Null, // Macht nix, nur für Debugging und Testzwecke
		eApiSound_DirectSound, // Default
		eApiSound_XAudio2, // Noch nicht implementiert
		eApiSound_OpenAL, // Noch nicht implementiert
		eApiSound_Own	// Falls man eine eigene DLL schreiben will
	};

class CApiSound
{
public:

	//---------------------------
	// Geburt, Leben und Sterben:
	//---------------------------

	/// <summary>Initalisiert die Sound-API.</summary>
	/// <param name= "hwnd"> Handle auf das Window-Fenster, welches den Sound-Fokus hat. </param>
	virtual bool Init(HWND & hwnd) = 0;  

	/// <summary>Finalisiert die Sound-API.</summary>
	virtual void Fini() = 0;

	/// <summary>Updated und positioniert eine 3D-Sound-Quelle.	<para><\para>
	/// Wird jedes Frame für 3D-Sounds und nur für diese aufgerufen (Äquivalent zu Draw-Aufrufen beim Renderer).</summary>
	/// <param name= "mAudio"> Homogene Matrix, welche Position und Orientierung der Soundqquelle beschreibt. </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen ist. </param>
	/// <param name= "iTick"> Nummer des Ticks, zählt fortlaufend hoch, Achtung, fängt bei Überlauf wieder von INT_MIN an zu zählen.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void PosSound(CHMat & mAudio, float & fTimeDelta, int  & iTick, int & idSound) = 0; 

	/// <summary>Positioniert die Position und Orientierung des Zuhörers bei 3D-Audios.<para><\para>
	/// Wird jedes Frame Aufgerufen.</summary>
	/// <param name= "mListener"> Homogene Matrix, welche Position und Orientierung des Hörenden beschreibt. </param>
	/// <param name= "iAudio"> Instanzennummer des 3D-Sounds, Zählung ab inklusive 0.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void Listen(CHMat & mListener, int & iAudio, int & idSound) = 0; // Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener

	/// <summary>Fügt einen positionsunabhängigen ambienten Sound hinzu. Gibt eindeutige Sound-ID aus.</summary>
	/// <param name= "acFile"> ASCII-Pfad zu einem Soundfile (inklusive Suffix, z.B. "..\\MeinSound.wav"). </param>
	virtual int AddSound(char * acFile) = 0;

	/// <summary>Fügt einen 3D-Sound hinzu, den man im Raum platzieren kann. Gibt eindeutige Sound-ID aus.</summary>
	/// <param name= "acFile"> ASCII-Pfad zu einem Mono-Soundfile (inklusive Suffix, z.B. "..\\MeinSound.wav"). </param>
	virtual int AddSound3D(char * acFile, float & fRadius) = 0; // Initialisiert einen Klang mit 3D-Audio, die Funktion gibt die ID aus, falls die Initailisierung erfolgreich war, ansonsten -1

	// -----------------
	// Schaltfunktionen:
	// -----------------

	/// <summary>Startet einen Klang, spielt ihn einmal ab.</summary>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void Start(int & idSound) = 0;	// Startet einen Klang, spielt ihn einmal ab

	/// <summary>Startet einen Klang, spielt ihn immer wieder ab.</summary>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void Loop(int & idSound) = 0;	// Startet einen Klang, spielt ihn immer wieder ab

	/// <summary>Pausiert einen gestarteten Klang.</summary>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void Pause(int & idSound) = 0;	

	/// <summary>Beendet einen gestarteten Klang.</summary>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void Stop(int & idSound) = 0;	 

	// --------------------------
	// Parametrisierungsmethoden:
	// --------------------------

	/// <summary>Modifiziert die Lautstärke.</summary>
	/// <param name= "frVolume"> Lautstärke (0.0F=aus ... 1.0F= volles Rohr).</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void SetVolume(float & frVolume, int & idSound) = 0; 

	/// <summary>Modifiziert den Wirkradius in Units eines 3D-Klanges.</summary>
	/// <param name= "fRadius"> Wirkradius in Units.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	virtual void SetRadius(float & fRadius, int & idSound) = 0; 

	/// <summary>Schaltet Doppler-Effekt ein und parametrisiert gleichzeitigt die Stärke.</summary>
	/// <param name= "fFactor"> Stärke des Doppler-Effektes (fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F).</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	virtual void SetDoppler(float & fFactor, int & idSound) = 0; 

	/// <summary>Modifiziert die Frequenz in Hertz, falls nicht aufgerufen, wird der Sound mit der originalen Frequenz abgespielt.</summary>
	/// <param name= "fFrequency"> Frequenz in Hertz.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void SetFrequency(float & fFrequency, int & idSound) = 0;  

	/// <summary>Modifiziert den Pan bei ambienten Sounds (Stereorichtung).</summary>
	/// <param name= "fFrequency"> Stereoballanceeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts) .</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des ambienten Sounds.</param>
	virtual void SetPan(float & fPan, int & idSound) = 0; 

	/// <summary>Setzt die Frequenz zurück auf die originale Einstellung des Soundfiles.</summary>
	/// <param name= "fFrequency"> Frequenz in Hertz.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des Sounds.</param>
	virtual void ResetFrequency(int & idSound) = 0;  

	// ---------------------
	// Sound-LoD-Funktionen:
	// ---------------------

	/// <summary>Pausiert den Zuhörer beim 3D-Audio wegen Level of Detail.</summary>
	/// <param name= "iAudio"> Instanzennummer des 3D-Sounds, Zählung ab inklusive 0.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	virtual void PauseCauseLoD(int & iAudio, int & idSound) = 0; 

	/// <summary>Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort.</summary>
	/// <param name= "iAudio"> Instanzennummer des 3D-Sounds, Zählung ab inklusive 0.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	virtual void ContinueCauseLoD(int & iAudio, int & idSound) = 0;  

	// ---------------------
	// Amplituden-Funktionen:
	// ---------------------

	/// <summary>Gibt die aktuelle Amplitude des Sounds in einer Skala zwischen -1 und +1 aus.</summary>
	/// <param name= "iAudio"> Instanzennummer des 3D-Sounds, Zählung ab inklusive 0.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	virtual float GetAmplitudeCurrent(int & iAudio, int & idSound) = 0; 

	/// <summary>Gibt die gemittelte Amplitude des Sounds in einer Skala zwischen -1 und +1 aus.</summary>
	/// <param name= "iAudio"> Instanzennummer des 3D-Sounds, Zählung ab inklusive 0.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	/// <param name= "iSamples"> Anzahl der letzten Samples, die für die Mittelung berücksichtigt werden.</param>
	virtual float GetAmplitudeAverage(int & iAudio, int & idSound, int & iSamples) = 0; 

	/// <summary>Gibt die maximale Amplitude des Sounds in einer Skala zwischen -1 und +1 aus.</summary>
	/// <param name= "iAudio"> Instanzennummer des 3D-Sounds, Zählung ab inklusive 0.</param>
	/// <param name= "idSound"> Eindeutige Identifikationsnummer des 3D-Sounds.</param>
	/// <param name= "iSamples"> Anzahl der letzten Samples, die für MAximalwertberechnung die berücksichtigt werden.</param>
	virtual float GetAmplitudeMax(int & iAudio, int & idSound, int & iSamples) = 0; 

};

}