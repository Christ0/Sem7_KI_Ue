#pragma once

#include "Vertex.h"
#include "FileVektoria.h"
//------------------------------------
// CVertexs, Pluralklasse von CVertex
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CVertexs
{
public:
	CVertexs();
	~CVertexs();
	CVertexs operator=(CVertexs & vertexs);

	void Copy(CVertexs & vertexs);
	void CopyHierarchy(CVertexs & vertexs);

	void Init();
	void Fini();

	void Load(CFileVektoria & filevektoria);
	void Save(CFileVektoria & filevektoria);

	void Add(CVertex * pvertex);
	bool Sub(CVertex * pvertex);

	///<summary> Mittelt alle Werte aller Vertices und gibt sie aus.</summary>
	CVertex CalcMid(); 

	///<summary> Setzt die Positionen in allen Vertices auf den Wert v.</summary>
	void SetPos(CHVector & v); 

	///<summary> Setzt die Normalenvektoren in allen Vertices auf den Wert v.</summary>
	void SetNormal(CHVector & v); 

	///<summary> Setzt die Tangentenvektoren in allen Vertices auf den Wert v.</summary>
	void SetTangent(CHVector & v); 

	///<summary> Setzt die Bitangentenvektoren in allen Vertices auf den Wert v.</summary>
	void SetBitangent(CHVector & v); 

	///<summary> Transformiert alle Vertices mit der Matrix m.</summary>
	void Transform(CHMat & m); 
	
	void AddFirst(CVertex * pvertex);

	CVertex * Make(CHVector vPos, CHVector vNormal, CHVector vTangent, float fU=0, float fV=0);
	bool Kill(CVertex * pvertex);

	///<summary> Schaut, ob ein Vertex schon in der Liste vorhanden ist, gibt true aus, falls ja.</summary>
	///<param name= "pvertex"> Pointer auf den zu �berpr�fenden Vertex</param>
	bool Has(CVertex * pvertex);

	///<summary> Setzt alle Tangenten und Bitangenten auf den Wert (0,0,0,0) zur�ck. </summary>
	void ClearTangentsAndBitangents();

	///<summary> L�scht die Topologiedaten (optionale Zusatzdaten �ber adjazentre Faces und �hnliche Vertices) aller Vertices . </summary>
	void ClearTopology();

	///<summary> H�ngt alle Vertices ab und l�scht sie danach.</summary>
	void KillAll();

	///<summary> H�ngt alle markierten Vertices (Vertices, deren Flag m_bMarked = true ist) ab und l�scht sie danach. </summary>
	void KillMarked();

	///<summary> H�ngt alle unmarkierten Vertices (Vertices, deren Flag m_bMarked = false ist) ab und l�scht sie danach. </summary>
	void KillUnmarked();

	///<summary> Markiert Vertices (Setzt alle m_bMarked auf true). </summary>
	void Mark();

	///<summary> L�scht alle Vertexmarkierungen (Setzt alle m_bMarked auf false). </summary>
	void Demark();

	///<summary> Markiert alle Vertices, die zueinander �hnlich sind. <para></para>
	/// Achtung! Dauert bei gro�en Listen extrem lange (quadratische Laufzeit bez�glich der Anzahl der Vertices)!</summary>
	///<param name = "bCheckNormals">Soll die Normaleninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "fPosThresholdRadius">Wie nah m�ssen zwei Vertices in Units sein, damit sie zusammengef�gt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz d�rfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenma� maximal haben, damit sie zusammengef�gt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah m�ssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengef�gt werden?</param>
	void MarkSimilar(bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);

	///<summary> Markiert einen Vertex, falls er zu einem anderen in der Liste �hnlich ist.<para></para>
	/// F�gt beim ersten �hnlichen Vertex in der Liste zur Vertex-Sameliste des Vertex hinzu, gibt die Listennummer des �hnlichen Vertex aus.</summary>
	///<param name = "pvertexToCompare">Pointer auf den zu vergleichenden Vertex.</param>
	///<param name = "bCheckNormals">Soll die Normaleninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "fPosThresholdRadius">Wie nah m�ssen zwei Vertices in Units sein, damit sie zusammengef�gt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz d�rfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenma� maximal haben, damit sie zusammengef�gt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah m�ssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengef�gt werden?</param>
	int MarkSimilar(CVertex * pvertexToCompare, bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);


	///<summary> Gibt den aktuelle Vertexliste im Logfile aus. </summary>
	void Log();

	CVertex ** m_apvertex;
	int m_iVertexAllocs;
	int m_iAllocBlock;
	int m_iVertexs;
};

}