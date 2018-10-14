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

	///<summary> Fügt einen Vertex dem Octree hinzu, falls er zu einem anderen im Octree ähnlich ist.<para></para>
	/// Fügt den ersten ähnlichen Vertex zur Vertex-Sameliste des Vertex hinzu, gibt true aus, falls es keinen ähnlichen Vertex gibt.</summary>
	///<param name = "pvertex">Hinzuzufügender Vertex.</param>
	///<param name = "bCheckNormals">Soll die Normaleninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Normalen unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckTangents">Soll die Tangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Tangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckBitangents">Soll die Bitangenteninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer Bitangenten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "bCheckUVs">Soll die UV-Koordinateninformation berücksichtigt werden? Bei false werden gleiche Vertices, die sich hinsichtlich ihrer UV-Koordinaten unterscheiden, trotzdem zusammengefügt.</param>
	///<param name = "fPosThresholdRadius">Wie nah müssen zwei Vertices in Units sein, damit sie zusammengefügt werden?</param>
	///<param name = "faThreshold">Welche Winkeldifferenz dürfen die jeweiligen Normalen/Tangenten/Bitangenten zweier Vertices im Bogenmaß maximal haben, damit sie zusammengefügt werden?</param>
	///<param name = "fUVThresholdRadius">Wie nah müssen die UV-Koordinaten zweier Vertices sein, damit sie zusammengefügt werden?</param>
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