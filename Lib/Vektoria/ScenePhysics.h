#pragma once
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Quaternion.h"

enum ESceneKind
{
	eSceneKind_Air,
	eSceneKind_Water,
	eSceneKind_Vacuum,
	eSceneKind_SelfDefined
};

namespace Vektoria
{

	class CScene;

	class CScenePhysics 
	{
		friend class CScene;
		friend class CPlacementPhysics;
	protected:

		///<summary> Wird jeden Tick automatisch von �bergeordneter Hierarchie aufgerufen.</summary>
		///<param name=fTimeDelta>Zeitspanne in Sekunden, die seit dem letzen Tick verstrichen ist</param>
		void Tick(float & fTimeDelta);

	public:
		///<summary> Konstruktor.</summary>
		CScenePhysics(CScene * pscene);

		///<summary> Destruktor.</summary>
		~CScenePhysics();

		///<summary> Kopieroperator, kopiert Werte ins vorliegende ScenePhysics.</summary>
		///<param name=placement>PlacementPhysics, welches in das vorliegende ScenePhysics kopiert wird</param>
		CScenePhysics operator=(CScenePhysics & scenephysics);

		///<summary> Kopiert Werte des Parameters scenephysics ins vorliegende ScenePhysic.</summary>  
		///<param name=placement>PlacementPhysics, welches in das vorliegende ScenePhysics kopiert wird</param>
		void Copy(CScenePhysics & scenephysics);

		///<summary> Initialisiert die Szene mit den wichtigsten physikalischen Parametern.</summary>
		void Init(ESceneKind escenekind);

		// ------------------------------
		// Parametrische Membervariablen:
		// ------------------------------

		///<summary> Art der Szene.</summary>
		ESceneKind m_eSceneKind;

		///<summary> Temperatur in Celsius (default = 20 Grad Celsius).</summary>
		float m_fTemperature;

		///<summary> Wasser- bzw. Luftdruck (bei NN=0).</summary>
		float m_fAirPressure;    

		///<summary> Magnetische Feldst�rke.</summary>
		CHVector m_vMagneticField;	   

		///<summary> Elektrische Feldst�rke.</summary>
		CHVector m_vElectricField;

		///<summary> Volatilit�t der Wind-bzw. Wasserbewegung. (0=Wind kommt immer mit gleichem Betrag aus einer Richtung, je h�her, desto mehr variiert das.)</summary>
		float m_frWindVolatility; 

		///<summary> Durchschnittliche Wellenl�nge der Volatilit�t der Wind- bzw. Wasserbewegung. </summary>
		float m_fWindWavelength;

		///<summary> Maximale Windgeschwindigkeit.</summary>
		float m_fWindVelocityMax;

		///<summary> Winkel der Wasser- bzw. Windrichtung. (0 = Osten ... HALFPI = Norden ... PI = Westen ... THREEHALFPI = S�den)</summary>
		float m_faWindDirection;

		///<summary> Volatilit�t der Winkel der  Wasser- bzw. Windrichtung. (0 = Wind bl�st immer aus einer Richtung... TWOPI = Wind kommt aus allen Richtungen )</summary>
		float m_faWindDirectionVolatility;

		///<summary> Erdbeschleunigungsvektor (default = (0,-9.81 m/s^2, 0,0)).</summary>
		CHVector m_vGravity;


		//----------------------------
		// Berechnete Membervariablen:
		//----------------------------

		///<summary> Aktuelle Wasser- bzw. Windgeschwindigkeit und -richtung.</summary>
		CHVector m_vWindVelocity;

		///<summary> Wasser- bzw. Windgeschwindigkeiten.</summary>
		CGraphNoise * m_pgraphnoiseWindVelocity;

		///<summary> Wasser- bzw. Windrichtungen.</summary>
		CGraphNoise * m_pgraphnoiseWindDirection;
		
		/*
		///<summary> N�chste aktuellen Wellenl�nge der Volatilit�t der Wind-bzw. Wasserbewegung. </summary>
		float m_fWindWavelengthVelocityNext;

		///<summary> Phasenzeit der n�chsten aktuellen Wellenl�nge der Volatilit�t der Wind-bzw. Wasserbewegung. </summary>
		float m_fTimeWavelengthVelocityNext;

		///<summary> Amplitude der n�chsten aktuellen Wellenl�nge der Volatilit�t der Wind-bzw. Wasserbewegung. </summary>
		float m_fAmplitudeVelocityNext;

		///<summary> N�chste aktuelle Wellenl�nge der Wind-bzw. Wasserbewegungsrichtung. </summary>
		float m_fWindWavelengthDirectionNext;

		///<summary> Phasenzeit der n�chsten aktuellen Wellenl�nge der Volatilit�t der Wind-bzw. Wasserbewegungsrichtung. </summary>
		float m_fTimeWavelengthDirectionNext;

		///<summary> N�chster Amplitudenwinkel der  Wasser- bzw. Windrichtung.</summary>
		float m_faAmplitudeDirectionNext;
		*/
	protected:

		///<summary> Pointer auf die �bergeordnete Szene.</summary>
		CScene * m_pscene;
	};

}
