
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_DECODE3D


#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "../cpp/alib/anullstream.h"

#include "ASmartMeshDecoder.h"

// Meshes
#include "A3DSDecoder.h"
#include "AHalfLifeDecoder.h"
#include "AMDLDecoder.h"
#include "AMD2Decoder.h"
#include "AMD3Decoder.h"
#include "AMD5Decoder.h"
#include "APLGDecoder.h"
#include "AWavefrontDecoder.h"


//static char tempStringBuf[256];


////////////////////////////////////////////////////////////////////////////////
//  ASmartMeshDecoder Class
////////////////////////////////////////////////////////////////////////////////

/* STATIC */
AMeshDecoder *ASmartMeshDecoder::pickMeshDecoder(const char *theFilename)
{
  uint8_t buffer[128];
  DEBUG_OUT<<"ASmartMeshDecoder::pickMeshDecoder...\n";
  if(!openAndBufferFile(theFilename,buffer,128))
  {
    std::cerr<<"openAndBufferFile failed, giving up!\n";
    return NULL;
  }
  AStringHelper_alib shelp;
  if(A3DSDecoder::recognize(buffer))  return (new A3DSDecoder(theFilename));
  if(AMDLDecoder::recognize(buffer))  return (new AMDLDecoder(theFilename));
  if(AMD2Decoder::recognize(buffer))  return (new AMD2Decoder(theFilename));
  if(AMD3Decoder::recognize(buffer))  return (new AMD3Decoder(theFilename));
  if(AHalfLifeDecoder::recognize(buffer))  return (new AHalfLifeDecoder(theFilename));
  if(AMD5Decoder::recognize(buffer))  return (new AMD5Decoder(theFilename));
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"plg")) {
    if(APLGDecoder::recognize(buffer))  return (new APLGDecoder(theFilename));
  }
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"obj")) {
    if(AWavefrontDecoder::recognize(buffer))  return (new AWavefrontDecoder(theFilename));
  }
  std::cerr<<"pickMeshDecoder couldn't recognize that file.\n";
  return NULL;
}


#endif // NICK_USE_DECODE3D


