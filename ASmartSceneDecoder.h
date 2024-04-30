#ifndef DECODERLIB_ASMARTSCENEDECODER_H
#define DECODERLIB_ASMARTSCENEDECODER_H


#ifdef NICK_USE_DECODE3D


#ifndef NICK_USE_NICK3D
#error "decode3d requires NICK_USE_NICK3D!!!"
#endif


#include "../cpp/decoderlib/ASmartDecoder.h"

#include "ASceneDecoder.h"


class ASmartSceneDecoder : ASmartDecoder
{
public:
  static ASceneDecoder *pickSceneDecoder(const char *theFilename);
};


#endif // NICK_USE_DECODE3D


#endif // DECODERLIB_ASMARTSCENEDECODER_H
