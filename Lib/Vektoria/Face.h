#pragma once
#include "../VektoriaMath/HVector.h"
#include "Vertex.h"
#include "../VektoriaMath/HMat.h"

//--------------------------------------------------------------------------------------------
// CFace: Klasse f�r eine Dreiecks-Polygon Facette 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

class CFace
{
public:
	// --------------
	// Basismethoden:
	// --------------

	///<summary> Konstruktor, setzt alle Werte auf nullptr.</summary>
	CFace();

	///<summary> Konstruktor, setzt gleich die drei Vertex-Pointer, Init wird danach nicht mehr ben�tigt.</summary>
	///<param name="pvertexA"> Pointer auf den Vertex A des Dreiecks</param>
	///<param name="pvertexB"> Pointer auf den Vertex B des Dreiecks</param>
	///<param name="pvertexC"> Pointer auf den Vertex C des Dreiecks</param>
	CFace(CVertex * pvertexA, CVertex * pvertexB, CVertex * pvertexC);

	///<summary> Kopieroperator.</summary>
	///<param name="face"> Zu kopierendes Face</param>
	CFace operator=(CFace & face);

	///<summary> Kopiermethode.</summary>
	///<param name="face"> Zu kopierendes Face</param>
	void Copy(CFace & face);

	///<summary> Setzt die drei Vertex-Pointer.</summary>
	///<param name="pvertexA"> Pointer auf den Vertex A des Dreiecks</param>
	///<param name="pvertexB"> Pointer auf den Vertex B des Dreiecks</param>
	///<param name="pvertexC"> Pointer auf den Vertex C des Dreiecks</param>
	void Init(CVertex * pvertexA, CVertex * pvertexB, CVertex * pvertexC);

	///<summary> Interpoliert bilienear.</summary>
	///<param name="fru"> Laufparameter von Vertex A zu Vertex B </param>
	///<param name="frv"> Laufparameter von Vertex A zu Vertex C </param>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	void InterpolBilinear(float fru, float frv, CVertex & vertexInterpolated, bool bInterpolTangentsAndBitangents = false, bool bInterpolUV = false);

	///<summary> Berechnet irgendeinen zuf�lligen interpolierten Vertex auf der Oberfl�che.</summary>
	///<param name="vertexInterpolated"> Resultierender interpolierter Vertex</param>
	void CalcRandomVertex(CVertex & vertexInterpolated);

	///<summary> Berechnet die Facettennormale.</summary>
	CHVector CalcNormal();

	///<summary> Berechnet die Facettennormale und tr�gt diese^in die drei Vertices ein, so dass die Facette flach geshadet wird.</summary>
	void Flatten();

	///<summary> Gibt den aktuellen Facettenstatus im Logfile aus. </summary>
	void Log();

	///<summary> Gibt den vorherigen Vertex aus (rechtsh�ndige Drehung).</summary>
	///<param name= "pvertex"> Der Vertex, zu dem der vorherige gesucht wird</param>
	CVertex * GetVertexPre(CVertex * pvertex);

	///<summary> Gibt den n�chsten Vertex aus (rechtsh�ndige Drehung).</summary>
	///<param name= "pvertex"> Der Vertex, zu dem der n�chste gesucht wird</param>
	CVertex * GetVertexNext(CVertex * pvertex);

	///<summary> Gibt true aus, wenn pvertex einer der Eckvertices ist.</summary>
	///<param name= "pvertex"> Pointer auf den zu �berpr�fenden Vertex</param>
	bool HasVertex(CVertex * pvertex);



	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Pointer auf 1. Vertex.</summary>
	CVertex * m_pvertexA;

	///<summary> Pointer auf 2. Vertex.</summary>
	CVertex * m_pvertexB;

	///<summary> Pointer auf 3. Vertex.</summary>
	CVertex * m_pvertexC;

	///<summary> Pointer auf 1. Nachbarfacette (gegen�ber von Vertex A).</summary>
	CFace * m_pfaceA;

	///<summary> Pointer auf 2. Nachbarfacette (gegen�ber von Vertex B).</summary>
	CFace * m_pfaceB;

	///<summary> Pointer auf 3. Nachbarfacette (gegen�ber von Vertex C).</summary>
	CFace * m_pfaceC;

	///<summary> Hilfsmarker, sinnvoll f�r verschiedene Netzalgorithmen <para></para>
	/// Achtung! Muss nach dem Ausf�hren des betreffenden Algorithmus wieder auf false gesetzt werden!</summary>
	bool m_bMarked;

};

}