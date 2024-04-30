#ifndef DECODERLIB_ASMARTMESHDECODER_H
#define DECODERLIB_ASMARTMESHDECODER_H


#ifdef NICK_USE_DECODE3D


#ifndef NICK_USE_NICK3D
#error "decode3d requires NICK_USE_NICK3D!!!"
#endif


#include "../cpp/decoderlib/ASmartDecoder.h"

#include "AMeshDecoder.h"


class ASmartMeshDecoder : ASmartDecoder
{
public:
  static AMeshDecoder *pickMeshDecoder(const char *theFilename);
};


#endif // NICK_USE_DECODE3D


#endif // DECODERLIB_ASMARTMESHDECODER_H
