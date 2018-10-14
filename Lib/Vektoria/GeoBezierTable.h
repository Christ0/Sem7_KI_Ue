#pragma once

#include "GeoTriangleTable.h"
#include "Light.h"

#define INDEX_INCREASE 1024

namespace Vektoria
{



class CGeoBezierTable : public CGeoTriangleTable
{
	friend class CGeoBezierTables;
	friend class CGeoTriangleTable;
	friend class CNode3D;
	friend class CGeo;

public:
	///<summary> Konstruktor.</summary>
	CGeoBezierTable();

	///<summary> Destruktor.</summary>
	~CGeoBezierTable();

	///<summary> Initialisiert die Bézier-Geometrie. Muss nach solchen Methoden wie AddPatch/LoadPatchFile aufgerufen werden.</summary>
	void Init();

	///<summary> Deinitialisiert die Bézier-Geometrie.</summary>
	void Fini();

	///<summary> Fügt ein bikubisches Bézier-Patch hinzu. Muss vor dem Init aufgerufen werden!</summary>
	///<param name = "aavControlPoints"> Kontrollpunkte des Patches (4 mal 4) </param>
	///<param name = "ixVertices"> Anzahl der Vertices in X-Richtung des Patches </param>
	///<param name = "iyVertices"> Anzahl der Vertices in Y-Richtung des Patches </param>
	void AddPatch(CHVector aavControlPoints[4][4], int ixVertices, int iyVertices);

	///<summary> Lädt ein Vektoria Patch-File und gereriert daraus eine Bézier-Geometrie.</summary>
	///<param name = "filevektoria"> Vektoria Patch-File </param>
	void LoadPatchFile(CFileVektoria filevektoria);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Kontollpunkte der Patches.</summary>
	CHVector * m_aaavControlPoints[4][4];

	///<summary> Anzahl der Vertioces pro Patch.</summary>
	int m_iPatchVertices;

};

}