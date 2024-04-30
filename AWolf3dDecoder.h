#ifndef ALIB_AWOLF3DDECODER_H
#define ALIB_AWOLF3DDECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMapDecoder.h"


// Wolf3d
class AWolf3dDecoder : public AMapDecoder
{
public:
  AWolf3dDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AWOLF3DDECODER_H

