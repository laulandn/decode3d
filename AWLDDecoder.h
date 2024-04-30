#ifndef ALIB_AWLDDECODER_H
#define ALIB_AWLDDECODER_H


#ifdef NICK_USE_DECODE3D


#include "ASceneDecoder.h"


struct AWLDDecoderSurfaceDef {
  char *name;
  unsigned long value;
};


struct AWLDDecoderSurfaceMap {
  char *name;
  AList_alib surfaces;
};


struct AWLDDecoderSurface {
  unsigned long num;
  char *name;
};


struct AWLDDecoderObject {
  char *tag;  // optional
  char *name;  // filename
  AMesh3D *mesh;
  char *surfMapName;  // optional
};


// WorLD format from Rend386 and Gossamer and friends...
class AWLDDecoder : public ASceneDecoder
{
public:
  AWLDDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjectsFromFile(FILE *fd);
  void fixObjectSurfMaps(AWLDDecoderObject *theObj);
  unsigned long lookupSurfNum(char *surfMapName,unsigned long surfNum);
  //
  AList_alib surfaceDefs;
  AList_alib surfaceMaps;
  AList_alib objects;
  AWLDDecoderSurfaceMap *curSurfMap;
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AWLDDECODER_H

