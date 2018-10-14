#pragma once
#include "HVector.h"

//------------------------------------------------------------------
// CHMat: Klasse für homogene 4*4-Matrizen
// Autor: Prof. Dr. Tobias Breiner 
// 
// Anmerkung: Aus Performanzgründen wurden keine Schleifen verwendet.
//-------------------------------------------------------------------

namespace Vektoria
{

	class CRay;

class CHMat
{
public:
	///<summary>  Konstruktor. Achtung! Setzt die Tupel aus Performanzgründen nicht auf Initialwerte!</summary> 
	CHMat();

	///<summary>  Konstruktor für alle Tupelwerte.</summary> 
	///<param name="">Tupel 1,1 der homogenen Matrix</param>
	///<param name="">Tupel 1,2 der homogenen Matrix</param>
	///<param name="">Tupel 1,3 der homogenen Matrix</param>
	///<param name="">Tupel 1,4 der homogenen Matrix</param>
	///<param name="">Tupel 2,1 der homogenen Matrix</param>
	///<param name="">Tupel 2,2 der homogenen Matrix</param>
	///<param name="">Tupel 2,3 der homogenen Matrix</param>
	///<param name="">Tupel 2,4 der homogenen Matrix</param>
	///<param name="">Tupel 3,1 der homogenen Matrix</param>
	///<param name="">Tupel 3,2 der homogenen Matrix</param>
	///<param name="">Tupel 3,3 der homogenen Matrix</param>
	///<param name="">Tupel 3,4 der homogenen Matrix</param>
	///<param name="">Tupel 4,1 der homogenen Matrix</param>
	///<param name="">Tupel 4,2 der homogenen Matrix</param>
	///<param name="">Tupel 4,3 der homogenen Matrix</param>
	///<param name="">Tupel 4,4 der homogenen Matrix</param>
	CHMat(float fx00, float fx01, float fx02, float fx03,
		  float fx10, float fx11, float fx12, float fx13, 
	      float fx20, float fx21, float fx22, float fx23, 
	      float fx30, float fx31, float fx32, float fx33);

	///<summary>  Zuweisungsoperator.</summary> 
	///<param name="hmat">Zu kopierende homogene Matrix</param>
	CHMat operator=(CHMat & hmat); 

	///<summary>  Kopiert die Matrix hmat in die vorliegende Matrix.</summary> 
	///<param name="hmat">Zu kopierende homogene Matrix</param>
	void Copy(CHMat & hmat); 

	///<summary>  Kopiert den Rotationsanteil von hmat, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt.</summary> 
	///<param name="hmat">Homogene Matrix, deren Rotationsanteil kopiert wird</param>
	void CopyRotation(CHMat & hmat); 	
	
	///<summary>  Kopiert den Rotationsanteil von hmat um die X-Achse, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt.</summary> 
	///<param name="hmat">Homogene Matrix, deren X-Rotationsanteil kopiert wird</param>
	void CopyRotationX(CHMat & hmat); 

	///<summary>  Kopiert den Rotationsanteil von hmat um die Y-Achse, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt.</summary> 
	///<param name="hmat">Homogene Matrix, deren Y-Rotationsanteil kopiert wird</param>
	void CopyRotationY(CHMat & hmat); 

	///<summary>  Kopiert den Rotationsanteil von hmat um die Z-Achse, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt.</summary> 
	///<param name="hmat">Homogene Matrix, deren Z-Rotationsanteil kopiert wird</param>
	void CopyRotationZ(CHMat & hmat); 

	///<summary>  Setzt nur den Rotationsanteil um die X-Achse.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
    void CopyRotationX(float fa); 

	///<summary>  Setzt nur den Rotationsanteil um die Y-Achse.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
    void CopyRotationY(float fa); 

	///<summary>  Setzt nur den Rotationsanteil um die Z-Achse.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
    void CopyRotationZ(float fa); 

	///<summary>  Setzt nur den Rotationsanteil um die X-Achse und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
    void CopyRotationXDelta(float fa);

	///<summary>  Setzt nur den Rotationsanteil um die Y-Achse und multipliziert diese mit der aktuellen Matrix.</summary>
	///<param name=fa">Rotationswinkel im Bogenmaß</param> 
	void CopyRotationYDelta(float fa);
  
