//------------------------------------
// CNodes, Pluralklasse von CNode
// 
// Autor: Prof. Dr. Tobias Breiner
// Kempten, 22.05.2015
//------------------------------------
#pragma once

namespace Vektoria
{

class CNode;

class CNodes
{
public:
	// Konstruktor.
	CNodes();

	// Destruktor.
	~CNodes();

	// Kopieroperator
	CNodes operator=(CNodes & nodes);

	// Kopiermethode.
	void Copy(CNodes & nodes);

	// Hängt Knoten in die Liste an.
	void Add(CNode* pnode);

	// Hängt Knoten aus die Liste ab, gibt true aus, falls es geklappt hat.
	bool Sub(CNode* pnode);

	// Schaut, ob Knoten in der Liste vorhanden ist, gibt true aus, falls ja.
	bool Has(CNode* pnode);

	// Gibt die aktuelle Anzahl der Knoten in der Liste aus.
	int GetCount(void);

	// Sucht in der angehängten Hierarchie abwärts rekursiv nach Node mit dem angegebenen eideutigen Namen (muss durch SetName vergeben werden) und gibt einen Pointer darauf zurück.
	CNode * SearchName(char * acName);

	// Sucht in der angehängten Hierarchie abwärts rekursiv nach Node mit der angegebenen eideutigen Knoten-Identfikationsnummer (wird bei Erstellung eines Knotens automatisch vergeben) und gibt einen Pointer darauf zurück.
	CNode * SearchID(int id); 

	// Sucht in der angehängten Hierarchie abwärts rekursiv nach Node mit der angegebenen IDLoaded (weicht von der normalen ID ab) und gibt einen Pointer darauf zurück.
	CNode * SearchIDLoaded(int idLoaded); 

	// Sucht in den direkten Nachfolgern nach Node mit der angegebenen Identifikationsnummer und gibt einen Pointer darauf aus (Im Gegensatz zu SearchID nicht rekursiv).
	CNode * SearchIDNonRecursive(int id); 

	// Sucht in den direkten Nachfolgern nach Node mit der angegebenen angegebenen IDLoaded (weicht von der normalen ID ab) und gibt einen Pointer darauf aus (Im Gegensatz zu SearchID nicht rekursiv)
	CNode * SearchIDLoadedNonRecursive(int idLoaded);

	//-----------------
	// Membervariablen:
	//-----------------

	// Dynamische Knotenliste.
	CNode** m_apnode;

	// Anzahl der allokierten Knoten in der Liste.
	int m_iNodeAllocs;

	// Anzahl der Knoten, die beim nächsten Mal allokiert werden.
	int m_iAllocBlock;

	// Aktuelle Anzahl der Knoten in der Liste.
	int m_iNodes;
};

}