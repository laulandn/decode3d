#ifndef ALIB_AIDMAPDECODER_H
#define ALIB_AIDMAPDECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMapDecoder.h"


// Quake style raw map (text, before being compiled to a bsp)
// Also Value VMF format
class AIdMapDecoder : public AMapDecoder
{
public:
  //
  AIdMapDecoder(const char *fname);
  static bool recognize(uint8_t *str);
  //
protected:
  //
  void init();
  void readObjects();
  void readBrushdef(unsigned char *line);
  //
  bool isVMF;
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AIDMAPDECODER_H

