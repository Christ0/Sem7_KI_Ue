#pragma once

namespace Vektoria
{

class CGeoTriangleList;
class CGeoTriangleTable;

class CFileWavefront
{
  public:
    CFileWavefront();
    ~CFileWavefront();
	CGeoTriangleTable * LoadGeo(char * pcPath, bool bUVFlipVertical = false); // nur der Aufwärtskompatibilität halber
	CGeoTriangleList * LoadGeoTriangleList(char * pcPath, bool bUVFlipVertical = false);
	CGeoTriangleTable * LoadGeoTriangleTable(char * pcPath, bool bUVFlipVertical = false);
private:
    CGeoTriangleList * m_pTriangleList;
	CGeoTriangleTable * m_pTriangleTable;
};

}