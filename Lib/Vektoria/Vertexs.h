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
	///<param name= "pvertex"> Pointer auf den zu überprüfenden Vertex</param>
	bool Has(CVertex * pvertex);

	///<summary> Setzt alle Tangenten und Bitangenten auf den Wert (0,0,0,0) zurück. </summary>
	void ClearTangentsAndBitangents();

	///<summary> Löscht die Topologiedaten (optionale Zusatzdaten über adjazentre Faces und ähnliche Vertices) aller Vertices . </summary>
	void ClearTopology();

	///<summary> Hängt alle Vertices ab und löscht sie danach.</summary>
	void KillAll();

	///<summary> Hängt alle markierten Vertices (Vertices, deren Flag m_bMarked = true ist) ab und löscht sie danach. </summary>
	void KillMarked();

	///<summary> Hängt alle unmarkierten Vertices (Vertices, deren Flag m_bMarked = false ist) ab und löscht sie danach. </summary>
	void KillUnmarked();

	///<summary> Markiert Vertices (Setzt alle m_bMarked auf true). </summary>
	void Mark();

	///<summary> Löscht alle Vertexmarkierungen (Setzt alle m_bMarked auf false). </summary>
	void Demark();

	///<summary> Markiert alle Vertices, die zueinander ähnlich sind. <para></para>
	/// Achtung! Dauert bei großen Listen extrem lange (quadratische Laufzeit bezüglich der Anzahl der Vertices)!</summary>
	///<param name = "bCheckNormals">Soll die Normaleninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "fPosThresholdRadius">Wie nah müssen zwei Vertices in Units sein, damit sie zusammengefügt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz dürfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenmaß maximal haben, damit sie zusammengefügt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah müssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengefügt werden?</param>
	void MarkSimilar(bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);

	///<summary> Markiert einen Vertex, falls er zu einem anderen in der Liste ähnlich ist.<para></para>
	/// Fügt beim ersten ähnlichen Vertex in der Liste zur Vertex-Sameliste des Vertex hinzu, gibt die Listennummer des ähnlichen Vertex aus.</summary>
	///<param name = "pvertexToCompare">Pointer auf den zu vergleichenden Vertex.</param>
	///<param name = "bCheckNormals">Soll die Normaleninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "fPosThresholdRadius">Wie nah müssen zwei Vertices in Units sein, damit sie zusammengefügt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz dürfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenmaß maximal haben, damit sie zusammengefügt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah müssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengefügt werden?</param>
	int MarkSimilar(CVertex * pvertexToCompare, bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);


	///<summary> Gibt den aktuelle Vertexliste im Logfile aus. </summary>
	void Log();

	CVertex ** m_apvertex;
	int m_iVertexAllocs;
	int m_iAllocBlock;
	int m_iVertexs;
};

}