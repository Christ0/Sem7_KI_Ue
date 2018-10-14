#pragma once
#include "GeoTriangleList.h"

//------------------------------------------------------------------
// CGeoTriangle: Klasse für ein 2D Dreieck im Raum
//
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt) 
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoTriangle :
	public CGeoTriangleList
{
public:
	///<summary> Konstruktor.</summary>
	CGeoTriangle(void);

	///<summary> Destruktor.</summary>
	~CGeoTriangle(void);

	///<summary> Initialisiert eine gleichschenklige Dreiecks-Geometrie aus einem einzigen Polygon.<para></para>
	/// Die Erstellungsebene ist die Z-Ebene.<para></para>
	/// Der Geometrietyp ist CGeoTriangleList</summary>
	///<param name = "fWidth"> Breite der Basis des gleichschenkligen Dreiecks</param>
	///<param name = "fHeight"> Höhe des gleichschenkligen Dreiecks</param>
	///<param name ="pmaterial"> Pointer auf das Material</param>
	void Init(float fWidth, float fHeight, CMaterial * pmaterial); 

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die drei Vertices des Dreiecks.</summary>
	CVertex m_avertex[3];

};

}