//------------------------------------
// CAABB
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Copyright: Vektoria UG (haftungsbeschränkt)
//------------------------------------

#pragma once

#include "HVector.h"
#include "HMat.h"
#include "Ray.h"

namespace Vektoria
{

	class CAABB
	{
	public:
		/// <summary>Konstruktor. Die Axis Aligned Bounding Box liegt im Ursprung</summary>
		CAABB(void);

		/// <summary>Konstruktor durch Angabe zweier Eckpunkte.</summary>
		/// <param name = "vMin">Minimaleckpunkt</summary>
		/// <param name = "vMax">Maximaleckpunkt</summary>
		CAABB(CHVector &vMin, CHVector &vMax);

		/// <summary>Kopieroperator.</summary>
		/// <param name = "aabb">Zu kopierende AABB</summary>
		void Copy(CAABB &aabb) { m_vMin = aabb.m_vMin; m_vMax = aabb.m_vMax; }

		/// <summary>Transformiert die Axis-Aligned Bounding Box.</summary>
		/// <param name = "m">Homogene Transformationsmatrix</summary>
		CAABB Transform(CHMat & m);

		/// <summary>Vergrößert die vorliegende AABB durch Hinzufügen einer zweiten Axis-Aligned Bounding Box.</summary>
		/// <param name = "aabb">Hinzuzufügende AABB</summary>
		void AddAABB(CAABB &aabb);

		/// <summary>Vergrößert die vorliegende AABB durch Hinzufügen einer zweiten Axis-Aligned Bounding Box.</summary>
		/// <param name = "aabb">Hinzuzufügende AABB</summary>
		/// <param name = "m">Homogene Transformationsmatrix für die hinzuzufügende AABB </summary>
		void AddAABB(CAABB &aabb, CHMat & m);

		/// <summary>Vergrößert die vorliegende AABB durch Hinzufügen einer zweiten Axis-Aligned Bounding Box.</summary>
		/// <param name = "aabb">Hinzuzufügende AABB</summary>
		/// <param name = "m">Homogene Transformationsmatrix für die hinzuzufügende AABB </summary>
		void AddAABBMax(CAABB &aabb, CHMat & m);

		/// <summary>Erzeugt eine AABB durch Angabe einer Kugel.</summary>
		/// <param name = "fRadius">Radius der Kugel</summary>
		/// <param name = "m">Homogene Transformationsmatrix der Kugel </summary>
		void AddRadius(float & fRadius, CHMat & m);

		/// <summary>Setzt eine unendlich große AABB, im Gegensatz zu SetToInfinity werden auch die acht Eckpunkte neu berechnet.</summary>
		void AddMax();

		/// <summary>Fügt einen Raumpunkt hinzu und berechnet die AABB neu.</summary>
		/// <param name = "vPos">Raumpunkt als homogener Vektor</summary>
		void AddVector(CHVector &vPos);

		/// <summary>Schaut, ob ein Raumpunkt innerhalb oder am Rand die vorliegenden Axis Aligned Bounding Box liegt, gibt true aus, falls ja.</summary>
		/// <param name = "vPos">Raumpunkt als homogener Vektor</summary>
		bool IsInside(CHVector &vPos);

		/// <summary>Schaut, ob sich zwei Axis Aligned Bounding Boxen berühren oder durchdringen, gibt true aus, falls ja.</summary>
		/// <param name = "aabb">Zweite AABB</summary>
		bool Intersects(CAABB &aabb);

		/// <summary>Setzt alle Werte der Box auf maximale Größe (Float-Max)<para></para>
		/// Achtung! Im Gegensatz zu SetMax werden die acht Eckpunkte nicht automatisch neu berechnet.</summary>
		void SetToInfinity();

		/// <summary>Ermittelt, ob der Strahl r die vorliegende Axis Aligned Bounding Box schneidet.</summary>
		/// <param name = "r">Strahl<para></para>Achtung, die Richtung des Strahles (m_vOrigin) muss vorher normiert sein!</summary>
		bool Intersects(CRay & r);

		/// <summary>Ermittelt, ob der Strahl r die vorliegende Axis Aligned Bounding Box schneidet, gibt die Entfernung zum Schnittpunkt aus. </summary>
		/// <param name = "r">Strahl<para></para>Achtung, die Richtung des Strahles (m_vOrigin) muss vorher normiert sein!</summary>
		/// <param name = "fDistance">Entfernung des Strahlursprungs zum Schnittpunkt</summary>
		bool Intersects(CRay & r, float & fDistance);

		/// <summary>Ermittelt, ob der Strahl r die vorliegende Axis Aligned Bounding Box schneidet oder der Strahlursprung innerhalb der AABB liegt.</summary>
		/// <param name = "r">Strahl<para></para> Achtung, die Richtung des Strahles (m_vOrigin) muss vorher normiert sein!</summary>
		bool IntersectsOrIsInside(CRay & r);

		/// <summary>Gibt die Position des Mittelpunktes der Axis Aligned Bounding Box aus. </summary>
		CHVector GetMid(); 

		/// <summary>Gibt eine zufällige Position innerhalb der Axis Aligned Bounding Box aus. </summary>
		CHVector GetRandPos();

		/// <summary>Gibt die Minimalpositionsecke der Axis Aligned Bounding Box aus.</summary>
		CHVector &GetMin(void) { return m_vMin; }

		/// <summary>Gibt die Maximalpositionsecke der Axis Aligned Bounding Box aus.</summary>
		CHVector &GetMax(void) { return m_vMax; }

		/// <summary>Gibt den Diagonalvektor der Axis Aligned Bounding Box aus.</summary>
		CHVector GetSize(void) { return m_vMax - m_vMin; }

		/// <summary>Löscht die Daten, sodass ein komplett neuer AABB aufgebaut werden kann.</summary>
		void Clear();

		/// <summary>Schreibt die aktuellen Werte der AABB ins Vektoria-Logfile.</summary>
		void Log();

		// ----------------
		// Membervariablen:
		// ----------------

		/// <summary>Minimalpositionsecke der Axis Aligned Bounding Box.</summary>
		CHVector m_vMin;

		/// <summary>Maximalpositionsecke der Axis Aligned Bounding Box.</summary>
		CHVector m_vMax;

		/// <summary>Die acht Ecken der Axis Aligned Bounding Box im lokalen Koordiatensystem.</summary>
		CHVector m_av[8];

		/// <summary>Die acht Ecken der Axis Aligned Bounding Box im letzten globalen Koordiatensystem.</summary>
		CHVector m_avGlobal[8];

		/// <summary>Flag, ob Axis Aligned Bounding Box gelöscht und neu berechnet werden muss.</summary>
		bool m_bClear;
	private:
		void CalcCube();


	};

}