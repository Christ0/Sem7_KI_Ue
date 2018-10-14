#pragma once

#include "../VektoriaMath/AABB.h"
#include "Vertexs.h"
//------------------
// Klasse COctree
// Autor: Tobas Breiner
//--------------------

namespace Vektoria
{

class COctree
{
public:
	COctree(CAABB & aabb, int iRekursionDepthMax, COctree * poctreeParent, bool bOverlap, float fOverlap);
	~COctree(void);

	void AddVertex(CVertex * pvertex, int iRekursionDepth);

	///<summary> F�gt einen Vertex dem Octree hinzu, falls er zu einem anderen im Octree �hnlich ist.<para></para>
	/// F�gt den ersten �hnlichen Vertex zur Vertex-Sameliste des Vertex hinzu, gibt true aus, falls es keinen �hnlichen Vertex gibt.</summary>
	///<param name = "pvertex">Hinzuzuf�gender Vertex.</param>
	///<param name = "bCheckNormals">Soll die Normaleninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation ber�cksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengef�gt.</param>
	///<param name = "fPosThresholdRadius">Wie nah m�ssen zwei Vertices in Units sein, damit sie zusammengef�gt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz d�rfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenma� maximal haben, damit sie zusammengef�gt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah m�ssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengef�gt werden?</param>
	///<param name = "iRekursionDepth">Rekursionstiefe, startet bei 0</param>
	bool AddVertexAndCheck(CVertex * pvertex, bool bCheckNormals, bool bCheckTangents, bool bCheckBitangents, bool bCheckUVs, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius, int iRekursionDepth);


	/*
	void UniteVerticesLocation();
	void UniteVerticesSame();
	*/
	CAABB m_aaabb[2][2][2];

	COctree * m_poctreeParent;
	COctree * m_apoctreeChild[2][2][2];
	COctree * m_apoctreeNeigbor[6];
	CVertexs m_vertices; 
	CAABB m_aabb;
	int m_iRekursionDepthMax;
	bool m_bOverlap;
	float m_fOverlap;
};

}