	///<summary>  Setzt nur den Rotationsanteil um die Z-Achse und multipliziert diese mit der aktuellen Matrix.</summary>
	///<param name="fa">Rotationswinkel im Bogenmaß</param> 
	void CopyRotationZDelta(float fa);

	///<summary>  Kopiert den translativen Anteil von hmat, ansonsten werden die Werte mit Einheitsmatrix-Werten aufgefüllt.</summary> 
	///<param name="hmat"></param>
	void CopyTranslation(CHMat & hmat); 
    
	///<summary>  Setzt ausschließlich den translativen Anteil.</summary> 
	///<param name="v">Vektor, deren X-, Y- und Z-Wert in die entsprechenden Tupel der Matrix kopiert wird</param>
    void CopyTranslation(CHVector & v); 

	///<summary>  Setzt ausschließlich den translativen Anteil von X.</summary> 
	///<param name="fx">X-Translationswert</param>
	void CopyTranslationX(float fx);

	///<summary>  Setzt ausschließlich den translativen Anteil von Y.</summary> 
	///<param name="fy">Y-Translationswert</param>
	void CopyTranslationY(float fy);

	///<summary>  Setzt ausschließlich den translativen Anteil von Z.</summary> 
	///<param name="fz">Z-Translationswert</param>
	void CopyTranslationZ(float fz);

	///<summary>  Setzt ausschließlich die Skalierung.</summary> 
	///<param name="f">Skalierungsfaktor</param>
    void CopyScale(float f); 

	///<summary>  Setzt ausschließlich die Skalierung in X-Richung.</summary> 
	///<param name="fx">X-Skalierungsfaktor</param>
    void CopyScaleX(float fx);
	
	///<summary>  Setzt ausschließlich die Skalierung in Y-Richung.</summary> 
	///<param name="fy">Y-Skalierungsfaktor</param>
	void CopyScaleY(float fy);
	
	///<summary>  Setzt ausschließlich die Skalierung in Z-Richung.</summary> 
	///<param name="fz">Z-Skalierungsfaktor</param>
	void CopyScaleZ(float fz);

	///<summary>  Setzt ausschließlich die Skalierung und multipliziert die entstehende Matrix mit der aktuellen Matrix.</summary> 
	///<param name=f"">Skalierungsfaktor</param>
    void CopyScaleDelta(float f); 

	///<summary>  Setzt ausschließlich die Skalierung in X-Richtung und multipliziert die entstehende Matrix mit der aktuellen Matrix.</summary> 
	///<param name="fx">X-Skalierungsfaktor</param>
	void CopyScaleXDelta(float fx);

	///<summary>  Setzt ausschließlich die Skalierung in Y-Richtung und multipliziert die entstehende Matrix mit der aktuellen Matrix.</summary> 
	///<param name="fy">Y-Skalierungsfaktor</param>
	void CopyScaleYDelta(float fy);

	///<summary>  Setzt ausschließlich die Skalierung in Z-Richtung und multipliziert die entstehende Matrix mit der aktuellen Matrix.</summary> 
	///<param name="fz">Z-Skalierungsfaktor</param>
	void CopyScaleZDelta(float fz);

	///<summary>  Matrix-Matrix-Multiplikation.</summary>  
	///<param name="hmat">Matrix, mit der multipliziert wird</param>
	CHMat operator*(CHMat & hmat); 	
	
	///<summary>  Matrix-Vector-Multiplikation.</summary> 
	///<param name="v">Vektor, mit dem multipliziert wird</param>
	CHVector operator*(CHVector & v);  

	///<summary>  Matrix-Strahl-Multiplikation (Alle Werte des Strahls werden sinnfällig gemäß der Matrix verändert).</summary> 
	///<param name="r">Strahl, mit dem multipliziert wird</param>
	CRay operator*(CRay & r);


	///<summary>  Matrix-Matrix-Multiplikation - Schnelloperator.</summary>
	///<param name="hmat">Matrix, mit der multipliziert wird</param>  
	void operator*=(CHMat & hmat); 

	///<summary>  Matrix-Matrix-Addition.</summary> 
	///<param name="hmat">Matrix, die aufaddiert wird</param>
	CHMat operator+(CHMat & hmat);

