#pragma once
#include "windows.h"
#include "Geo.h"
#include "Placement.h"
#include "Overlay.h"
#include "Background.h"
#include "Hitpoints.h"

//--------------------------------------------------------------------------------------------
// CDeviceCursor: Klasse für die Cursorbehandlung in 3D-Applikationen 
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------


namespace Vektoria
{
class CFrame; 

class CDeviceCursor : public CNode
{
	friend class CFrame;
protected: 
	// ---------------
	// Basis-Methoden:
	// ---------------

	///<summary> Wird jeden Tick automatisch von der übergeordneten Hierarchie aufgerufen.</summary>
	void Tick();

public:
	///<summary>Konstruktor</summary>
	CDeviceCursor(void);

	///<summary>Destruktor</summary>
	~CDeviceCursor(void);

	///<summary>Gibt die Zeigerpositionskoordinaten bezüglich der linken oberen Ecke des Frames aus, gibt true aus, wenn Cursor sich innerhalb des Frames befindet.</summary>
	///<param name= "ix"> Absolute Pixelkoordinate in X-Richtung </param>
	///<param name= "iy"> Absolute Pixelkoordinate in Y-Richtung </param>
	///<param name= "bHideCursor"> Bei true verschwindet der Cursor, wenn sich der Mauszeiger in das Frame bewegt. Mit einem Overlay kann man dann seinen eigenen Mauszeiger erstellen.</param>
	bool GetAbsolute(int & ix, int & iy, bool bHideCursor = false);

	///<summary>Gibt die fraktionalen Zeigerpositionskoordinaten (Wertebereich jeweils 0..1) bezüglich des Frames aus, gibt true aus, wenn Cursor sich innerhalb des Frames befindet.</summary>
	///<param name= "frx"> Relative fraktionale Pixelkoordinate in X-Richtungbezüglich des Frames, 0.0 = am linken Rand des Frames ...1.0 = am rechten Rand des Frames </param>
	///<param name= "fry"> Relative fraktionale Pixelkoordinate in Y-Richtung (Wertebereich jeweils 0..1) bezüglich des Frames </param>
	///<param name= "bHideCursor"> Bei true verschwindet der Cursor, wenn sich der Mauszeiger in das Frame bewegt. Mit einem Overlay kann man dann seinen eigenen Mauszeiger erstellen.</param>
	bool GetFractional(float & frx, float & fry, bool bHideCursor = false);


	///<summary>Setzt eine virtuelle Zeigerpositionskoordinaten (Wertebereich jeweils 0..1) bezüglich des Frames.<para></para> 
	///Achtung! Die Mausposition gibt danach nicht mehr die tatsächliche Position sondern die virtuelle Position wieder.</summary> 
	///<param name= "frx"> Relative fraktionale Pixelkoordinate in X-Richtungbezüglich des Frames, 0.0 = am linken Rand des Frames ...1.0 = am rechten Rand des Frames </param>
	///<param name= "fry"> Relative fraktionale Pixelkoordinate in Y-Richtung (Wertebereich jeweils 0..1) bezüglich des Frames </param>
	void SetVirtualFractional(float frx, float fry);

	///<summary>Setzt eine absolute Zeigerpositionskoordinate (in Pixeln) bezüglich des Frames. <para></para>
	///Achtung! Die Mausposition gibt danach nicht mehr die tatsächliche Position sondern die virtuelle Position wieder.</summary> 
	///<param name= "ix"> Absolute Pixelkoordinate in X-Richtung </param>
	///<param name= "iy"> Absolute Pixelkoordinate in Y-Richtung </param>
	void SetVirtualAbsolute(int ix, int iy);

	///<summary>Schaltet den Cursor wieder vom virtuellen Modus zurück. Danach werden die Koordinaten wieder durch die Mausbewegungen ermittelt. </summary>
	void SetVirtualOff();

	///<summary>Gibt true aus, falls Taste iButton gedrückt wurde, ansonsten false.</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonPressed(int iButton);

	///<summary>Gibt einmal true aus, falls Taste iButton gedrückt wurde, ansonsten false.</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonDown(int iButton);

	///<summary>Gibt einmal true aus, falls Taste iButton losgelassen wurde, ansonsten false.</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonUp(int iButton);

	///<summary>Gibt true aus, falls linke Maustaste gedrückt wird, ansonsten false.</summary>
	///<param name= "iButton"> Nummer des Mausbuttons (0..7)</param>
	bool ButtonPressedLeft();

