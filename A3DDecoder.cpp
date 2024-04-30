
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_DECODE3D


#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "../cpp/alib/abasics.h"

#include "../cpp/alib/apalette.h"
#include "../cpp/alib/anullstream.h"

#include "../nick3d/AVertex3D.h"
#include "../nick3d/AFace3D.h"
#include "../nick3d/ATextCoord3D.h"

#include "A3DDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

unsigned long ARend386Colors16[]={
/*0*/  0x000000,  // black, no shades
/*1*/  0xff0000,  // red
/*2*/  0xff8000,  // orange-brown
/*3*/  0xff8080,  // pale pink
/*4*/  0xffc080,  // pale brown
/*5*/  0xffff80,  // pale yellow
/*6*/  0xffff00,  // yellow
/*7*/  0x00ff80,  // pale green
/*8*/  0x00ff00,  // green
/*9*/  0x00ffc0,  // pale cyan
/*a*/  0x00c0ff,  // pale blue
/*b*/  0x0000ff,  // blue
/*c*/  0xff00ff,  // hot pink
/*d*/  0xff00c0,  // magenta
/*e*/  0x808080,  // gray
/*f*/  0xffffff   // white
};


unsigned long ARend386Colors256base[]={
/*0*/  0x000000,  // black, no shades
/*1*/  0xff0000,  // red
/*2*/  0xff8000,  // orange-brown
/*3*/  0xff8080,  // pale pink
/*4*/  0xffc080,  // pale brown
/*5*/  0xffff80,  // pale yellow
/*6*/  0xffff00,  // yellow
/*7*/  0x00ff80,  // pale green
/*8*/  0x00ff00,  // green
/*9*/  0x00ffc0,  // pale cyan
/*a*/  0x00c0ff,  // pale blue
/*b*/  0x0000ff,  // blue
/*c*/  0xff00ff,  // hot pink
/*d*/  0xff00c0,  // magenta
/*e*/  0x808080,  // gray
/*f*/  0xffffff   // white
};


////////////////////////////////////////////////////////////////////////////////
//  A3DDecoder Class
////////////////////////////////////////////////////////////////////////////////


A3DDecoder::A3DDecoder(const char *fname) : ADecoderAbstract(fname)
{
}


A3DDecoder::~A3DDecoder()
{
}


void A3DDecoder::lookupRend386Color(unsigned long surf, float *r, float *g, float *b)
{
  DEBUG_OUT<<"lookupRend386Color ";
  unsigned int surf1=(surf&0xf000)>>12,surf2=(surf&0xf00)>>8,surf3=(surf&0xf0)>>4,surf4=surf&0xf;
  unsigned int surf34=surf&0xff;
  DEBUG_OUT<<surf1<<" "<<surf2<<" "<<surf3<<" "<<surf4<<" ";
  if(surf1&0x80) { /*dBug<<"Mapped color"<<"\n";*/ return; }
  //unsigned int brightness=surf34;
  float frr,fgg,fbb;
  frr=1.0;  fgg=1.0;  fbb=1.0;  // default to white
  unsigned long rgb=0xffffff;
  switch(surf1&0x03) {
    case 0:
      //DEBUG_OUT<<"unshaded ";
      if(surf2) {
        DEBUG_OUT<<"color16 "<<surf2<<" brightness "<<surf34;
        rgb=ARend386Colors16[surf2];
      }
      else {
        DEBUG_OUT<<"unshaded color256 "<<surf34;
        rgb=ARend386Colors256base[(surf34>>8)&0xf];
        DEBUG_OUT<<rgb;
      }
      break;
    case 1:
      DEBUG_OUT<<"shaded ";
      DEBUG_OUT<<"color16 "<<surf2<<" brightness "<<surf34;
      rgb=ARend386Colors16[surf2];
      break;
    case 2:
      DEBUG_OUT<<"metalic color16 "<<surf2<<" brightness "<<surf34;
      rgb=ARend386Colors16[surf2];
      break;
    case 3:
      DEBUG_OUT<<"glass color16 "<<surf2<<" brightness "<<surf34;
      rgb=ARend386Colors16[surf2];
      break;
    default:
      break;
  }
  DEBUG_OUT<<" rgb "<<rgb<<" ";
  unsigned int ir=getRGBRed24(rgb);
  frr=((float)ir/256.0)*((float)surf34/256.0);
  if(frr>1.0) frr=1.0;
  unsigned int ig=getRGBGreen24(rgb);
  fgg=((float)ig/256.0)*((float)surf34/256.0);
  if(fgg>1.0) fgg=1.0;
  unsigned int ib=getRGBBlue24(rgb);
  fbb=((float)ib/256.0)*((float)surf34/256.0);
  if(fbb>1.0) fbb=1.0;
  DEBUG_OUT<<frr<<","<<fgg<<","<<fbb<<"\n";
  *r=frr; *g=fgg; *b=fbb;
}