	///<summary>  Matrix-Matrix-Subtraktion.</summary> 
	///<param name="hmat">Matrix, die subtrahiert wird</param>
	CHMat operator-(CHMat & hmat); 

	///<summary>  Initialisiert Matrix als Einheitsmatrix.</summary> 
	void Init();				

	///<summary>  Initialisiert Matrix mit dedizierten Tupelwerten.</summary> 
	///<param name="fx00">Tupel 1,1</param>
	///<param name="fx01">Tupel 1,2</param>
	///<param name="fx02">Tupel 1,3</param>
	///<param name="fx03">Tupel 1,4</param>
	///<param name="fx10">Tupel 2,1</param>
	///<param name="fx11">Tupel 2,2</param>
	///<param name="fx12">Tupel 2,3</param>
	///<param name="fx13">Tupel 2,4</param>
	///<param name="fx20">Tupel 3,1</param>
	///<param name="fx21">Tupel 3,2</param>
	///<param name="fx22">Tupel 3,3</param>
	///<param name="fx23">Tupel 3,4</param>
	///<param name="fx30">Tupel 4,1</param>
	///<param name="fx31">Tupel 4,2</param>
	///<param name="fx32">Tupel 4,3</param>
	///<param name="fx33">Tupel 4,4</param>
	void Init(float fx00, float fx01, float fx02, float fx03,
		      float fx10, float fx11, float fx12, float fx13, 
			  float fx20, float fx21, float fx22, float fx23, 
			  float fx30, float fx31, float fx32, float fx33); 

	///<summary>  Generiert Einheitsmatrix.</summary> 
	void Unit();				

	///<summary>  Generiert Farbwert-Rotationsmatrix mit Winkel fa.</summary> 
	///<param name="fa">Farbwertwinkel im Bogenmaß (Rot = 0, Grün = 2/3 pi, Blau = 4/3 pi)</param>
	void RotateHue(float fa);	

	///<summary>  Generiert eine Rotationsmatrix um die X-Achse mit Winkel fa.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateX(float fa);		

	///<summary>  Generiert eine Rotationsmatrix um die Y-Achse mit Winkel fa.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateY(float fa);		

	///<summary>  Generiert eine Rotationsmatrix um die Z-Achse mit Winkel fa.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateZ(float fa);		

	///<summary>  Generiert eine Rotationsmatrix um die kartesische Achse eAxis mit Winkel fa.</summary> 
	///<param name="eAxis">Kartesische Achse (eAxisX, eAxisY oder eAxisZ)</param>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void Rotate(EAxis eAxis, float fa);		

	///<summary>  Generiert eine beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa.</summary> 
	///<param name="fx">X-Anteil der Drehachse</param>
	///<param name="fy">Y-Anteil der Drehachse</param>
	///<param name="fz">Z-Anteil der Drehachse</param>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void Rotate(float fx, float fy, float fz, float fa); 

	///<summary>  Generiert eine beliebige Rotationsmatrix um die Drehachse v mit Winkel fa.</summary> 
	///<param name="v">Drehachse</param>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void Rotate(CHVector & v, float fa); 

	///<summary>  Erzeugt eine Rotationsmatrix, die Richtungsvektor vFrom genau in die Richtung des Richtungsvektors vTo rotiert.</summary> 
	///<param name="vTo">Richtung, zu der rotiert wird</param>
	///<param name="vFrom">Richtung, von der aus rotiert wird</param>
	void Rotate(CHVector & vTo, CHVector & vFrom); 

	///<summary>  Generiert eine Skalierungsmatrix mit drei verschiedenen Skalierungswerten.</summary> 
	///<param name="v">Skalierungsvektor</param>
	void Scale(CHVector & v);	

	///<summary>  Generiert eine Skalierungsmatrix mit drei verschiedenen Skalierungswerten.</summary> 
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	///<param name="fz">Skalierungsfaktor in Z-Richtung</param>
	void Scale(float fx,float fy,float fz);

	///<summary>  Generiert eine uniforme Skalierungsmatrix.</summary> 
	///<param name="f">Skalierungsfaktor</param>
	void Scale(float f);		

