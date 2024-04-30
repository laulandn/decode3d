#ifndef ALIB_ALIGHTWAVEDECODER_H
#define ALIB_ALIGHTWAVEDECODER_H


#ifdef NICK_USE_DECODE3D


#include "ASceneDecoder.h"


// Lightwave model
class ALightwaveDecoder : public ASceneDecoder
{
public:
  ALightwaveDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
  void readSurf();
  void readPols();
  void readPnts();
  void readPtag();
  void readTags();
  void readBbox();
  void readLayr();
  void readClip();
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_ALIGHTWAVEDECODER_H

