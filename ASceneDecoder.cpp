
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

#include "../nick3d/AScene3D.h"

#include "ASceneDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  ASceneDecoder Class
////////////////////////////////////////////////////////////////////////////////

ASceneDecoder::ASceneDecoder(const char *fname) : A3DDecoder(fname)
{
  DEBUG_OUT<<"ASceneDecoder::ASceneDecoder("<<fname<<")\n";
  init();
}


ASceneDecoder::~ASceneDecoder()
{
}


void ASceneDecoder::init()
{
  DEBUG_OUT<<"ASceneDecoder::init()\n";
  isAScene=true;
  nmeshes=0;  ncameras=0;  nlights=0;
  // default sky is light blue
  theSky.surf=1; /// ???
  theSky.fRed=ASCENE3D_SKY_RED;
  theSky.fGreen=ASCENE3D_SKY_GREEN;
  theSky.fBlue=ASCENE3D_SKY_BLUE;
  // default ground is green
  theGround.surf=2; // ???
  theGround.fRed=ASCENE3D_GROUND_RED;
  theGround.fGreen=ASCENE3D_GROUND_GREEN;
  theGround.fBlue=ASCENE3D_GROUND_BLUE;
  ts=NULL;
}


AScene3D *ASceneDecoder::createNewSceneObject()
{
  DEBUG_OUT<<"ASceneDecoder::createNewSceneObject() starting...\n";
  if(err.getError()) {
    std::cerr<<"Can't createNewSceneObject, error!\n";
    exit(EXIT_FAILURE);
  }
  if(!ts) { ts=new AScene3D(); }
  else {
    DEBUG_OUT<<"Can't createNewSceneObject, ts is already allocated!  Giving up!\n";
    DEBUG_OUT<<"This probably means createNewSceneObject needed to be overloaded but wasn't.\n";
    exit(EXIT_SUCCESS);
  }
  DEBUG_OUT<<"Meshes...\n";
  ts->setMeshes((AMesh3D **)allocArray(getMeshes()));
  ts->setNumMeshes(arrayFromList((void **)ts->getMeshes(),getMeshes()));
  DEBUG_OUT<<"Lights...\n";
  ts->setLights((ALight3D **)allocArray(getLights()));
  ts->setNumLights(arrayFromList((void **)ts->getLights(),getLights()));
  DEBUG_OUT<<"Cameras...\n";
  ts->setCameras((ACamera3D **)allocArray(getCameras()));
  ts->setNumCameras(arrayFromList((void **)ts->getCameras(),getCameras()));
  //
  //DEBUG_OUT<<"Sky...\n";
  //theSky.surf=readFile->getTheSky()->surf;
  //theSky.fRed=readFile->getTheSky()->fRed;
  //theSky.fBlue=readFile->getTheSky()->fBlue;
  //theSky.fGreen=readFile->getTheSky()->fGreen;
  //DEBUG_OUT<<"Ground...\n";
  //createGroundMesh(readFile->getTheGround());
  DEBUG_OUT<<"Done.\n";
  return ts;
}


#endif // NICK_USE_DECODE3D