	///<summary>  Generiert eine uniforme Skalierungsmatrix für die X-Achse.</summary> 
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	void ScaleX(float fx);		

	///<summary>  Generiert eine uniforme Skalierungsmatrix für die Y-Achse.</summary> 
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	void ScaleY(float fy);		

	///<summary>  Generiert eine uniforme Skalierungsmatrix für die Z-Achse.</summary> 
	///<param name="fz">Skalierungsfaktor in Z-Richtung</param>
	void ScaleZ(float fz);		

	///<summary>  Generiert eine Verschiebungsmatrix.</summary> 
	///<param name="v"></param>
	void Translate(CHVector & v); 

	///<summary>  Generiert eine Verschiebungsmatrix.</summary> 
	///<param name="fx">Verschiebungswert in X-Richtung</param>
	///<param name="fy">Verschiebungswert in Y-Richtung</param>
	///<param name="fz">Verschiebungswert in Z-Richtung</param>
	void Translate(float fx, float fy, float fz); 

	///<summary>  Generiert eine Verschiebungsmatrix in X-Richtung.</summary>
	///<param name="fx">Verschiebungswert in X-Richtung</param> 
	void TranslateX(float fx); 

	///<summary>  Generiert eine Verschiebungsmatrix in Y-Richtung.</summary> 
	///<param name="fy">Verschiebungswert in Y-Richtung</param>
	void TranslateY(float fy); 

	///<summary>  Generiert eine Verschiebungsmatrix in Z-Richtung.</summary> 
	///<param name="fz">Verschiebungswert in Z-Richtung</param>
	void TranslateZ(float fz); 

	///<summary>  Generiert eine Verschiebungsmatrix in Axenrichtung, die durch eAxis festgelegt ist.</summary> 
	///<param name="eAxis">Kartesische Verschiebungsachse (eAxisX, eAxisY oder eAxisZ)</param>
	///<param name="f">Verschiebungswert entlang der gewählten Achse</param>
	void Translate(EAxis eAxis, float f); 

	///<summary>  Generiert eine orthografische Projektionsmatrix.</summary> 
	///<param name="fWidth">Breite der Projektionsfläche</param>
	///<param name="fHeight">Höhe der Projektionsfläche</param>
	///<param name="fNear">Near Clipping Plane</param>
	///<param name="fFar">Far Clipping Plane</param>
	void ProjectionOrtho(float fWidth, float fHeight, float fNear, float fFar); 

	///<summary>  Generiert eine foveale Projektionsmatrix.</summary> 
	///<param name="faFovHorizontal">Horizontaler Öffnungswinkel im Bogenmaß</param>
	///<param name="fRatio">Breite/Höhe</param>
	///<param name="fNear"></param>
	///<param name="fFar"></param>
	void ProjectionFov(float faFovHorizontal, float fRatio, float fNear, float fFar); 

	///<summary>  Generiert eine foveale Projektionsmatrix wie sie in OpenGl verwendet wird.</summary> 
	///<param name="faFovHorizontal">Horizontaler Öffnungswinkel im Bogenmaß</param>
	///<param name="fRatio">Breite/Höhe</param>
	///<param name="fNear">Near Clipping Plane</param>
	///<param name="fFar">Far Clipping Plane</param>
	void ProjectionFovOpenGL(float faFovHorizontal, float fRatio, float fNear, float fFar); 

	///<summary>  Generiert eine foveale Projektionsmatrix.</summary> 
	///<param name="faFovHorizontal">Horizontaler Öffnungswinkel im Bogenmaß</param>
	///<param name="fRatio">Breite/Höhe</param>
	///<param name="fNear">Near Clipping Plane</param>
	///<param name="fFar">Far Clipping Plane</param>
	void ProjectionFovOld(float faFovHorizontal, float fRatio, float fNear, float fFar); 

	///<summary>  Generiert eine horizontal gespiegelte foveale Projektionsmatrix.</summary> 
	///<param name="faFovHorizontal">Horizontaler Öffnungswinkel im Bogenmaß</param>
	///<param name="fRatio">Breite/Höhe</param>
	///<param name="fNear">Near Clipping Plane</param>
	///<param name="fFar">Far Clipping Plane</param>
	void ProjectionFovMirror(float faFovHorizontal, float fRatio, float fNear, float fFar); 

