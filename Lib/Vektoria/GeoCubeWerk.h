#pragma once
#include "GeoTriangleList.h"
#include "Vertex.h"
#include "Face.h"

//------------------------------------------------------------------
// CGeoCubeWerk: Klasse f�r eine Quader-Geometrie
//
// Autor    : Prof. Dr. Tobias Breiner 
// Copyright: Vektoria UG (haftungsbeschr�nkt) 
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoCubeWerk :
	public CGeoTriangleList
{
private:
	void MakeFace(CHVector vA, CHVector vB, CHVector vC, CHVector vD, float fr, int & iIndex, float fTextureRepeat);
public:
	///<summary> Konstruktor.</summary>
	CGeoCubeWerk(void);

	///<summary> Destruktor.</summary>
	~CGeoCubeWerk(void);

	///<summary> Erzeugt einen W�rfel.</summary>
	///<param name = "fSize"> Halbe Kantenl�nge (da fSize = Abstand der Seiten vom Ursprung)<para></para>
	/// Falls man Kompabilit�t mit CGeoTetraheron, CGeoIcosahedron, CGeoDodecahedron und CGeoOctahedron haben will, muss diser Parameter mit 1.732f dividiert werden.   </param>
	///<param name = "fr"> Relative Breite der Eckma�b�gen. (0.0=hauchd�nn ... 1.0 = Gewerk f�llt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material des W�rfels</param>
	///<param name = "fTextureRepeat"> Anzahl der Texturwiederholungen pro Seite</param>
	void Init(float fSize, float fr, CMaterial * pmaterial, float fTextureRepeat = 1.0f); // Initialisiert eine W�rfel-Geometrie


	///<summary> Erzeugt einen Quader.</summary>
	///<param name = "fxSize"> Halbe Kantenl�nge in X-Richtung (da fxSize = Abstand der X-Seiten vom Ursprung)</param>
	///<param name = "fySize"> Halbe Kantenl�nge in Y-Richtung (da fySize = Abstand der Y-Seiten vom Ursprung)</param>
	///<param name = "fzSize"> Halbe Kantenl�nge in Z-Richtung (da fzSize = Abstand der Z-Seiten vom Ursprung)</param>
	///<param name = "fr"> Relative Breite der Eckma�b�gen. (0.0=hauchd�nn ... 1.0 = Gewerk f�llt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material des W�rfels</param>
	///<param name = "fTextureRepeat"> Anzahl der Texturwiederholungen pro Seite</param>
	void Init(float fxSize, float fySize, float fzSize, float fr, CMaterial * pmaterial, float fTextureRepeat = 1.0f); // Initialisiert eine W�rfel-Geometrie

	///<summary> Erzeugt einen Quader.</summary>
	///<param name = "vSize"> Ausma�e des Kubus (x= halbe Kantenl�nge in X-Richtung, y = halbe Kantenl�nge in Y-Richtung, z= halbe Kantenl�nge in Z-Richtung, w wird ignoriert) </param>
	///<param name = "fr"> Relative Breite der Eckma�b�gen. (0.0=hauchd�nn ... 1.0 = Gewerk f�llt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material des W�rfels</param>
	///<param name = "fTextureRepeat"> Anzahl der Texturwiederholungen pro Seite</param>
	void Init(CHVector vSize, float fr, CMaterial * pmaterial, float fTextureRepeat = 1.0f);

	///<summary> Visualisiert die Axis-Aligned Bounding Box von Placements als Quader.</summary>
	///<param name = "pzn"> Pointer auf einen Node3D (der eine AABB hat) </param>
	///<param name = "iInstance"> Instanznummer (nur bei zusammenlaufenden Hierarchien wichtig)</param>
	///<param name = "fr"> Relative Breite der Eckma�b�gen. (0.0=hauchd�nn ... 1.0 = Gewerk f�llt kompletten Innenbereich aus)</param>
	///<param name = "pmaterial"> Pointer auf das Material des W�rfels</param>
	void InitByAABB(CNode3D * pzn, int iInstance = 0, float fr=0.8f, CMaterial * pmaterial = NULL);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Die Eckvertices des Quaders. Jeder Eckpunkt kommt drei mal vor (f�r jede Seite ein mal).</summary>
	CVertex m_avertex[1024];
};

}