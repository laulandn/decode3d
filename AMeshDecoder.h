#ifndef ALIB_AMESHDECODER_H
#define ALIB_AMESHDECODER_H


#ifdef NICK_USE_DECODE3D


#ifndef NICK_USE_NICK3D
#error "decode3d requires NICK_USE_NICK3D!!!"
#endif


// I'm an idiot.  I don't know where the circular references are that make me need this
class AMatrix3D;


#include "../cpp/alib/abasics.h"


class AMesh3D;
class AVertexF3D;


#include "A3DDecoder.h"


class AMeshDecoder : public A3DDecoder
{
public:
  AMeshDecoder(const char *fname);
  virtual ~AMeshDecoder();
  //
  virtual AMesh3D *createNewMeshObject();
  //
  unsigned long getNumParts() { return numParts; }
  AList_alib *getParts() { return &parts; }
  AList_alib *getFrameVerts(unsigned int num);
  unsigned long getNumSeqs() { return nseqs; }
  unsigned long getNumFrames() { return nframes; }
  unsigned long getNumVerts() { return nverts; }
  //
  AList_alib *getFaces() { return &faces; }
  AList_alib *getFaceInfos() { return &faceInfos; }
  unsigned long getNumFaces() { return nfaces; }
  AList_alib *getVertNormals() { return &vertNormals; }
  AList_alib *getFaceNormals() { return &faceNormals; }
  AList_alib *getFaceTextCoords() { return &faceTextCoords; }
  //
  AList_alib *getTextures() { return &textures; }
  unsigned long getNumTextures() { return ntextures; }
  AList_alib *getTextCoords() { return &textCoords; }
  unsigned long getNumTextCoords() { return ntextcoords; }
  bool getFixTextCoords() { return fixTextCoords; }
  //char *getName() { return name; }
protected:
  //
  virtual void init();
  void readVectorL(AVertexF3D *v);
  void readVectorB(AVertexF3D *v);
  void readC1VectorL(AVertexF3D *v);  // one byte compressed quake vector with normal index
  void readC2VectorL(AVertexF3D *v);  // two byte compressed quake vector with normal index
  void readMatrixL(AMatrix3D *m);
  //
  unsigned long nverts;
  unsigned long ntextures,ntextcoords;
  unsigned long nfaces,nframes,nseqs;
  unsigned long numParts;
  unsigned long vertOffset,oldVertOffset,faceOffset;
  bool fixTextCoords;
  //
  AList_alib parts;
  AList_alib *verts;  // array of list of verts, one per anim frame
  AList_alib faces;
  AList_alib faceInfos;
  // all the rest are optional
  AList_alib seqs;
  AList_alib vertNormals;  // same as num of verts
  AList_alib faceNormals;  // same as num of faces
  AList_alib faceTextCoords;  // same as num of faces
  AList_alib textures;
  AList_alib textCoords;
  AMesh3D *tm;
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AMESHDECODER_H

