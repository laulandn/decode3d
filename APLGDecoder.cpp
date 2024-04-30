
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_DECODE3D


#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "../cpp/alib/anullstream.h"

#include "../nick3d/AVertex3D.h"

#include "APLGDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  APLGDecoder Class
////////////////////////////////////////////////////////////////////////////////

APLGDecoder::APLGDecoder(const char *fname) : AMeshDecoder(fname)
{
  init();
  openFile(fname);
  if(!err.getError()) readObjects();
}


/* STATIC */
bool APLGDecoder::recognize(uint8_t *str)
{
  bool ret=false;
  bool isText=recognizeTextFile(str);
  DEBUG_OUT<<"isText is "<<isText<<"\n";
  // TODO: finish
  // If it isn't a text file, we KNOW it isn't a plg file...
  if(isText) ret=true;  // good enough for now...we assume ASmartDecoder checked the file extension
  return ret;
}


// TODO: Rewrite, this is hard coded to expect verts and then faces, and that's it
// This doesn't handle extra whitespace well, and ignores multiple models per file
void APLGDecoder::readObjects()
{
  DEBUG_OUT<<"APLGDecoder::readObjects()...\n";
  if(!fd) return;
  //if(errorFlag) return;
  verts=new AList_alib[nframes];
  if(!verts) return;
  fseek(fd,0L,SEEK_SET);
  char *line=(char *)malloc(256);
  char *theName=(char *)malloc(256);
  //char *surf=(char *)malloc(256);
  //int a,b,c,d;
  //int n;
  float fa,fb,fc;
  unsigned int vertsToRead=0,facesToRead=0;
  AVertexF3D *theVert=NULL;
  //AFace3D *theFace=NULL;
  bool gotOne=false;
  bool stillReading=true;
  while(stillReading) {
    bool looking=true;
    while(looking) {
      fgets(line,256,fd);
      vertsToRead=0;  facesToRead=0;
      sscanf(line,"%s %d %d",theName,&vertsToRead,&facesToRead);
      if(vertsToRead!=0) looking=false;
      if(facesToRead!=0) looking=false;
    }
    gotOne=true;  // TODO: This is unfinished support for multiple models per file
    DEBUG_OUT<<"PLG: verts="<<vertsToRead<<" faces="<<facesToRead<<"\n";
    unsigned int t;
    for(t=0;t<vertsToRead;t++) {
      fgets(line,256,fd);
      if(!feof(fd)) { DSHELPER_alib.parseString(line,NULL,false,','); }
      DEBUG_OUT<<line;
      bool good=false;
      char first;
      for(unsigned int i=0;i<strlen(line);i++) {
        first=line[i];
        if(first=='#') { good=false; break; }
        if((first!=' ')&&(first!='\n')) { good=true; break; }
      }
      if(good) {
        fa=0.0; fb=0.0; fc=0.0;
        sscanf(line,"%f %f %f",&fa,&fb,&fc);
        DEBUG_OUT<<"v: "<<fa<<","<<fb<<","<<fc<<"\n";
        theVert=new AVertexF3D;
        theVert->x=fa;  theVert->y=fb;  theVert->z=fc;
        verts[0].append(theVert);
        nverts++;
      }
      else t--;
      if(feof(fd)) break;
    }
    AList_alib faceStack;
    for(t=0;t<facesToRead;t++) {
      fgets(line,256,fd);
      if(!feof(fd)) { DSHELPER_alib.parseString(line,NULL,false,','); }
      bool good=true;
      char first;
      for(unsigned int i=0;i<strlen(line);i++) {
        first=line[i];
        if(first=='#') { good=false; break; }
        if(first!=' ') break;
      }
      if(!DSHELPER_alib.getArgc()) good=false;
      if(good) {
        nfaces+=handleFace(&faces,&faceInfos,2,0,DSHELPER_alib.parseNumber(DSHELPER_alib.getArgv(0)));
      } else t--;
      if(feof(fd)) break;
    }
    // TODO: This is unfinished support for multiple models per file
    if(gotOne) stillReading=false;
  }
}


#endif // NICK_USE_DECODE3D


