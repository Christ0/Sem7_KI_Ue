#pragma once
#include "../VektoriaMath/HMat.h"
#include "../VektoriaMath/Quaternion.h"
#include "Cameras.h"
#include "Emitters.h"
#include "Geos.h"
#include "Audios.h"
#include "LightRadials.h"
#include "LightSpots.h"
#include "ApiRender.h"
#include "Nodes.h"
#include "GeoWall.h"
#include "GeoWindow.h"
#include "Node3D.h"
#include "Scenes.h"
#include "PlacementPhysics.h"

#define BILLBOARD_NO 0
#define BILLBOARD_XYZ 1
#define BILLBOARD_XYZ_FRUSTUM_ORIENTED 2
#define BILLBOARD_X 3
#define BILLBOARD_Y 4
#define BILLBOARD_Z 5


///---------------------------------------------------
///CPlacement: Klasse für eine Positionierungs-Instanz mit Lokaler Matrix für den Szenegrafen
///
///Autor: Prof. Dr. Tobias Breiner
///Firma: Vektoria UG (haftungsbeschränkt)
///---------------------------------------------------

namespace Vektoria
{

	class CCamera;
	class CPlacements;
	class CGeoTriangleLists;
	class CWribels;
	class CWribel;
	class CScenes;
	class CViewports;
	class CEmitterParticles;

	class CPlacement : public CNode3D
	{
		friend class CRoot;
		friend class CEmitter;
		friend class CPlacements;
		friend class CWribel;
		friend class CWribels;
		friend class CNode3D;
		friend class CScene;
	protected:
		///<summary> Berechnet globale Matrizen/ Switch / etc. bei jedem Tick (wird automatisch von Überhierarchie aufgerufen).</summary>
		/// <param name= "mGlobal"> Die globale Matrix des übergeordneten Knotens </param>
		/// <param name= "iTick"> Nummer des Ticks </param>
		/// <param name= "iInst"> Nummer der Instanz </param>
		/// <param name= "fTimeDelta"> Zeit in Sekunden, die seit dem letzten Tick verstrichen sind </param>
		void Tick(CHMat & m, int & iTick, int & iInst, float & fTimeDelta);
		
		///<summary> Trägt die Szene in die Ahnen-Szenenliste ein.</summary>
		/// <param name= "pscene"> Pointer auf eine Szene, die ein Vorgänger ist. </param>
		void SetScene(CScene * pscene);

		///<summary>Zeichnet die Placements der Liste nicht.</summary>
		void DontDraw(int & iTick);

		///<summary>Zeichnet alle Placements der Liste.</summary>
		void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, int & iTick);

	
	public:
		///--------------
		///Basismethoden: 
		///-------------

		///<summary>Konstruktor</summary>
		CPlacement();

		///<summary> Destruktor</summary>
		~CPlacement();

		///<summary> Kopieroperator, kopiert Werte ins vorliegende Placement.</summary>
		///<param name=placement>Placement, welches in das vorliegende Placement kopiert wird</param>
		CPlacement operator=(CPlacement & placement);

		///<summary> Kopiert die Parameterwerte von placement ins vorliegende Placement, belässt aber die bestehenden Verknüfungen.</summary>  
		///<param name=placement>Placement, welches in das vorliegende Placement kopiert wird</param>
		void CopyParameters(CPlacement & placement);

		///<summary> Kopiert die Werte und Verknüfungen des Parameters placement ins vorliegende Placement.</summary>  
		///<param name=placement>Placement, welches in das vorliegende Placement kopiert wird</param>
		void Copy(CPlacement & placement);

		///<summary> Kopiert die Werte des Parameters placement und alle darunter liegenden Nodes ins vorliegende Placement.<para></para>
		/// Achtung, noch ungetestet!</summary>  
		///<param name=placement>Placement, welches in das vorliegende Placement kopiert wird</param>
		void CopyHierarchy(CPlacement & placement);

		///<summary> Initialisierungsmethode (muss nicht unbedingt aufgerufen, da Werte schon im Konstruktur initialisiert werden).</summary>
		void Init();

		///<summary> Beendigungsmethode.</summary>
		void Fini();

		///---------------------
		///Verknüfungsmethoden:
		///---------------------

		///<summary> Hängt eine Geometrie an das Placement an.</summary>
		///<param name="pgeo">Zeiger auf die anzuhängende Geometrie</param>
		void AddGeo(CGeo * pgeo);

		///<summary> Hängt einen Emitter an das vorliegende Placement an.</summary>
		///<param name="pemitter">Zeiger auf den anzuhängenden Emitter</param>
		void AddEmitter(CEmitter * pemitter);

		///<summary> Hängt eine Kamera an das vorliegende Placement an.</summary>
		///<param name="pcamera">Zeiger auf die anzuhängende Kamera</param>
		void AddCamera(CCamera * pcamera);

		///<summary> Hängt ein Punktlicht an das vorliegende Placement an.</summary>
		///<param name="plightradial">Zeiger auf das anzuhängende Punktlicht</param>
		void AddLightRadial(CLightRadial * plightradial);

		///<summary> Hängt ein Scheinwerferlicht an das vorliegende Placement an.</summary>
		///<param name="plightspot">Zeiger auf das anzuhängende Scheinwerferlicht</param>
		void AddLightSpot(CLightSpot * plightspot);

		///<summary> Hängt ein anderes Placement an das vorliegende Placement an.</summary>
		///<param name="pplacement">Zeiger auf das anzuhängende Placement</param>
		void AddPlacement(CPlacement * pplacement);

		///<summary> Hängt ein 3D-Sound an das vorliegende Placement an (Achtung! Sound muss 3D-Sound sein).</summary>
		///<param name="paudio">Zeiger auf den anzuhängenden 3D-Sound</param>
		void AddAudio(CAudio * paudio);

		///<summary> Hängt ein Text-Label an das vorliegende Placement an.</summary>
		///<param name="pwribel">Zeiger auf den anzuhängenden Text-Label</param>
		void AddWribel(CWribel * pwribel);

		///<summary> Hängt die Geometrie wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pgeo">Zeiger auf die abzuhängende Geometrie</param>
		bool SubGeo(CGeo * pgeo);

		///<summary> Hängt den Emitter wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pemitter">Zeiger auf den abzuhängenden Emitter</param>
		bool SubEmitter(CEmitter * pemitter);

		///<summary> Hängt die Kamera wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pcamera">Zeiger auf die abzuhängende Kamera</param>
		bool SubCamera(CCamera * pcamera);

		///<summary> Hängt das Punktlicht wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="plightpoint">Zeiger auf das abzuhängende Punktlicht</param>
		bool SubLightRadial(CLightRadial * plightpoint);

		///<summary> Hängt das Scheinwerferlicht wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="plightspot">Zeiger auf das abzuhängende Scheinwerferlicht</param>
		bool SubLightSpot(CLightSpot * plightspot);

		///<summary> Hängt das Unterplacement wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pplacement">Zeiger auf das abzuhängende Unterplacement</param>
		bool SubPlacement(CPlacement * pplacement);

		///<summary> Hängt den 3D Sound wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="paudio">Zeiger auf den abzuhängenden 3D Sound</param>
		bool SubAudio(CAudio * paudio);

		///<summary> Hängt das Textlabel wieder von dem vorliegenden Placement ab, gibt true aus, wenn es funktioniert hat.</summary>
		///<param name="pwribel">Zeiger auf das abzuhängende Textlabel</param>
		bool SubWribel(CWribel * pwribel);

