#ifndef ALIB_AMD2DECODER_H
#define ALIB_AMD2DECODER_H


#ifdef NICK_USE_DECODE3D


#include "AMeshDecoder.h"


// Quake 2 model
class AMD2Decoder : public AMeshDecoder
{
public:
  AMD2Decoder(const char *fname);
  static bool recognize(uint8_t *str);
protected:
  void readHeader();
  void readFrames();
  void readTriangles();
  void readSkins();
  void readTextCoords();
  //
  unsigned long skinWidth,skinHeight;
  unsigned long frameSize;
  unsigned long skinsOffset;  // from start of file
  unsigned long textCoordsOffset;  // from start of file
  unsigned long trianglesOffset;  // from start of file
  unsigned long framesOffset;  // from start of file
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_AMD2DECODER_H

