#pragma once
#include "Plane.h"
#include "Ray.h"
#include "AABB.h"

//------------------------------------
// CFrustum
//
// Autor    : Prof. Dr. Tobias Breiner
// Copyright: Vektoria UG (haftungsbeschr‰nkt)
//------------------------------------

namespace Vektoria
{

class CFrustum
{
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor - Erzeugt Pyramidenstumpf ohne Initialisierung.</summary>
	CFrustum(); 

	///<summary> Konstruktor - Initialisiert Pyramidenstumpf.</summary>
	///<param name="r">Mittelstrahl durch den Pyramidenstumpf</param>
	///<param name="vNormalRight">Richtung nach Rechts</param>
	///<param name="faHorizontal">Horizontaler Winkel im Bogenmaﬂ</param>
	///<param name="faVertical">Vertikaler Winkel im Bogenmaﬂ</param>
	CFrustum(CRay r, CHVector vNormalRight, float faHorizontal, float faVertical); 

	///<summary> Destruktor.</summary>
	~CFrustum();

	///<summary> Kopieroperator.</summary>
	///<param name="frustum">Zu kopierender Pyramidenstumpf</param>
	CFrustum operator=(CFrustum & frustum);

	///<summary> Kopierfunktion.</summary>
	///<param name="frustum">Zu kopierender Pyramidenstumpf</param>
	void Copy(CFrustum & frustum);

	///<summary> Re-Initialisiert Pyramidenstumpf.</summary>
	///<param name="r">Mittelstrahl durch den Pyramidenstumpf</param>
	///<param name="vNormalRight">Richtung nach Rechts</param>
	///<param name="faHorizontal">Horizontaler Winkel im Bogenmaﬂ</param>
	///<param name="faVertical">Vertikaler Winkel im Bogenmaﬂ</param>
	void Init(CRay r, CHVector vNormalRight, float faHorizontal, float faVertical); 

	///<summary> Deinitialieriert Pyramidenstumpf.</summary>
	void Fini();

	///<summary> Gibt true aus, wenn Punkt innerhalb des Pyramidenstumpfes liegt, ansonsten false.</summary>
	///<param name="v">Punktvektor</param>
	bool IsInside(CHVector & v); 

	///<summary> Gibt -1 aus, wenn Box komplett auﬂerhalb des Pyramidenstumpfes liegt, 0 falls halb drin, halb drauﬂen, 1 falls komplett drinnen.</summary>
	///<param name="aabb">Axis Alligned Bounding Box</param>
	int IsInside(CAABB & aabb); 

	///<summary> Gibt die Mitte des Frustrums aus.</summary>
	CHVector GetCenter();

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Strahl, der durch die Mitte des Pyramidenstumpfes f¸hrt.</summary> 
	CRay m_r; 

	///<summary> Halber horizontaler ÷ffnungswinkel des Pyramidenstumpfes.</summary>
	float m_faHorizontal; 

	///<summary> Halber vertikaler ÷ffnungswinkel des Pyramidenstumpfes.</summary>
	float m_faVertical; 

	///<summary> Normalenvektor der die rechte Richtung representiert.</summary>
	CHVector m_vNormalRight; 

	///<summary> Normalenvektor der die Aufw‰rtsrichtung representiert.</summary>
	CHVector m_vNormalUp; 

	///<summary> Vorderseite.</summary>
	CPlane m_planeFront; 

	///<summary> Hinterseite.</summary>
	CPlane m_planeBack;  

	///<summary> Linke Seite.</summary>
	CPlane m_planeLeft; 

	///<summary> Rechte seite.</summary>
	CPlane m_planeRight; 

	///<summary> Oberseite.</summary>
	CPlane m_planeTop; 

	///<summary> Unterseite.</summary>
	CPlane m_planeBottom; 

	///<summary> Hozizontale Schnittebene entlang der Sichtachse (Braucht man nicht unbedingt, beschleunigt aber einige Rechenoperationen).</summary>
	CPlane m_planeHorizontal; 

	///<summary> Vertikale Schnittebene  entlang der Sichtachse (Braucht man nicht unbedingt, beschleunigt aber einige Rechenoperationen).</summary>
	CPlane m_planeVertical; 
};

}
