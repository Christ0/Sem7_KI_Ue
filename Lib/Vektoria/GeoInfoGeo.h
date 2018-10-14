#pragma once

#include "GeoTriangleStrip.h"
#include "GeoPointList.h"
#include "GeoLineList.h"

namespace Vektoria
{


	class CGeoInfoGeo : public CGeoTriangleStrip
	{
	public:
		CGeoInfoGeo();
		~CGeoInfoGeo();

		void Init(CGeo & zg, bool bShowVertices = true, bool bShowNormals = true, bool bShowTangentsAndBitangents = true);
		CGeoPointList m_geopointlist;
		CGeoLineList m_geolinelistNormals;
		CGeoLineList m_geolinelistTangents;
		CGeoLineList m_geolinelistBitangents;

		CVertex * avertexVertex;
		CVertex * avertexNormal;
		CVertex * avertexTangent;
		CVertex * avertexBitangent;

	};

}