	///<summary>  Generiert eine neue Farbwert-Rotationsmatrix mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fa">Farbwert-Rotationswinkel im Bogenmaß</param>
	void RotateHueDelta(float fa);	

	///<summary>  Generiert eine neue Rotationsmatrix um die X-Achse mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateXDelta(float fa);	

	///<summary>  Generiert eine neue Rotationsmatrix um die Y-Achse mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>  
	void RotateYDelta(float fa);	

	///<summary>  Generiert eine neue Rotationsmatrix um die Z-Achse mit dem Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateZDelta(float fa);	

	///<summary>  Generiert beliebige Rotationsmatrix um die Drehachse fx, fy, fz mit Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fx">X-Wert der Drehachse</param>
	///<param name="fy">Y-Wert der Drehachse</param>
	///<param name="fz">Z-Wert der Drehachse</param>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateDelta(float fx, float fy, float fz, float fa); 

	///<summary>  Generiert beliebige Rotationsmatrix um die Drehachse v mit Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="v">Drehachse</param>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateDelta(CHVector & v, float fa); 

	///<summary>  Generiert beliebige Rotationsmatrix um die Drehachse eAxis mit Winkel fa und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="eAxis">Kartesische Drehachse (eAxisX, eAxisY oder eAxisZ)</param>
	///<param name="fa">Rotationswinkel im Bogenmaß</param>
	void RotateDelta(EAxis eAxis, float fa); 

	///<summary>  Generiert eine Rotationsmatrix, die Richtungsvektor vFrom genau in die Richtung des Richtungsvektors vTo rotiert und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="vTo">Richtung zu der rotiert wird</param>
	///<param name="vFrom">Richtung von der aus rotiert wird</param>
	void RotateDelta(CHVector & vTo, CHVector & vFrom); 

	///<summary>  Generiert eine Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="v">Skalierungsvektor</param>
	void ScaleDelta(CHVector & v);	

	///<summary>  Generiert eine Skalierungsmatrix mit drei verschiedenen Skalierungswerten und multipliziert diese mit der aktuellen Matrix.</summary>  
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	///<param name="fz">Skalierungsfaktor in Z-Richtung</param>
	void ScaleDelta(float fx, float fy, float fz);

	///<summary>  Generiert eine uniforme Skalierungsmatrix und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="f">Skalierungsfaktor</param>
	void ScaleDelta(float f);		

	///<summary>  Generiert eine uniforme Skalierungsmatrix für die X-Achse und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	void ScaleXDelta(float fx);		

	///<summary>  Generiert eine uniforme Skalierungsmatrix für die Y-Achse und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	void ScaleYDelta(float fy);		

	///<summary>  Generiert eine uniforme Skalierungsmatrix für die Z-Achse und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fz">Skalierungsfaktor in Z-Richtung</param>
	void ScaleZDelta(float fz);		

	///<summary>  Generiert eine Verschiebungsmatrix und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	///<param name="fz">Skalierungsfaktor in Z-Richtung</param>
	void TranslateDelta(float fx, float fy, float fz); 

	///<summary>  Generiert eine Verschiebungsmatrix und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="v">Verschiebungsvektor</param>
	void TranslateDelta(CHVector & v); 

	///<summary>  Generiert eine Verschiebungsmatrix in X-Richtung und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fx">Verschiebungswert in X-Richtung</param>
	void TranslateXDelta(float fx); 

	///<summary>  Generiert eine Verschiebungsmatrix in Y-Richtung und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fy">Verschiebungswert in Y-Richtung</param>
	void TranslateYDelta(float fy);  

	///<summary>  Generiert eine Verschiebungsmatrix in Z-Richtung und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="fz">Verschiebungswert in Z-Richtung</param>
	void TranslateZDelta(float fz); 

	///<summary>  Generiert eine Verschiebungsmatrix in Axenrichtung, die durch eAxis festgelegt ist, und multipliziert diese mit der aktuellen Matrix.</summary> 
	///<param name="eAxis">Kartesische  Verschiebungsachse (eAxisX, eAxisY oder eAxisZ)</param>
	///<param name="f">Verschiebungswert</param>
	void TranslateDelta(EAxis eAxis, float f); 