	///<summary>Gibt true aus, falls rechte Maustaste gedrückt wird, ansonsten false.</summary>
	bool ButtonPressedRight(); 

	///<summary>Gibt true aus, falls mittlere Maustaste gedrückt wird, ansonsten false.</summary>
	bool ButtonPressedMid(); 

	///<summary>Gibt einmal true aus, falls linke Maustaste gedrückt wurde, ansonsten false.</summary>
	bool ButtonDownLeft(); 

	///<summary>Gibt einmal true aus, falls rechte Maustaste gedrückt wurde, ansonsten false.</summary>
	bool ButtonDownRight(); 

	///<summary>Gibt einmal true aus, falls mittlere Maustaste gedrückt wurde, ansonsten false.</summary>
	bool ButtonDownMid(); 

	///<summary>Gibt einmal true aus, falls linke Maustaste losgelassen wurde, ansonsten false.</summary>
	bool ButtonUpLeft(); 

	///<summary>Gibt einmal true aus, falls rechte Maustaste losgelassen wurde, ansonsten false.</summary>
	bool ButtonUpRight(); 

	///<summary>Gibt einmal true aus, falls mittlere Maustaste losgelassen wurde, ansonsten false.</summary>
	bool ButtonUpMid(); 

	///<summary>Macht Cursor unsichtbar.</summary>
	void Hide(); 

	///<summary>Macht Cursor wieder sichtbar.</summary>
	void Show(); 

	///<summary>Gibt true aus, wenn der Cursor unsichtbar ist, ansonsten false.</summary>
	bool IsHidden(); 
	
	// ----------------------------
	// Picking-Routinen (Singular):
	// ----------------------------

	///<summary>Gibt erstes sichtbares Viewport aus, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL.</summary>
	CViewport * PickViewport(); 

	///<summary>Gibt erstes sichtbares Viewport aus, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL, dazu werden die passenden Bildschirmkoordinaten frxViewport und fryViewport des Picking-Punktes mit ausgegeben.</summary>
	///<param name= "frxViewport"> Relative fraktionale Pixelkoordinaten in X-Richtung, bezüglich des übergeordneten Viewports (0.0 = linker Rand des Viewports ... 1.0 = rechter Rand des Viewports)</param>
	///<param name= "fryViewport"> Relative fraktionale Pixelkoordinaten in Y-Richtung, bezüglich des übergeordneten Viewports (0.0 = oberer Rand des Viewports ... 1.0 = unterer Rand des Viewports)</param>
	CViewport * PickViewport(float & frxViewport, float & fryViewport);

	///<summary>Gibt erstes sichtbares Overlay aus, welches unter dem Cursor liegt, falls kein Overlay gefunden wurde ist das Ergebnis NULL.</summary>
	COverlay * PickOverlay(); 

	///<summary>Gibt die Kamera aus, die mit dem sichtbaren Viewport verbunden ist, welches unter dem Cursor liegt, falls kein Viewport gefunden wurde ist das Ergebnis NULL.</summary>
	CCamera * PickCamera(); 

	///<summary>Gibt die Szene aus, welche das sichtbare Viewport zeigt, welches unter dem Cursor liegt, falls keine Szene gefunden wurde ist das Ergebnis NULL.</summary>
	CScene * PickScene(); 

	///<summary>Gibt dasjenige näheste Placement mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Placment gefunden wurde ist das Ergebnis NULL.</summary>
	CPlacement * PickPlacement(); 

	///<summary>Gibt dasjenige Geo mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL.</summary>
	CGeo * PickGeo(); 

	///<summary>Gibt dasjenige Geo mit der niedersten Hierarchiestufe aus, welches unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL, vIntersection ist der genaue Schnittpunkt, fDistanceSquare ist das Quadrat der Entfernung zwischen Strahlursprung und Schnittpunkt, kann bei großen Geometrien einige Millisekunden dauern, ist dafür sehr exakt <para></para>
	///Achtung!!! Kommt ab V15 raus, da veraltet!</summary>
	CGeo * PickGeo(CHVector & vIntersection, float & fDistanceSquare); 

	///<summary>Gibt den nähesten HitPoint aus, der unter dem Cursor liegt, falls kein Geo gefunden wurde ist das Ergebnis NULL, vIntersection ist der genaue Schnittpunkt, fDistanceSquare ist das Quadrat der Entfernung zwischen Strahlursprung und Schnittpunkt, kann bei großen Geometrien einige Millisekunden dauern, ist dafür sehr exakt.</summary>
	CHitPoint * PickHitPoint(); 

