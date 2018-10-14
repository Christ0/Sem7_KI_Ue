 #pragma once

namespace Vektoria
{

class CFloatRect
{
public:
	///<summary> Konstruktor.</summary> 
	CFloatRect();

	///<summary> Konstuktor mit fxPos = linker x-Wert, fyPos = oberer y-Wert, fxSize = Breite, fy-Size = Höhe.	</summary>
	///<param name="fxPos">x-Position im Kordinatensystem</param>
	///<param name="fyPos">y-Position im Kordinatensystem</param>
	///<param name="fxSize">x-Breite im Kordinatensystem</param>
	///<param name="fySize">y-AchsenpositionBreite im Kordinatensystem</param>
	CFloatRect(float fxPos, float fyPos, float fxSize, float fySize); 

	///<summary> Kopieroperator.</summary> 
	///<param name="floatrect">Das zu kopierende Rechteck</param>
	CFloatRect operator=(CFloatRect & floatrect);

	///<summary> Kopiermethode.</summary> 
	///<param name="floatrect">Das zu kopierende Rechteck</param>
	void Copy(CFloatRect & floatrect);

	///<summary> Produktoperator.</summary>
	///<param name="floatrect">Das zu produzierende Rechteck</param>
	CFloatRect operator*(CFloatRect & floatrect); 

	///<summary> Re-Initialisierung mit fxPos = linker x-Wert, fyPos = oberer y-Wert, fxSize = Breite, fy-Size = Höhe.</summary> 
	///<param name="fxPos">x-Position im Kordinatensystem</param>
	///<param name="fyPos">y-Position im Kordinatensystem</param>
	///<param name="fxSize">x-Breite im Kordinatensystem</param>
	///<param name="fySize">y-AchsenpositionBreite im Kordinatensystem</param>
	void Init(float fxPos, float fyPos, float fxSize, float fySize); 

	///<summary> Deinitialisierung.</summary> 
	void Fini();

	///<summary> Gibt true aus, falls sich fx zwischen linker und rechter Kante befindet (ausschließlich Kante).</summary> 
	///<param name="fx">X-Wert, der überprüft werden soll</param>
	bool IsBetweenX(float fx); 

	///<summary> Gibt true aus, falls sich fy zwischen oberer und unterer Kante befindet (ausschließlich Kante).</summary> 
	///<param name="fy">Y-Wert, der überprüft werden soll</param>
	bool IsBetweenY(float fy); 

	///<summary> Gibt true aus, wenn der Punkt P=(fx,fy) im Rechteck ist, ansonsten false (ausschließlich Kante).</summary>
	///<param name="fx">X-Wert, der überprüft werden soll</param>
	///<param name="fy">Y-Wert, der überprüft werden soll</param>
	bool IsBetween(float fx, float fy); 

	///<summary> Gibt true aus, falls sich fx zwischen linker und rechter Kante befindet (einschleißlich Kante).</summary> 
	///<param name="fx">X-Wert, der überprüft werden soll</param>
	bool IsInnerX(float fx); 

	///<summary> Gibt true aus, falls sich fy zwischen oberer und unterer Kante befindet (einschleißlich Kante).</summary> 
	///<param name="fy">Y-Wert, der überprüft werden soll</param>
	bool IsInnerY(float fy); 

	///<summary> Gibt true aus, wenn der Punkt P=(fx,fy) im Rechteck ist, ansonsten false (einschleißlich Kante).</summary> 
	///<param name="fx">X-Wert, der überprüft werden soll</param>
	///<param name="fy">Y-Wert, der überprüft werden soll</param>
	bool IsInner(float fx, float fy); 

	///<summary> Gibt Zwischendistanz des Parameter-Floatrects von der linken Kante aus.</summary>
	///<param name="floatrect">Rechteck 2</param>
	float GetDistLeft(CFloatRect & floatrect); 

	///<summary> Gibt Zwischenddistanz des Parameter-Floatrects von der rechten Kante aus.</summary>
	///<param name="floatrect">Rechteck 2</param>
	float GetDistRight(CFloatRect & floatrect); 

	///<summary> Gibt Zwischenddistanz des Parameter-Floatrects von der oberen Kante aus.</summary>
	///<param name="floatrect">Rechteck 2</param>
	float GetDistTop(CFloatRect & floatrect); 

	///<summary> Gibt Zwischenddistanz des Parameter-Floatrects von der unteren Kante aus.</summary> 
	///<param name="floatrect">Rechteck 2</param>
	float GetDistBottom(CFloatRect & floatrect); 

