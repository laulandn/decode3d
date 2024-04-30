#ifndef ALIB_AMAYADECODER_H
#define ALIB_AMAYADECODER_H


#ifdef NICK_USE_DECODE3D


#include "ASceneDecoder.h"


// NOTE: This only handles the .ma ASCII format!

// Maya model
class AMayaDecoder : public ASceneDecoder
{
public:
  AMayaDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AMAYADECODER_H

