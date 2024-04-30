#ifndef ALIB_AVRMLDECODER_H
#define ALIB_AVRMLDECODER_H


#ifdef NICK_USE_DECODE3D


#include "ASceneDecoder.h"


// VRML model
class AVRMLDecoder : public ASceneDecoder
{
public:
  AVRMLDecoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readObjects();
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AVRMLDECODER_H

