#ifndef ALIB_APLGDECODER_H
#define ALIB_APLGDECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMeshDecoder.h"


// PoLyGon format from Rend386 and Gossamer and friends...
class APLGDecoder : public AMeshDecoder
{
public:
  APLGDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
  //
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_APLGDECODER_H

