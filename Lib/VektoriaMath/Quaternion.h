#pragma once
#include "HVector.h"
#include "HMat.h"

//------------------------------------
// CQuaternion
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.12.2011
// Copyright: Vektoria UG (haftungsbeschr‰nkt)
//------------------------------------

namespace Vektoria
{

class CQuaternion
{
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor.
	/// Achtung, setzt keine Tupelwerte, auch nicht auf 0!</summary> 
	CQuaternion();  

	///<summary> Konstruktor mit impliziter Angabe der Tupelwerte des Quaternions.</summary>
	///<param name="fx">X-Tupel des Quaternions</param>
	///<param name="fy">Y-Tupel des Quaternions</param>
	///<param name="fz">Z-Tupel des Quaternions</param>
	///<param name="fw">W-Tupel des Quaternions</param>
	CQuaternion(float fx, float fy, float fz, float fw);

	///<summary> Zuweisungsoperator.</summary>
	///<param name="quaternion">Zu kopierendes Quaternion</param>
	CQuaternion operator=(CQuaternion quaternion); 

	///<summary> Kopiermethode.</summary>
	///<param name="quaternion">Zu kopierendes Quaternion</param>
	void Copy(CQuaternion & quaternion); 

	///<summary> Vergleich zweier Quaternionen auf Gleichheit.</summary>
	///<param name="quaternion">Zu vergleichendes Quaternion</param>
	bool operator==(CQuaternion & quaternion); 

	///<summary> Vergleich zweier Quaternionen auf Ungleichheit.</summary>
	///<param name="quaternion">Zu vergleichendes Quaternion</param>
	bool operator!=(CQuaternion & quaternion); 

	///<summary> Quaternionenmultiplikation.</summary>
	///<param name="q">Quaternionenfaktor</param>
	CQuaternion operator*(CQuaternion & q); 

	///<summary> Quaternionenaddition.</summary>
	///<param name="q">Quaternionensummand</param>
	CQuaternion operator+(CQuaternion & q); 

	///<summary> Quaternionensubtraktion.</summary>
	///<param name="q">Quaternionensubtrahent</param>
	CQuaternion operator-(CQuaternion & q); 

	///<summary> Quaternionenmultiplikation - Schnelloperator.</summary>
	///<param name="q">Quaternionenfaktor</param>
	CQuaternion operator*=(CQuaternion & q); 

	///<summary> Quaternionenaddition - Schnelloperator.</summary>
	///<param name="q">Quaternionensummand</param>
	CQuaternion operator+=(CQuaternion & q); 

	///<summary> Quaternionensubtraktion - Schnelloperator.</summary>
	///<param name="q">Quaternionensubtrahent</param>
	CQuaternion operator-=(CQuaternion & q); 

	///<summary> Skalarprodukt (Quaternionenskalierung durch Multiplikation, rechts).</summary>
	///<param name="f">Skalarfaktor</param>
	CQuaternion operator*(float f); 

	///<summary> Skalardivision (Quaternionenskalierung durch Division, rechts).</summary>
	///<param name="f">Skalardivident</param>
	CQuaternion operator/(float f); 

	///<summary> Quaternionenskalierung durch Multiplikation - Schnelloperator.</summary>
	///<param name="f">Skalarfaktor</param>
	CQuaternion operator*=(float f); 

	///<summary> Quaternionenskalierung durch Division - Schnelloperator.</summary>
	///<param name="f">Skalardivident</param>
	CQuaternion operator/=(float f); 
	
	///<summary> Setzt das Quaternion auf die angegebenen Werte.</summary>
	///<param name="fx">X-Tupel</param>
	///<param name="fy">Y-Tupel</param>
	///<param name="fz">Z-Tupel</param>
	///<param name="fw">W-Tupel</param>
	void Init(float fx, float fy, float fz, float fw); 	
	
	///<summary> Finalisiert das Quaternion.<para></para>
	/// Nur der Vollst‰ndigkeit halber implementiert, macht gar nix, weils es nichts zu finalisieren gibt.</summary>
	void Fini(); 

	///<summary> Konjugiert das Quaternion.</summary>
	void Conjugate();

	///<summary> Invertiert das Quaternion.</summary>
	void Inverse(); 

	///<summary> Normiert das Quaternion.</summary>
	void Norm(); 

	///<summary> Gibt den Betrag des Quaternions aus.</summary>
	float Length(); 

	///<summary> Rotiert den Punkt v mit Hilfe des vorliegenden Rotationsquaternions und gibt Ergebnis als Returnwert aus.</summary>
	///<param name="v">Der zu rotierende Punkt</param>
	CHVector ApplyRotation(CHVector & v); 

	///<summary> Generiert ein Rotationsquaternion um die X-Achse. <para></para>
	/// fa: Winkel im Bogenmaﬂ.</summary>
	///<param name="fa">Rotationswinkel im Bogenmaﬂ</param>
	void RotateX(float fa);		