	///<summary> Gibt true aus, wenn ver vorlioegende FloatRect mit floatrect kollidiert (sich irgendwo überlappt oder berührt).</summary> 
	///<param name="floatrect">Rechteck 2</param>
	bool Collides(CFloatRect & floatrect);

	///<summary> Gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von links berührt (kann mit Komma-Ungenauigkeiten umgehen).</summary>
	///<param name="floatrect">Rechteck 2</param>
	bool TouchesLeft(CFloatRect & floatrect); 

	///<summary> Gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von rechts berührt (kann mit Komma-Ungenauigkeiten umgehen).</summary>
	///<param name="floatrect">Rechteck 2</param>
	bool TouchesRight(CFloatRect & floatrect); 

	///<summary> Gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von oben berührt (kann mit Komma-Ungenauigkeiten umgehen).</summary>
	///<param name="floatrect">Rechteck 2</param>
	bool TouchesTop(CFloatRect & floatrect); 

	///<summary> Gibt true aus, falls Parameter-Floatrect das Klassenfloatrect von unten berührt (kann mit Komma-Ungenauigkeiten umgehen).</summary>
	///<param name="floatrect">Rechteck 2</param>
	bool TouchesBottom(CFloatRect & floatrect); 

	///<summary> Schneidet Ränder des Rechtecks dergestalt ab, dass sie alle zwischen Null und Eins liegen.</summary> 
	void Clip(); 

	///<summary> Setzt linken X-Wert.</summary> 
	///<param name="fxPos">X-Wert</param>
	void SetXPos(float fxPos); 

	///<summary> Setzt oberen Y-Wert.</summary>
	///<param name="fyPos">Y-Wert</param>
	void SetYPos(float fyPos);  

	///<summary> Setzt Breite.</summary>
	///<param name="fxSize">Breite</param>
	void SetXSize(float fxSize); 

	///<summary> Setzt Höhe.</summary>
	///<param name="fySize">Höhe</param>
	void SetYSize(float fySize);  

	///<summary> Holt linken X-Wert des FloatRects.</summary> 
	float GetXPos(); 

	///<summary> Holt linken Y-Wertdes FloatRects.</summary> 
	float GetYPos();  	
	
	///<summary> Gibt die Mitte des FloatRects in X-Richtung aus.</summary> 
	float GetXMid(); 

	///<summary> Gibt die Mitte des FloatRects in Y-Richtung aus.</summary> 
	float GetYMid();  

	///<summary> Gibt die Breite des FloatRects aus.</summary> 
	float GetXSize(); 

	///<summary> Gibt die Höhe des FloatRects aus.</summary> 
	float GetYSize();

	///<summary> Gibt die rechte X-Position aus.</summary>
	float GetRight(); 

	///<summary> Gibt die untere Y-Position aus.</summary> 
	float GetBottom(); 

	///<summary> Gibt das Verhältnis zwischen Breite und Höhe aus.</summary> 
	float GetRatio(); 

	///<summary> Skaliert Rechteck ausgehend vom Ursprung um den Betrag f in x- und y-Reichtung.</summary> 
	///<param name="f"></param>
	void Scale(float f); 

	///<summary> Skaliert Rechteck um den Betrag f in x- und y-Reichtung, aber lässt untere Kante auf gleichem Level (Rechteck wird hochgezogen).</summary>
	///<param name="f">Skalierungsfaktor</param>
	void ScaleFromBottom(float f); 

	///<summary> Skaliert Rechteck ausgehend vom Ursprung.</summary>
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	void Scale(float fx, float fy); 

	///<summary> Skaliert Rechteck, aber lässt untere Kante auf gleichem Level (Rechteck wird hochgezogen).</summary> 
	///<param name="fx">Skalierungsfaktor in X-Richtung</param>
	///<param name="fy">Skalierungsfaktor in Y-Richtung</param>
	void ScaleFromBottom(float fx, float fy); 

	///<summary> Verschiebt Rechteck um den Vektor(fx,fy).</summary> 
	///<param name="fx">Verschiebungsfaktor in X-Richtung</param>	
	///<param name="fy">Verschiebungsfaktor in Y-Richtung</param>
	void Translate(float fx, float fy); 

	//------------------
	// Member-Variablen:
	//------------------

	///<summary> Linke Position.</summary> 
	float m_fxPos;

	///<summary> Obere Position.</summary> 
	float m_fyPos;

	///<summary> Breite.</summary> 
	float m_fxSize;

	///<summary> Höhe.</summary> 
	float m_fySize;
};

}