		///<summary> Hängt alle Kinderknoten auf einmal ab, gibt true aus, wenn es funktioniert hat.</summary>
		void SubAll();

		///-------------------------------------
		/// Änderungsmethoden zum Placment-Typ:
		///-------------------------------------

		///<summary> Setzt die Entfernungsgrenzen von der Kamera für das Level of Detail.</summary>
		///<param name="fDistNear">Minimaler Abstand zur Kamera in Units, ab der das LoD eingeschaltet wird</param>
		///<param name="fDistFar">Maximaler Abstand zur Kamera in Units, bis zu der das LoD eingeschaltet wird</param>
		void SetLoD(float fDistNear, float fDistFar);

		///<summary> Wird diese Methode aufgerufen, richtet sich das Placement danach in Richtung der Kamera aus.</summary>
		void SetBillboard();

		///<summary> Wird diese Methode aufgerufen, richtet sich das Placement danach in Richtung des Kamerafrustums aus.<para></para> 
		/// Dies ist bvesser für Emitter und Partikelsysteme geeignet, da die Wahrscheinlichkeit von Billboard-Überlagerungen und Flimmer-Artefakten geringer ist.</summary>
		void SetBillboardForEmitters();

		///<summary> Wird diese Methode aufgerufen, richtet sich das Placement danach in Richtung der Kamera aus. Die Orientierung in X-Richtung wird beibehalten.</summary>
		void SetBillboardX();

		///<summary> Wird diese Methode aufgerufen, richtet sich das Placement danach in Richtung der Kamera aus. Die Orientierung in Y-Richtung wird beibehalten.</summary>
		void SetBillboardY();

		///<summary> Wird diese Methode aufgerufen, richtet sich das Placement danach in Richtung der Kamera aus. Die Orientierung in Z-Richtung wird beibehalten.</summary>
		void SetBillboardZ();

		///<summary> Skaliert die Billboard-Größe. </summary>
		///<param name="fx">Skalierungsfaktor in X-Richtung</param>
		///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
		void SetBillboardScaling(float fx, float fy);

		///<summary>Setzt den Rotationswinkel des Billboards.</summary>
		///<param name="fa">Winkel im Bogenmaß, mathematisch postiv von der Kamera aus</param>
		void SetBillboardAngle(float fa);

		///<summary>Gibt den Rotationswinkel des Billboards aus.<para></para>
		///Returnwert = Winkel im Bogenmaß, mathematisch postiv von der Kamera aus</summary>
		float GetBillboardAngle();

		///<summary> Gibt die Skalierung in X-Richtung des Billboards aus.</summary>
		float GetBillboardScalingX();

		///<summary> Gibt die Skalierung in Y-Richung des Billboards aus.</summary>
		float GetBillboardScalingY();

		///<summary> Macht das Placement zu einem Sky-Placment (Placment transliert danach sinnfällig mit der Kamera mit), sinnvoll für Skydomes, Skycubes, multiple Skydomes etc.</summary>
		void SetSky();

		///<summary> Macht das Placement zu einem Ground-Placment (Placment transliert und orientiert danach sinnfällug mit der Kamera mit), sinnvoll für fixe 3D-Guis.</summary>
		void SetGround();

		///<summary> Macht das Placement zu einem Appendage-Placment (wenn Elternplacement ein Billboard, Ground oder Appendage ist, orientiert sich das Appendage-Placement an den Elternplacements), sinnvoll für Skydomes, Skycubes, multiple Skydomes etc.</summary>
		void SetAppendage();

		///--------------------------------------------------------------
		///Methoden, welche die homogene Matrix des Placements betreffen:
		///-------------------------------------------------------------

		///<summary> Setzt die lokale Matrix.</summary>
		///<param name="m">lokale Matrix</param>
		void SetMat(CHMat & m);

		///<summary> Setzt alle globalen Matrizen auf m und ignoriert lokale Matrix.</summary>
		///<param name="m">globale Matrix</param>
		///<param name="iInstance">Nummer der Instanz (bei zusammenlaufenden Hierarchien, können mehrere Instanzen eines Placements vorhanden sein)</param>
		void SetMatGlobal(CHMat & m, int iInstance = 0);

		///<summary> Setzt lokal Einheitsmatrix für das Placement => Placement wird wieder auf Ursprungsposition gesetzt.</summary>
		void Unit();

		///<summary> Addiert lokal die X-Rotation.</summary>
		///<param name="fa">Winkel im Bogenmaß</param>
		void CopyRotationXDelta(float fa);

		///<summary> Addiert lokal die Y-Rotation.</summary>
		///<param name="fa">Winkel im Bogenmaß</param>
		void CopyRotationYDelta(float fa);

		///<summary> Addiert lokal die Z-Rotation.</summary>
		///<param name="fa">Winkel im Bogenmaß</param>
		void CopyRotationZDelta(float fa);

		///<summary> Setzt lokal die X-Translation.</summary>
		///<param name="fx">Verschiebungsanteil in x-Richtung</param>
		void CopyTranslationX(float fx);

		///<summary> Setzt lokal die Y-Translation.</summary>
		///<param name="fy">Verschiebungsanteil in y-Richtung</param>
		void CopyTranslationY(float fy);

		///<summary> Setzt lokal die Z-Translation.</summary>
		///<param name="fz">Verschiebungsanteil in z-Richtung</param>
		void CopyTranslationZ(float fz);

		///<summary> Setzt lokal die X-Skalierung.</summary>
		///<param name="fx">Vergrößerungsfaktor in x-Richtung</param>
		void CopyScaleX(float fx);

		///<summary> Setzt lokal die Y-Skalierung.</summary>
		///<param name="fy">Vergrößerungsfaktor in y-Richtung</param>
		void CopyScaleY(float fy);

		///<summary> Setzt lokal die Z-Skalierung.</summary>
		///<param name="fz">Vergrößerungsfaktor in z-Richtung</param>
		void CopyScaleZ(float fz);

		///<summary> Rotiert Placement lokal um die X-Achse. <para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fa">Winkel im Bogenmaß (mathematisch rechtshändiges System)</param>
		void RotateX(float fa);

		///<summary> Rotiert Placement lokal um die Y-Achse.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fa">Winkel im Bogenmaß (mathematisch rechtshändiges System) </param>
		void RotateY(float fa);

		///<summary> Rotiert Placement lokal um die Z-Achse. <para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary> 
		///<param name="fa">Winkel im Bogenmaß (mathematisch rechtshändiges System)</param>
		void RotateZ(float fa);

		///<summary> Generiert beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa für das Placement.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fx">x-Anteil der Drehachse</param>
		///<param name="fy">y-Anteil der Drehachse</param>
		///<param name="fz">z-Anteil der Drehachse</param>
		///<param name="fa"n>Drehwinkel im Bogenmaß</param>
		void Rotate(float fx, float fy, float fz, float fa);

		///<summary> Generiert beliebige Rotationsmatrix um die Drehachse v mit Winkel fa für das Placement.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="v">Drehachse</param>
		///<param name="fa">Winkel im Bogenmaß</param>
		void Rotate(CHVector & v, float fa);

		///<summary> Erzeugt eine Rotationsmatrix, die Richtungsvektor vFrom genau in die Richtung des Richtungsvektors vTo rotiert für das Placement.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="vTo">Zielrichtungsvektor</param>
		///<param name="vFrom">Startrichtungsvektor</param>
		void Rotate(CHVector & vTo, CHVector & vFrom);

