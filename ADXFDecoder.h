#ifndef ALIB_ADXFDECODER_H
#define ALIB_ADXFDECODER_H


#ifdef NICK_USE_DECODE3D


#include "ASceneDecoder.h"


// DXF model
class ADXFDecoder : public ASceneDecoder
{
public:
  ADXFDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_ADXFDECODER_H

