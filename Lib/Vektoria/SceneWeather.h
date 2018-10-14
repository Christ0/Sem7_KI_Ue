#pragma once


//---------------------------------------------------
// CScene: Klasse für ein Szenenwetterobjekt 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{
	class CScene;
	class CPlacement;
	class CGeoDome;
	class CGeoQuad;
	class CLightSpot;
	class CMaterial;
	class CEmitter;


	class CSceneWeather
	{
	public:
		///<summary> Konstruktor.</summary>
		CSceneWeather(CScene * pscene);

		///<summary> Destruktor.</summary>
		~CSceneWeather();

		///<summary> Ruft den Himmel ins Leben.</summary>
		void Init(CPlacement * pzpCamera);

		///<summary> Tick.</summary>
		void Tick(float & fTimeDelta);

		///<summary> Der Himmel wird zerstört, Götterdämmerung!</summary>
		void Fini();

		// ----------------
		// Membervariablen:
		// ----------------

		///<summary> Radius der Himmelssphäre.</summary>
		float m_fRadiusSky;

		///<summary> Radius der Sonnensphäre.</summary>
		float m_fRadiusSun;

		///<summary> Fraktionale Tageszeit.</summary>
		float m_frTimeOfDay;

		///<summary> Fraktionale Jahreszeit.</summary>
		float m_frTimeOfYear;

		///<summary> Deklination des Planeten.</summary>
		float m_faDeclination;
			
		///<summary> Tageszeit-Winkel.</summary>
		float m_faDay;

		///<summary> Jahreszeit-Winkel.</summary>
		float m_faYear;

		///<summary> Maximale Elevation der Sonne.</summary>
		float m_faMaxSunHeight;

		///<summary> Längengrad im Bogenmaß.</summary>
		float m_faLongitude;

		///<summary> Höhengrad im Bogenmaß.</summary>
		float m_faLattitude;

		///<summary> Niederschlag.</summary>
		float m_fPrecipitation;
		
		///<summary> Bewölkung.</summary>
		float m_frCloudStrength;

		///<summary> Nebligkeit.</summary>
		float m_fFog;

		///<summary> Flag, ob Tages- und Nachtzeit automatisch wechseln sollen.</summary>
		bool m_bFlow;

		///<summary> Faktor mit der die Zeit beschleunigt werden kann (Bei 24.0f dauert z.B. ein virtueller Tag nur eine Stunde).</summary>
		float m_fFlowFactor;

		///<summary> Schnee, der auf der Erde liegt.</summary>
		float m_fSnowFallen;

		///<summary> Sonnenplacement.</summary>
		CPlacement * m_pzpSun;

		///<summary> Placement für das Niederschlags-Quad.</summary>
		CPlacement * m_pzpPrecipitation;

		///<summary> Niederschlagsgeo.</summary>
		CGeoQuad * m_pzgPrecipitation;

		///<summary> Placement für das Schnee-Quad.</summary>
		CPlacement * m_pzpSnow;

		///<summary> Schneegeo.</summary>
		CGeoQuad * m_pzgSnow;



		///<summary> Placement für das Nebel-Quad.</summary>
		CPlacement * m_pzpFog;

		///<summary> Nebelgeo.</summary>
		CGeoQuad * m_pzgFog;

		///<summary> Placement für Domes.</summary>
		CPlacement * m_azpSky;

		///<summary> Domes.</summary>
		CGeoDome * m_azgSky;

		///<summary> Dome-Materialien.</summary>
		CMaterial * m_azmSky;

		///<summary> Sonnenlicht.</summary>
		CLightSpot * m_pzlSun;

		///<summary> Nebelemitter.</summary>
		CEmitter * m_pzeFog;

		///<summary> Regenemitter.</summary>
		CEmitter * m_pzeRain;

		///<summary> Schneeemitter.</summary>
		CEmitter * m_pzeSnow;

		///<summary> Material für die Emittergeometrien.</summary>
		CMaterial * m_pzmNone;

	protected:

		///<summary> Pointer auf die übergeordnete Szene.</summary>
		CScene * m_pscene;

		///<summary> Pointer auf das Kamera-Placmenet.</summary>
		CPlacement * m_pzpCamera;

	};

}