#pragma once
#include "GeoTriangleStrip.h"
#include "../VektoriaMath/FloatRect.h"
#include "../VektoriaMath/HMat.h"

//--------------------------------------------------------------------------------------------
// CFace: Klasse f�r ein Rechteckiges Doppelpolygon 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{

class CGeoQuad :
	public CGeoTriangleStrip
{
public:
	///<summary> Konstruktor. </summary>
	CGeoQuad(void);

	///<summary> Destruktor. </summary>
	~CGeoQuad(void);

	///<summary> Gibt "CGeoQuad" aus. </summary>
	const char* ClassName() { return "CGeoQuad"; }

	///<summary> Setzt die kartesische Erstellungsachse des Quads. <para></para>
	/// Muss vor dem Init-Methodenaufruf aufgerufen werden, damit die Methode einen Effekt hat. </summary>
	///<param name="eAxis"> Kann drei verschiedene Werte annehmen: eAxisX, eAxisY oder eAxisZ (default) </param>
	void SetAxis(EAxis eAxis);

	///<summary> Initialisiert und erzeugt eine Quadrat-Geometrie (=Quad).<para></para>
	/// Die Erstellungsebene kann durch vorheriges Aufrufen von eAxis definiert werden, ansonsten wird das Quad automatisch in der XY-Ebene erzeugt.<para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name="fSize"> halbe Kantenl�nge des Quads (Quad erstreckt sich horizontal von -fxSize bis +fxSize)</param>
	///<param name="pmaterial"> Pointer auf das aufzubringende Material</param>
	///<param name="fuStart"> U-Koordinatenwert des UV-Mappings der linken Seite</param>
	///<param name="fvStart"> V-Koordinatenwert des UV-Mappings der rechten Seite</param>
	///<param name="fuEnd"> U-Koordinatenwert des UV-Mappings der oberen Seite</param>
	///<param name="fvEnd"> V-Koordinatenwert des UV-Mappings der unteren Seite</param>
	void Init(float fSize, CMaterial * pmaterial, float fuStart = 0, float fvStart = 0, float fuEnd = 1, float fvEnd = 1);


	///<summary> Initialisiert und erzeugt eine Rechteck-Geometrie (=Quad).<para></para>
	/// Die Erstellungsebene kann durch vorheriges Aufrufen von eAxis definiert werden, ansonsten wird das Quad automatisch in der XY-Ebene erzeugt.<para></para>
	/// Der Geometrietyp ist CGeoTriangleStrip.</summary>
	///<param name="fxSize"> halbe horizontale Gr��e des Quads (Quad erstreckt sich horizontal von -fxSize bis +fxSize)</param>
	///<param name="fySize"> halbe vertikale Gr��e des Quads (Quad erstreckt sich horizontal von -fySize bis +fySize)</param>
	///<param name="pmaterial"> Pointer auf das aufzubringende Material</param>
	///<param name="fuStart"> U-Koordinatenwert des UV-Mappings der linken Seite</param>
	///<param name="fvStart"> V-Koordinatenwert des UV-Mappings der rechten Seite</param>
	///<param name="fuEnd"> U-Koordinatenwert des UV-Mappings der oberen Seite</param>
	///<param name="fvEnd"> V-Koordinatenwert des UV-Mappings der unteren Seite</param>
	void Init(float fxSize, float fySize, CMaterial * pmaterial, float fuStart = 0, float fvStart = 0, float fuEnd = 1, float fvEnd = 1); 

	///<summary> Initialisiert und erzeugt eine spezielle Rechteck-Geometrie (=Quad) f�r die Verwendung durch die Klasse CSprite. <para></para>
	/// Ansonsten ist die Methode "CGeoQuad::Init" in der Regel sinnvoller.</summary>
	///<param name="fcloatrect"> Ausma�e des Quads</param>
	///<param name="pmaterial"> Pointer auf das aufzubringende Material</param>
	void InitForSprites(CFloatRect & floatrect, CMaterial * pmaterial);

	///<summary> Setzt das UV-Koordinatenrechteck. <para></para>
	/// Praktisch f�r Minimaps und �hnliches.<para></para>
	/// Kann auch w�hrend der Laufzeit aufgerufen werden, ist aber langsam.</summary>
	///<param name = "floatrect"> Au�me�e der UV-Koordinaten. Beispiel: CFloatRect(0.0,0.5,0.5,0.5) zeigt linkes unteres Viertel der Textur.</param>
	void SetUVRect(CFloatRect & floatrect);


	//-----------------
	// Membervariablen:
	//-----------------


	///<summary> Die Erstellungsebenennormale des Quads. </summary>
	EAxis m_eAxis;

	///<summary>Linker UV-Wert der Quadtextur.</summary> 
	float m_fuStart; 

	///<summary>Oberer UV-Wert der Quadtextur.</summary> 
	float m_fvStart; 

	///<summary>Rechter UV-Wert der Quadtextur.</summary> 
	float m_fuEnd;

	///<summary>Unterer UV-Wert der Quadtextur.</summary> 
	float m_fvEnd;

protected: 
	///<summary> Die Vertices des Quads. </summary>
	CVertex m_avertex[4];
};

}