		///<summary> Erzeugt eine Rotationsmatrix aus dem Rotationsquaternion q.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="q">Rotationsquaternion</param>
		void Rotate(CQuaternion &q);

		///<summary> Skaliert das Placment mit den drei verschiedenen Skalierungswerten v.x, v,y und vz, v.w wird ignoriert.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="v">Skalierungsvektor</param>
		void Scale(CHVector & v);

		///<summary> Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten für das Placement.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fx">Skalierungsfaktor in x-Richtung</param>
		///<param name="fy">Skalierungsfaktor in y-Richtung</param>
		///<param name="fz">Skalierungsfaktor in z-Richtung</param>
		void Scale(float fx, float fy, float fz);

		///<summary> Skaliert Placement uniform (= gleichmäßig in alle Richtungen). <para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="f">Skalierungsfaktor in alle Richtungen</param>
		void Scale(float f);

		///<summary> Skaliert Placement in X-Richtung. <para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fx">Skalierungsfaktor in x-Richtung.</param>
		void ScaleX(float fx);

		///<summary> Skaliert Placement in Y-Richtung.<para></para> 
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fy">Skalierungsfaktor in y-Richtung.</param>
		void ScaleY(float fy);

		///<summary> Skaliert Placement in Z-Richtung.<para></para> 
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fz">Skalierungsfaktor in y-Richtung.</param>
		void ScaleZ(float fz);

		///<summary> Verschiebt Placement in Richtung (v.x, v.y,v.z).<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="v">Verschiebt Placement in x,y,z-Richtung.</param>
		void Translate(CHVector & v);

		///<summary> Verschiebt Placement in Richtung (fx, fy, fz).<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fx">Verschiebt Placement in x-Richtung.</param>
		///<param name="fy">Verschiebt Placement in y-Richtung.</param>
		///<param name="fz">Verschiebt Placement in z-Richtung.</param>
		void Translate(float fx, float fy, float fz);

		///<summary> Verschiebt Placement in X-Richtung.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>	
		///<param name="fx">Verschiebt Placement in x-Richtung.</param>
		void TranslateX(float fx);

		///<summary> Verschiebt Placement in Y-Richtung.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fy">Verschiebt Placement in y-Richtung.</param>
		void TranslateY(float fy);

		///<summary> Verschiebt Placement in Z-Richtung.<para></para>
		///Löscht dabei alle vorherigen Transformationsinformationen.</summary>
		///<param name="fz">Verschiebt Placement in z-Richtung.</param>
		void TranslateZ(float fz);

		///<summary> Gibt die lokale Richtung des Placements aus (bezüglich lokaler -Z-Richtung).</summary>
		CHVector GetDirection();

		///<summary> Gibt die lokale Position des Placements aus.</summary>
		CHVector GetPos();

		///<summary> Gibt die lokale Sklaierung des Placements aus.</summary>
		CHVector GetScale();

		///<summary> Generiert Rotationsmatrix um die X-Achse mit dem Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wird um Winkel fa um die X-Achse weitergedreht.</summary>
		///<param name="fa">Drehwinkel im Bogenmaß</param>
		void RotateXDelta(float fa);

		///<summary> Generiert Rotationsmatrix um die Y-Achse mit dem Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements.<para></para> 
		///=> Placement wird um Winkel fa um die Y-Achse weitergedreht.</summary>
		///<param name="fa">Drehwinkel im Bogenmaß</param>
		void RotateYDelta(float fa);

		///<summary> Generiert Rotationsmatrix um die Z-Achse mit dem Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements.<para></para> 
		///=> Placement wird um Winkel fa um die Z-Achse weitergedreht.</summary>
		///<param name="fa">Drehwinkel im Bogenmaß</param>
		void RotateZDelta(float fa);

		///<summary> Generiert eine Rotationsmatrix um die Drehachse (fx, fy, fz) mit dem Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements.<para></para> 
		///=> Placement wird um Winkel fa (Bogenmaß) um die Drehachse weitergedreht.</summary> 
		///<param name="fx">x-Anteil der Drehachse</param>
		///<param name="fy">y-Anteil der Drehachse</param>
		///<param name="fz">z-Anteil der Drehachse</param>
		///<param name="fa">Drehwinkel im Bogenmaß</param>
		void RotateDelta(float fx, float fy, float fz, float fa);

		///<summary> Generiert eine Rotationsmatrix um die Drehachse v mit dem Winkel fa und multipliziert diese mit der bisherigen Matrix des Placements.<para></para> 
		///=> Placement wird um Winkel fa (Bogenmaß) um die Drehachse weitergedreht.</summary> 
		///<param name="v">Drehachse</param>
		///<param name="fa">Drehwinkel im Bogenmaß</param>
		void RotateDelta(CHVector & v, float fa);

		///<summary> Erzeugt eine Rotationsmatrix aus dem Rotationsquaternion q und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wird weitergedreht.</summary> 
		///<param name="q">Rotationsquaternion</param>
		void RotateDelta(CQuaternion &q);

		///<summary> Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der bisherigen Matrix des Placements. 
		///=> Placement wird um (fx,fy,fz) größer.</summary>
		///<param name="v">Skalierungsvektor</param>
		void ScaleDelta(CHVector & v);


		///<summary> Generiert Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wird um (fx,fy,fz) größer.</summary>
		///<param name="fx">Skalierungsfaktor in x-Richtung</param>
		///<param name="fy">Skalierungsfaktor in y-Richtung</param>
		///<param name="fz">Skalierungsfaktor in z-Richtung</param>
		void ScaleDelta(float fx, float fy, float fz);

		///<summary> Generiert uniforme Skalierungsmatrix und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wird um Faktor f größer.</summary>
		///<param name="f">uniforme Skalierungsfaktor</param>
		void ScaleDelta(float f);

		///<summary> Generiert eine uniforme Skalierungsmatrix für das Placement, bei der nur X skaliert wird, und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wird in X-Richtung um den Faktor fx größer.</summary>
		///<param name="fx">Skalierungsfaktor in x-Richtung</param>
		void ScaleXDelta(float fx);

		///<summary> Generiert eine uniforme Skalierungsmatrix für das Placement, bei der nur Y skaliert wird, und multipliziert diese mit der bisherigen Matrix des Placements. <para></para>
		///=> Placement wird in Y-Richtung um den Fakor fy größer.</summary>
		///<param name="fy">Skalierungsfaktor in y-Richtung</param>
		void ScaleYDelta(float fy);

		///<summary> Generiert eine uniforme Skalierungsmatrix für das Placement, bei der nur Z skaliert wird, und multipliziert diese mit der bisherigen Matrix des Placements. <para></para>
		///=> Placement wird in Z-Richtung um den Fakor fz größer.</summary>
		///<param name="fz">Skalierungsfaktor in z-Richtung</param>
		void ScaleZDelta(float fz);

		///<summary> Generiert Verschiebungsmatrix für das Placement und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wandert um (fx, fy, fz) weiter.</summary>
		///<param name="fx">Verschiebungsanteil in x-Richtung</param>
		///<param name="fy">Verschiebungsanteil in y-Richtung</param>
		///<param name="fz">Verschiebungsanteil in z-Richtung</param>
		void TranslateDelta(float fx, float fy, float fz);

