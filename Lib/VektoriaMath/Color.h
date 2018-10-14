#pragma once

//---------------------------------------------------
// CColor: Klasse für RGB-Farben mit Alpha-Anteil
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//---------------------------------------------------

namespace Vektoria
{

class CColor
{
public:
	///<summary> Konstruktor, initialisiert die Farbe schwarz. </summary> 
	CColor(); 

	///<summary> Konstruktor zur Initialisierung einer Farbe im RGB-System, Alphakanal wird automatisch auf 0 (opak) gesetzt.</summary>
	///<param name="frR">Rotanteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frG">Grünanteil (Wertebereich zwischen 0 und 1</param>
	///<param name="frB">Blauanteil (Wertebereich zwischen 0 und 1</param>
	CColor(float frR, float frG, float frB); 

	///<summary> Konstruktor zur Initialisierung einer Farbe im RGB-System.</summary>
	///<param name="frR">Rotanteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frG">Grünanteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frB">Blauanteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frA">Transparenz (Wertebereich zwischen 0 und 1)</param>
	CColor(float frR, float frG, float frB, float frA); 

	///<summary> Kopieroperator.</summary> 
	///<param name="color">Die zu kopierende Farbe</param>
	CColor operator=(CColor & color); 

	///<summary> Skalarprodukt.</summary> 
	///<param name="frIntensity">Skalarfaktor</param>
	CColor operator*(float frIntensity);

	///<summary> Kopiert eine Farbe.</summary> 
	///<param name="color">Die zu kopierende Farbe</param>
	void Copy(CColor & color); 

	///<summary> Kopiert eine Farbe, belässt aber den Alpha-Wert.</summary>
	///<param name="color">Die zu kopierende Farbe</param>
	void CopyWithoutAlpha(CColor & color); 

	///<summary><summary> Initalisiert die Farbe im RGB+Alpha-System.</summary>
	///<summary><param name="frR">Rotanteil (Wertebereich zwischen 0 und 1)</param>
	///<summary><param name="frG">Grünanteil (Wertebereich zwischen 0 und 1)</param>
	///<summary><param name="frB">Blauanteil (Wertebereich zwischen 0 und 1)</param>
	///<summary><param name="frA">Tranzparenz (Wertebereich zwischen 0 und 1)</param>

	void Init(float frR, float frG, float frB, float frA);		

	///<summary> Initalisiert eine 100% weiße Farbe.</summary>
	void InitWhite();		

	///<summary> Initalisiert eine 100% schwarze Farbe.</summary>
	void InitBlack();		

	///<summary> Initalisiert eine 100% rote Farbe.</summary>
	void InitRed();			

	///<summary> Initalisiert eine 100% blaue Farbe.</summary>
	void InitBlue();		

	///<summary> Initalisiert eine 100% grüne Farbe.</summary>
	void InitGreen();		

	///<summary> Initalisiert eine 100% gelbe Farbe.</summary>
	void InitYellow();		

	///<summary> Initalisiert eine 100% türkisene Farbe.</summary>
	void InitCyan();		

	///<summary> Initalisiert eine 100% magentafarbene Farbe.</summary>
	void InitMagenta();		

	///<summary> Initalisiert eine graue Farbe mit 50% Weißanteil.</summary>
	void InitGrey();		 

	///<summary> Finalisiert die Farbe (macht noch nichts, nur der Vollständigkeit halber implementiert).</summary>
	void Fini(); 

	///<summary> Invertiert die Farbe.</summary>
	void Invert();			

	///<summary> Interpoliert 2 Farben, fr ist der Laufparameter, der von 0 bis 1 geht.</summary> 
	///<param name="clorFrom">Erste zu interpolierende Farbe</param>
	///<param name="colorTo">Zweite zu interpolierende Farbe</param>
	///<param name="fr">Laufparameter(Wertebereich zwischen 0 und 1)</param>
	void Interpol(CColor & colorFrom, CColor & colorTo, float fr);  

	///<summary> RGB -> HSV ; gibt die Farbe im HSV-System aus.</summary>
	///<param name="frH">Hue (Farbwert)</param>
	///<param name="frS">Saturation (Sättigung) </param>
	///<param name="frV">Value (Helligkeit)</param>
	void GetHSV(float & frH, float & frS, float & frV);			

	///<summary> HSV -> RGB ; Setzt die Farbe durch HSV-Systemwerte.</summary> 
	///<param name="frH">Hue (Farbwert)</param>
	///<param name="frS">Saturation (Sättigung) </param>
	///<param name="frV">Value (Helligkeit)</param>
	void SetHSV(float frH, float frS, float frV);			

	///<summary> RGB -> CMY ; gibt die Farbe im CMY-System aus.</summary> 
	///<param name="frC">Cyananteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frM">Magentaanteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frY">Gelbanteil (Wertebereich zwischen 0 und 1)</param>
	void GetCMY(float & frC, float & frM, float & frY);

	///<summary> CMY -> RGB ; Setzt die Farbe durch CMY-Systemwerte.</summary> 
	///<param name="frC">Cyananteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frM">Magentaanteil (Wertebereich zwischen 0 und 1)</param>
	///<param name="frY">Gelbanteil (Wertebereich zwischen 0 und 1)</param>
	void SetCMY(float frC, float frM, float frY);				 

	///<summary> Rotanteil 0..1.</summary>
	float m_frR; 

	///<summary> Grünanteil 0..1.</summary>
	float m_frG; 

	///<summary> Blauanteil 0..1.</summary>
	float m_frB; 

	///<summary> Alpha-Anteil 0..1 0=opak, 1=transparent.</summary>
	float m_frA; 
};

}