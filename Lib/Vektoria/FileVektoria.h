// CFileVektoria: 
//
// Enthält Utility Functions für das Speichern und Laden
//
// Autor: Prof. Dr. Tobias Breiner, 
// Company:  Vektoria UG (haftungsbeschränkt), Germany
// -----------------------------------------------------------------------


#pragma once
#include "UtilLogFile.h"
#include "Vertex.h"

// #define LOG_OK_MESSAGES

// Anzahl der Zeilen, die maximal übersprungen werden können (Eingefügt zur Aufwärtskompabilität, damit zukünftig auch neue Parameter eingfügt werden können, und alte Files trotzdem noch eingelesen werden) 
#define NR_OF_FILE_PRELINES 70

namespace Vektoria
{

	class CNode; 
	class CNodes;

	class CFileVektoria
	{
	public:
		CFileVektoria();
		~CFileVektoria();

		bool OpenToSave(char * acPath);
		bool OpenToLoad(char * acPath);
		void Close();

		void SetSection(char * acSection, int id);
		void SetSection(char * acSection);
		char m_acSection[100];

		int GetNextLine(char * acSection, char * acKey, char * acDefault, char * acBuf, int iacBuf, char * acPath);
		int GetNextLineInt(char * acSection, char * acKey, char * acDefault, char * acPath);
		int SetNextLine(char * acSection, char * acKey, char * acValue, char * acPath);

		// checking routines:
		bool CheckFloat(float * f, float fMin, float fMax, float fDefault, char * acVariable, char * acUnit);
		bool CheckInt(int * i, int iMin, int iMax, int   iDefault, char * acVariable, char * acUnit);
		bool CheckLong(unsigned long * l, unsigned long  lMin, unsigned long lMax, unsigned long lDefault, char * acVariable, char * acUnit);

		// frequently used routines, for loading out of the ini-file:
		void LoadVersion(float & fVersion);

		bool LoadBool(bool  & b, char * acKey);
		void LoadTrint(int  & it, char * acKey);
		void LoadInt(int & i, int   iMin, int   iMax, int   iDefault, char * acKey, char * acUnit);
		void LoadInt(int & i, int   iMin, int   iMax, char * acKey);
		void LoadInt(int & i, char * acKey);
		void LoadLong(unsigned long & l, unsigned long  lMin, unsigned long   lMax, unsigned long   lDefault, char * acKey, char * acUnit);
		void LoadEnum(int & e, int iDefault, char * acSelection, char * acKey);
		void Load3Enum(int & e, int iDefault, char * acSelection, char * acKey);
		void LoadXEnum(int & e, int iDefault, char * acSelection, char * acKey);
		void LoadFloat(float & f, float fMin, float fMax, float fDefault, char * acKey, char * acUnit);
		void LoadFloat(float & f, float fMin, float fMax, char * acKey);
		void LoadFloat(float & f, char * acKey);
		void LoadChar(char & c, char * acKey);
		void LoadChararray(char * ac, char * acKey);
		void LoadAngle(float & fa, char * acKey);
		void LoadFract(float & fr, char * acKey, bool bLimitMax = TRUE);

		void LoadMat(CHMat & m, char * acKey);
		void LoadVector(CHVector & v, char * acKey);
		void LoadColor(CColor & color, char * acKey);
		void LoadVertex(CVertex & vertex, char * acKey);



		// frequently used routines, for reading the section headers of an ini-file
		int LoadSectionCount(char * acPrefix);
		bool LoadSectionInit(char * acPrefix);
		bool LoadSectionNext(char * acSection, char * acSuffix1, char * acSuffix2);
		bool LoadSectionNext(char * acSection);
		void LoadSectionFini();

		// frequently used routines, for saving into the ini-file:
		void SaveVersion(float & fVersion);

		bool SaveBool(bool b, char * acKey);
		void SaveTrint(int it, char * acKey);
		void SaveInt(int i, char * acKey);
		void SaveLong(unsigned long l, char * acKey);
		void SaveEnum(int e, char * acSelection, char * acKey);
		void SaveChar(char c, char * acKey);
		void SaveFloat(float f, char * acKey);
		void SaveChararray(char * ac, char * acKey);
		void SaveAngle(float fa, char * acKey);
		void SaveFract(float fr, char * acKey);

		void SaveMat(CHMat & m, char * acKey);
		void SaveVector(CHVector & v, char * acKey);
		void SaveColor(CColor & color, char * acKey);
		void SaveVertex(CVertex & vertex, char * acKey);

		// ----------------------------- 
		// Methoden für die Knotenliste: 
		// ----------------------------- 

		void AddNode(CNode * pnode, int idLoaded);
		CNode * GetNode(int id);

		// ---------------- 
		// Membervariablen: 
		// ---------------- 

		// Knotenliste
		CNodes * m_pnodes; 

		char m_acPath[MAX_PATH]; 
		FILE * m_pfile;
		char m_acPrefix[256];

		char m_aacLastLine[NR_OF_FILE_PRELINES][260]; // später dynamisch

		bool m_bLastLineFound;
		bool m_bLastLineSkipped;

		int m_iLines;
		int m_iLineFirst;
		int m_iLineLast;

		bool m_bOpenedToLoad;

		// Flag, on Laden bzw. Speichern aus irgendweelchen gründen gescheitert ist
		bool m_bFailed;
	};

}

