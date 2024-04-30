
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

#include "AMeshDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  AMeshDecoder Class
////////////////////////////////////////////////////////////////////////////////

AMeshDecoder::AMeshDecoder(const char *fname) : A3DDecoder(fname)
{
  init();
}


AMeshDecoder::~AMeshDecoder()
{
}


void AMeshDecoder::init()
{
  isAMesh=true;
  nverts=0; ntextcoords=0;
  nfaces=0; ntextures=0;
  nframes=1;  nseqs=0;
  numParts=0;
  vertOffset=0;  oldVertOffset=0;  faceOffset=0;
  fixTextCoords=false;
  tm=NULL;
}


AMesh3D *AMeshDecoder::createNewMeshObject()
{
  DEBUG_OUT<<"AMeshDecoder::createNewMeshObject() starting...\n";
  if(err.getError()) {
    std::cerr<<"Can't createNewMeshObject, error!\n";
    exit(EXIT_FAILURE);
  }
  if(!tm) { tm=new AMesh3D(); }
  else {
    DEBUG_OUT<<"Can't createNewMeshObject, tm is already allocated!  Giving up!\n";
    DEBUG_OUT<<"This probably means createNewMeshObject needed to be overloaded but wasn't.\n";
    exit(EXIT_SUCCESS);
  }
  //
  DEBUG_OUT<<"parts...\n";
  tm->setParts((AMeshPart3D **)allocArray(&parts));
  tm->setNumParts(arrayFromList((void **)tm->getParts(),&parts));
  //
  DEBUG_OUT<<"faces...\n";
  tm->setFaces(alloc3USArray(&faces));
  tm->setNumFaces(array3USFromList(tm->getFaces(),&faces));
  //
  DEBUG_OUT<<"faceInfos...\n";
  // If the decoder created any, this will do...
  tm->setFaceInfos((AFaceInfo3D **)allocArray(&faceInfos));
  // If not, we'll make some to match the faces...
  if(!tm->getFaceInfos()) {
    DEBUG_OUT<<"(decoder didn't have any faceInfos...making some)\n";
    tm->setFaceInfos((AFaceInfo3D **)calloc(tm->getNumFaces(),sizeof(AFaceInfo3D *)));
    for(unsigned int t=0;t<tm->getNumFaces();t++) {
      tm->getFaceInfos()[t]=new AFaceInfo3D();
    }
  }
  //
  DEBUG_OUT<<"frames/verts...\n";
  tm->setNumFrames(nframes);
  for(unsigned int t=0;t<nframes;t++) {
    tm->createVertsPerFrame(t,getFrameVerts(t),nverts);
  }
  DEBUG_OUT<<nframes<<" frames of "<<nverts<<" verts each.\n";
  //
  DEBUG_OUT<<"vertNormals...\n";
  tm->createVertNormals(&vertNormals,nverts);
  //
  DEBUG_OUT<<"textCoords...\n";
  tm->setFixTextCoords(fixTextCoords);
  if(fixTextCoords) DEBUG_OUT<<"(textCoords need to be fixed)\n";
  tm->setTextCoords(alloc2FArray(&textCoords));
  tm->setNumTextCoords(array2FFromList(tm->getTextCoords(),&textCoords));
  //
  DEBUG_OUT<<"faceTextCoords...\n";
  /*
  m->setFaceTextCoords((AFace3D **)allocArray(&faceTextCoords));
  m->setNumFaceTextCoords(arrayFromList((void **)m->getFaceTextCoords(),&faceTextCoords));
  */
  tm->setFaceTextCoords(alloc3USArray(&faceTextCoords));
  array3USFromList(tm->getFaceTextCoords(),&faceTextCoords);
  //
  if(!tm->getFaceTextCoords()) {
    DEBUG_OUT<<"No faceTextCoords, so going to see if we've got plain old vert textCoords...";
    if(tm->getNumTextCoords()) {
      DEBUG_OUT<<"we do.\n";
      tm->buildFTCsFromTCs();
    }
    else DEBUG_OUT<<"we don't.\n";
  }
  //
  DEBUG_OUT<<"textures...\n";
  tm->createTextures(&textures,ntextures);
  //
  tm->calcWidths();
  tm->isValid();
  DEBUG_OUT<<"Done.\n";
  return tm;
}


void AMeshDecoder::readVectorL(AVertexF3D *v)
{
  v->x=readFloatL();
  v->y=readFloatL();
  v->z=readFloatL();
}


void AMeshDecoder::readVectorB(AVertexF3D *v)
{
  v->x=readFloatB();
  v->y=readFloatB();
  v->z=readFloatB();
}


void AMeshDecoder::readC1VectorL(AVertexF3D *v)
{
  v->x=readByte();
  v->y=readByte();
  v->z=readByte();
  unsigned char normalIndex=readByte();
  // ???
}


void AMeshDecoder::readC2VectorL(AVertexF3D *v)
{
  v->x=readShortL();
  v->y=readShortL();
  v->z=readShortL();
  unsigned short normalIndex=readShortL();
  // ???
}


void AMeshDecoder::readMatrixL(AMatrix3D *m)
{
  AVertexF3D a,b,c;
  readVectorL(&a);
  readVectorL(&b);
  readVectorL(&c);
}


AList_alib *AMeshDecoder::getFrameVerts(unsigned int num)
{
  if(verts) return &(verts[num]);
  else return NULL;
}


#endif // NICK_USE_DECODE3D

