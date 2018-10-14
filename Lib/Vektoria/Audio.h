#pragma once

#include "Node3D.h"
#include "windows.h" 
#include <stdio.h>
#include "ApiSound.h"

//---------------------------------------------------
// CAudio: Klasse für 3D-Raumklang
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------


enum EAudioState
{
	eAudioState_Slacking,
	eAudioState_Started,
	eAudioState_Looped,
	eAudioState_StartedAndPaused,
	eAudioState_LoopedAndPaused
};


namespace Vektoria
{

class CAudio: public CNode3D
{
	friend class CAudios;
	friend class CPlacment;
protected: 
	//-----------------
	// Methoden:
	//-----------------

	///<summary> Updated einen Klang mit 3D-Audio, muss bei jeden Frame aufgerufen werden, mAudio ist die globale Matrix der Klangquelle, fTimeDelta ist die verstrichene Zeit seit dem letzten Tick.</summary>
	/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
	/// <param name= "iTick"> Nummer des Ticks </param>
	/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
	void Tick(CHMat & mAudio, int  & iTick, float & fTimeDelta);
public:
	///<summary> Konstruktor.</summary>
	CAudio(void);

	///<summary> Destruktor.</summary>
	~CAudio(void);

	///<summary> Initialisiert einen Klang ohne 3D-Audio, dieser kann nicht in den Szenengraf eingebaut werden, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false.</summary>
	///<param name="acWavFile">ASCII-Pfadangabe eines WAV-Files.<para></para>
	/// Achtung! Muss Mono und WAV sein!!!</param>
	void Init(char * acWavFile);

	///<summary> Initialisiert einen Klang mit 3D-Audio, die Funktion gibt true aus, falls die Initailisierung erfolgreich war, ansonsten false.</summary>
	///<param name="acWavFile">ASCII-Pfadangabe eines WAV-Files.<para></para>
	/// Achtung! Muss Mono und WAV sein!!!</param>
	///<param name="fRadius">Radius, in der der Sound maximale Lautstärke hat (danach quadratische Abnahme).</param>
	void Init3D(char * acWavFile, float fRadius);

	///<summary> Finalisiert einen Klang, egal ob mit oder ohne 3D-Audio.</summary>
	void Fini(); 

	///<summary> Berechnet die Axis Aligned Bounding Boxen neu.</summary>
	virtual void UpdateAABB();

	///<summary> Positioniert den Zuhörer beim 3D-Audio mittels der globalen Matrix mListener. <para></para>
	/// Wird normalerweise automatisch von der übergeordneten Hierarchie aufgerufen</summary>
	///<param name="mListener">Nummer der Audioinstanz.</param>
	///<param name="iAudio">Nummer der Audioinstanz.</param>
	void Listen(CHMat & mListener, int iAudio);

	///<summary> Startet einen Klang, spielt ihn einmal ab.</summary>
	void Start();	

	///<summary> Startet einen Klang, spielt ihn immer wieder ab.</summary>
	void Loop();	

	///<summary> Pausiert einen gestarteten Klang.</summary>
	void Pause();	

	///<summary> Beendet einen gestarten Klang.</summary>
	void Stop();	

	///<summary> Modifiziert die Lautstärke (0.0F=aus 1.0F= volles Rohr).</summary>
	void SetVolume(float frVolume); 

	///<summary> Modifiziert den Wirkradius in Units eines 3D-Klanges.</summary> 
	///<param name="fRadius">Radius, in der der Sound maximale Lautstärke hat (danach quadratische Abnahme).</param>
	void SetRadius(float fRadius);

	///<summary> Modifiziert den Doppler-Faktor eines 3D-Klanges.</summary> 
	///<param name="fFactor"> Dopplerfaktor: fFactor=1.0: physikalisch richtiger Doppler-Effekt, fFactor=0.0: kein Doppler-Effekt; Default = 1.0F.</param>
	void SetDoppler(float fFactor); 

	///<summary> Setzt die Frequenz in Hertz, wenn nicht aufgerufen, wird die originale Frequenz des Samples genommen.</summary>
	///<param name="fFrequency"> Frequenz in Herz.</param>
	void SetFrequency(float fFrequency);

	///<summary> Setzt die Stereoeinstellungen zwischen links und rechts eines ambienten Sounds, wenn nicht aufgerufen, befindet sich der Sound in der Mitte.</summary>
	///<param name="fFrequency">  Stereoeinstellungen zwischen links und rechts (-1 = links, 0= Mitte, 1 = rechts).</param>
	void SetPan(float ftPan);  

	///<summary> Gibt die aktuelle Amplitude des Sounds in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!).</summary>
	///<param name="iAudio">Nummer der Audioinstanz.</param>
	float GetAmplitudeCurrent(int iAudio = 0);

	///<summary> Gibt die aktuelle Amplitude des Sounds in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!).</summary>
	///<param name="iSamples">Anzahl der letzten Werte, die für die Berechnung berücksichtigt werden.</param>
	///<param name="iAudio">Nummer der Audioinstanz.</param>
	float GetAmplitudeAverage(int iSamples, int iAudio = 0);