		///<summary> Generiert Verschiebungsmatrix für das Placement und multipliziert diese mit der bisherigen Matrix des Placements.<para></para>
		///=> Placement wandert um den Richtungsvektor v weiter.</summary>
		///<param name="v">Verschiebungsvektor</param>
		void TranslateDelta(CHVector & v);

		///<summary> Generiert Verschiebungsmatrix in X-Richtung und multipliziert diese mit der bisherigen Matrix für das Placement.<para></para>
		///=> Placement wandert in X-Richtung um den Betrag fx weiter.</summary>
		///<param name="fx">Verschiebungsanteil in x-Richtung</param>
		void TranslateXDelta(float fx);

		///<summary>Generiert Verschiebungsmatrix in Y-Richtung und multipliziert diese mit der bisherigen Matrix für das Placement.<para></para>
		///Das Placement wandert somit in Y-Richtung um den Betrag fy weiter.</summary>
		///<param name="fy"> Translation in Y-Richtung </param>
		void TranslateYDelta(float fy);

		///<summary> Generiert eine Verschiebungsmatrix in Z-Richtung und multipliziert diese mit der bisherigen Matrix für das Placement. <para></para>
		///Das Placement wandert somit in Z-Richtung um den Betrag fz weiter.	</summary>
		///<param name="fz">Translation in Z-Richtung.</param>
		void TranslateZDelta(float fz);

		///-------------------
		///Kollisionsmethoden:
		///-------------------

		///<summary> Gibt true aus, wenn eines der Bounding-Boxen des Placements pzp mit einem der Bounding-Boxern des vorliegenden Placements kollidiert.<para></para>
		///Vorsicht bei mehreren Instanzen der Placements!</summary>
		///<param name="pzp">Zeiger auf ein anderes Placement, das mit dem aktuellen Placement kollidieren kann.</param>
		bool IsColliding(CPlacement * pzp);

		///<summary> Gibt in einer Szene alle Placements aus, mit denen das aktuelle Placement kollidiert. </summary>
		///<param name="pzs"></param>
		CPlacements * GetCollidingPlacements(CScene *pzs);

		///<summary> Schaut, ob das Placement mit der irgendeiner Boundingbox der Unterhierarchie kollidiert, fMin und fMax geben die Ausmaßdistanzen des gefundenen Placments aus.</summary> 
		///<param name="r">Suchstrahl durch die Szene</param>
		///<param name="fMin">Entfernung des Eintrittspunktes in das Placementdes Strahls vom Strahlursprung.</param>
		///<param name="fMax">Entfernung des Austrittspunktes in das Placementdes Strahls vom Strahlursprung.</param>
		///<param name="ePlacementSearch">Suchparameter: <para></para> 
		///ePlacementSearch_All = Alle Placements werden gesucht.<para></para> 
		///ePlacementSearch_OnlyWithDirectGeos = Nur Placements werden gesucht, an denen direkt untendran eine Geometrie angehängt ist.<para></para> 
		///ePlacementSearch_OnlyWithDirectWribels = Nur Placements werden gesucht, an denen direkt untendran eine Wribels angehängt ist.</param>
		CPlacement * PickPlacement(CRay & r, float & fMin, float & fMax, EPlacementSearch ePlacementSearch = ePlacementSearch_All);

		///<summary> Schaut, ob das Placement mit der irgendeiner Boundingbox der Unterhierarchie kollidiert, fMin und fMax geben die Ausmaßdistanzen des gefundenen Placments aus. </summary>
		///<param name="r">Suchstrahl durch die Szene</param>
		///<param name="pzps">Instanziierter Container, indem danach alle gepickten Placements stehen.</param>
		///<param name="ePlacementSearch">Suchparameter: <para></para> 
		///ePlacementSearch_All = Alle Placements werden gesucht.<para></para> 
		///ePlacementSearch_OnlyWithDirectGeos = Nur Placements werden gesucht, an denen direkt untendran eine Geometrie angehängt ist.<para></para> 
		///ePlacementSearch_OnlyWithDirectWribels = Nur Placements werden gesucht, an denen direkt untendran eine Wribels angehängt ist.</param>
		void PickPlacements(CRay & r, CPlacements * pzps, EPlacementSearch ePlacementSearch = ePlacementSearch_All);

		///<summary> Schaut, ob Strahl r mit der BoundingBox irgendeiner Instanz dieses Placments kollidiert.</summary>
		///<param name="r">Suchstrahl durch die Szene</param>
		bool Intersects(CRay & r);

		///---------------------
		///Stereoskopiemethoden:
		///---------------------

		///<summary>Erzeugt eine komplexe Struktur aus drei Placements und zwei Kameras für Stereoskopie.</summary>
		///<param name="pplacementLeftCamera">Placement, an der die linke Kamera hängt</param>
		///<param name="pcameraLeftEye">Kamera für das linke Auge, sollte nicht initialisiert sein</param>
		///<param name="pplacementRightCamera">Placement, an der die rechte Kamera hängt</param>
		///<param name="pcameraRightEye">Kamera für das rechte Auge, sollte nicht initialisiert sein</param>
		///<param name="fEyeDistance">Augenabstand</param>
		///<param name="fFocusDistance">Fokusssierungsdistanz</param>
		///<param name="faFov=2.0F">horizontaler Kameraöffnungswinkel</param>
		///<param name="fNearClipping=0.1F">Vordere Clipping Plane (ab welcher Distanz sieht man was, sollte größer Null sein)</param>
		///<param name="fFarClipping=1000.0F">Hintere Clipping Plane (bis zu welcher Distanz sieht man was)</param>
		void MakeStereoscopicCameras(CPlacement * pplacementLeftCamera, CCamera *pcameraLeftEye, CPlacement * pplacementRightCamera, CCamera *pcameraRightEye, float fEyeDistance, float fFocusDistance, float faFov = 2.0F, float fNearClipping = 0.1F, float fFarClipping = 1000.0F);

		///<summary> Verändert die Parameter der stereoskopischen Struktur, wenn vorhanden.</summary>
		///<param name=" fEyeDistance">Augenabstand</param>
		///<param name="fFocusDistance">Fokussierungsdistanz</param>
		void SetStereoscopicParameters(float fEyeDistance, float fFocusDistance);

		///<summary> Gibt die Parameter der stereoskopischen Struktur zurück, gibt true aus wenn vorhanden.</summary>
		///<param name=" fEyeDistance">Augenabstand</param>
		///<param name="fFocusDistance">Fokussierungsdistanz</param>
		bool GetStereoscopicParameters(float & fEyeDistance, float & fFocusDistance);

		///------------------------------------------
		///Hierarchiemethoden für die Beschleunigung:
		///Beschleunigungsroutinen, die sich auf das aktuelle Placement plus die gesamte angehängte Hierarchie auswirken, müssen NACH allen Add- und Init-Routinen einmal aufgerufen werden:
		///------------------------------------------

		///<summary> Wandelt alle Geos in der darunter liegenden Hierarchie, die GeoTriangleStrips sind, rekursiv in TriangleLists um.<para></para>
		///Achtung die ursprünglichen GeoTriangleStrips existieren danach immer noch, sie sind nur abgehängt.</summary>
		void HierarchyToGeoTriangleList();

		///<summary> Schaltet das Frustum Culling rekursiv für die gesamte Unterhierarchie an.</summary>
		void SetFrustumCullingOn();

		///<summary> Schaltet das Frustum Culling rekursiv für die gesamte Unterhierarchie aus.</summary>
		void SetFrustumCullingOff();

