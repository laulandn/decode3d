#ifndef ALIB_A3DDECODER_H
#define ALIB_A3DDECODER_H


#ifdef NICK_USE_DECODE3D


#ifndef NICK_USE_NICK3D
#error "decode3d requires NICK_USE_NICK3D!!!"
#endif


#include "../cpp/decoderlib/ADecoder.h"


// TODO: Should this be the common parent of scene and mesh?  Do we need one?


class AList_alib;


extern unsigned long ARend386Colors16[];
extern unsigned long ARend386Colors256base[];


class A3DDecoder : public ADecoderAbstract
{
public:
  A3DDecoder(const char *fname);
  virtual ~A3DDecoder();
  //
  void lookupRend386Color(unsigned long surf, float *r, float *g, float *b);
  unsigned int handleFace(AList_alib *faces, AList_alib *faceInfos, int offset,  int voff, unsigned long surf);
  //
  void **allocArray(AList_alib *theList);
  unsigned short *alloc3USArray(AList_alib *theList);
  float *alloc3FArray(AList_alib *theList);
  float *alloc2FArray(AList_alib *theList);
  //
  unsigned int arrayFromList(void **theArray,AList_alib *theList);
  unsigned int array3USFromList(unsigned short *theArray,AList_alib *theList);
  unsigned int array3FFromList(float *theArray,AList_alib *theList);
  unsigned int array2FFromList(float *theArray,AList_alib *theList);
  //
  virtual bool isMap() { return false; }
  //
protected:
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_A3DDECODER_H

