#pragma once
#include "Sprite.h"

//------------------------------------
// CBackground
//
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	class CViewport;

	class CBackground : public CSprite
	{
		friend class CBackgrounds;
	protected:
		///<summary> Wird vom übergeordneten Knoten automatisch jedes Frame aufgerufen.</summary>
		///<param name= "fTimeDelta"> Verstríchene Zeit seit dem letzten Tick </param>
		void Tick(float & fTimeDelta);

	public:
		///<summary> Konstruktor.</summary>
		CBackground();

		///<summary> Destruktor.</summary>
		~CBackground();

		///<summary> Kopieroperator.</summary>
		///<param name="background">In das vorliegende Background zu kopierendes Background</param>
		CBackground operator=(CBackground & background);

		///<summary> Lädt eine Backgroundbeschreibung aus einem Vektoria-Backgroundfile.</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="id">Eindeutige Identifikationsnummer des zu ladenden Backgrounds</param>
		void Load(CFileVektoria & filevektoria, int id);

		///<summary> Speichert eine Backgroundbeschreibung in ein Vektoria-Backgroundfile.</summary>
		///<param name="filevektoria">Ein mit dem korrekten Pfad vorinitialisiertes Vektoria-File</param>
		///<param name="bWithID">Soll die eigene Identifikationsnummer in das Backgroundfile mit abgespeichert werden?</param>
		void Save(CFileVektoria & filevektoria, bool bWithID = false);
	};

}