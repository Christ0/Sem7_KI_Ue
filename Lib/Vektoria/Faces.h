#pragma once

#include "Face.h"

//------------------------------------
// CFaces, Pluralklasse von CFace
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CFaces
{
public:
	///<summary> Konstruktor. </summary>
	CFaces();

	///<summary> Destruktor. </summary>
	~CFaces();

	///<summary> Kopieroperator. </summary>
	///<param name="faces"> Zu kopierender Facetten-Container</param>
	CFaces operator=(CFaces & faces);

	///<summary> Kopiert ein Facetten-Container in den vorliegenden Facetten-Container hinein. </summary>
	///<param name="faces"> Zu kopierender Facetten-Container</param>
	void Copy(CFaces & faces);

	///<summary> Löscht alle Informationen im Container<para></para>
	/// Achtung! Die Facetten sind noch vorhanden, nur die Liste verweist nicht mehr auf sie.</summary>
	void Clear();

	///<summary> Fügt ein Face dem Face-Container hinzu. </summary>
	///<param name="pface"> Pointer auf das hinzuzufügende Face</param>
	void Add(CFace * pface);

	///<summary> Hängt ein Face vom Face-Container ab, gibt true aus, wenn es geklappt hat. </summary>
	///<param name="pface"> Pointer auf das abzuhängende Face</param>
	bool Sub(CFace * pface);

	///<summary> Erzeugt ein Face und fügt es dem Face-Container hinzu. </summary>
	///<param name="pvertexA"> Pointer auf den 1. Vertex</param>
	///<param name="pvertexB"> Pointer auf den 2. Vertex</param>
	///<param name="pvertexC"> Pointer auf den 3. Vertex</param>
	CFace * Make(CVertex * pvertexA, CVertex * pvertexB, CVertex * pvertexC);

	///<summary> Hängt eine Facette ab und zerstört sie. <para></para>
	/// Achtung! Funktioniert nur bei Facetten, die mit Make (oder new) erzeugt wurden.</summary>
	///<param name="pface"> Pointer auf die abzuhängende und zu zerstörende Facette</param>
	bool Kill(CFace * pface);

	///<summary> Hängt alle Facetten in der Liste ab und zerstört sie. <para></para>
	/// Achtung! Funktioniert nur bei Facetten, die mit Make (oder new) erzeugt wurden.</summary>
	void KillAll();

	///<summary> Hängt alle Facetten, die markiert sind, in der Liste ab und zerstört sie. <para></para>
	/// Achtung! Funktioniert nur bei Facetten, die mit Make (oder new) erzeugt wurden.</summary>
	void KillMarked();


	///<summary> Gibt den aktuellen Status ´der Facettenliste im Logfile aus. </summary>
	void Log();

	///<summary> Löscht die Markierungen aller Facetten. </summary>
	void Demark();


	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Array der Facetten. </summary>
	CFace ** m_apface;

	///<summary> Anzahl der allokierten Facetten im Container. </summary>
	int m_iFaceAllocs;

	///<summary> Hilfsvariable für das Smart Allocating. </summary>
	int m_iAllocBlock;

	///<summary> Anzahl der Facetten im Container. </summary>
	int m_iFaces;
};

}