		///<summary> Reicht die Information, ob das Frustum Culling an oder aus ist, einfach in der Hierarchie weiter.</summary>
		void SetFrustumCullingByParent();

		///<summary> Schaltet die exakte Berechnung der Bounding Volume Hierarchie rekursiv für die gesamte Unterhierarchie an.<para></para>
		///Achtung! Sollte nur in Notfällen benutzt werden, da sehr langsam!!!</summary>
		void SetBVHExactCalculationOn();

		///<summary> Schaltet die exakte Berechnung der Bounding Volume Hierarchie rekursiv für die gesamte Unterhierarchie aus. (Default)<para></para>
		///Die BVH wird danach mit dem neuen schnellen heuristischen Vektoria-Algorithmus berechnet. <para></para> 
		///Dies reicht in den allermeisten Fällen aus und ist wesentlich schneller als die exakte herkömmliche BVH-Berechnung. </summary> 
		void SetBVHExactCalculationOff();

		///<summary> Reicht die Information, ob die exakte Bounding Volume Hierarchieberechnung an oder aus ist, einfach in der Hierarchie weiter.</summary>
		void SetBVHExactCalculationByParent();

		///<summary> Sollte aufgerufen werden, wenn sicher ist, dass Placment und Unterplacements starr in der Gegend stehen => Beschleunigt das Rendering, da dann die Matrizen nicht immer wieder neu berechnet werden.</summary>
		void Fix();

		///<summary>Macht Fix rückgängig
		void Unfix();

		///<summary> Sortiert nach Status-Calls, um CPUGPU-Traffic zu reduzieren und vereinigt Geometrien mit gleichem Material. <para></para> 
		///Erlaubt Beschleunigung der untergeortneten Hierarachie, das Placement kann im Gegensatz zu FixAndFasten trotzdem noch bewegt werden.<para></para>
		///Achtung 1: Die Rekalkulation dauert lange!, <para></para>
		///Achtung 2: Transparente Objekte innerhalb der Placement-Hierarchie können danach untereinander Artefakte verursachen.</summary>
		void Fasten();

		///<summary> Macht Fasten rückgängig (Achtung, dauert lange).</summary>
		void Unfasten();

		///<summary> Sortiert nach Status-Calls, um CPUGPU-Traffic zu reduzieren und vereinigt Geometrien mit gleichem Material.  <para></para>
		///Daraus folgt eine Beschleunigung.<para></para> 
		///Achtung 1: Die Rekalkulation dauert lange! Daher möglichst nur im Init verwenden. <para></para>
		///Achtung 2: Transparente Objekte innerhalb der Placement-Hierarchie können danach untereinander Artefakte verursachen!<para></para>
		///Achtung 3: Objekte der Placement-Hierarchie lassen sich danach nicht mehr bewegen! </summary>
		void FixAndFasten();

		///<summary> Macht FixAndFasten rückgängig (Achtung, dauert lange).</summary>
		void UnfixAndUnfasten();

		///<summary> Gibt true aus, wenn irgenein transparentes Objekt an das Placement angehangen wurde.</summary>
		bool HasTransparent();

		///<summary> Gibt "CPlacement" aus.</summary>
		///<returns>CPlacement</returns>
		const char* ClassName() { return "CPlacement"; }

		///--------------------
		/// Ausrichetemethoden:
		/// -------------------

		///<summary> Macht, dass das Placement automatisch sich in Richtung des Raumpunkts orientiert, der durch pvPointing gegeben ist.<para></para>
		///Dies ist u.a. wichtig für Kameras, die auf einen Punkt schauen sollen.</summary>
		///<param name="pvPointing">Pointer auf einen Punktvektor (Achtung auf Scope der Variablen!)</param>
		void SetPointing(CHVector * pvPointing);

		///<summary> Macht, dass das Placement automatisch sich in Richtung des Placements orientiert, der durch pplacement gegeben ist. <para></para>
		///Dies ist u.a. wichtig für Kameras, die auf ein Objekt schauen sollen.<para></para>
		///Falls mehere Instanzen des Placements (in zusammenlaufenden Hierartchien) existieren sollten, muss die Instanznummer angegeben werden.</summary>
		///<param name="pplacementPointing">Pointer auf ein anderes Placement</param>
		///<param name="iInstance">Instanzennummer des anderen Placements (wenn nur eine Instanz vorhanden ist, dann automatisch Null)</param>
		void SetPointing(CPlacement * pplacementPointing, int iInstance = 0);

		///<summary> Setzt das SetPointing wieder zurück.</summary>
		void SetPointingOff();

		// --------------------
		// AABB-Updatemethoden:
		// --------------------

		///<summary> Aktualisiert die AABB für diesen Node und seine gesamte Unterhierarchie.</summary>
		void UpdateAABBsFromDirectChildrenUpwards();

		///<summary> Aktualisiert die AABB für diesen Node miotsamt der Geometrien</summary>
		void UpdateAABBHierarchyWithGeos();

		///<summary> Aktualisiert die AABB rekursiv in der Hierarchie hoch.</summary>
		void UpdateAABBAnchestors();

		///<summary> Aktualisiert die AABB für diesen Node und eine Hierarchiestufe untendran.</summary>
		void UpdateAABBThisFromDirectChildren();

		///<summary> Aktualisiert die AABB rekursiv in der Hierarchie hoch.</summary>
		void UpdateAABBsFromPlacementHierarchyUpwards();

		// -----------------
		// Weitere Methoden:
		// -----------------

		///<summary> Fixiert die Distanz, die für die Z-Buffer-Sortierung verwendet wird, z.B. notwendig für ineinander geschachtelte semitransparente Skydomes. </summary>
		///<param name="fDistance"></param>
		void FixDistance(float fDistance);

		///<summary> Reicht alle Informationen rekursiv an die Grafikkarte / Soundkarte weiter (wird automatisch von der darüber liegenden Hierarchie aufgerufen).</summary>
		void Create();

		///<summary> Gibt die Anzahkl der Geometrien aus, die in dem Placement-Branch vorhanden sind.</summary>
		int CountGeos();

		///<summary> Sammelt alle Materialien, die in dem Placement-Branch vorhanden sind, und meldet sie bei der Root an.</summary>
		void CollectMaterials();

		///---------------------------------------
		///Methoden für die sphärische Platzierung
		///---------------------------------------

		///<summary> Platziert das Placment mittels sphärischer Koordiaten um ein anderes Placement.<para></para>
		///Dies ist z.B. sinnvoll, um das Zielplacement von allen Seiten anzuschauen.</summary>
		///<param name="fRadius"> Entfernung von zpCenter(i-te Instanz)</param>
		///<param name="faAzimuth"> Azimut (Rotationswinkel im Bogenmaß um die Y-Achse)</param>
		///<param name="faAltitude"> Elevation (Rotationswinkel im Bogenmaß von der XZ-Ebene)</param> 
		///<param name="zpCenter"> Zielplacement, um das sich das vorliegende Placement dreht</param>
		///<param name="iGlobalInstance"> Verwendete Instanz des Zielplacements zpCenter</param>
		void PlaceSphericalGlobal(float fRadius, float faAzimuth, float faAltitude, CPlacement & zpCenter, int iGlobalInstance = 0);