	///<summary>  Berechnet die Determinante der Matrix.</summary> 
	float Det();				

	///<summary>  Transponiert die Matrix.</summary> 
	void Transpose();		

	///<summary>  Invertiert die Matrix.</summary> 
	void Inverse();		

	///<summary>  Setzt die aktuelle Matrix auf die Transponierte der Matrix m.</summary> 
	///<param name="m">Matrix, aus der die Transponierte berechnet wird</param>
	void Transpose(CHMat & m);	

	///<summary>  Setzt die aktuelle Matrix auf die Inverse der Matrix m.</summary> 
	///<param name="m">Matrix, aus der die Inverse berechnet wird</param>
	void Inverse(CHMat & m);	

	///<summary>  Normiert die Matrix dahingehend, dass das letzte Element [3,3] gleich 1. 0 ist.</summary> 
	void NormOne();				

	///<summary>  Gibt die Translation als homogenen Vektor aus. <para></para> 
	/// Im Gegensatz zu GetPos ist der W-Tupel gleich Null.</summary> 	
	CHVector GetTranslation();  


	///<summary>  Gibt die Richtung aus, wenn der Minus-Z-Einhetsvektor mit der vorliegenden Matrix rotiert werden würde. <para></para> 
	/// Der W-Tupel ist gleich Null.</summary> 	
	CHVector GetDirection();

	///<summary>  Gibt die Rotation als Pitch-, Yaw- und Roll-Winkel aus.<para></para>
	/// Achtung! Diese Funktion ist aufgrund des Gimbal Locks nur mit äußerster Vorsicht zu geniesen!</summary> 
	///<param name="faPitch">Drehwinkel um die X-Achse</param>
	///<param name="faYaw">Drehwinkel um die Y-Achse</param>
	///<param name="faRoll">Drehwinkel um die Z-Achse</param>
    void GetRotation(float &faPitch, float &faYaw, float &faRoll); 

	///<summary>  Gibt den Skalierungsfaktor für x, y und z als homogenen Vektor aus.</summary> 
    CHVector GetScaleFactor(); 

	///<summary>  Gibt die Position als homogenen Vektor der homogenenen Matrix aus (Matrix * Ursspung).<para></para>  
	///  Im Gegensatz zu GetTranslation ist der W-Tupel gleich Eins.</summary> 
	CHVector GetPos();  

	///<summary>  Gibt bei Nullskalierung true aus.</summary>  
	bool IsScaledToNull(); 

	// ------
	// Tupel:
	// ------

	///<summary>  Tupel 1,1 der homogenen Matrix.</summary> 
	float m_fx00;

	///<summary>  Tupel 1,2 der homogenen Matrix.</summary> 
	float m_fx01;
	
	///<summary>  Tupel 1,3 der homogenen Matrix.</summary> 
	float m_fx02;
	
	///<summary>  Tupel 1,4 der homogenen Matrix.</summary> 
	float m_fx03;
	
	///<summary>  Tupel 2,1 der homogenen Matrix.</summary> 
	float m_fx10;
	
	///<summary>  Tupel 2,2 der homogenen Matrix.</summary> 
	float m_fx11;
	
	///<summary>  Tupel 2,3 der homogenen Matrix.</summary> 
	float m_fx12;
	
	///<summary>  Tupel 2,4 der homogenen Matrix.</summary> 
	float m_fx13;
	
	///<summary>  Tupel 3,1 der homogenen Matrix.</summary> 
	float m_fx20;
	
	///<summary>  Tupel 3,2 der homogenen Matrix.</summary> 
	float m_fx21;
	
	///<summary>  Tupel 3,3 der homogenen Matrix.</summary> 
	float m_fx22;
	
	///<summary>  Tupel 3,4 der homogenen Matrix.</summary> 
	float m_fx23;
	
	///<summary>  Tupel 4,1 der homogenen Matrix.</summary> 
	float m_fx30;
	
	///<summary>  Tupel 4,2 der homogenen Matrix.</summary> 
	float m_fx31;
	
	///<summary>  Tupel 4,3 der homogenen Matrix.</summary> 
	float m_fx32;
	
	///<summary>  Tupel 4,4 der homogenen Matrix.</summary> 
	float m_fx33;
};

}