	///<summary> Gibt die maximale Amplitude des Sounds der letzten i Samples in einer Skala zwischen -1 und +1 aus (Achtung alpha, noch ungetestet!).</summary>
	///<param name="iSamples">Anzahl der letzten Werte, die für die Berechnung berücksichtigt werden.</param>
	///<param name="iAudio">Nummer der Audioinstanz.</param>
	float GetAmplitudeMax(int iSamples, int iAudio = 0);

	///<summary> Gibt true aus, wenn 3D-Audio, ansonsten false.</summary>
	bool Is3D(); 

	///<summary> Pausiert den Zuhörer beim 3D-Audio wegen LoD.</summary>
	///<param name="iAudio">Nummer der Audioinstanz.</param>
	void PauseCauseLoD(int iAudio);

	///<summary> Setzt den Zuhörer beim 3D-Audio nach LoD-Eintritt wieder fort.</summary>
	///<param name="iAudio">Nummer der Audioinstanz.</param>
	void ContinueCauseLoD(int iAudio);  

	///<summary> Lädt die Daten aus einer Vektoria-Audiodatei (.va).</summary>
	///<param name="acPath">ASCII-Pfadangabe der Audiodatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyAudio.va" oder ".\\Audios\\MyAudio.va" </param>
	void Load(char * acPath);

	///<summary> Speichert die Daten in eine Vektoria-Audiodatei (.va).</summary>
	///<param name="acPath">ASCII-Pfadangabe der Audiodatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyAudio.va" oder ".\\Audios\\MyAudio.va" </param>
	void Save(char * acPath);

	///<summary> Lädt eine Audiobeschreibung aus einer Vektoria Audiodatei (.va).</summary>
	///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
	///<param name="id">Eindeutige Identifikationsnummer der zu ladenden Szene</param>
	///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
	void Load(CFileVektoria & filevektoria, int id, float fVersion = 14.11f);

	///<summary> Speichert eine Audiobeschreibung in eine Vektoria Audiodatei (.va).</summary>
	///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
	///<param name="bWithID">Soll die eigene Identifikationsnummer in das Szenenfile mit abgespeichert werden?</param>
	void Save(CFileVektoria & filevektoria, bool bWithID = false);

	//-----------------
	// Membervariablen:
	//-----------------

	///<summary> Flag, ob es sich um einen 3D-Sound (true) oder einen Ambient-Sound (false) handelt.</summary>
	bool m_b3D;

	///<summary> Flag, ob Doppler-Effekt berechnet werden soll.</summary>
	bool m_bDoppler; 

	///<summary> Stärke der Doppler-Berechnung.</summary>
	float m_fDopplerFactor;

	///<summary> Eingestellter Wirkradius in Units eines 3D-Klanges, Default = 1.0F.</summary>
	float m_fRadius;  

	///<summary> eingestellte Lautstärke (0.0F=aus 1.0F= volles Rohr), Default = 1.0F.</summary> 
	float m_frVolume; 

	///<summary> Frequenz in Hertz, wenn nicht aufgerufen wird die originale Frequenz des Samples genommen.</summary>
	float m_fFrequency; 

	///<summary> eingestellte Stereobalance (-1.0F=links, 0.0= normal bzw. Mitte, 1.0F= rechts), Default = 1.0F.</summary> 
	float m_ftPan;	

	///<summary> Flag, ob beim nächsten Tick der Sound geloopt werden soll.</summary>
	bool m_bHaveToLoop;

	///<summary> Flag, ob beim nächsten Tick der Sound gestartet werden soll.</summary>
	bool m_bHaveToStart;

	///<summary> Flag, ob beim nächsten Tick der Sound angehalten werden soll.</summary>
	bool m_bHaveToStop;

	///<summary> Flag, ob beim nächsten Tick der Sound pausiert werden soll.</summary>
	bool m_bHaveToPause;

	///<summary> Flag, ob beim nächsten Tick eine Doppler-Berechnung stattfinden soll.</summary>
	bool m_bHaveToSetDoppler;

	///<summary> Flag, ob beim nächsten Tick der Radius angepasst werden soll.</summary>
	bool m_bHaveToSetRadius;

	///<summary> Flag, ob beim nächsten Tick die Lautstärke angepasst werden soll.</summary>
	bool m_bHaveToSetVolume;

	///<summary> Flag, ob beim nächsten Tick der Pan angepasst werden soll.</summary>
	bool m_bHaveToSetPan;

	///<summary> Flag, ob beim nächsten Tick die Frequenz angepasst werden soll.</summary>
	bool m_bHaveToSetFrequency;

	///<summary> Position des Kameramikrophons des letzten Ticks.</summary>
	CHVector m_vListenerOld;

	///<summary> Position der Soundquelle des letzten Ticks.</summary>
	CHVector m_vAudioOld;

	///<summary> Flag, welchen Abspielstatus der Sound hat.</summary>
	EAudioState m_eAudioState;

	///<summary> Flag, ob der Sound schon initialisiert wurde.</summary>
	bool m_bInitialized;

	///<summary> Flag, ob der Sound schon comitted wurde.</summary>
	bool m_bFirstCommit;

	///<summary> Flag, ist true beim ersten Tick.</summary>
	bool m_bFirstTick;

	///<summary> ID des Sounds.</summary>
	int m_idSound;

	///<summary> Pfad des SoundFiles.</summary>
	char m_acWavFile[MAX_PATH];
};

}