		///<summary> Platziert das Placment mittels sphärischer Koordiaten um ein anderes Placement.<para></para>
		///Dies ist z.B. sinnvoll, um das Zielplacement von allen Seiten anzuschauen.</summary>
		///<param name="fRadius"> Entfernung von zpCenter(i-te Instanz)</param>
		///<param name="faAzimuth"> Azimut (Rotationswinkel im Bogenmaß um die Y-Achse)</param>
		///<param name="faAltitude"> Elevation (Rotationswinkel im Bogenmaß von der XZ-Ebene)</param> 
		///<param name="zpCenter"> Zielplacement, um das sich das vorliegende Placement dreht</param>
		///<param name="faLeftRight"> Anfangswinkel um die Y-Achse im Bogenmaß</param>
		///<param name="faUpDown"> Anfangswinkel von der XZ-Ebene im Bogenmaß</param>
		///<param name="iGlobalInstance"> Verwendete Instanz des Zielplacements zpCenter</param>
		void PlaceSphericalGlobal(float fRadius, float faAzimuth, float faAltitude, float faLeftRight, float faUpDown, CPlacement & zpCenter, int iGlobalInstance = 0);

		///<summary> Plaziert das vorliegende Placmentmittels sphärischer Koordiaten um ein anderes Placement in seinem lokalen Koordiantensystem: <para></para>
		///Dies ist z.B. sinnvoll, um das Zielplacement von allen Seiten anzuschauen.</summary>
		///<param name="fRadius"> Entfernung von zpCenter(i-te Instanz)</param>
		///<param name="faAzimuth"> Azimut (Rotationswinkel im Bogenmaß um die Y-Achse)</param>
		///<param name="faAltitude"> Elevation (Rotationswinkel im Bogenmaß von der XZ-Ebene)</param> 
		///<param name="zpCenter"> Zielplacement, um das sich das vorliegende Placement dreht</param>
		void PlaceSphericalLocal(float fRadius, float faAzimuth, float faAltitude, CPlacement & zpCenter);

		//--------------------
		// Bewegungssteuerung:
		//--------------------

		///<summary> Setzt die Grenzen der Bewegungssteuerungen.</summary>
		///<param name="aabbMove">Grenze der Bewegungssteuerungen in Form einer Axis Aligned Bounding Box</param>
		void SetMoveRange(CAABB aabbMove);


		///<summary> Setzt die Verschiebungsempfindlichkeit (Geschwindigkeit) bei den Bewegungssteuerungen in Einheiten / Sekunde für Move und MovePan.</summary>
		///<param name="fTranslationSensitivity">Verschiebungsempfindlichkeit in Einheiten / Sekunde</param>
		void SetTranslationSensitivity(float fTranslationSensitivity);

		///<summary> Setzt die Drehempfindlichkeit (Rotationsgeschwindigkeit) bei den Bewegungssteuerungen in Bogenmaß / Sekunde für Move und MovePan.</summary>
		///<param name="fTranslationSensitivity">Rotationsempfindlichkeit in Bogenmaßeinheiten / Sekunde</param>
		void SetRotationSensitivity(float fRotationSensitivity);

		///<summary> Holt den Parameter für die Verschiebungsempfindlichkeit (Geschwindigkeit) in Einheiten / Sekunde bei den Bewegungssteuerungen.</summary>
		float GetTranslationSensitivity();

		///<summary> Holt den Parameter für die Drehempfindlichkeit (Rotationsgeschwindigkeit) in Bogenmaß / Sekunde für die Bewegungssteuerungen.</summary>
		float GetRotationSensitivity();

		///<summary> Setzt den Azimuth-Anfangswinkel bei einer MovePan-Steuerung.</summary>
		///<param name="faPanAzimuth"> Azimut (Rotationswinkel im Bogenmaß um die Y-Achse)</param>
		void SetPanAzimuth(float faPanAzimuth);

		///<summary> Setzt den Elevations-Anfangswinkel bei einer MovePan-Steuerung.</summary>
		///<param name="faPanAltitude">Elevation (Höhenwinkel über der XZ-Ebene) im Bogenmaß</param>
		void SetPanAltitude(float faPanAltitude);

		///<summary> Setzt den Radius bei einer MovePan-Steuerung.</summary>
		///<param name="fRadius">Radius um das Zentralplacment in Units</param>
		void SetPanRadius(float fPanRadius);

		///<summary> WASD-artige Bewegungssteuerung.</summary>
		///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
		///<param name="fAD">-1 für Linksverschiebung (translation left), 0 für nichts, 1 für Rechtsverschiebung (translation right)</param>
		///<param name="fSW">-1 für Vorwärts (translation forward), 0 für nichts, 1 für Rückwärts (translation back)</param>
		///<param name="fFR">-1 für Runterverschiebung (translation down), 0 für nichts, 1 für Hochverschiebung (translation up)</param>
		///<param name="fLR">-1 für Linksdrehung (rotation left), 0 für nichts, 1 für Rechtsdrehung (rotation right)</param>
		///<param name="fUD">-1 für Hochdrehung (rotation up), 0 für nichts, 1 für Runterdrehung (rotation down)</param>
		void Move(float & fTimeDelta, bool bEarth, float & fAD, float & fSW, float & fFR, float & fLR, float & fUD);

		///<summary> WASD-artige Bewegungssteuerung mit Kollisionserkennung.<para></para>
		/// Gibt bei Kollision true aus.</summary>
		///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
		///<param name="fAD">-1 für Linksverschiebung (translation left), 0 für nichts, 1 für Rechtsverschiebung (translation right)</param>
		///<param name="fSW">-1 für Vorwärts (translation forward), 0 für nichts, 1 für Rückwärts (translation back)</param>
		///<param name="fFR">-1 für Runterverschiebung (translation down), 0 für nichts, 1 für Hochverschiebung (translation up)</param>
		///<param name="fLR">-1 für Linksdrehung (rotation left), 0 für nichts, 1 für Rechtsdrehung (rotation right)</param>
		///<param name="fUD">-1 für Hochdrehung (rotation up), 0 für nichts, 1 für Runterdrehung (rotation down)</param>
		///<param name="zgsCollisionItems">Container, der alle Geometrien enthält, an die am anstoßen kann</param>
		bool MoveWithCollisionDetection(float & fTimeDelta, bool bEarth, float & fAD, float & fSW, float & fFR, float & fLR, float & fUD, CGeos & zgsCollisionItems);

		///<summary> Bewegungssteuerung, bei der die Richtung durch eine Rotationsmatrix vorgegeben ist.</summary>
		///<param name="mOrientation">Homogene Rotationsmatrix mit der vorgegebenen Bewegungsrichtung. Translationsanteil wird ignoriert. </param>
		///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
		///<param name="fAD">-1 für Linksverschiebung (translation left), 0 für nichts, 1 für Rechtsverschiebung (translation right)</param>
		///<param name="fSW">-1 für Vorwärts (translation forward), 0 für nichts, 1 für Rückwärts (translation back)</param>
		///<param name="fFR">-1 für Runterverschiebung (translation down), 0 für nichts, 1 für Hochverschiebung (translation up)</param>
		void MoveDirection(CHMat & mOrientation, float & fTimeDelta, bool bEarth, float & fAD, float & fSW, float & fFR);

