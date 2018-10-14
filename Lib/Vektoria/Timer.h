#pragma once

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#endif
#ifdef LINUX
#include <sys/time.h>
#else
#include <windows.h>
#endif

///<summary> Anzahl der letzten Ticks, die für die Frame-Rate-Berechnung herangezogen werden, je höher der Wert, desto genauer die Berechnung, aber desto weniger oft wird der Wert aktualisiert </summary>
#define I_FR_TICKS 30 

///<summary> Anzahl des Faktors, der für die Langzeit Frame-Rate-Berechnung herangezogen wird, wird intern mit I_FR_TICKS multipliziert </summary>
#define I_FR_LONG_TERM_FAKTOR 100 

namespace Vektoria
{

	class CTimer
	{
	protected:
		///<summary> Berechnet die Bildwiederholrate (vier Werte: der arithmetische Kurzzeitdurchschnitt, der arithmetische Langzeitdurchschnitt, die schlechteste und der beste Wert).</summary>
		void CalcFrameRate();
	public:
		///<summary> Konstruktor des Timers.</summary>
		CTimer(); 

		///<summary> Initialisiert den Timer neu, falls der Aufruf des Konstruktors zu lange her ist.</summary>
		void Init();    

		///<summary> Sollte jeden Tick aufgerufen werden, berechnet fTime (Zeit in Sekunden, die seit Init bzw. Konstruktor-Aufruf vergangen ist) und fTimeDelta (Zeit, seit dem letzten Tick vergangen ist).</summary>
		void Tick(float & fTime, float & fTimeDelta);	

		///<summary> Finalisiert den Timer.</summary>
		void Fini();	

		///<summary> Schaltet die Berechnung der Bildwiederholrate ein, FR-Berechnung kostet ein wenig Performanz, daher per Default aus.</summary>
		void SwitchFrameRateCalculationOn();	

		///<summary> Schaltet die Berechnung der Bildwiederholrate aus, FR-Berechnung kostet ein wenig Performanz, daher per Default aus.</summary>
		void SwitchFrameRateCalculationOff();	

		///<summary> Gibt den arithmetischen Kurzzeitdurchschnitt über die letzten Ticks (I_FR_TICKS) der FrameRate aus.</summary>
		float GetFrameRateAverage();			

		///<summary> Gibt den arithmetischen Langzeitdurchschnitt über die letzten Ticks (I_FR_TICKS*I_FR_LONG_TERM_FAKTOR)der FrameRate aus.</summary>
		float GetFrameRateAverageLong();		 
		
		///<summary> Gibt den schlechtesten Wert über die letzten Ticks (I_FR_TICKS) der FrameRate aus.</summary>
		float GetFrameRateMin();				 

		///<summary> Gibt den besten Wert über die letzten Ticks (I_FR_TICKS) der FrameRate aus.</summary>
		float GetFrameRateMax();				 

		///<summary> Startet den Timer.</summary>
		void Start();   

		///<summary> Stoppt den Timer.</summary>
		void Stop();	

		///<summary> Gibt vergangene Zeit seit Start in Sekunden aus.</summary>
		double GetElapsedTime();  

		///<summary> Gibt vergangene Zeit seit Start in Millisekunden aus.</summary>
		double GetElapsedTimeInMilliSeconds(); 

		///<summary> Gibt vergangene Zeit seit Start in Mikroisekunden aus.</summary>
		double GetElapsedTimeInMicroSeconds(); 

		//-----------------
		// Membervariablen:
		//-----------------


		///<summary> Startzeit.</summary>
		double m_dStartTime;

		///<summary> Stopzeit.</summary>
		double m_dStopTime;

		///<summary> Flag, ob Timer angehalten wurde.</summary>
		bool m_bStopped;

#ifdef LINUX
		timeval m_Frequency;
		timeval m_StartCount;
		timeval m_StopCount;
		timeval m_CountFirst;
		timeval m_Count;
		timeval m_CountOld;
#else
		LARGE_INTEGER m_Frequency;
		LARGE_INTEGER m_StartCount;
		LARGE_INTEGER m_StopCount;
		LARGE_INTEGER m_CountFirst;
		LARGE_INTEGER m_Count;
		LARGE_INTEGER m_CountOld;

		///<summary> Taktfrequenz des PCs.</summary>
		float m_fPCFrequency;

		///<summary> Eins durch Taktfrequenz des PCs.</summary>
		float m_fPCFrequencyInv;
#endif


		///<summary> Zeit in Sekunden, die seit dem letzten Init bzw. Konstuktoraufruf vergangen ist.</summary>
		float m_fTime;					

		///<summary> Zeit in Sekunden, die seit dem letzten Tick vergangen ist.</summary>
		float m_fTimeDelta;				

		///<summary> Flag, ob Bildwiederholrate berechnet werden soll.</summary>
		bool m_bCalcFrameRate;					
		
		///<summary> Frame Rate seit dem letzten Tick.</summary>
		float m_fFrameRate;				

		///<summary> Der arithmetische Kurzzeitdurchschnitt über die letzten Ticks der FrameRate.</summary>
		float m_fFrameRateAverage;		

		///<summary> Der arithmetische Kurzzeitdurchschnitt über die letzten Ticks der FrameRate.</summary>
		float m_fFrameRateAverageLong;			
		
		///<summary> Der schlechteste FR-Wert über die letzten Ticks der FrameRate.</summary>
		float m_fFrameRateMin;			

		///<summary> Der beste FR-Wert über die letzten Ticks der FrameRate.</summary>
		float m_fFrameRateMax;			

		///<summary> Maximale Framerate (wird nur befüllt, wenn Framerateberechnung angeschaltet ist).</summary>
		float m_fFRMax;  

		///<summary> Minimale Framerate (wird nur befüllt, wenn Framerateberechnung angeschaltet ist).</summary>
		float m_fFRMin;

		///<summary> Durchschnittliche Framerate (wird nur befüllt, wenn Framerateberechnung angeschaltet ist).</summary>
		float m_fFRAvg;

		///<summary> Durchschnittliche Langzeitframerate (wird nur befüllt, wenn Framerateberechnung angeschaltet ist).</summary>
		float m_fFRAvgLong;


	protected:
		///<summary> Liste für die durchschnittliche Framerateberechnung (wird nur befüllt, wenn Framerateberechnung angeschaltet ist).</summary>
		float m_afFRAvg[I_FR_TICKS];

		///<summary>  Liste für die durchschnittliche Langzeit-Framerateberechnung (wird nur befüllt, wenn Framerateberechnung angeschaltet ist).</summary>
		float m_afFRAvgLong[I_FR_LONG_TERM_FAKTOR];

		///<summary> Nummer des Frame für die durchschnittliche Framerateberechnung.</summary>
		int m_iFR;

		///<summary> Nummer des Frame für die durchschnittliche Langzeit-Framerateberechnung.</summary>
		int m_iFRLong;
	};

}