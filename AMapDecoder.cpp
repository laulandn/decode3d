
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

#include "../nick3d/AMesh3D.h"

#include "AMapDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  ABrush2D Class
////////////////////////////////////////////////////////////////////////////////

ABrush2D::ABrush2D()
{
  for(unsigned int t=0;t<4;t++) { v[t].x=0.0;  v[t].y=0.0;  v[t].z=0.0; }
  fRed=.5;  fGreen=.5;  fBlue=.5;
  textID=0;
  solid=true;
}


////////////////////////////////////////////////////////////////////////////////
//  AMapDecoder Class
////////////////////////////////////////////////////////////////////////////////

AMapDecoder::AMapDecoder(const char *fname) : ASceneDecoder(fname)
{
  init();
}


void AMapDecoder::init()
{
  DEBUG_OUT<<"AMapDecoder::init()\n";
  numMaps=0;
  curMapNum=0;
  numBrushes=0;
  playerX=0.0;  playerY=0.0;  playerZ=0.0;
  playerXAngle=0.0;  playerYAngle=0.0;  playerZAngle=0.0;
}


unsigned int AMapDecoder::getNumMaps()
{
  return numMaps;
}


void AMapDecoder::setMapNumber(unsigned int n)
{
  if(n<(numMaps+1)) curMapNum=n;
}


bool AMapDecoder::readTheCurrentMap()
{
  std::cerr<<"AMapDecoder::readTheCurrentMap()...NOT IMPLEMENTED!\n";
  return false;
}


void AMapDecoder::brushes2Mesh()
{
  std::cerr<<"AMapDecoder::brushes2mesh()...\n";
  AFace3D **tFaces=(AFace3D **)calloc(sizeof(AFace3D *),numBrushes*2);
  AFaceInfo3D **tFaceInfos=(AFaceInfo3D **)calloc(sizeof(AFaceInfo3D *),numBrushes*2);
  AVertexF3D **tVertices=(AVertexF3D **)calloc(sizeof(AVertexF3D *),numBrushes*4);
  brushes.jumpToHead();
  ABrush2D *b=NULL;
  AVertexF3D *v0=NULL;
  AVertexF3D *v1=NULL;
  AVertexF3D *v2=NULL;
  AVertexF3D *v3=NULL;
  AFace3D *f1=NULL;
  AFaceInfo3D *fi1=NULL;
  AFace3D *f2=NULL;
  AFaceInfo3D *fi2=NULL;
  bool reading=true;
  unsigned int iFace=0,iVertex=0;
  while(reading) {
    b=(ABrush2D *)brushes.info();
    if(b) {
      //DEBUG_OUT<<"iVertex="<<iVertex<<" iFace="<<iFace<<"\n";
      // First thing, we get the verts from the brush...
      v0=new AVertexF3D();  if(!v0) { std::cerr<<"Couldn't alloc v0!\n"; return; }
      v1=new AVertexF3D();  if(!v1) { std::cerr<<"Couldn't alloc v1!\n"; return; }
      v2=new AVertexF3D();  if(!v2) { std::cerr<<"Couldn't alloc v2!\n"; return; }
      v3=new AVertexF3D();  if(!v3) { std::cerr<<"Couldn't alloc v3!\n"; return; }
      v0->x=b->v[0].x;  v0->y=b->v[0].y;  v0->z=b->v[0].z;
      v1->x=b->v[1].x;  v1->y=b->v[1].y;  v1->z=b->v[1].z;
      v2->x=b->v[2].x;  v2->y=b->v[2].y;  v2->z=b->v[2].z;
      v3->x=b->v[3].x;  v3->y=b->v[3].y;  v3->z=b->v[3].z;
      tVertices[iVertex]=v0;  tVertices[iVertex+1]=v1;  tVertices[iVertex+2]=v2;  tVertices[iVertex+3]=v3;
      // Then the first face...
      f1=new AFace3D();  if(!f1) { std::cerr<<"Couldn't alloc f1!\n"; return; }
      f1->a=iVertex;  f1->b=iVertex+1;  f1->c=iVertex+3;  // 0, 1 and 3...
      fi1=new AFaceInfo3D();  if(!fi1) { std::cerr<<"Couldn't alloc fi1!\n"; return; }
      fi1->textID=b->textID;  fi1->fRed=b->fRed;  fi1->fGreen=b->fGreen;  fi1->fBlue=b->fBlue;
      //DEBUG_OUT<<"face1 "<<f1->fRed<<" "<<f1->fGreen<<" "<<f1->fBlue<<"\n";
      // Then second face...
      f2=new AFace3D();  if(!f2) { std::cerr<<"Couldn't alloc f2!\n"; return; }
      f2->a=iVertex+1;  f2->b=iVertex+2;  f2->c=iVertex+3;  // 1, 2 and 3...
      fi2=new AFaceInfo3D();  if(!fi2) { std::cerr<<"Couldn't alloc fi2!\n"; return; }
      fi2->textID=b->textID;  fi2->fRed=b->fRed;  fi2->fGreen=b->fGreen;  fi2->fBlue=b->fBlue;
      //DEBUG_OUT<<"face2 "<<f2->fRed<<" "<<f2->fGreen<<" "<<f2->fBlue<<"\n";
      //
      tFaces[iFace]=f1;
      tFaceInfos[iFace]=fi1;
      tFaces[iFace+1]=f2;
      tFaceInfos[iFace+1]=fi2;
      iVertex+=4;
      iFace+=2;
    }
    brushes.advance();
    if(brushes.atEnd()) reading=false;
  }
  AMesh3D *mapMesh=new AMesh3D(numBrushes*4,tVertices,numBrushes*2,tFaces);
  nmeshes++;
  meshes.append(mapMesh);
}


void AMapDecoder::player2Camera()
{
  std::cerr<<"AMapDecoder::player2Camera()...\n";
  DEBUG_OUT<<"player coords are: "<<playerX<<","<<playerY<<","<<playerZ<<"\n";
  thePlayer.translateTo(playerX,playerY,playerZ);
  DEBUG_OUT<<"player angles are: "<<playerXAngle<<","<<playerYAngle<<","<<playerZAngle<<"\n";
  // NOTE: Order is important!
  thePlayer.xRotBy(playerXAngle);
  thePlayer.yRotBy(playerYAngle);
  thePlayer.zRotBy(playerZAngle);
  cameras.append((void *)(&thePlayer));
  ncameras++;
}


#endif // NICK_USE_DECODE3D