		///<summary> Bewegungssteuerung, bei der die Richtung durch eine Matrix vorgegeben ist mit zusätzlicher Kollisionserkennung.<para></para>
		/// Gibt bei Kollision true aus.</summary>
		///<param name="mOrientation">Homogene Rotationsmatrix mit der vorgegebenen Bewegungsrichtung. Translationsanteil wird ignoriert. </param>
		///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
		///<param name="fAD">-1 für Linksverschiebung (translation left), 0 für nichts, 1 für Rechtsverschiebung (translation right)</param>
		///<param name="fSW">-1 für Vorwärts (translation forward), 0 für nichts, 1 für Rückwärts (translation back)</param>
		///<param name="fFR">-1 für Runterverschiebung (translation down), 0 für nichts, 1 für Hochverschiebung (translation up)</param>
		///<param name="zgsCollisionItems">Container, der alle Geometrien enthält, an die am anstoßen kann</param>
		bool MoveDirectionWithCollisionDetection(CHMat & mOrientation, float & fTimeDelta, bool bEarth, float & fAD, float & fSW, float & fFR, CGeos & zgsCollisionItems);

		///<summary> Bewegungssteuerung, bei der die Richtung durch eine Matrix vorgegeben ist mit zusätzlicher Kollisionserkennung.<para></para>
		/// Gibt bei Kollision true aus.</summary>
		///<param name="mOrientation">Homogene Rotationsmatrix mit der vorgegebenen Bewegungsrichtung. Translationsanteil wird ignoriert. </param>
		///<param name="mOffset">Zusatz-Matrix, z.B. falls an Kameraplacement noch ein HMD-Positionsplacement hängt). </param>
		///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		///<param name="bEarth">Flag, wenn true wird eine erdgebundene Steuerung verwendet (Horizont in der XZ-Ebene bleibt waagrecht) </param>
		///<param name="fAD">-1 für Linksverschiebung (translation left), 0 für nichts, 1 für Rechtsverschiebung (translation right)</param>
		///<param name="fSW">-1 für Vorwärts (translation forward), 0 für nichts, 1 für Rückwärts (translation back)</param>
		///<param name="fFR">-1 für Runterverschiebung (translation down), 0 für nichts, 1 für Hochverschiebung (translation up)</param>
		///<param name="zgsCollisionItems">Container, der alle Geometrien enthält, an die am anstoßen kann</param>
		bool MoveDirectionWithCollisionDetection(CHMat & mOrientation, CHMat & mOffset, float & fTimeDelta, bool bEarth, float & fAD, float & fSW, float & fFR, CGeos & zgsCollisionItems);


		///<summary> WASD-artige Bewegungssteuerung um ein Zentrum.</summary>
		///<param name="fTimeDelta">Zeitspanne in Sekunden, die seit dem letzten Tick verstrichen ist</param>
		///<param name="zpCenter"> Zielplacement, um das sich das vorliegende Placement dreht</param>
		///<param name="fLR">-1 für Linksdrehung (rotation left), 0 für nichts, 1 für Rechtsdrehung (rotation right)</param>
		///<param name="fUD">-1 für Hochdrehung (rotation up), 0 für nichts, 1 für Runterdrehung (rotation down)</param>
		///<param name="fAD">-1 für Linksverschiebung (translation left), 0 für nichts, 1 für Rechtsverschiebung (translation right)</param>
		///<param name="fSW">-1 für Vorwärts (translation forward), 0 für nichts, 1 für Rückwärts (translation back)</param>
		///<param name="fFR">-1 für Runterverschiebung (translation down), 0 für nichts, 1 für Hochverschiebung (translation up)</param>
		bool MovePan(float & fTimeDelta, CPlacement & zpCenter, float & fAD, float & fSW, float & fFR, float & fLR, float & iUD, bool bRot);

		// ---------------------------
		// Physikmethoden:
		// ---------------------------

		///<summary> Schaltet die Physikberechnungen an.</summary>
		void SetPhysicsOn();

		///<summary> Schaltet die Physikberechnungen ein und setzt gleichzeitig die wichtigsten physikalischen Parameter.</summary>
		///<param name="fMass">Masse des Partikels in Kg </param>
		///<param name="fMass">Luftwiderstandswert des Partikels in N/m^2 </param>
		///<param name="fMass">Elektrische Ladung in V </param>
		///<param name="fMass">Spezifisches Gewicht in kg/m^3 </param>
		///<param name="fMass">Flag, ob das Partikel fest ist </param>
		void SetPhysics(float fMass, float fCW, float fCharge, float fSpecificWeight, bool bSolid);

		///<summary> Schaltet die Physikberechnungen wieder aus.</summary>
		void SetPhysicsOff();

		// ---------------------------
		// Lade- und Speichermethoden:
		// ---------------------------

		///<summary> Lädt die Parameterdaten mitsamt untergeordneter Hierarchie aus einer Vektoria-Placementdatei (.vp).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Placementdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyPlacement.vp" oder ".\\Placements\\MyPlacement.vp" </param>
		bool Load(char * acPath);

		///<summary> Speichert das Placement mitsamt untergeordneter Hierarchie in eine Vektoria-Placementdatei (.vp).<para></para> 
		/// Gibt true aus, falls es funktioniert hat.</summary>
		///<param name="acPath">ASCII-Pfadangabe der Placementdatei (mit Suffix), absolute und relative Pfade sind möglich, z.B. "C:\\MyPlacement.vp" oder ".\\Placements\\MyPlacement.vp" </param>
		bool Save(char * acPath);

	protected: 

		///<summary> Lädt die Parameterdaten mitsamt untergeordneter Hierarchie  aus einem Vektoria-Placementfile (.vp).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Placments</param>
		///<param name="fVersion">Vektoriaversion, um Aufwärtskombabilität zu gewährleisten, z.B. 14.11 für die Version 14 Patch 11 </param>
		void Load(CFileVektoria & filevektoria, int id = 1, float fVersion = 14.11f);

		///<summary> Speichert die Parameterdaten mitsamt untergeordneter Hierarchie in ein Vektoria-Placementfile (.vp).</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="bWithID">Flag, ob die eigene Identifikationsnummer in das Placmentfile mit abgespeichert werden soll.</param>
		///<param name = "bCalcConverging"> Flag, ob die Berechnung konvergierender Hierarchien durchgeführt werden soll.</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false, bool bCalcConverging = true);

	public:

		//------------------
		//  Membervariablen:
		//------------------

		///<summary> Flag, ob es sich um ein von der Hioerarchie unabhängiges Placement handelt.</summary>
		bool m_bIndependent;

		///<summary> Lokale homogene Matrix</summary>
		CHMat m_mLocal;

		///<summary> Flag, ob Distanz zur Kamera nicht berechnet, sondern mit einem Wert fixiert wurde.</summary>
		bool m_bFixedDistance;

		///<summary> Entfernung zur Kamera im Quadrat.</summary>
		float m_fDistanceToCameraSquare;

		///<summary> Flag, ob es sich um ein stereoskopisches Placement handeklt.</summary>
		bool m_bStereoscopic;

		///<summary> Augenabstand bei stereoskopischen Kameraplacements.</summary>
		float m_fEyeDistance;

		///<summary> Fokussierungsabstand bei stereoskopischen Kameraplacements.</summary>
		float m_fFocusDistance;

		///<summary> Flag, ob es sich um ein Billboard-Placement handeklt.</summary>
		bool m_bBillboard;

		///<summary> Billboard-Art (normal, um die Y-Achse,...).</summary>
		int m_eBillboardType;

		///<summary> Flag, ob das Billboard modifiziert wurde (Rotation oder Skalierung).</summary>
		bool m_bBillboardModification;

		///<summary> Flag, ob es sich um ein Appendage-Placement handeklt.</summary>
		bool m_bAppendage;