	///<summary>Gibt erstes sichtbares Overlay oder Writing aus, welches unter dem Cursor liegt, falls kein Overlay bzw. Writing gefunden wurde ist das Ergebnis NULL.</summary>
	COverlay * PickOverlayOrWriting(); 

	///<summary>Gibt erstes sichtbares Writing aus, welches unter dem Cursor liegt, falls kein Writing gefunden wurde ist das Ergebnis NULL.</summary>
	CWriting * PickWriting(); 

	///<summary>Gibt erstes sichtbares Wribel aus, welches unter dem Cursor liegt, falls kein Wribel gefunden wurde ist das Ergebnis NULL.</summary>
	CWribel * PickWribel(); 

	///<summary>Gibt erstes sichtbares Background aus, welches unter dem Cursor liegt, falls kein Background gefunden wurde ist das Ergebnis NULL.</summary>
	CBackground * PickBackground(); 

	// ---------------------------
	// Picking-Routinen (1 aus n):
	// ---------------------------

	///<summary>Untersucht nur diejenigen Overlays (oder Writings), die in der Liste zos angegeben sind und pickt nur daraus eine Geo aus, falls kein Geo gefunden wurde, ist das Ergebnis NULL. Diese Funktion kann das Picking stark beschleunigen.</summary>
	///<param name= "zps"> Containerklasse, darin müssen vorher alle Overlays eingetragen werden, die gepickt werden können</param>
	COverlay * PickOverlayPreselected(COverlays & zos);

	///<summary>Untersucht nur diejenigen Placements, die in der Liste zps angegeben sind und pickt nur daraus eine Geo aus, falls kein Geo gefunden wurde, ist das Ergebnis NULL. Diese Funktion kann das Picking stark beschleunigen.</summary>
	///<param name= "zps"> Containerklasse, darin müssen vorher alle Placements eingetragen werden, die gepickt werden können</param>
	CPlacement * PickPlacementPreselected(CPlacements & zps);

	///<summary>Untersucht nur diejenigen Geos, die in der Liste zgs angegeben sind und pickt nur daraus eine Geo aus, falls kein Geo gefunden wurde, ist das Ergebnis NULL. Diese Funktion kann das Picking stark beschleunigen.</summary>
	///<param name= "zgs"> Containerklasse, darin müssen vorher alle Geometrien eingetragen werden, die gepickt werden können</param>
	CGeo * PickGeoPreselected(CGeos & zgs);

	///<summary>Untersucht nur diejenigen HitPoints, die durch die Liste zgs erzeugt werden können.</summary>
	///<param name= "zgs"> Containerklasse, darin müssen vorher alle Geometrien eingetragen werden, die gepickt werden können</param>
	CHitPoint * PickHitPointPreselected(CGeos & zgs);

	///<summary>Untersucht nur diejenigen Wribels, die in der Liste zgw angegeben sind und pickt nur daraus ein Wribel aus, falls kein Wribel gefunden wurde, ist das Ergebnis NULL.Diese Funktion kann das Picking stark beschleunigen.</summary>
	///<param name= "zws"> Containerklasse, darin müssen vorher alle Wribels eingetragen werden, die gepickt werden können</param>
	CWribel * PickWribelPreselected(CWribels & zws);

	// --------------------------
	// Picking-Routinen (Plural):
	// --------------------------

	///<summary>Gibt alle Overlays (Ohne Writings) in pzos aus, welche unter dem Cursor liegen, unabhängig davon, ob sie eventuell von anderen Overlays verdeckt werden. </summary>
	///<param name= "pzos"> Pointer auf eine instanziierte (Achtung!) Containerklasse, darin stehen danach alle gefundenen Overlays.</param>
	void PickOverlays(COverlays * pzos);

	///<summary>Gibt alle Placements in pzps aus, welches unter dem Cursor liegen. </summary>
	///<param name= "pzps"> Pointer auf eine instanziierte (Achtung!) Containerklasse, darin stehen danach alle gefundenen Placements.</param>
	///<param name= "bPickOnlyPlacementsWithDirectGeos"> Wenn true, werden nur Placements gepickt, an denen direkt eine Geometrie angehängt ist.</param>
	void PickPlacements(CPlacements * pzps, bool bPickOnlyPlacementsWithDirectGeos = false);

