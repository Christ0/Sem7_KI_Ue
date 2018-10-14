#pragma once
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Quaternion.h"


namespace Vektoria
{

	class CPlacement;

	class CPlacementPhysics 
	{
		friend class CPlacement;
		friend class CScenePhysics;
	protected:

		///<summary> Wird jeden Tick automatisch von übergeordneter Hierarchie aufgerufen.</summary>
		void Tick(float & fTimeDelta);

	public:
		///<summary> Konstruktor.</summary>
		CPlacementPhysics(CPlacement * pplacement);

		///<summary> Destruktor.</summary>
		~CPlacementPhysics();

		///<summary> Kopieroperator, kopiert Werte ins vorliegende PlacementPhysics.</summary>
		///<param name=placement>PlacementPhysics, welches in das vorliegende PlacementPhysics kopiert wird</param>
		CPlacementPhysics operator=(CPlacementPhysics & placementphysics);

		///<summary> Kopiert Werte des Parameters placementphysics ins vorliegende PlacementPhysic.</summary>  
		///<param name=placement>PlacementPhysics, welches in das vorliegende PlacementPhysics kopiert wird</param>
		void Copy(CPlacementPhysics & placementphysics);

		///<summary> Initialisiert Partikel mit physikalischen Parametern.</summary>
		void Init(float fMass, float fCW, bool bSolid);

		///<summary> Appliziert einen Drehmoment auf den Partikel, kann mehrfach angewendet werden.</summary>
		void ApplyTorque(CHVector vDistToCenter, CHVector vForce); 

		///<summary> Appliziert eine Kraft auf den Partikel, kann mehrfach angewendet werden.</summary>
		void ApplyForce(CHVector v); 

		///<summary> Applziert die normale Gravitationskraft (9.81 m/s^2) auf das Partikel. Die Gravitation wirkt in -Y-Richtung.</summary>
		void ApplyGravity(); 

		///<summary> Setzt die Erscheinungszeit des Partikels. (Zeit in Sekunden, die es braucht, bis der Partikel seine volle Größe bzw. Sichtbarkeit erreicht hat).</summary>
		void SetTimeToCome(float fTimeToCome);

		///<summary> Setzt die Bleibezeit des Partikels.(Zeit in Sekunden, die der Partikel in voller Größe bzw.Sichtbarkeit lebt).</summary>
		void SetTimeToStay(float fTimeToStay);

		///<summary> Setzt die Verschwindezeit des Partikels.(Zeit in Sekunden, die es braucht, bis der Partikel wieder verschwunden ist)</summary>
		void SetTimeToFade(float fTimeToFade);

		///<summary> Berechnet die Gesamtlebenszeit aus den drei Unterzeiten.</summary>
		float CalcTimeOfLife();

		///<summary> Schreibt die wichtigsten Physikalischen Daten ins Vektoria LogFile.</summary>
		void Log();

		///<summary>Lädt die physikalischen Parameter aus einem Vektoria-Placement-File, vererbbare Hilfmethode.</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		void Load(CFileVektoria & filevektoria);

		///<summary>Speichert die physikalischen Parameter in ein Vektoria-Materialfile, vererbbare Hilfsmethode.</summary>
		///<param name = "filevektoria"> Vektoria-File mit gesetzer Pfadangabe.</param>
		void Save(CFileVektoria & filevektoria);

		// ----------------------------------------------
		// Membervariablen (physikalische Festparameter):
		// ----------------------------------------------

		///<summary> Ist er fest (true) oder gasförmig/flüssig (false)</summary>
		bool m_bSolid;

		///<summary> CW-Wert (Luftwiderstandwert)</summary>
		float m_fCW;    

		///<summary> Masse des Partikels</summary>
		float m_fMass;	

		///<summary> Trägheitstensor (wird in Papers als I oder manchmal J bezeichnet) (Analog Masse bei geradlinigen Bewegungen, gibt Masseverteilung innerhalb des Körpers wieder)  </summary>
		CHMat m_mInertiaTensor;

		///<summary> Elektrische Ladung</summary>
		float m_fCharge;

		///<summary> Spezifisches Gewicht</summary>
		float m_fSpecificWeight;

		// -------------------------------------------
		// Membervariablen (zu berechnende Parameter):
		// -------------------------------------------

		///<summary> Gesamtkraft, die auf das Teilchen einwirkt</summary>
		CHVector m_vForceTotal;	   

		///<summary> Geschwindigkeit</summary>
		CHVector m_vVelocity;

		///<summary> Beschleunigung</summary>
		CHVector m_vAcceleration; 

		///<summary> Gesamtdrehmoment, das auf das Teilchen einwirkt (Analog F bei der geradlinigen Beschleunigung).  </summary>
		CQuaternion m_qTorqueTotal;  

		///<summary> Gesamtdrehgeschwindigkeit </summary>
		CQuaternion m_qTorqueVelocity;

		///<summary> Gesamtdrehbeschleunigung </summary>
		CQuaternion m_qTorqueAcceleration;  

		///<summary> Gesamtwinkelbeschleunigung = Drehbeschleunigung (wird in Papern mit Apha beszeichent) (analog Beschelunigung bei geradliniger Bewegung) </summary>
		CHVector m_vTorqueAcceleration;


	protected:

		///<summary> Pointer auf das übergeordnete Placement</summary>
		CPlacement * m_pplacement;

	};

}