		///<summary> Winkel des Billboards im Bogenmaß.</summary>
		float m_faBillboard;

		///<summary> Skalierung des Billboards in X-Richtung.</summary>
		float m_fxBillboardScale;

		///<summary> Skalierung des Billboards in Y-Richtung.</summary>
		float m_fyBillboardScale;

		///<summary> Modifizierungsmatrix des Billboards (nur akltiv bei Billboard-Placements).</summary>
		CHMat m_mBillboardModification;

		///<summary> Flag, ob es sich um ein Pointing-Placement handelt.</summary>
		bool m_bPointing;

		///<summary> Flag, ob es sich um ein PointingToVector-Placement handelt.</summary>
		bool m_bPointingToVector;

		///<summary> Die Instanz des Placements, auf den ein Pointing-Placment zeigt (Nur aktiv bei PointingToPlacment-Placments).</summary>
		int m_iPointingInstance;

		///<summary> Die Position, auf die ein Pointing-Placment zeigt (Nur aktiv bei PointingToVector-Placments).</summary>
		CHVector * m_pvPointing;

		///<summary> Zeiger auf dadjenige Placment, auf das ein Pointing-Placment zeigt (Nur gesetzt bei PointingToPlacment-Placments).</summary>
		CPlacement * m_pplacementPointing;

		///<summary> Flag, ob das Frustum Culling für die Unterhierarchie angeschaltet ist.</summary>
		bool m_bFrustumCulling;

		///<summary> Flag, ob das Frustum Culling von den Elternknoten überschrieben wird.</summary>
		bool m_bFrustumCullingEntry;

		///<summary> Flag, ob die Bounding Volume Hierarchie genau berechnet werden soll (langsam!) (Default = false).</summary>
		bool m_bBVHExactCalculation;

		///<summary> Flag, ob die Bounding Volume Hierarchie-Informationen von den Eltern an die Kinder weitergereicht weitergereicht werden sollen (Default = false).</summary>
		bool m_bBVHExactCalculationEntry;

		///<summary> Flag, ist true, wenn ein einziges transparentes Objekt unter Placement hängt (wird automatisch gesetzt).</summary>
		bool m_bTransparent;

		///<summary> Flag, ist true, wenn Inhalt für die Grafikkarte optimiert wurde (Hierarchie unter Placement ist dann niocht mehr direkt zugreifbar!).</summary>
		bool m_bStateSorted;

		///<summary> Quadrierte Ferndistanz des Level of Detail.  </summary>
		float m_fDistFarSquare;

		///<summary> Quadrierte Nahdistanz des Level of Detail.</summary>  
		float m_fDistNearSquare;

		///<summary> Flag, ob Level-of-Detail angeschaltet ist.</summary>
		bool m_bLoD;

		///<summary> Flag, ob es sich um ein Sky-Placement handelt (wandert mit der Kamera mit). </summary>
		bool m_bSky;

		///<summary> Flag, ob es sich um ein Special-Placement (Sky, Billboard, Independent ...) handelt (wird automatisch errechnet). </summary>
		bool m_bSpecial;

		///<summary> Pointer auf die untergeordneten Kamera-Placement (nur bei stereoskopischen / multiskopischen Kameras gesetzt).</summary>
		CPlacement ** m_applacementCamera;

		///<summary> Szenenliste, mit denen das Placement verbunden ist.</summary>
		CScenes  m_scenesAnchestor;

		///<summary> Pointer auf Liste der Unterplacements, wenn keine Unterplacements vorhanden sind, ist der Pointer = NULL.</summary>
		CPlacements * m_pplacements;

		///<summary> Pointer auf Liste der Unter-Scheinwerferlichtern.</summary>
		CLightSpots * m_plightspots;

		///<summary> Pointer auf Liste der Unter-Punktlichtern.</summary>
		CLightRadials * m_plightradials;

		///<summary> Pointer auf Liste der Unter-Geometrien.</summary>
		CGeos * m_pgeos;

		///<summary> Pointer auf Liste der Unter-Emitter.</summary>
		CEmitters * m_pemitters;

		///<summary> Pointer auf Liste der Unter-Kameras.</summary>
		CCameras * m_pcameras;

		///<summary> Pointer auf Liste von Unter-3D-Soundquellen.</summary>
		CAudios * m_paudios;

		///<summary> Pointer auf Liste von Schriftlabels.</summary>
		CWribels * m_pwribels;

		///<summary> Hier wird bei StateSorting die alte Unterhierarchie geparkt.</summary>
		CPlacement *m_pzpUnsorted;

		///<summary> Hier wird bei UnstateSorting die state gesortete Unterhierarchie geparkt.</summary>
		CPlacement *m_pzpSorted;

		//-----------------------------------------
		//  Membervariablen der Bewegungssteuerung:
		//-----------------------------------------

		///<summary> Translationsempfindlichkeit der Bewegungssteuerungen.</summary>
		float m_fTranslationSensitivity;

		///<summary> Rotationsempfindlichkeit der Bewegungssteuerungen.</summary>
		float m_fRotationSensitivity;

		///<summary> Azimut der Pan-Steuerungen im Bogenmaß.</summary>
		float m_faPanAzimuth;

		///<summary> Elevation der Pan-Steuerungen im Bogenmaß.</summary>
		float m_faPanAltitude;

		///<summary> Radius derPan-Steuerungen.</summary>
		float m_fPanRadius;

		///<summary> Rechts-Links-Zusatzwinkel der WASD-Pan-Steuerungen im Bogenmaß.</summary>
		float m_faLeftRight;

		///<summary> Hoch-Runter-Zusatzwinkel der WASD-Pan-Steuerungen im Bogenmaß.</summary>
		float m_faUpDown;

		///<summary> Grenzen der Bewegungssteuerungen (Nur innerhalb dieser AABB-Box kann sich bewegt werden).</summary>
		CAABB m_aabbMove;

		///<summary> Pointer auf eine potientielle Memberklasse für Physikalische Parameter und Berechnungen.
		/// Wird nur instanziiert, wenn SetPhysicsOn aufgerufen wurde, ansonsten null</summary>
		CPlacementPhysics * m_pphysics;

		///<summary> Array globaler Matrizen bei Independent-Placements.</summary>
		CHMat * m_amGlobalIndependent;

		///<summary> Anzahl globaler Matrizenbei Independent-Placements.</summary>
		int m_iGlobalIndependent;

	protected:
		///<summary> Kopiert alle Eigenschaften des Placements rekursiv in der Hierarchie hinunter, belässt die Eigenschaften, wo ein Entry-Flag gesetzt wurde.</summary>
		void CopyDownwards();

		void HierarchyStateSort(bool bFix);
		void HierarchyToGeo(CHMat & m, CGeoTriangleLists * ptrianglelists, bool bSon);
		void HierarchyToGeo();
		void HierarchyGeosToGeo(CGeoTriangleLists * ptrianglelists, CGeos * pgeos, CHMat & mGlobal);
		void HierarchyGeoToGeo(CGeoTriangleLists * ptrianglelists, CGeo * pgeo, CHMat & mGlobal);
		void HierarchyWing(CGeoTriangleLists * ptrianglelists, CGeo * pgeo, CHMat & mGlobal);
		void HierarchyWall(CGeoTriangleLists * ptrianglelists, CGeo * pgeo, CHMat & mGlobal);

		int m_iDraw;
		bool m_bLastInsideLoD;
		int m_iTickPlacement;


	};

}