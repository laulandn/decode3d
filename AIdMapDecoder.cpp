
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

#include "AIdMapDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  AIdMapDecoder Class
////////////////////////////////////////////////////////////////////////////////

AIdMapDecoder::AIdMapDecoder(const char *fname) : AMapDecoder(fname)
{
  init();
  openFile(fname);
  if(!err.getError()) readObjects();
}


void AIdMapDecoder::init()
{
  isVMF=false;
}


/* STATIC */
bool AIdMapDecoder::recognize(uint8_t *str)
{
  bool ret=false;
  bool isText=recognizeTextFile(str);
  DEBUG_OUT<<"isText is "<<isText<<"\n";
  // TODO: finish
  // If it isn't a text file, we KNOW it isn't a map file...
  if(isText) ret=true;  // good enough for now...we assume ASmartDecoder checked the file extension
  return ret;
}


void AIdMapDecoder::readObjects()
{
  DEBUG_OUT<<"AIdMapDecoder::readObjects()...\n";
  if(!fd) return;
  //if(errorFlag) return;
  fseek(fd,0L,SEEK_SET);
  uint8_t *line=(uint8_t *)malloc(256);
  unsigned int bracketCount=0;
  bool understood=false;
  bool reading=true;
  while(reading) {
    if(feof(fd)) {
      reading=false;
      break;
    }
    line[0]=0;
    fgets((char *)line,256,fd);
    if(!feof(fd)) {
      DSHELPER_alib.parseString((char *)line,NULL);
      understood=false;
      //DEBUG_OUT<<DSHELPER_alib.getArgv(0)<<"\n";
      //
      if(!DSHELPER_alib.getArgc()) understood=true;
      else {
        if(!strcmp("Version",DSHELPER_alib.getArgv(0))) {
          DEBUG_OUT<<"Version: "<<DSHELPER_alib.getArgv(1)<<"\n";
          understood=true;  // a version number
        }
        if(!strcmp("classname",DSHELPER_alib.getArgv(0))) {
        //if(!strcmp("\"classname\"",DSHELPER_alib.getArgv(0))) {
          DEBUG_OUT<<"classname: "<<DSHELPER_alib.getArgv(1)<<"\n";
          if(!strcmp("worldspawn",DSHELPER_alib.getArgv(0))) {
            DEBUG_OUT<<"Found wordspawn...\n";
          }
          understood=true;
        }
        if(!strcmp("//",DSHELPER_alib.getArgv(0))) understood=true;  // a comment
        if(!strcmp("{",DSHELPER_alib.getArgv(0))) { bracketCount++; understood=true; }
        if(!strcmp("}",DSHELPER_alib.getArgv(0))) {
          bracketCount--; understood=true;
        }
        if(!strcmp("brushDef3",DSHELPER_alib.getArgv(0))) {
          understood=true;
          readBrushdef(line);
        }
       }
      //
      if(!understood) DEBUG_OUT<<"*** Command \""<<DSHELPER_alib.getArgv(0)<<"\" not understood!\n";
    }
  }
}


void AIdMapDecoder::readBrushdef(unsigned char *line)
{
  DEBUG_OUT<<"AIdMapDecoder::readBrushdef()...\n";
  bool reading=true;
  bool understood=false;
  unsigned int bracketCount=0;
  while(reading) {
    fgets((char *)line,256,fd);
    DSHELPER_alib.parseString((char *)line,NULL);
    if(!strcmp("{",DSHELPER_alib.getArgv(0))) { understood=true; bracketCount++; }
    if(!strcmp("(",DSHELPER_alib.getArgv(0))) {
      understood=true;
      for(unsigned int t=0;t<DSHELPER_alib.getArgc();t++) DEBUG_OUT<<"\""<<DSHELPER_alib.getArgv(t)<<"\" ";
      DEBUG_OUT<<"\n";
    }
    if(!strcmp("}",DSHELPER_alib.getArgv(0))) {
      understood=true;
      bracketCount--;
      reading=false;
    }
    if(!understood) DEBUG_OUT<<"*** Command \""<<DSHELPER_alib.getArgv(0)<<"\" not understood!\n";
  }
  DEBUG_OUT<<"AIdMapDecoder::readBrushdef() done.\n";
}


#endif // NICK_USE_DECODE3D

