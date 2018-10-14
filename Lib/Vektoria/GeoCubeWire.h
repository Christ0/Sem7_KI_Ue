#pragma once
#include "GeoLineList.h"
#include "Vertex.h"
#include "Face.h"

//------------------------------------------------------------------
// CGeoCubeWire: Klasse für eine Quader-Geometrie
//
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschränkt) 
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoCubeWire :
	public CGeoLineList
{
public:
	///<summary> Konstruktor.</summary>
	CGeoCubeWire(void);

	///<summary> Destruktor.</summary>
	~CGeoCubeWire(void);

	///<summary> Erzeugt einen Würfel.</summary>
	///<param name = "fSize"> Halbe Kantenlänge (da fSize = Abstand der Seiten vom Ursprung)<para></para>
	/// Falls man Kompabilität mit CGeoTetraheron, CGeoIcosahedron, CGeoDodecahedron und CGeoOctahedron haben will, muss diser Parameter mit 1.732f dividiert werden.   </param>
	///<param name = "pmaterial"> Pointer auf das Material des Würfels</param>
	///<param name = "fTextureRepeat"> Anzahl der Texturwiederholungen pro Seite</param>
	void Init(float fSize, CMaterial * pmaterial, float fTextureRepeat = 1.0f); // Initialisiert eine Würfel-Geometrie


	///<summary> Erzeugt einen Quader.</summary>
	///<param name = "fxSize"> Halbe Kantenlänge in X-Richtung (da fxSize = Abstand der X-Seiten vom Ursprung)</param>
	///<param name = "fySize"> Halbe Kantenlänge in Y-Richtung (da fySize = Abstand der Y-Seiten vom Ursprung)</param>
	///<param name = "fzSize"> Halbe Kantenlänge in Z-Richtung (da fzSize = Abstand der Z-Seiten vom Ursprung)</param>
	///<param name = "pmaterial"> Pointer auf das Material des Würfels</param>
	///<param name = "fTextureRepeat"> Anzahl der Texturwiederholungen pro Seite</param>
	void Init(float fxSize, float fySize, float fzSize, CMaterial * pmaterial, float fTextureRepeat = 1.0f); // Initialisiert eine Würfel-Geometrie

	///<summary> Erzeugt einen Quader.</summary>
	///<param name = "vSize"> Ausmaße des Kubus (x= halbe Kantenlänge in X-Richtung, y = halbe Kantenlänge in Y-Richtung, z= halbe Kantenlänge in Z-Richtung, w wird ignoriert) </param>
	///<param name = "pmaterial"> Pointer auf das Material des Würfels</param>
	///<param name = "fTextureRepeat"> Anzahl der Texturwiederholungen pro Seite</param>
	void Init(CHVector vSize, CMaterial * pmaterial, float fTextureRepeat = 1.0f); 

	///<summary> Visualisiert die Axis-Aligned Bounding Box von Placements als Quader.</summary>
	///<param name = "pzn"> Pointer auf einen Node3D (der eine AABB hat) </param>
	///<param name = "iInstance"> Instanznummer (nur bei zusammenlaufenden Hierarchien wichtig)</param>
	///<param name = "pmaterial"> Pointer auf das Material des Würfels</param>
	void InitByAABB(CNode3D * pzn, int iInstance = 0, CMaterial * pmaterial = NULL);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die 8 Eckvertices des Quaders.</summary>
	CVertex m_avertex[8];
};

}