	///<summary>Gibt alle Geos aus, welches unter dem Cursor liegen. </summary>
	///<param name= "pzgs"> Pointer auf eine instanziierte (Achtung!) Containerklasse, darin stehen danach alle gefundenen Geometrien.</param>
	///<param name= "iMaxVertices"> Maximale Anzahl der Vertices (Eingeführt, da die Zeitdauer bei hochpolygonalen Modellen sehr lange betragen kann.)</param>
	void PickGeos(CGeos * pzgs, int iMaxVertices = INT_MAX);

	///<summary>Gibt alle Geos mit Zusatzinformationen aus, welches unter dem Cursor liegen. Achtung, phitpoints muss muss ein Pointer auf ein instanziertes Hitpoints-Objekt sein.</summary>
	///<param name= "phitpoints"> Pointer auf eine instanziierte (Achtung!) Containerklasse, darin stehen danach alle gefundenen Hitpoints.</param>
	///<param name= "iMaxVertices"> Maximale Anzahl der Vertices (Eingeführt, da die Zeitdauer bei hochpolygonalen Modellen sehr lange betragen kann.)</param>
	void PickHitPoints(CHitPoints * phitpoints, int iMaxVertices = INT_MAX);

	///<summary>Gibt alle Overlays oder Writings in pzos aus, welche unter dem Cursor liegen, unabhängig davon, ob sie eventuell von anderen Overlays verdeckt werden. Achtung, pzos muss muss ein Pointer auf ein instanziertes Overlays-Objekt sein.</summary>
	///<param name= "pzos"> Pointer auf eine instanziierte (Achtung!) Containerklasse, darin stehen danach alle gefundenen Overlays.</param>
	void PickOverlaysOrWritings(COverlays * pzos);

	///<summary>Gibt alle Writings in pzos aus, welche unter dem Cursor liegen, unabhängig davon, ob sie eventuell von anderen Overlays verdeckt werden. Achtung, pzos muss muss ein Pointer auf ein instanziertes Overlays-Objekt sein.</summary>
	///<param name= "pzos"> Pointer auf eine instanziierte (Achtung!) Containerklasse, darin stehen danach alle gefundenen Overlays.</param>
	void PickWritings(COverlays * pzos);

	///<summary>Aktualisiert die Größe des Frames, damit die Picking-Grenzen richtig skaliert werden. <para></para>
	/// Diese Funktion wird automatisch vom übergeordneten Frame aufgerufen, wenn die CFrame::ReSize korrekt aufgerufen wird. Der Anwender muss daher diese Funktion normalerweise nicht aufrufen.</summary>
	///<param name= "hwnd"> Pointer auf das Window.</param>
	///<param name= "ixFrameSize"> Neue Frame-Breite in Pixeln</param>
	///<param name= "iyFrameSize"> Neue Frame-Höhe in Pixeln</param>
	void SetFrame(HWND & hwnd, int & ixFrameSize, int & iyFrameSize);

	// ----------------
	// Membervariablen:
	// ----------------

	///<summary>Handle auf das Window (Wird gebraucht, um den Cursor verschwiunden zu lassen).</summary>
	HWND m_hwnd;

	///<summary>True, falls es sich um einen virtuellen Zeiger handelt.</summary>
	bool m_bVirtual;

	///<summary>Relative X-Position bei einem virtuellen Cursor.</summary>
	float m_frxVirtual;

	///<summary>Relative Y-Position bei einem virtuellen Cursor.</summary>
	float m_fryVirtual;

	///<summary>Horizontale Größe des übergeordneten Frames in Pixeln.</summary>
	int m_ixFrameSize;

	///<summary>Vertikale Größe des übergeordneten Frames in Pixeln.</summary>
	int m_iyFrameSize;

	///<summary>Fraktionale X-Position des Cursors (0.0 = links ... 1.0 = rechts). </summary>
	float m_frxFrame;

	///<summary>Fraktionale Y-Position des Cursors (0.0 = oben ... 1.0 = unten). </summary>
	float m_fryFrame;

	///<summary>Flag, ob Betriebssystem-Cursor unsichtbar ist.</summary>
	bool m_bHidden;

	///<summary>Ein Pointer auf das übergeordnete Frame.</summary>
	CFrame * m_pframe;

	///<summary>Die Pixelkoordinaten des Cursors.</summary>
	POINT m_p;

	///<summary>Array für die 8 Mausbuttons. True, wenn gedrückt.</summary>
	bool m_abButton[8];
};

}