#pragma once

//---------------------------------------------------
// CHVector : Klasse für homogene Vektoren
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{

enum EAxis
{
	eAxisX = 0,
	eAxisY,
	eAxisZ
};

class CHVector
{
public:
	///<summary> Konstruktor 1 (alle Werte auf Null).</summary> 
	CHVector(); 

	///<summary> Konstruktor 2 (alle Werte werden dediziert übergeben).</summary> 
	///<param name="fx">X-Anteil</param> 
	///<param name="fy">Y-Anteil</param> 
	///<param name="fz">Z-Anteil</param> 
	///<param name="fw">Homogener Anteil (0=Richtung, 1 = genormte Position)</param>
	CHVector(float fx, float fy, float fz, float fw); 

	///<summary> Konstruktor 3 für Raumpunkte (x-,y- und z-Position werden angegeben, letzter homogener Wert wird auf Eins gesetzt).</summary>  
	///<param name="fx">X-Anteil</param> 
	///<param name="fy">Y-Anteil</param> 
	///<param name="fz">Z-Anteil</param>
	CHVector(float fx, float fy, float fz); 

	///<summary> Konstruktor 4 (Erzeugt angegebenen Axenrichtungsvektor, letzter Wert wird auf Null gesetzt).</summary>  
	///<param name="eAxis">Kartesische Achse (eAxisX, eAxisY oder aAxisZ) </param>
	CHVector(EAxis eAxis); 

	///<summary> Vektorzuweisung.</summary>  
	///<param name="v">Zu kopierender Vektor </param>
	CHVector operator=(CHVector & v); 

	///<summary> Vektoraddition.</summary>  
	///<param name="v">Vektorsummand</param>
	CHVector operator+(CHVector & v); 

	///<summary> Vektorsubtraktion.</summary>  
	///<param name="v">Vektorsubtrahent</param>
	CHVector operator-(CHVector & v); 

	///<summary> Vektoraddition mit inklusiver Zuweisung - Schnelloperator.</summary>  
	///<param name="v">Vektorsummand</param>
	CHVector operator+=(CHVector & v); 

	///<summary> Vektorsubtraktion mit inklusiver Zuweisung - Schnelloperator.</summary>  
	///<param name="v">Vektorsubtrahent</param>
	CHVector operator-=(CHVector & v); 

	///<summary> Skalarprodukt.</summary> 
	///<param name="v">Vektorfaktor</param>
	float operator*(CHVector & v); 

	///<summary> Skalardivision.</summary>  
	///<param name="v">Vektordivident</param>
	float operator/(CHVector & v); 

	///<summary> Skalarprodukt (rechts).</summary>  
	///<param name="f">Skalarfaktor</param>
	CHVector operator*(float f); 

	///<summary> Skalardivision (rechts).</summary>  
	///<param name="f">Skalardivident</param>
	CHVector operator/(float f);

	///<summary> Vektorskalierung durch Multiplikation - Schnelloperator.</summary>  
	///<param name="f">Skalarfaktor</param>
	CHVector operator*=(float f); 

	///<summary> Vektorskalierung durch Division - Schnelloperator.</summary>  
	///<param name="f">Skalardivident</param>
	CHVector operator/=(float f); 

	///<summary> Vergleich zweier Vektoren auf Gleichheit.</summary>  
	///<param name="v">Vegleichsvektor</param>
	bool operator==(CHVector & v); 

	///<summary> Vergleich zweier Vektoren auf Ungleichheit.</summary> 
	///<param name="v">Vegleichsvektor</param>
	bool operator!=(CHVector & v); 

	///<summary> Gibt Stelle iPos des Vektors aus.</summary> 
	///<param name="iPos">Tupelstelle</param>
	float operator[] (int iPos); 

	///<summary> Negation des Vektors.	<para></para>
	/// => Minus vor allen Vektorelementen.</summary>
	CHVector operator -(void); 

	///<summary> Positivzeichen vor Vektor. <para></para>
	/// Führt zu keiner Veränderung, trotzdem der mathematisch vollwertigen Notation halber wichtig.</summary> 
	CHVector operator +(void); 
 
	///<summary> Kreuzprodukt.</summary> 
	///<param name="v">Vektor-Faktor für das Kreuzprodukt</param>
	CHVector operator^(CHVector & v); 

	///<summary> Kopiert den Vektor v in den vorliegnden Vector.</summary> 
	///<param name="v">Zu kopierender Vektor</param>
	void Copy(CHVector & v);	

	///<summary> Initialisiert oder überschreibt die Werte des Vektors.</summary> 
	///<param name="fx">X-Wert</param>
	///<param name="fy">Y-Wert</param>
	///<param name="fz">Z-Wert</param>
	///<param name="fw">Homogener Wert</param>
	void Init(float fx, float fy, float fz, float fw); 

	///<summary> Initialisiert oder überschreibt die Werte des Vektors, der W-Wert ist Eins, um einen Raumpunkt anzuzeigen.</summary> 
	///<param name="fx">X-Wert</param>
	///<param name="fy">Y-Wert</param>
	///<param name="fz">Z-Wert</param>
	void InitPoint(float fx, float fy, float fz); 

	///<summary> Initialisiert oder überschreibt die Werte des Vektors, der W-Wert ist Null, um eine Richtung anzuzeigen.</summary> 
	///<param name="fx">X-Wert</param>
	///<param name="fy">Y-Wert</param>
	///<param name="fz">Z-Wert</param>
	void InitDirection(float fx, float fy, float fz); 

	///<summary> Setzt alle Tupelwerte auf Null.</summary> 
	void Null(); 

	///<summary> Gibt true aus, wenn alle Tupelwerte gleich Null sind.</summary> 
	bool IsNull(); 

	///<summary> Gibt einen Vektor aus, der genau in der Mitte zwischen aktuellem und angegebenen Vektor liegt.</summary> 
	///<param name="v">2. Vektor</param>
	CHVector Mid(CHVector & v); 

	///<summary> Gibt einen Vektor aus den jeweils kleineren Tupelwerten aus.</summary> 
	///<param name="v">Ursprünglicher Vektor</param>
	CHVector Min(CHVector & v);

	///<summary> Gibt einen Vektor aus den jeweils größeren Tupelwerten aus.</summary> 
	///<param name="v">Ursprünglicher Vektor</param>
	CHVector Max(CHVector & v);

	///<summary> Gibt Projizierte von v auf den vorliegenden Vektor aus.</summary> 
	///<param name="v">Zu projizierender Vektor</param>
	CHVector Project(CHVector &v); 

	///<summary> Gibt Projizierte vom vorliegenden Vektor auf v aus.</summary> 
	///<param name="v">Vektor, auf den die Projizierte kopiert wird</param>
	CHVector Reject(CHVector &v);

	///<summary> Erzeugt einen normierten Richtungsvektor und gibt ihn gleichzeitig aus. <para></para>
	/// Im Gegensatz zur Methode "Norm" wird noch zusätzlich gecheckt, ob der W-Tupel korrekt auf Null gesetzt ist. </summary>
	CHVector Normal();	

	///<summary> Normiert den vorliegenden Vektor.</summary> 
	void Norm();	 

	///<summary> Dreht die Richtung des Vektors um.</summary> 
	void Flip();	

	///<summary> Gibt den Betrag (=Länge) des Vektors als Skalar aus.</summary> 
	float Length();	

	///<summary> Gibt den quadrierten Betrag des Vektors aus.</summary> 
	float LengthSquare();	

	///<summary> Macht aus einem Raumpunkt einen Richtungsvektor.</summary>  
	void MakeDirection();

	///<summary> Macht aus einem Richtungsvektor einen Raumpunkt.</summary> 
	void MakePoint();		

	///<summary> Skaliert einen Vektor mit den Werten eines anderen Vectors.</summary> 
	///<param name="v">Skalierender Vektor</param>
	void Scale(CHVector & v);		

	///<summary> Gibt true aus, wenn der vorliegende Vektor auf der Geraden zwischen zwei anderen Vektoren liegt.</summary> 
	///<param name="vA">Punktvektor A</param>
	///<param name="vB">Punktvektor B</param>
	///<param name="fAccuracyThreshold">Genauigkeitsschwelle, je größer, desto mehr darf der Punkt von der genauen Geraden abweichen.</param>
	bool IsBetween(CHVector & vA, CHVector & vB, float fAccuracyThreshold = 0.001f);

	///<summary> Berechnet die euklidische Distanz zwischen diesem Vektor und einem anderen Vektor.</summary> 
	///<param name="v">Anderer Vektor</param>
    float Dist(CHVector & v);       

	///<summary> Interpoliert linear zwischen Positionsvektor A und Positionsvektor B über einen fraktionalen Gewichtungsfaktor.<para></para> 
	/// Gibt interpolierten Vektor zusätzlich als Returnwert aus.</summary> 
	///<param name="vA">Positionsvektor A</param>
	///<param name="vA">Positionsvektor B</param>
	///<param name="fr">Fraktionaler Gewichtungsfaktor (0.0 = Vektor A ... 0.5 = in der Mitte .. 1.0 = Vektor B)</param>
	CHVector InterpolLinear(CHVector & vA, CHVector & vB, float fr);

	///<summary> Interpoliert den Winkel zwischen Richtungsvektor A und Richtungsvektor B via dem SLERP-Algorithmus über einen fraktionalen Gewichtungsfaktor.<para></para> 
	/// Gibt interpolierten Vektor zusätzlich als Returnwert aus. <para></para>
	/// Achtung!!! Noch nicht getestet! </summary> 
	///<param name="vA">Richtungsvektor A</param>
	///<param name="vA">Richtungsvektor B</param>
	///<param name="fr">Fraktionaler Gewichtungsfaktor (0.0 = Vektor A ... 0.5 = in der Mitte .. 1.0 = Vektor B)</param>
	CHVector InterpolAngular(CHVector & vA, CHVector & vB, float fra);


	///<summary> Setzt den X-Wert.</summary> 
	///<param name="f">Wert</param>
	void SetX(float f);

	///<summary> Setzt den Y-Wert.</summary> 
	///<param name="f">Wert</param>
	void SetY(float f); 

	///<summary> Setzt den Z-Wert.</summary> 
	///<param name="f">Wert</param>
	void SetZ(float f); 

	///<summary> Setzt den homogenen Wert.</summary> 
	///<param name="f">Wert</param> 
	void SetW(float f); 

	///<summary> Setzt alle Tupelwerte des Vektors auf den Wert f.</summary> 
	///<param name="f">Wert</param>
	void SetXYZW(float f); 

	///<summary> Setzt die Tupelwerte X,Y,Z auf den Wert f</summary>
	///<param name="f">Wert</param>
	void SetXYZ(float f); 

	///<summary> Setzt die Tupelwerte X,Y,Z auf den Wert f und den W-Tupelwert auf 0.</summary> 
	///<param name="f">Wert</param>
	void SetXYZ0(float f); 

	///<summary> Setzt die Tupelwerte X,Y,Z auf den Wert f und den W-Tupelwert auf 1.</summary> 
	///<param name="f">Wert</param>
	void SetXYZ1(float f); 

	///<summary> Setzt den Vektor auf die X-Normale. <para></para>
	// Der Vektor hat danach folgende Werte:  (1,0,0,0).</summary> 
	void NormalX(); 

	///<summary> Setzt den Vektor auf die Y-Normale. <para></para>
	// Der Vektor hat danach folgende Werte:  (0,1,0,0).</summary> 
	void NormalY(); 

	///<summary> Setzt den Vektor auf die Z-Normale. <para></para>
	// Der Vektor hat danach folgende Werte:  (0,0,1,0)´.</summary> 
	void NormalZ();

	///<summary> Gibt den aktuellen X-Wert aus.</summary> 
	float GetX(); 

	///<summary> Gibt den aktuellen Y-Wert aus.</summary> 
	float GetY(); 

	///<summary> Gibt den aktuellen Z-Wert aus.</summary> 
	float GetZ();

	///<summary> Gibt den homogenen Wert aus.</summary> 
	float GetW(); 

	///<summary> Gibt den Winkel im Bogenmaß aus, der sich zwischen dem bestehenden Vektor und dem Vector v befindet.</summary> 
	///<param name="v">Zweiter Richtungsvektor, der mit dem vorliegenden einen Winkel aufspannnt</param>
	float Angle(CHVector & v);

	///<summary> Gibt den auf die XY-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht X-Achse).</summary> 
	float AngleXY(); 

	///<summary> Gibt den auf die XZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Z-Achse).</summary> 
	float AngleZX(); 

	///<summary> Gibt den auf die YZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Y-Achse).</summary> 
	float AngleYZ(); 

	///<summary> Gibt den auf die XY-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Y-Achse).</summary> 
	float AngleYX(); 

	///<summary> Gibt den auf die XZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht X-Achse).</summary> 
	float AngleXZ(); 

	///<summary> Gibt den auf die YZ-Ebene projizierten Drehwinkel im Bogenmaß aus (Null entspricht Z-Achse).</summary> 
	float AngleZY(); 

	///<summary> Berechnet den interpolierten Punkt einer kubischen Bézier-Kurve, f ist der Laufparameter definiert zwischen 0.0 und 1.0.</summary> 
	///<param name="v0">Erster Stützpunkt</param>
	///<param name="v1">Zweiter Stützpunkt</param>
	///<param name="v2">Dritter Stützpunkt</param>
	///<param name="v3">Vierter und letzter Stützpunkt</param>
	///<param name="fr">Laufparameter, Wertebereich = [0.0f...1.0f]</param>
	CHVector BezierCurve(CHVector v0, CHVector v1, CHVector v2, CHVector v3, float & fr); 

	///<summary> Berechnet den interpolierten Punkt einer kubischen Bézier-Kurve, f ist der Laufparameter definiert zwischen 0.0 und 1.0.</summary> 
	///<param name="av">Array der vier Stützpunkte</param>
	///<param name="fr">Laufparameter, Wertebereich = [0.0f...1.0f]</param>
	CHVector BezierCurve(CHVector av[4], float & fr); 

	///<summary> Berechnet den interpolierten Punkt eines bikubischen Bezier-Patches,  fu und fv sind díe Laufparameter, jeweils definiert zwischen 0.0 und 1.0.</summary>
	///<param name="aav">Zweidimensionales Array von vier mal vier Stützpunkten</param>
	///<param name="fru">Laufparameter in U-Richtung, Wertebereich = [0.0f...1.0f]</param>
	///<param name="frv">Laufparameter in V-Richtung, Wertebereich = [0.0f...1.0f]</param>
	CHVector BezierPatch(CHVector aav[4][4], float &fru, float &frv); 

	///<summary> Berechnet die erste Ableitung einer kubischen Bézier-Kurve.</summary> 
	///<param name="av">Array der vier Stützpunkte</param>
	///<param name="fr">Laufparameter, Wertebereich = [0.0f...1.0f]</param>
	CHVector BezierCurveDeriv(CHVector av[4], float & fr); 

	///<summary> Berechnet die erste Ableitung eines bikubischen Bézier-Patches in U-Richtung.</summary> 
	///<param name="aav">Zweidimensionales Array von vier mal vier Stützpunkten</param>
	///<param name="fru">Laufparameter in U-Richtung, Wertebereich = [0.0f...1.0f]</param>
	///<param name="frv">Laufparameter in V-Richtung, Wertebereich = [0.0f...1.0f]</param>
	CHVector BezierPatchDerivU(CHVector aav[4][4], float &fru, float &frv); 

	///<summary> Berechnet die erste Ableitung eines bikubischen Bézier-Patches in V-Richtung.</summary> 
	///<param name="aav">Zweidimensionales Array von vier mal vier Stützpunkten</param>
	///<param name="fru">Laufparameter in U-Richtung, Wertebereich = [0.0f...1.0f]</param>
	///<param name="frv">Laufparameter in V-Richtung, Wertebereich = [0.0f...1.0f]</param>
	CHVector BezierPatchDerivV(CHVector aav[4][4], float &fru, float &frv); 


	union
	{
		struct
		{
			///<summary> Der X-Tupel.</summary> 
			float m_fx;

			///<summary> Der Y-Tupel.</summary> 
			float m_fy;

			///<summary> Der Z-Tupel.</summary> 
			float m_fz;

			///<summary> Der homogene Tupel.</summary> 
			float m_fw;
		};
		struct
		{
			///<summary> Der X-Tupel.</summary> 
			float x;

			///<summary> Der Y-Tupel.</summary> 
			float y;

			///<summary> Der Z-Tupel.</summary> 
			float z;

			///<summary> Der homogene Tupel.</summary> 
			float w;
		};
	};
};

}