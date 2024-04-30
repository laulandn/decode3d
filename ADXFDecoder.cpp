
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

#include "ADXFDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  ADXFDecoder Class
////////////////////////////////////////////////////////////////////////////////

ADXFDecoder::ADXFDecoder(const char *fname) : ASceneDecoder(fname)
{
  init();
  openFile(fname);
  if(!err.getError()) readObjects();
}


/* STATIC */
bool ADXFDecoder::recognize(uint8_t *str)
{
  bool ret=false;
  bool isText=recognizeTextFile(str);
  DEBUG_OUT<<"isText is "<<isText<<"\n";
  // TODO: finish
  // If it isn't a text file, we KNOW it isn't a DXF file...
  if(isText) ret=true;  // good enough for now...we assume ASmartDecoder checked the file extension
  return ret;
}


void ADXFDecoder::readObjects()
{
  DEBUG_OUT<<"ADXFDecoder::readObjects()...\n";
  if(!fd) return;
  //if(errorFlag) return;
  fseek(fd,0L,SEEK_SET);
  std::cerr<<"*** Warning! Not really implemented! ***\n";
  char *line=(char *)malloc(256);
  bool understood=false;
  bool reading=true;
  while(reading) {
    if(feof(fd)) {
      reading=false;
      break;
    }
    line[0]=0;
    fgets(line,256,fd);
    if(!feof(fd)) {
      DSHELPER_alib.parseString(line,NULL);
      understood=false;
      DEBUG_OUT<<DSHELPER_alib.getArgv(0)<<"\n";
      //
      if(!DSHELPER_alib.getArgc()) understood=true;
      else {
        if(!strcmp("SECTION",DSHELPER_alib.getArgv(0))) { understood=true; }
        if(!strcmp("ENDSEC",DSHELPER_alib.getArgv(0))) { understood=true; }
        if(!strcmp("HEADER",DSHELPER_alib.getArgv(0))) { understood=true; }
        if(!strcmp("CLASSES",DSHELPER_alib.getArgv(0))) { understood=true; }
        if('$'==DSHELPER_alib.getArgv(0)[0]) {
          understood=true;
        }
      }
      //
      if(!understood) DEBUG_OUT<<"*** Didn't understand that line!\n";
    }
  }
}


#endif // NICK_USE_DECODE3D

