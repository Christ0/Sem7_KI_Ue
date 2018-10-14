// UtilLogFile.h: 
//
// Enthält Utility FunctionHheaders für ein Logfile
// Nicht Objektorientiert, damit man es einfach global über alle Klassen verwenden kann!
//
// Copyright: Tobias Breiner, Company Vektoria UG (haftungsbeschränkt), Germany
// -----------------------------------------------------------------------

#if !defined(UTL_LOG_H)
#define UTL_LOG_H

#include "..\\VektoriaMath\\Color.h"
#include "..\\VektoriaMath\\HVector.h"
#include "..\\VektoriaMath\\HMat.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include "windows.h"
#include <stdio.h>

namespace Vektoria
{
// --------------------
// Bibliotheksroutinen:
// --------------------

// Setzt die Standard-Library
void ULSetLibPath(char * acPath);

// Holt die Standard-Library
void ULGetLibPath(char * acPath);

// Setzt den Pfad zum Log-File.
void ULSetLogFilePath(char * acPath);

// Gibt den Pfad zum Log-File aus.
char * ULGetLogFilePath();

// Setzt den Pointer zum Log-File.
void ULSetLogFilePtr(FILE * pfile);

// Gibt einen Pointer zum Log-File aus.
FILE * ULGetLogFilePtr();

// Setzt die Zeit des Log-Files.
void ULSetLogTime(unsigned int uTime);

// Gibt die Zeit des Log-Files aus.
unsigned int ULGetLogTime();


// ----------------
// Anfang und Ende:
// ----------------

// Initialisiert das Logfile und öffnet es zum schreiben, es ist wichtig, den Pfad mit Suffix anzugeben, z.B.  "C:\\Work\\Log.txt" oder "Log\\Vektoria.log".
void ULInit(char * szFile); 

// Finalisiert das Logfile.
void ULFini(); 

// ----------------
// An und aus:
// ----------------


// Schaltet Logfile an (Default).
void ULOn();

// Schaltet Lofile aus
void ULOff(); 

// ----------------
// Hilfs-Routinen for die Logfile-Einträge, :
// ----------------

// Startet das Logfile, schreibt Überschrift und setzt die Logfile-Uhr auf Null Sekunden.
void ULStart(LPCSTR szMsg, bool bOn = true);   

// Schreibt die Meldung szMsg ins Logfile.
void ULWrite(LPCSTR szMsg); 

// Schriebt die Meldung szMsg ins Logfile und geht danach in die nächste Zeile.
void ULWriteLn(LPCSTR szMsg); 

// Erzeugt  einen Unterstrich der Länge iLength mit dem Zeichen ch.
void ULLine(char ch, int iLength); 

// ----------------------------------------------------------------
// Eintrags-Routinen (können so verwendet werden, wie mit "printf"):
// ----------------------------------------------------------------


// Checkt, of das File mit dem Pfad szFile zu öffnen ist, uns schreibt das Ergebnis ins Logfile.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
bool ULCheckFile(LPCSTR szFile, BOOL bReadWrite = false);


// Schreibt eine Überschrift ins Logfile.
// Kann so verwendet werden, wie printf.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
void ULSection(LPCSTR szMsg, ...);

// Schreibt eine OK-Meldung ins Logfile.
// Kann so verwendet werden, wie printf.
// Erscheint sowohl im Debug- als auch im Release-Modus.
void ULOk(LPCSTR szMsg, ...);

// Schreibt eine INFO-Meldung ins Logfile.
// Kann so verwendet werden, wie printf.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
void ULInfo(LPCSTR szMsg, ...);

// Schreibt eine WARN-Meldung ins Logfile.
// Kann so verwendet werden, wie printf.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
void ULWarn(LPCSTR szMsg, ...);

// Schreibt eine ERROR-Meldung ins Logfile.
// Kann so verwendet werden, wie printf.
// Erscheint sowohl im Debug- als auch im Release-Modus.
void ULError(LPCSTR szMsg, ...);

// Schreibt eine DEBUG-Meldung ins Logfile.
// Kann so verwendet werden, wie printf.
// Erscheint sowohl im Debug- als auch im Release-Modus.
void ULDebug(LPCSTR szMsg, ...);

// Schreibt die 4 Tupelinhalte des homogenen Vektors v ins Logfile, szVektor ist der Name des Vektors.
// Erscheint sowohl im Debug- als auch im Release-Modus.
void ULDebugVector(LPCSTR szVektor, CHVector v);

// Schreibt  die 16 Tupelinhalte der homogenen Matrix m ins Logfile, szMat ist der Name der Matrix.
// Erscheint sowohl im Debug- als auch im Release-Modus.
void ULDebugMat(LPCSTR szMat, CHMat m);


// Schreibt die 4 Tupelinhalte des homogenen Vektors v ins Logfile, szVektor ist der Name des Vektors.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
void ULVector(LPCSTR szVektor, CHVector v);

// Schreibt  die 16 Tupelinhalte der homogenen Matrix m ins Logfile, szMat ist der Name der Matrix.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
void ULMat(LPCSTR szMat, CHMat m);

// Schreibt die 4 Tupelinhalte der Farbe color ins Logfile, szColor ist der Name der Farbe.
// Erscheint nur im Debug-Modus, aber nicht im Release-Modus.
void ULColor(LPCSTR szColor, CColor color);

// Gibt die letzte Log-File-Meldung aus.
void ULGetLastMsg(char * ac);


}

#endif 