unsigned int A3DDecoder::handleFace(AList_alib *faces, AList_alib *faceInfos, int offset,  int voff, unsigned long surf)
{
  DEBUG_OUT<<"A3DDecoder::handleFace()...\n";
  if(!faces) return 0;
  unsigned int ret=0;
  unsigned long a=0,b=0,c=0;
  float frr,fgg,fbb;
  AFace3D *theFace=NULL;
  AFaceInfo3D *theFaceInfo=NULL;
  lookupRend386Color(surf,&frr,&fgg,&fbb);
  for(unsigned int t=offset;t<(DSHELPER_alib.getArgc()-2);t++) {
    a=DSHELPER_alib.parseNumber(DSHELPER_alib.getArgv(t));
    b=DSHELPER_alib.parseNumber(DSHELPER_alib.getArgv(t+1));
    c=DSHELPER_alib.parseNumber(DSHELPER_alib.getArgv(t+2));
    DEBUG_OUT<<"f: "<<surf<<" "<<a<<","<<b<<","<<c<<"\n";
    theFace=new AFace3D;
    theFace->a=a+voff; theFace->b=b+voff; theFace->c=c+voff;
    theFaceInfo=new AFaceInfo3D;
    theFaceInfo->fRed=frr;  theFaceInfo->fGreen=fgg;  theFaceInfo->fBlue=fbb;
    theFaceInfo->surf=surf;
    faces->append(theFace);
    faceInfos->append(theFaceInfo);
    ret++;
  }
  return ret;
}


void **A3DDecoder::allocArray(AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::allocArray()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return NULL; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return NULL; }
  void **ret=NULL;
  unsigned n=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    //void *thing=(void *)theList->get();
    // ?
    theList->advance();
    n++;
  }
  if(n) ret=(void **)calloc(n,sizeof(void *));
  DEBUG_OUT<<"Alloc'd array for "<<n<<" objects.\n";
  return ret;
}


unsigned short *A3DDecoder::alloc3USArray(AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::alloc3USArray()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return NULL; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return NULL; }
  unsigned short *ret=NULL;
  unsigned n=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    //void *thing=(void *)theList->get();
    // ?
    theList->advance();
    n++;
  }
  if(n) ret=(unsigned short *)calloc(n*3,sizeof(unsigned short));
  DEBUG_OUT<<"Alloc'd array for "<<n<<" unsigned shorts x 3.\n";
  return ret;
}


float *A3DDecoder::alloc3FArray(AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::alloc3FArray()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return NULL; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return NULL; }
  float *ret=NULL;
  unsigned n=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    //void *thing=(void *)theList->get();
    // ?
    theList->advance();
    n++;
  }
  if(n) ret=(float *)calloc(n*3,sizeof(float));
  DEBUG_OUT<<"Alloc'd array for "<<n<<" floats x 3.\n";
  return ret;
}


float *A3DDecoder::alloc2FArray(AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::alloc2FArray()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return NULL; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return NULL; }
  float *ret=NULL;
  unsigned n=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    //void *thing=(void *)theList->get();
    // ?
    theList->advance();
    n++;
  }
  if(n) ret=(float *)calloc(n*2,sizeof(float));
  DEBUG_OUT<<"Alloc'd array for "<<n<<" floats x 2.\n";
  return ret;
}


unsigned int A3DDecoder::arrayFromList(void **theArray,AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::arrayFromList()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return 0; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return 0; }
  if(!theArray) { DEBUG_OUT<<"(no array)\n"; return 0; }
  unsigned int ret=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    void *thing=(void *)theList->info();
    theArray[ret]=(void *)thing;
    theList->advance();
    ret++;
  }
  DEBUG_OUT<<"Built array of "<<ret<<" objects.\n";
  return ret;
}


unsigned int A3DDecoder::array3USFromList(unsigned short *theArray,AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::array3USFromList()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return 0; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return 0; }
  if(!theArray) { DEBUG_OUT<<"(no array)\n"; return 0; }
  unsigned int ret=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    AFace3D *thing=(AFace3D *)theList->info();
    theArray[ret*3]=thing->a;
    theArray[ret*3+1]=thing->b;
    theArray[ret*3+2]=thing->c;
    theList->advance();
    ret++;
  }
  DEBUG_OUT<<"Built array of "<<ret<<" unsigned shorts x 3.\n";
  return ret;
}


unsigned int A3DDecoder::array3FFromList(float *theArray,AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::array3FFromList()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return 0; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return 0; }
  if(!theArray) { DEBUG_OUT<<"(no array)\n"; return 0; }
  unsigned int ret=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    AVertexF3D *thing=(AVertexF3D *)theList->info();
    theArray[ret*3]=thing->x;
    theArray[ret*3+1]=thing->y;
    theArray[ret*3+2]=thing->z;
    theList->advance();
    ret++;
  }
  DEBUG_OUT<<"Built array of "<<ret<<" floats x 3.\n";
  return ret;
}


unsigned int A3DDecoder::array2FFromList(float *theArray,AList_alib *theList)
{
  //DEBUG_OUT<<"A3DDecoder::array2FFromList()...\n";
  if(!theList) { DEBUG_OUT<<"(no list)\n"; return 0; }
  if(theList->isEmpty()) { DEBUG_OUT<<"(empty list)\n"; return 0; }
  if(!theArray) { DEBUG_OUT<<"(no array)\n"; return 0; }
  unsigned int ret=0;
  theList->jumpToHead();
  while(!theList->atEnd()) {
    ATextCoord3D *thing=(ATextCoord3D *)theList->info();
    theArray[ret*2]=thing->u;
    theArray[ret*2+1]=thing->v;
    theList->advance();
    ret++;
  }
  DEBUG_OUT<<"Built array of "<<ret<<" floats x 2.\n";
  return ret;
}


#endif // NICK_USE_DECODE3D

