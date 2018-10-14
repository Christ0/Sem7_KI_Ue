// UtilIni.h: 
//
// Enthält Utility FunctionHheaders zum speichern und laden
// Nicht Objektorientiert, damit man es einfach global über alle Klassen verwenden kann!
//
// Copyright: Tobias Breiner, Company Vektoria UG (haftungsbeschränkt), Germany
// -----------------------------------------------------------------------


#ifndef UTL_INI
#define UTL_INI



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UtilLogFile.h"

namespace Vektoria
{

	class CFileVektoria
	{
	public:
		// check routines:
		BOOL CheckFloat(float * f, float fMin, float fMax, float fDefault, char * szVariable, char * szUnit);
		BOOL CheckInt(int * i, int iMin, int iMax, int   iDefault, char * szVariable, char * szUnit);
		BOOL CheckLong(unsigned long * l, unsigned long  lMin, unsigned long lMax, unsigned long lDefault, char * szVariable, char * szUnit);

		// frequently used routines, for loading out of the ini-file:
		BOOL LoadBool(BOOL  & b, char * szKey, char * szSection);
		void LoadTrint(int  & it, char * szKey, char * szSection);
		void LoadInt(int & i, int   iMin, int   iMax, int   iDefault, char * szKey, char * szUnit, char * szSection);
		void LoadInt(int & i, int   iMin, int   iMax, char * szKey, char * szSection);
		void LoadInt(int & i, char * szKey, char * szSection);
		void LoadLong(unsigned long & l, unsigned long  lMin, unsigned long   lMax, unsigned long   lDefault, char * szKey, char * szUnit, char * szSection);
		void LoadEnum(int & e, int iDefault, char * szSelection, char * szKey, char * szSection);
		void Load3Enum(int & e, int iDefault, char * szSelection, char * szKey, char * szSection);
		void LoadXEnum(int & e, int iDefault, char * szSelection, char * szKey, char * szSection);
		void LoadFloat(float & f, float fMin, float fMax, float fDefault, char * szKey, char * szUnit, char * szSection);
		void LoadFloat(float & f, float fMin, float fMax, char * szKey, char * szSection);
		void LoadFloat(float & f, char * szKey, char * szSection);
		void LoadString(char * sz, char * szKey, char * szSection);
		void LoadAngle(float & fa, char * szKey, char * szSection);
		void LoadFract(float & fr, char * szKey, char * szSection, BOOL bLimitMax = TRUE);

		void LoadVector(CHVector & v, char * szKey, char * szSection);
		void LoadColor(CColor & color, char * szKey, char * szSection);



		// frequently used routines, for reading the section headers of a ini-file
		int LoadSectionCount(char * szPrefix);
		BOOL LoadSectionInit(char * szPrefix);
		BOOL LoadSectionNext(char * szSection, char * szSuffix1, char * szSuffix2);
		BOOL LoadSectionNext(char * szSection);
		void LoadSectionFini();

		// frequently used routines, for saving into the ini-file:
		BOOL SaveBool(BOOL b, char * szKey, char * szSection);
		void SaveTrint(int it, char * szKey, char * szSection);
		void SaveInt(int i, char * szKey, char * szSection);
		void SaveLong(unsigned long l, char * szKey, char * szSection);
		void SaveEnum(int e, char * szSelection, char * szKey, char * szSection);
		void SaveFloat(float f, char * szKey, char * szSection);
		void SaveString(char * sz, char * szKey, char * szSection);
		void SaveAngle(float fa, char * szKey, char * szSection);
		void SaveFract(float fr, char * szKey, char * szSection);

		void SaveVector(CHVector & v, char * szKey, char * szSection);
		void SaveColor(CColor & color, char * szKey, char * szSection);

		char m_acFile[MAX_PATH];

	};

}

#endif