#ifndef ALIB_A3DSDECODER_H
#define ALIB_A3DSDECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMeshDecoder.h"


// 3ds model
class A3DSDecoder : public AMeshDecoder
{
public:
  A3DSDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  bool readObjects();
  bool readEdVer();
  bool readEditor();
  //
  bool readMaterialChunk();
  bool readMatAmbient();
  bool readMatDiffuse();
  bool readMatSpecular();
  bool readMatShininess();
  bool readMatTransparent();
  bool readMatTexture();
  bool readMatTexFile();
  //
  bool readObjectChunk();
  bool readTriMesh();
  bool readMeshVertexl();
  bool readMeshFace();
  bool readMeshTexCoords();
  bool readMeshMatInfo();
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_A3DSDECODER_H