	///<summary> Generiert ein Rotationsquaternion um die Y-Achse. <para></para>
	/// fa: Winkel im Bogenmaﬂ.</summary>
	///<param name="fa">Rotationswinkel im Bogenmaﬂ</param>
	void RotateY(float fa);		

	///<summary> Generiert ein Rotationsquaternion um die Z-Achse.<para></para> 
	/// fa: Winkel im Bogenmaﬂ.</summary>
	///<param name="fa">Rotationswinkel im Bogenmaﬂ</param>
	void RotateZ(float fa);		


	///<summary> Generiert ein beliebiges Rotationsquaternion um die Drehachse (fx, fy, fz) mit dem Winkel fa.<para></para>
	/// Achtung, die Drehachse sollte normiert sein!</summary>
	///<param name="fx">X-Tupel</param>
	///<param name="fy">Y-Tupel</param>
	///<param name="fz">Z-Tupel</param>
	///<param name="fa">Rotationswinkel im Bogenmaﬂ</param>
	void Rotate(float fx, float fy, float fz, float fa);

	///<summary> Generiert ein beliebiges Rotationsquaternion um die Drehachse (fx, fy, fz) mit dem Winkel fa.<para></para> 
	/// v: Drehachse (Achtung, sollte normiert sein)</summary>
	///<param name="v">Rotationsachse</param>
	///<param name="fa">Rotationswinkel im Bogenmaﬂ</param>
	void Rotate(CHVector & v, float fa); 

	///<summary> Addiert die Rotation von qRot auf das aktuelle Rotationsquaternion.<para></para>  
	/// Achtung, noch ungetetstet!</summary>
	///<param name="qRot">Rotationsquaternion</param>
	void RotateDelta(CQuaternion qRot); 

	///<summary> Lineare Interpolation zwischen zwei Quaternionen.</summary>
	///<param name="qFrom">Startrotationsquaternion</param>
	///<param name="qTo">Zielrotationsquaternion</param>
	///<param name="fr">Laufparameter, Wertebereich [0..1|</param>
	void Lerp(CQuaternion qFrom, CQuaternion qTo, float fr); 

	///<summary> Sph‰rische Interpolation zwischen zwei Quaternionen.</summary>
	///<param name="qFrom">Startrotationsquaternion</param>
	///<param name="qTo">Zielrotationsquaternion</param>
	///<param name="fr">Laufparameter, Wertebereich [0..1|</param>
	void Slerp(CQuaternion qFrom, CQuaternion qTo, float fr); 

	///<summary> Holt die Tupelwerte X, Y und Z des Quaternions und schreibt sie in den Vektor, der homogene Faktor wird auf 0 gesetzt.</summary>
	CHVector GetVector(); 

	///<summary> Setzt die Tupelwerte X, Y und Z des Quaternions auf die entsprechenden Werte des Vektors, der Tupelwert W wird auf 0 gesetzt.</summary>
	///<param name="v">Vektor dessen Tupelwerte X,Y und Z ins vorliegende Quaternion kopiert werden</param>
	void SetVector(CHVector  & v); 

	///<summary> Generiert eine Rotationsmatrix aus Quaternion und gibt sie aus.</summary>
	CHMat GetMatrix(); 

	///<summary> Generiert eine Rotationsmatrix aus einem normierten Quaternion und gibt sie aus.<para></para>
	/// Achtung, das Quaternion muss normiert sein, sonst kommt hier etwas falsches raus, daf¸r ist sie etwas schneller als GetMatrix.</summary>
	CHMat GetMatrixByNormed(); 

	///<summary> Generiert das Quaternion aus der Rotationsmatrix m.</summary>
	///<param name="m">Matrix</param>
	void SetMatrix(CHMat & m); 

	///<summary> Setzt den X-Wert.</summary>
	///<param name="f">X-Wert</param>
	void SetX(float f); 

	///<summary> Setzt den Y-Wert.</summary>
	///<param name="f">Y-Wert</param>
	void SetY(float f); 

	///<summary> Setzt den Z-Wert.</summary>
	///<param name="f">Z-Wert</param>
	void SetZ(float f); 

	///<summary> Setzt den rationalen Wert.</summary>
	///<param name="f">W-Wert</param>
	void SetW(float f); 

	///<summary> Gibt den aktuellen X-Wert aus.</summary>
	float GetX(); 

	///<summary> Gibt den aktuellen Y-Wert aus.</summary>
	float GetY(); 

	///<summary> Gibt den aktuellen Z-Wert aus.</summary>
	float GetZ(); 

	///<summary> Gibt den rationalen Wert aus.</summary>
	float GetW(); 

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Der X-Tupel.</summary>
	float m_fx;

	///<summary> Der Y-Tupel.</summary>
	float m_fy;

	///<summary> Der Z-Tupel.</summary>
	float m_fz;

	///<summary> Der rationale Tupel.</summary>
	float m_fw;

};

}