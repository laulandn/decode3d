#ifndef ALIB_ABSPDECODER_H
#define ALIB_ABSPDECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMapDecoder.h"


// BSP game map
class ABspDecoder : public AMapDecoder
{
public:
  //
  ABspDecoder(const char *fname);
  static bool recognize(uint8_t *str);
  //
protected:
  //
  void init();
  void readObjects();
  //
  char the_format;
  //
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_ABSPDECODER_H

