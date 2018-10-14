#pragma once
#include "GeoTriangleStrip.h"
#include "../VektoriaMath/HMats.h"
#include "../VektoriaMath/HVectors.h"


namespace Vektoria
{

class CGeoSweep :
	public CGeoTriangleStrip
{
public:
	// ---------
	// Methoden:
	// ---------

	///<summary> Konstruktor.</summary>
	CGeoSweep(void);

	///<summary> Destruktor.</summary>
	~CGeoSweep(void);

	///<summary> Gibt "CGeoSweep" aus.</summary>
    virtual const char* ClassName(void) { return "CGeoSweep"; }

	///<summary> Setzt die Anfangs-UV-Koordinaten (Default = 0.0).<para></para>
	/// Muss vor dem Init aufgerufen werden.</summary>
	void SetTextureStart(float fuTextureStart, float fvTextureStart);

	///<summary> Bestimmt, wie oft die Textur in U und V-Richtung wiederholt werden soll (Default = 1.0).<para></para>
	/// Muss vor dem Init aufgerufen werden.</summary>
	void SetTextureRepeat(float fuTextureRepeat, float fvTextureRepeat);

	///<summary> Setzt die grundlegende Sweeping-Achse (default = in Y-Richtung).<para></para>
	/// Muss vor dem Init aufgerufen werden.</summary>
	void SetAxis(EAxis m_eAxis);

	///<summary> Initialisiert eine radiale Sweeping-Geometrie.<para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name ="vSize"> Allgemeiner Skalierungsvektor, sollte in der Regel CHVector(1.0,1.0,1.0,0.0f) sein. <para></para>
	/// Wenn man eine allgemeine Skalierung will, können auch andere Werte verwendet werden.</param>
	///<param name ="pmaterial"> Pointer auf das Material</param>
	///<param name ="iLongitude"> Anzahl der Vertices um die Achse, je höher dieser Wert, desto mehr Polygone</param>
	///<param name ="iLattitude"> Anzahl der Vertices entlang der Achse, je höher dieser Wert, desto mehr Polygone</param>
	///<param name ="afrRadius"> Floating-Point-Array der Radien des Querschnitts. Die Anzahl der Arrayelemente muss iLongitude sein.</param>
	///<param name ="afrDistance"> Floating-Point-Array der Entfernungen der Sweep-Applikationen vom Ursprung. Die Anzahl der Arrayelemente muss iLattitude sein.</param>
	///<param name ="bFlip"> Flag, ob die Flächennormalen nach innen zeigen sollen</param>
	void InitRadial(CHVector vSize, CMaterial * pmaterial, int iLongitude, int iLattitude, float * afrRadius, float * afrDistance, bool bFlip = false);

	///<summary> Initialisiert eine schlauchförmige Sweeping-Geometrie. <para></para>
	/// Der Querschnitt hat eine Kreisform.<para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name ="pmaterial">Pointer auf das Material</param>
	///<param name ="iLongitude"> Anzahl der Vertices um die Achse, je höher dieser Wert, desto mehr Polygone</param>
	///<param name ="matsPath"> Gibt den Pfad als Liste homogener Matrizen an</param>
	void InitCircle(CMaterial * pmaterial, int iLongitude, CHMats & matsPath);

	///<summary> Initialisiert eine Sweeping-Geometrie auf sehr komplexe Weise, insbesondere mit Angabe eines beliebigen Querschnitts.</summary>
	///<param name ="vSize"> Allgemeiner Skalierungsvektor, sollte in der Regel CHVector(1.0,1.0,1.0,0.0f) sein.<para></para> 
	/// Wenn man eine allgemeine Skalierung will, können auch andere Werte verwendet werden.</param>
	///<param name ="pmaterial"> Pointer auf das Material</param>
	///<param name ="matsPath"> Gibt den Pfad als Liste homogener Matrizen an</param>
	///<param name ="vs"> Die Punkte des Querschnitts. Achtung, muss entlang der Sweeping-Achse rechtshändige Drehrichtung aufweisen!</param>
	void Init(CHVector vSize, CMaterial * pmaterial, CHMats & matsPath, CHVectors & vs);  

	///<summary> Erzeugt ein planares Mapping an der Basis. <para></para>
	/// Muss vor dem Init aufgerufen werden.</summary>
	void SetPlanarMappingBottomOn(); 

	///<summary> Erzeugt planares Mapping am Kopf.	<para></para>
	/// Muss vor dem Init aufgerufen werden.</summary>
	void SetPlanarMappingTopOn(); 

	///<summary> Gibt den Index auf den entsprechenden Vertex zurück.</summary>	
	///<param name ="iLo"> Vertexnummer um die Achse herum</param>
	///<param name ="iLa"> Vertexnummer entlang der Achse</param>
	int GetVertexIndex(int iLo, int iLa);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Pointer auf die Vertices.</summary>
	CVertex * m_avertex;

	///<summary> Bei welchem Wert soll die Textur um die Sweep-Achse gestartet werden?</summary>
	float m_fuTextureStart;

	///<summary> Bei welchem Wert soll die Textur in Richtung der Sweep-Achse gestartet werden?</summary>
	float m_fvTextureStart;

	///<summary> Wie oft soll die Textur um die Sweep-Achse herum wiederholt werden?</summary>
	float m_fuTextureRepeat;

	///<summary> Wie oft soll die Textur entlang der Sweep-Achse wiederholt werden?</summary>
	float m_fvTextureRepeat;

	///<summary> Flag, on die Basis ein planares Mapping aufweist.</summary>
	bool m_bPlanarMappingBottom;

	///<summary> Flag, on die Spitze ein planares Mapping aufweist.</summary>
	bool m_bPlanarMappingTop; 

	///<summary> Sweep-Achse. (Der Sweep-Querschnitt sollte orthogonal dazu gespannt werden).</summary>
	EAxis m_eAxis;
	
	///<summary> Allgemeine zusätzliche Skalierung.</summary>
	CHVector m_vSize;

	///<summary> Anzahl der Vertices radial um die Sweep-Röhre.</summary>
	int m_iLongitude; 

	///<summary> Anzahl der Vertices in Sweep-Richtung.</summary>
	int m_iLattitude; 
};

}