#ifndef ALIB_ASCENEDECODER_H
#define ALIB_ASCENEDECODER_H


#ifdef NICK_USE_DECODE3D


#ifndef NICK_USE_NICK3D
#error "decode3d requires NICK_USE_NICK3D!!!"
#endif


#include "../cpp/alib/abasics.h"

#include "../nick3d/AFace3D.h"

class AScene3D;

#include "A3DDecoder.h"


class ASceneDecoder : public A3DDecoder
{
public:
  ASceneDecoder(const char *fname);
  virtual ~ASceneDecoder();
  //
  virtual AScene3D *createNewSceneObject();
  //
  AList_alib *getMeshes() { return &meshes; }
  unsigned int getNumMeshes() { return nmeshes; }
  AList_alib *getCameras() { return &cameras; }
  unsigned int getNumCameras() { return ncameras; }
  AList_alib *getLights() { return &cameras; }
  unsigned int getNumLights() { return nlights; }
  AFaceInfo3D *getTheGround() { return &theGround; }
  AFaceInfo3D *getTheSky() { return &theSky; }
  //char *getName() { return name; }
protected:
  //
  virtual void init();
  //
  AList_alib lights;
  AList_alib cameras;
  AList_alib meshes;
  unsigned int nmeshes,ncameras,nlights;
  AFaceInfo3D theGround;  // for the color only
  AFaceInfo3D theSky;  // for the color only
  AScene3D *ts;
  //
};


#endif // NICK_USE_DECODE3D


#endif // ALIB_ASCENEDECODER_H

