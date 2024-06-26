
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

#include "ASmartSceneDecoder.h"

// Scenes
#include "AVRMLDecoder.h"
#include "A3DSDecoder.h"
#include "ADXFDecoder.h"
#include "AWLDDecoder.h"
#include "ALightwaveDecoder.h"
#include "AMayaDecoder.h"
#include "AIdMapDecoder.h"
#include "ABspDecoder.h"
#include "AWADDecoder.h"
#include "AWolf3dDecoder.h"


//static char tempStringBuf[256];


////////////////////////////////////////////////////////////////////////////////
//  ASmartSceneDecoder Class
////////////////////////////////////////////////////////////////////////////////

/* STATIC */
ASceneDecoder *ASmartSceneDecoder::pickSceneDecoder(const char *theFilename)
{
  uint8_t buffer[128];
  DEBUG_OUT<<"ASmartSceneDecoder::pickSceneDecoder...\n";
  if(!openAndBufferFile(theFilename,buffer,128))
  {
    std::cerr<<"openAndBufferFile failed, giving up!\n";
    return NULL;
  }
  AStringHelper_alib shelp;
  if(ABspDecoder::recognize(buffer))  return (new ABspDecoder(theFilename));
  if(AWADDecoder::recognize(buffer))  return (new AWADDecoder(theFilename));
  if(AWolf3dDecoder::recognize(buffer))  return (new AWolf3dDecoder(theFilename));
  if(ALightwaveDecoder::recognize(buffer))  return (new ALightwaveDecoder(theFilename));
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"wld")) {
    if(AWLDDecoder::recognize(buffer))  return (new AWLDDecoder(theFilename));
  }
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"map")) {
    if(AIdMapDecoder::recognize(buffer))  return (new AIdMapDecoder(theFilename));
  }
  if(shelp.extensionMatch(theFilename,(char *)"vmf")) {
    if(AIdMapDecoder::recognize(buffer))  return (new AIdMapDecoder(theFilename));
  }
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"dxf")) {
    if(ADXFDecoder::recognize(buffer))  return (new ADXFDecoder(theFilename));
  }
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"ma")) {
    if(AMayaDecoder::recognize(buffer))  return (new AMayaDecoder(theFilename));
  }
  // NOTE: Because these are mostly textfiles, we have to go by file extension...
  if(shelp.extensionMatch(theFilename,(char *)"wrl")) {
    if(AVRMLDecoder::recognize(buffer))  return (new AVRMLDecoder(theFilename));
  }
  std::cerr<<"pickSceneDecoder couldn't recognize that file.\n";
  return NULL;
}


#endif // NICK_USE_DECODE3D


