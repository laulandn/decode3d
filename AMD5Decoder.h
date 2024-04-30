#ifndef ALIB_AMD5DECODER_H
#define ALIB_AMD5DECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMeshDecoder.h"


struct AMD5Vert {
  float s,t;
  int start,count;
};


struct AMD5Tri {
  int a,b,c;
};


struct AMD5Weight {
  int joint,bias;
  float x,y,z;
};


// Doom 3 model
class AMD5Decoder : public AMeshDecoder
{
public:
  AMD5Decoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
  void convertAll();
  AMD5Vert *getVertNum(unsigned int n);
  AMD5Tri *getTriNum(unsigned int n);
  AMD5Weight *getWeightNum(unsigned int n);
  //
  unsigned int ndVerts,ndTris,ndWeights;
  AList_alib dVerts;
  AList_alib dTris;
  AList_alib dWeights;
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AMD5DECODER_H

